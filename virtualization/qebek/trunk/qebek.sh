#! /bin/sh
SBK_DIAG=../../../sebekd/trunk/sbk_diag.pl
IMAGE_FILE=../images/winxp.img

#tunctl -b -u root -t tap0
#brctl addif br0 tap0
#ifconfig tap0 0.0.0.0 promisc up


i386-softmmu/qebek -localtime -m 1024 $IMAGE_FILE -net nic,vlan=0,macaddr=00:11:22:33:44:55,model=pcnet -net tap,vlan=0,ifname=tap0,script=/etc/qebek-ifup,downscript=/etc/qebek-ifdown -winxp | $SBK_DIAG -sbk_ip 192.168.0.44 
#-qmp tcp:localhost:4444,server #-sbk_ip 192.168.0.1 


#ifconfig tap0 down
#brctl delif br0 tap0
#tunctl -d tap0
