#!/bin/bash
#
# rm is to delete some files 30 days ago
#
# chkconfig: 2345 55 25
USER="root"
MEM1="29"
TIME=$2
MEM=$3
let TIME1=$TIME-1
#DAY=3
do_start() {

cd /home/ubuntu/doudoudou/ceshi/
Usemem=$(du -sk)
echo ${Usemem%.*}
find ./  -mtime +$TIME -type f -exec rm -f {} \; 
while [[ "$Usemem" > "$MEM" ]]
	do
		find ./  -mtime +$TIME1 -type f -exec rm -f {} \;
#		while true
#			do
#				find ./  -mtime +30 -type f -exec rm -f {} \; 
#			done
		let TIME1=$TIME1-1
		Usemem=$(du -sk)
	done

}




case $1 in 
start) do_start;;
*)
echo "Usage: $0 {start}"
exit 1 
esac
