[![Build Status](https://secure.travis-ci.org/bmstu-rk6/libgod.png)](http://travis-ci.org/bmstu-rk6/libgod) [![Dependency Status](https://secure.travis-ci.org/bmstu-rk6/libgod.png?travis)](http://travis-ci.org/bmstu-rk6/libgod)

libgod
========

Global Optimization Data Library.

Nothing personal. Pure atheistic. Pure phdic.

Welcome to the [discussion wiki](https://github.com/bmstu-rk6/libgod/wiki)

How to build
============

Currently only UNIX systems are supported - Linux, Mac OS X.

Dependencies
------------

 * [asn1c](http://lionet.info/asn1c) 
 * [google test](http://code.google.com/p/googletest)
 * [boost](http://boost.org)
 * [doxygen](http://doxygen.org) (optional)

Boost and CMake must be installed on the system.
For example, for debian system:
  
         sudo apt-get install cmake libboost-dev doxygen

Building
--------

### Prepare a build

Simply run:
  
        ./build.sh prepare

It generates typical `build.conf` and downloads dependencies to the project directory.

Run:
  
        ./build.sh bootstrap

to extract dependencies to the `third-party` directory.

Then adjust `build.conf` if needed. Consult `build.conf.default` for sample settings.
You are ready to build a project.

### Build a libgod

Build a god library and its dependencies:

        ./build.sh

It builds everything, installs library locally and runs tests.

You can run only library build by issuing:

        ./build.sh build

Finally, you can clean a build by issuing:

        ./build.sh clean

Please consult `build.sh` for more useful tasks such as _clean_all_, _fast_, _bootstrap_.
Travis build is supported and configured in `.travis.yml`.
