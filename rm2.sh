#!/bin/bash
#
# rm is to delete some files 30 days ago
#索引搜索
# chkconfig: 2345 55 25
USER="root"
MEM1="29"
TIME=$2 //获取时间阀值参数
MEM=$3	//获取内存阀值参数
let TIME1=$TIME-1   //设置临时间阀值最近的参数
#DAY=3
do_start() {

cd /home/ubuntu/doudoudou/ceshi/  //切换目录
Usemem=$(du -sk)    	//查看硬盘使用大小
echo ${Usemem%.*}	
find ./  -mtime +$TIME -type f -exec rm -f {} \; //删除超过时间阀值的文件
while [[ "$Usemem" > "$MEM" ]] //比较硬盘使用量是否超过阀值	
	do
		find ./  -mtime +$TIME1 -type f -exec rm -f {} \; //删除离阀值最近的文件
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
