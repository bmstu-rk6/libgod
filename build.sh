#!/bin/sh
set -e

BASEDIR=`pwd`

GTEST_VERSION=1.6.0
ASN1C_VERSION=0.9.21

mode=$1
[ -z "$1" ] || shift

# parameters
[ "$mode" = "prepare" ] || [ "$mode" = "clean" ] || [ "$mode" = "clean_all" ] || . ./build.conf

trap "cd $BASEDIR" exit

clean()
{
	rm -f lib/gen/*c lib/gen/*h lib/gen/Makefile.am.sample include/libgod-config.h 
	rm -rf build
}

clean_all()
{
	clean
	rm -rf third-party
}

bootstrap_asn1c()
{
	echo Boostraping asn1c-$ASN1C_VERSION ...
	cd third-party
	gunzip < $BASEDIR/asn1c-$ASN1C_VERSION.tar.gz | tar xf -
	cd asn1c-$ASN1C_VERSION
	./configure
	make
	cd $BASEDIR
}

bootstrap_gtest()
{
	echo Boostraping gtest-$GTEST_VERSION ...
	cd third-party
	unzip -q $BASEDIR/gtest-$GTEST_VERSION.zip
	cd gtest-$GTEST_VERSION
	cmake .
	make
	cd $BASEDIR
}

bootstrap()
{
	rm -rf third-party
	mkdir -p third-party
	bootstrap_asn1c
	bootstrap_gtest
}

build()
{ 
	mkdir -p $INSTALL_DIR build
	cd build
	CMAKE_COMMAND="cmake --no-warn-unused-cli \
		-DCMAKE_INSTALL_PREFIX=$INSTALL_DIR \
		-DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE \
		-DBOOST_ROOT=$BOOST_ROOT \
		-DGTEST_ROOT=$BASEDIR/third-party/gtest-$GTEST_VERSION \
		-DASN1C_ROOT=$BASEDIR/third-party/asn1c-$ASN1C_VERSION \
		-DBUILD_DOCUMENTATION=ON \
		$* .."
	echo Executing following cmake command
	echo $CMAKE_COMMAND
	$CMAKE_COMMAND
	make 
	make doc
	CTEST_OUTPUT_ON_FAILURE=YES make test
	cd $BASEDIR
}

build_fast()
{ 
	cd build
	make 
	CTEST_OUTPUT_ON_FAILURE=YES make test
	cd $BASEDIR
}

case "$mode" in
	clean)
		clean
		;;

	clean_all)
		clean_all
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

	prepare)
		# make a conf
		echo "INSTALL_DIR=`pwd`/localgod" > build.conf
		echo "CMAKE_BUILD_TYPE=Debug" >> build.conf
		echo "BOOST_ROOT=/usr/include/boost" >> build.conf
		# download deps
		wget -q -nc "https://googletest.googlecode.com/files/gtest-$GTEST_VERSION.zip"
		wget -q -nc "http://lionet.info/soft/asn1c-$ASN1C_VERSION.tar.gz"
		;;

	bootstrap)
		bootstrap
		;;

	*)
		clean
		[ -d "$BASEDIR/third-party" ] || bootstrap
		build $*
		(cd build && make install)
		;;
esac

echo ok 
