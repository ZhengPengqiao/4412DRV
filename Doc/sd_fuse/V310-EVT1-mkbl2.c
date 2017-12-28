/*
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *              http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	FILE		*fp;
	unsigned char	src;
	char		*Buf, *a;
	int		BufLen;
	int		nbytes, fileLen;
	unsigned int	checksum = 0;
	int		i;

	if (argc != 4)
	{
		printf("Usage: mkbl1 <source file> <destination file> <size> \n");
		return -1;
	}

	BufLen = atoi(argv[3]);
	Buf = (char *)malloc(BufLen);
	memset(Buf, 0x00, BufLen);

	fp = fopen(argv[1], "rb");
	if( fp == NULL)
	{
		printf("source file open error\n");
		free(Buf);
		return -1;
	}

	fseek(fp, 0L, SEEK_END);
	fileLen = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

#if 0   	//代码大于14K
	
	//如果裸机程序大于14K,则需要将程序重定向到别的位置，将程序前14K修改为具有校验码的程序，
	//在14K代码内，需要实现代码重定位。
	if ( BufLen > fileLen )
	{
		printf("Usage: unsupported size\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	nbytes = fread(Buf, 1, BufLen, fp);

	if ( nbytes != BufLen )
	{
		printf("source file read error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

#else   	//代码小于14K
	
	//焼写裸机程序时，裸机程序一般14K,所以这里按照规定，在14K位置添加校验码，将裸机程序转为转换为合格的bin文件
	if ( fileLen >  (BufLen-16))
	{
		printf("Usage: unsupported size,size more than 14K \n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	nbytes = fread(Buf, 1, BufLen, fp);

#endif
	fclose(fp);

	for(i = 0;i < (14 * 1024) - 4;i++)
	{
		checksum += (unsigned char)(Buf[i]);
	}
	*(unsigned int*)(Buf+i) = checksum;

	fp = fopen(argv[2], "wb");
	if (fp == NULL)
	{
		printf("destination file open error\n");
		free(Buf);
		return -1;
	}

	a	= Buf;
	nbytes	= fwrite( a, 1, BufLen, fp);

	if ( nbytes != BufLen )
	{
		printf("destination file write error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	free(Buf);
	fclose(fp);

	return 0;
}