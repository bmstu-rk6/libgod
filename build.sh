#!/bin/sh
set -e

OLDDIR=`pwd`

# parameters
. ./build.conf

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
		-DBOOST_ROOT=$BOOST_ROOT -DGTEST_ROOT=$GTEST_ROOT .."
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

case "$1" in
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
		build
		;;

	fast)
		build_fast
		;;

	*)
		clean
		build
		(cd build && make install)
		;;
esac

echo ok 
