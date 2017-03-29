#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
int main(){
	char cache[100];
	int filedis[2];
	int flag;
	if(pipe(filedis) < 0)
	{
		printf("create pipe failed\n");
		return -1;		
	}

	memset(cache, 0, sizeof(cache));
	
	int pid;
	pid = fork();
	if(pid == 0)
	{
		printf("child\n");
		close(filedis[1]);//filedis[1] is write pip
		sleep(3);
		if((flag = execlp("nmap", "nmap", "192.168.6.*", NULL)))
		{
			printf("EXECLP ERROR\n");
		}
//		execve("/home/ubuntu/doudoudou/pip/un.sh",NULL,NULL);
		read(filedis[0], cache, 100);
		printf("%s\n", cache);
		close(filedis[0]);
	}

	else if(pid > 0)
	{
		printf("dad\n");
		close(filedis[0]);
		write(filedis[1],"hello ",6);
		write(filedis[1],"linuxdba",8);
		close(filedis[1]);
		wait(NULL);
	}

	else{
		printf("process failed\n");
		return -1;
	}

	return 0;
}

