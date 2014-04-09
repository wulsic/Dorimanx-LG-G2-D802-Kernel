#!/bin/bash

if [ "${1}" != "" ]; then
	cd ..;
	cd Ramdisk;
	git checkout ${1};
	cd ..;
	cd samsung-kernel-jfltexx;
fi;
