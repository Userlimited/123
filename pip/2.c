#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
typedef struct node
{
	char buff[1024];
	struct node *next;
}NODE;

NODE *createlist()
{
	NODE *head = (NODE *)malloc(sizeof(NODE));
	assert(head != NULL);
	memset(head->buff, 0, sizeof(head->buff));
	head->next = head;
	return head;
}

void insertlist(NODE *head, char *str)
{
	NODE *p = head;
	NODE *pnew = (NODE *)malloc(sizeof(NODE));
	assert(pnew != NULL);
	strcpy(pnew->buff,str);
	while(p->next != head)
	{
		p = p->next;
	}
//	printf("11");
	p->next = pnew;
	pnew->next = head;
}

void displaylist(NODE *head)
{
	NODE *p = head->next;
	while(p != head)
	{
		printf("%s",p->buff);
		p = p->next;
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
/*	memset( buf, 0, sizeof(buf) );//初始化buf,以免后面写如乱码到文件中
	stream = popen( "sudo nmap 192.168.6.*", "r" ); //将"nmap”命令的输出 通过管道读取（“r”参数）到FILE* stream
	wstream = fopen( "/home/ubuntu/doudoudou/pip/test_popen.txt", "w"); //新建一个可写的文件

	fread( buf, sizeof(char), sizeof(buf), stream); //将刚刚FILE* stream的数据流读取到buf中
	fwrite( buf, 1, sizeof(buf), wstream );//将buf中的数据写到FILE    *wstream对应的流中，也是写到文件中
	
	pclose( stream );
	fclose( wstream );
*/

	memset(str, 0, sizeof(str) );
	memset(str1, 0, sizeof(str1));
	fp = fopen("/home/ubuntu/doudoudou/pip/test_p.txt","r");
	if(fp == NULL)
	{
		printf("NULL\n");
		exit(1);
	}
	while (1)
	{
		memset(str1, 0, sizeof(str1));

		fgets(str1, sizeof(str1), fp);
	/*	if(feof(fp))
		{
			break;
		}*/
		strcat(str,str1);
		if(str1[0]=='\n'||str[0]=='\r')
		{
			insertlist(head,str);
			memset(str, 0, sizeof(str));
		}
		 if(feof(fp))
		{
			break;
		}

	}
	fclose(fp);
	displaylist(head);
	return 0;
}   
