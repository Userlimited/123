FILESYSTEM=/dev/sda1 # or whatever filesystem to monitor
CAPACITY=80 # start cleaning up if FS is over 80% of usage 
DATADIR=/data/guacamole/ # the given folder
#DATADIR=/home/ubuntu/doudoudou/ceshi/
SIZE=100 # size (in GB) threshold to reach for the given folder before starting to delete files
DAYSOLD=30 # delete files created number of days ago
while getopts p:d:c:s: opt
do
	case ${opt} in
		p)
		DATADIR=$OPTARG
		echo "datadir is $DATADIR"
		;;
		d)
		DAYSOLD=$OPTARG
		echo "daysold is $DAYSOLD"
		;;
		c)
		CAPACITY=$OPTARG
		echo "capacity is $CAPACITY"
		;;
		s)
		SIZE=${OPTARG}
		echo "size is $SIZE"
		;;
		*)
		echo "USAGE [-p]:Set the path  [-d]: Set the number of days before [-c]:Set the capacity [-s]:Set the size"
		;;
	esac
done

#find $DATADIR -type f -mtime -$DAYSOLD -print

# first delete files older than 30 days in DATADIR
find $DATADIR -type f -mtime +$DAYSOLD -exec rm {} \;
# using [ instead of [[ for better error handling.
if [ $(df -P $FILESYSTEM | awk '{ gsub("%",""); capacity = $5 }; END { print capacity }') -gt $CAPACITY ]
then
	# ls -lc delete the oldest files if total file size in this folder is greater than $SIZE G
	cd $DATADIR && ls -lc | awk '{ if (!system("test -f " $9)) { size += $5; if (size > "$SIZE"*2^30 ) system("rm " $9) } }'
fi

