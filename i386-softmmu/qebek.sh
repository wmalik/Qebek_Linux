#! /bin/sh

tunctl -b -u root -t tap0
brctl addif br0 tap0
ifconfig tap0 0.0.0.0 promisc up
./qebek -localtime -m 2047 ../winxp.img -cdrom ../winxp.iso -net nic,vlan=0,macaddr=00:11:22:33:44:55,model=pcnet -net tap,vlan=0,ifname=tap0,script=,downscript= -winxp -sbk_ip 127.0.0.1 
ifconfig tap0 down
brctl delif br0 tap0
tunctl -d tap0
