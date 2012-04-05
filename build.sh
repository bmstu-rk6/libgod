#!/bin/sh
set -e

OLDDIR=`pwd`
INSTALL_DIR=/tmp/localgod
trap "cd $OLDDIR" exit

rm -f lib/gen/*c lib/gen/*h lib/gen/Makefile.am.sample include/libgod-config.h 
rm -rf build
if [ "$1" = "clean" ] ; then
	exit 
fi

rm -rf $INSTALL_DIR 
mkdir -p $INSTALL_DIR build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR ..
make $1
make install
echo ok
