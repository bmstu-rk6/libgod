[![Build](https://github.com/bmstu-rk6/libgod/actions/workflows/build.yml/badge.svg)](https://github.com/bmstu-rk6/libgod/actions/workflows/build.yml)

libgod
========

Global Optimization Data Library.

Nothing personal. Pure atheistic. Pure phdic.

Welcome to the [discussion wiki](https://github.com/bmstu-rk6/libgod/wiki)

How to build
============

Currently only UNIX systems are supported - Linux, macOS.

Dependencies
------------

 * Conan
 * CMake (could be specified as Conan build dependency in profile)
 * [Doxygen](http://doxygen.org) (optional)

Building
--------

To build, test and package the library run:

    conan create . libgod/@ -b missing

Documentation is not built by default.

