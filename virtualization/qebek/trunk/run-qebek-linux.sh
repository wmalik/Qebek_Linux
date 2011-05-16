#!/bin/sh

IMAGE_FILE=../images/linux-0.2.img

i386-softmmu/qebek -localtime -m 1024 $IMAGE_FILE 2>&1 | python parser.py

