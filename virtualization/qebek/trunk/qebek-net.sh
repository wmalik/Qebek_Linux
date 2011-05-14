#! /bin/sh
SBK_DIAG=../../../sebekd/trunk/sbk_diag.pl
IMAGE_FILE=./windows.img

# your user id here
sudo sh -x ./qebek_networking.sh start
i386-softmmu/qebek -localtime -m 1024 $IMAGE_FILE -net nic,vlan=0,macaddr=00:11:22:33:44:55,model=rtl8139 -net tap,vlan=0,ifname=tap0,script=no,downscript=no -winxp | $SBK_DIAG #-qmp tcp:localhost:4444,server #-sbk_ip 192.168.0.1 
sudo sh -x ./qebek_networking.sh stop
