libgod
========

Global Optimization Data Library.

Nothing personal. Pure atheistic. Pure phdic.

Welcome to the [discussion wiki](https://github.com/bmstu-rk6/libgod/wiki)

How to build
=============

Linux, Mac OS X
------------------

1. Install needed packages with your favourite package manager:

	sudo apt-get install cmake asn1c libboost-dev

2. Download and build [google test](http://code.google.com/p/googletest):

	cmake . && make

3. Adjust library path in `build.conf` if needed

4. Build a god library:

	./build.sh

