#! /bin/sh

tunctl -b -u root -t tap0
brctl addif br0 tap0
ifconfig tap0 0.0.0.0 promisc up
i386-softmmu/qebek -localtime -m 512 winxp2.img -net nic,vlan=0,macaddr=00:11:22:33:44:55,model=pcnet -net tap,vlan=0,ifname=tap0,script=no,downscript=no -winxp #-qmp tcp:localhost:4444,server #-sbk_ip 192.168.0.1 
ifconfig tap0 down
brctl delif br0 tap0
tunctl -d tap0
