#!/bin/sh
mkdir -p config
aclocal
libtoolize --force
automake --foreign --add-missing
autoconf

