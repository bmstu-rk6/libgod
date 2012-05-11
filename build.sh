#!/bin/sh
set -e

OLDDIR=`pwd`
INSTALL_DIR=/tmp/localgod
trap "cd $OLDDIR" exit

clean()
{
	rm -f lib/gen/*c lib/gen/*h lib/gen/Makefile.am.sample include/libgod-config.h 
	rm -rf build
}

case "$1" in
	clean)
		clean
		exit
	;;

makelist)
	echo "set(GOD_GENERATED_ASN_FILES"
	find lib/gen -type f -regex '.*[ch]' | sed -E 's/^/  ${CMAKE_SOURCE_DIR}\//'
	echo ")"
	echo
	echo "set(GOD_GENERATED_SUPPORT_FILES"
	find lib/gen -type l -regex '.*[ch]' | sed -E 's/^/  ${CMAKE_SOURCE_DIR}\//'
	echo ")"
	;;

	*)
		clean
		mkdir -p $INSTALL_DIR build
		cd build
		cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR -DBOOST_ROOT=/projects/libs/boost_1_49_0 ..
		make $1
		make install
	;;
esac

echo ok 
