libgod
========

Global Optimization Data Library.

Nothing personal. Pure atheistic. Pure phdic.

Welcome to the [discussion wiki](https://github.com/bmstu-rk6/libgod/wiki)

How to build
=============

Linux, Mac OS X
------------------

Install needed packages with your favourite package manager:

	sudo apt-get install cmake asn1c libboost-dev

Download and build [google test](http://code.google.com/p/googletest):

	cmake . && make

Copy `build.conf.default` to `build.conf` and make adjustments for your system.

Build a god library:

	./build.sh

