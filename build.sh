#!/bin/sh
set -e

OLDDIR=`pwd`

mode=$1
[ -z "$1" ] || shift

# parameters
[ "$mode" == "travis_pre" ] || . ./build.conf

trap "cd $OLDDIR" exit

clean()
{
	rm -f lib/gen/*c lib/gen/*h lib/gen/Makefile.am.sample include/libgod-config.h 
	rm -rf build
}

build()
{ 
	mkdir -p $INSTALL_DIR build
	cd build
	CMAKE_COMMAND="cmake --no-warn-unused-cli -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE \
		-DBOOST_ROOT=$BOOST_ROOT -DGTEST_ROOT=$GTEST_ROOT $* .."
	echo Executing following cmake command
	echo $CMAKE_COMMAND
	$CMAKE_COMMAND
	make 
	CTEST_OUTPUT_ON_FAILURE=YES make test
	cd $OLDDIR
}

build_fast()
{ 
	cd build
	make 
	CTEST_OUTPUT_ON_FAILURE=YES make test
	cd $OLDDIR
}

case "$mode" in
	clean)
		clean
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

	build)
		build $*
		;;

	fast)
		build_fast
		;;

	travis_pre)
		GTEST_NAME=gtest-1.6.0
		# make a conf
		echo "INSTALL_DIR=`pwd`/localgod" > build.conf
		echo "CMAKE_BUILD_TYPE=Debug" >> build.conf
		echo "BOOST_ROOT=/usr/include/boost" >> build.conf
		echo "GTEST_ROOT=`pwd`/$GTEST_NAME" >> build.conf
		# download and build gtest
		if [ ! -d "$GTEST_NAME" ] ; then
			wget -q "https://googletest.googlecode.com/files/$GTEST_NAME.zip"
			unzip -qq "$GTEST_NAME.zip"
			rm $GTEST_NAME.zip
			cd $GTEST_NAME
			cmake .
			make
			cd ..
		fi
		;;

	*)
		clean
		build $*
		(cd build && make install)
		;;
esac

echo ok 
