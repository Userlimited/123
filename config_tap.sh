
#!/bin/bash
#
# config_tap Start up the tun/tap virtual nic
#
# chkconfig: 2345 55 25
USER="gushenxing"
TAP_NETWORK="192.168.5.22"
TAP_DEV_NUM=0
DESC="TAP config"
BR_NETWORK="192.168.5.25"
BR_NUM=0
ETH_NUM=0
ETH_NETWORK="192.168.5.10"
do_start() {
if [ ! -x /usr/sbin/tunctl ]; then
echo "/usr/sbin/tunctl was NOT found!"
exit 1
fi

#if [ ! -x /usr/sbin/brctl ]; then
#echo "/sbin/brctl was NOT found!"
#exit 1
#fi

tunctl -t tap$TAP_DEV_NUM -u root
ifconfig tap$TAP_DEV_NUM 0.0.0.0
brctl addbr br$BR_NUM
brctl addif br$BR_NUM tap$TAP_DEV_NUM
#ifconfig eth$ETH_NUM up
brctl addif br$BR_NUM eth$ETH_NUM
ifconfig br$BR_NUM ${BR_NETWORK} up
ifconfig tap$TAP_DEV_NUM ${TAP_NETWORK} netmask 255.255.255.0 promisc
ifconfig eth$BR_NUM ${ETH_NETWORK}  
#ifconfig tap$TAP_DEV_NUM
ifconfig -a
}

do_stop() {
ifconfig tap$TAP_DEV_NUM down 
brctl delif br$BR_NUM tap$TAP_DEV_NUM
brctl delif br$BR_NUM eth$ETH_NUM
ifconfig br$BR_NUM down
tunctl	-d tap$TAP_DEV_NUM
brctl delbr br$BR_NUM
}

do_restart() {
do_stop
do_start
}

check_status() {
#ifconfig tap$TAP_DEV_NUM 
ifconfig -a
}

case $1 in 
start) do_start;;
stop) do_stop;;
restart) do_restart;;
status)
echo "Status of $DESC: "
check_status
exit "$?"
;;
*)
echo "Usage: $0 {start|stop|restart|status}"
exit 1 
esac
