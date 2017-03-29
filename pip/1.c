#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
typedef struct node
{
	char ip[1000];
	char mac[100];
	char port[1024];
	struct node *next;
}NODE;

NODE *createlist()
{
	NODE *head = (NODE *)malloc(sizeof(NODE));
	assert(head != NULL);
	memset(head->ip, 0, sizeof(head->ip));
	memset(head->mac, 0, sizeof(head->mac));
	memset(head->port, 0, sizeof(head->port));
	head->next = head;
	return head;
}

void insertlist(NODE *head, char *str)
{
	NODE *p = head;
	NODE *pnew = (NODE *)malloc(sizeof(NODE));
	assert(pnew != NULL);
	char ip[1000];
	char mac[100];
	char port[1024];
	strcpy(pnew->ip,"NULL");
	strcpy(pnew->mac,"NULL");
	int i,j,k;
	j = 0;
	k = 0;
	for (i = 0; i < strlen(str)+1; i++)
	{
		memset(ip, 0, sizeof(ip));
		strncpy(ip, str+i, 16);
		if(strcmp(ip,"Nmap scan report")==0)
		{
			memset(pnew->ip, 0, sizeof(pnew->ip));
			strncpy(pnew->ip,str+i+21,17);
		}
		memset(port, 0, sizeof(port));
		strncpy(port, str+i, 7);
		if(strcmp(port,"SERVICE")==0)
		{
			k = i;
		}
		memset(mac, 0, sizeof(mac));
		strncpy(mac, str+i, 13);
		if(strcmp(mac,"MAC Address: ")==0)
		{
			memset(pnew->mac, 0, sizeof(pnew->mac));
			j = i;
			strcpy(pnew->mac,str+i+13);
		}
	}	
	if(j!=0)
	{
		strncpy(pnew->port,str+k+7,j-k-7);
	}
	else
	{
		strcpy(pnew->port,str+k+7);
	}
	while(p->next != head)
	{
		p = p->next;
	}
	p->next = pnew;
	pnew->next = head;
}

void displaylist(NODE *head)
{
	NODE *p = head->next;
	while(p != head)
	{
		if(strcmp(p->ip,"NULL")==0)
		{
			p = p->next;
		}
		else
		{
		printf("ip:%s", p->ip);
		//printf("port:%s\n", p->port);
		printf("mac:%s", p->mac);
		printf("port:%s\n",p->port);
		printf("\n");
		p = p->next;
		}
	}
}

int main( void )
{
	FILE   *stream;
	FILE   *wstream;
	FILE *fp;
	char   buf[1024];
	char str[1024];
	char str1[1024];
	int count = 0;
	NODE *head = createlist();
	memset( buf, 0, sizeof(buf) );//初始化buf,以免后面写如乱码到文件中
	stream = popen( "sudo nmap 192.168.6.*", "r" ); //将“nmap”命令的输出 通过管道读取（“r”参数）到FILE* stream
	wstream = fopen( "/home/ubuntu/doudoudou/pip/test_popen.txt", "w"); //新建一个可写的文件

	fread( buf, sizeof(char), sizeof(buf), stream); //将刚刚FILE* stream的数据流读取到buf中
	fwrite( buf, 1, sizeof(buf), wstream );//将buf中的数据写到FILE    *wstream对应的流中，也是写到文件中
	
	pclose( stream );
	fclose( wstream );
/*
	memset(str, 0, sizeof(str) );
	memset(str1, 0, sizeof(str1));
	fp = fopen("/home/ubuntu/doudoudou/pip/test_popen.txt","r");
//	if(fp == NULL)
//	{
//		printf("NULL\n");
//		exit(1);
//	}
	while (1)
	{
		memset(str1, 0, sizeof(str1));

		fgets(str1, sizeof(str1), fp);
		if(feof(fp))
		{
			break;
		}
		strcat(str,str1);
		strcat(str,"       ");
		if(str1[0]=='\n'||str[0]=='\r')
		{
			if(count != 0)
			{
			insertlist(head,str);
			memset(str, 0, sizeof(str));
			}
			count=1;
		}
		 if(feof(fp))
		{
			break;
		}

	}
	fclose(fp);
	displaylist(head);
*/
	return 0;
}   
