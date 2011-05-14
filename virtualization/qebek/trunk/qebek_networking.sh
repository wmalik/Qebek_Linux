#!/bin/bash

kvm_if_up(){
    tunctl -u paulo -t tap0

    /sbin/ifconfig tap0 192.168.22.123

    sysctl net.ipv4.ip_forward=1
    sysctl net.ipv4.conf.wlan0.proxy_arp=1

    sysctl net.ipv4.conf.tap0.proxy_arp=1

    ip link set dev tap0 up

    route add -host 192.168.22.125 dev tap0

    sudo /usr/sbin/iptables -t nat -A POSTROUTING -s 192.168.22.1/24 -j MASQUERADE -v
}

kvm_if_down(){

    #sysctl net.ipv4.ip_forward=0
    sysctl net.ipv4.conf.wlan0.proxy_arp=0

    sysctl net.ipv4.conf.tap0.proxy_arp=0

    ip link set dev tap0 down

    tunctl -d tap0

    sudo /usr/sbin/iptables -t nat -D POSTROUTING 1
}

if [[ $EUID -ne 0 ]]; then
  echo "This script must be run as root" 1>&2
  exit 1
else

    case "$1" in

        start)
            kvm_if_up
            ;;
        stop)
            kvm_if_down
            ;;
        *)
            echo "Usage: $0 {start|stop}"
            ;;
    esac

fi

exit 0
