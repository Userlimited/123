#!/bin/bash
#
# rm is to delete some files 30 days ago
#
# chkconfig: 2345 55 25
USER="root"
MEM="29"
DAY=3
do_start() {

#find ./ -name "*.mp4"  -mtime +30 -type f   -exec rm -f {} \;
cd /home/ubuntu/doudoudou/ceshi/
Usemem=$(du -sk)
#echo "$Usemem"
echo ${Usemem%.*}
#if [ "$Usemem" \> "$MEM" ]; then
#	find ./ -name "*.c" -mtime -1 -type f -print
#else
#	echo 0
#fi
while true
do

	find ./  -mtime +30 -type f -exec rm -f {} \; 
	while [[ "$Usemem" > "$MEM" ]]
		do
		find ./  -mtime +$DAY -type f -exec rm -f {} \;
#		while true
#			do
#				find ./ -name "*.sh" -mtime +30 -type f -exec rm -f {} \; 
#			done
		let DAY=$DAY-1;
		done
done
}




case $1 in 
start) do_start;;
*)
echo "Usage: $0 {start}"
exit 1 
esac
