#
# Copyright (C) 2011 Samsung Electronics Co., Ltd.
#              http://www.samsung.com/
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
####################################

SOURCE="$0"
while [ -h "$SOURCE"  ]; do # resolve $SOURCE until the file is no longer a symlink
    DIR="$( cd -P "$( dirname "$SOURCE"  )" && pwd  )"
    SOURCE="$(readlink "$SOURCE")"
    [[ $SOURCE != /*  ]] && SOURCE="$DIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
SCRIPTDIR="$( cd -P "$( dirname "$SOURCE"  )" && pwd  )"
RUNDIR="$(pwd)"
echo script Path: $SCRIPTDIR
echo runing Path : $RUNDIR

if [ -z $1 ]
then
    echo "usage: ./sd_fusing.sh <SD Reader's device file>"
    exit 0
fi

if [ -b $1 ]
then
    echo "$1 reader is identified."
else
    echo "$1 is NOT identified."
    exit 0
fi

####################################
#<verify device>

BDEV_NAME=`basename $1`
BDEV_SIZE=`cat /sys/block/${BDEV_NAME}/size`

if [ ${BDEV_SIZE} -le 0 ]; then
	echo "Error: NO media found in card reader."
	exit 1
fi

if [ ${BDEV_SIZE} -gt 32000000 ]; then
	echo "Error: Block device size (${BDEV_SIZE}) is too large"
	exit 1
fi

####################################
# check files
E4412_BOOT=$RUNDIR/boot.bin
E4412_USER=$RUNDIR/user.bin
MKBL2=$SCRIPTDIR/../mkbl2

if [ ! -f ${E4412_BOOT} ]; then
	echo "Error: boot.bin NOT found, please build it & try again."
	exit -1
fi

if [ ! -f ${MKBL2} ]; then
	echo "Error: can not find host tool - mkbl2, stop."
	exit -1
fi

#<make bl2>
${MKBL2} ${E4412_BOOT} bl2.bin 14336

####################################
# fusing images

signed_bl1_position=1
bl2_position=17
user_position=49
tzsw_position=705

#<BL1 fusing>
echo "---------------------------------------"
echo "BL1 fusing"
dd iflag=dsync oflag=dsync if=$SCRIPTDIR/E4412_N.bl1.bin of=$1 seek=$signed_bl1_position

#<BL2 fusing>
echo "---------------------------------------"
echo "BL2 fusing"
dd iflag=dsync oflag=dsync if=$RUNDIR/bl2.bin of=$1 seek=$bl2_position

#<u-boot fusing>
echo "---------------------------------------"
echo "user.bin fusing"
if [ ! -f ${E4412_USER} ]; then
	echo "W:NOT Found: ${E4412_USER}"
    echo "W:NO Fuse To SDCard: ${E4412_USER}"
else
    dd iflag=dsync oflag=dsync if=${E4412_USER} of=$1 seek=$user_position
fi

#<TrustZone S/W fusing>
echo "---------------------------------------"
echo "TrustZone S/W fusing"
dd iflag=dsync oflag=dsync if=$SCRIPTDIR/E4412_tzsw.bin of=$1 seek=$tzsw_position

#<flush to disk>
sync

####################################
#<Message Display>
echo "---------------------------------------"
echo "boot.bin user.bin image is fused successfully."
echo "Eject SD card and insert it again."

