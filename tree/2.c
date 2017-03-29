#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define HASH_LEN 8000

typedef struct Englishword
{   
	char *word;
	char *meaning;
}En;


void RemoveSpace(char *str);
long DJBHash(char *str);
int isExist(En *hword, int index);
En *CreateHash(int size);
int InsertHash(En *hword, char *word, char *meaning);
int handle_linestring(char *buf, char *word, char *meaning);	
int findHash(En *hword, char *word);
int Isspace(char w);

int Isspace(char w)
{
	if(w  == ' ')
	{
		return 1;
	}
	return 0;
}

En *CreateHash(int size)
{
	int i;
	En *hword = (En *)malloc(sizeof(En) * size);
	assert(hword != NULL);

	for (i = 0; i < size; i++)
	{
		hword[i].word = NULL;
		hword[i].meaning = NULL;
	}
	return hword;
}

int InsertHash(En *hword, char *word, char *meaning)
{
	int i;
	int index = DJBHash(word) % HASH_LEN;
	if (index < 0)
	{
		index = -index;
	}
	for (i = 0; i <= 40; i++)
	{
		if (!isExist(hword, index))
		{
			hword[index].word = (char *)malloc(strlen(word)+1);
			assert(hword[index].word != NULL);
			hword[index].meaning = (char *)malloc(strlen(meaning)+1);
			assert(hword[index].meaning != NULL);
			strcpy(hword[index].word, word);
			strcpy(hword[index].meaning, meaning);
			break;
		}

		if (i % 2 != 0)
		{
			index += ((i+1)/2) * ((i+1)/2);
		}
		else
		{
		
			index += -((i+1)/2) * ((i+1)/2);
		}

		if (index >= 8000)
		{
			index -= 8000;
		}
		if (index < 0)
		{
			index += 8000;
		}
	}
	if (i == 41)
	{
		return -1;
	}
	else
		return i;

}

int handle_linestring(char *buf, char *word, char *meaning)
{
	char *p;
	buf[strlen(buf)-1] = 0;
	RemoveSpace(buf);
	if ((p = strchr(buf, ' ')) == NULL)
	{
		return 0;
	}
	if (buf[0] >= 'A' && buf[0] <= 'Z')
	{
		return 0;
	}
	*p = 0;
	strcpy(word, buf);
	RemoveSpace(p+1);
	strcpy(meaning, p+1);

	return 1;
}

void RemoveSpace(char *str)
{
	int i;
	int len = strlen(str);
	for (i = len-1; i >= 0 && Isspace(str[i]); i--)
	{
		str[i] = 0;
	}
	for (i = 0; i < len && Isspace(str[i]); i++)
	{
	
	}
	if (i != 0)
	{
		strcpy(str, str+i);
	}
}

int isExist(En *hword, int index)
{
	if (hword[index].word != NULL)
	{
		return 1;
	}
	return 0;
}

int findHash(En *hword, char *word)
{
	int i;
	int index = DJBHash(word) % HASH_LEN;
	if (index < 0)
	{
		index = -index;
	}
	for (i = 0; i <= 40; i++)
	{
		if (!isExist(hword, index))
		{
			return -1;
		}
		if (strcmp(hword[index].word, word) == 0)
		{
			printf("%s\n", hword[index].meaning);
			break;
		}

		if (i % 2 != 0)
		{
			index += ((i+1)/2) * ((i+1)/2);
		}
		else 
		{
			index += -((i+1)/2) * ((i+1)/2);
		}

		if (index >= 8000)
		{
			index -= 8000; 
		}

		if (index < 0)
		{
			index += 8000;
		}
	}
	if (i == 41)
	{
		return -1;
	}
	else 
		return i;
}

long DJBHash(char *str)
{
	long hash = 5381;
	int i;
	for (i = 0; i < strlen(str); i++)
	{
		hash = ((hash << 5) + hash) + str[i];
	}
	return hash;
}

int main()
{
	FILE *fp = fopen("Englishwords.txt","r");
	assert(fp!= NULL);

	int num = 0;
	int clash = 0;
	int err = 0;

	char buf[100] = {0};
	char word[30] = {0};
	char meaning[70] = {0};

	En *hword = CreateHash(HASH_LEN);

	int ret;
	
	while(fgets(buf, sizeof(buf), fp))
	{
		if (!handle_linestring(buf, word, meaning))
		{
			continue;
		}
		num++;

		ret = InsertHash(hword, word, meaning);
		if (ret == -1)
		{
			printf("%s %sinsert error\n", word, meaning);
			err++;
		}
		if (ret != 0)
		{
			clash++;
		}
		memset(buf, 0, sizeof(buf));
		memset(word, 0, sizeof(word));
		memset(meaning, 0, sizeof(meaning));
	}
	printf("num:%d\n", num);
	printf("chong:%d\n", clash);
	printf("err:%d\n", err);

	char src[30] = {0};
	fgets(src, 30 , stdin);
	src[strlen(src)-1] = 0;

//	ret = findHash(hword, src);
	printf("ret:%d\n", ret);
}
