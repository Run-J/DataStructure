//Filename: stringForceMatch.cpp
//Programmer: Run Ji 润
//First Version: Janurary 1, 2023

#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:6011)
#pragma warning(disable:26451)

typedef struct String
{
	char* data;
	int len;
}String;

String* initString()
{
	String* s = (String*)malloc(sizeof(String));
	s->data = NULL;
	s->len = 0;
	return s;
}

void stringAssign(String* s, const char* data) // write a function like "strcpy"
{
	if (s->data != NULL)
	{
		free(s->data);
	}
	int len = 0;
	const char* temp = data;
	while (*temp != '\0') // check how many of characters
	{
		len++;
		temp++; // move the pointer one place forward
	}
	if (len == 0) // if len equal 0 means nothing character entered (or empty string)
	{
		s->data = NULL;
		s->len = 0;
	}
	else // if a valid string is entered
	{
		temp = data; // move pointer from end of string back to the first character of the string
		s->len = len;
		s->data = (char*)malloc(sizeof(char) * (len + 1)); //'+1' for the null terminator '0'
		for (int i = 0; i <= len; i++, temp++) //allocation of characters, include '\0' (i<=len)
		{
			s->data[i] = *temp;
		}
	}
}

void printString(String* s)
{
	for (int i = 0; i < s->len; i++)
	{
		printf(i == 0 ? "%c" : "->%c", s->data[i]);
	}
	printf("\n");
}

void forceMatch(String* master, String* sub)
{
	int i = 0;
	int j = 0;
	while (i < master->len && j < sub->len)
	{
		if (master->data[i] == sub->data[j]) // current character is match
		{
			i++;
			j++;
		}
		else // not match
		{
			i = i - j + 1; //对齐string刚才匹配失败的下一位
			j = 0; //pattern回到头
		}
	}

	if (j == sub->len)
	{
		printf("force match success.\n");
	}
	else
	{
		printf("force match fail.\n");
	}
}

int main(int argc, char* argv[])
{
	String* master = initString();
	String* sub = initString();
	stringAssign(master, argv[1]);
	stringAssign(sub, argv[2]);
	printString(master);
	printString(sub);
	forceMatch(master, sub);
	return 0;
}