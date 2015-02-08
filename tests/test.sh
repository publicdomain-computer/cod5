#!/bin/sh

echo testing...

do_test () {
	echo Test: \#${1} ------------------------------------------------
	../bin/cxx.exe ${1}.cpp
}


if [ "x${1}" = "x" ] ; then
	n=100000
	while [ -f ${n}.cpp ] ; do
		do_test $n
		n=$((n+1))
	done
else
	do_test $1
fi
echo
echo end testing!!!



