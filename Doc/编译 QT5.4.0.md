# build_qt5.4.0.sh

```bash
#!/bin/bash

echo "build Qt5 for embedded linux, Author: Lipengxiang"

mkdir Qt5.4.0_arm
cd Qt5.4.0_arm

/opt/qt-everywhere-opensource-src-5.4.0/configure \
        -v \
        -prefix
        /opt/Qt5.4.0_arm/Qt5.4.0_arm_install \
        -release \
        -make libs \
        -xplatform linux-arm-gnueabi-g++ \
        -optimized-qmake \
        -pch \
        -qt-sql-sqlite \
        -qt-zlib \
        -no-opengl \
        -no-sse2 \
        -no-openssl \
        -no-nis \
        -no-cups \
        -no-glib \
        -no-pkg-config \
        -no-xcursor -no-xfixes -no-xrandr -no-xrender \
        -no-separate-debug-info \
```
