#!/bin/sh

IMAGE_FILE=linux-0.2.img

i386-softmmu/qebek -localtime -m 1024 ../images/linux-0.2.img 2>&1 | python parser.py

