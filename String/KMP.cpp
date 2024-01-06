﻿//Filename: stringForceMatch.cpp
//Programmer: Run Ji 润
//First Version: Janurary 2, 2023

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

void stringAssign(String* s, const char* data)
{
	if (s->data != NULL)
	{
		free(s->data);
	}

	int len = 0;
	const char* temp = data;
	while (*temp != '\0')
	{
		len++;
		temp++;
	}
	
	if (len == 0)
	{
		s->data = NULL;
		s->len = 0;
	}
	else
	{
		temp = data;
		s->len = len;
		s->data = (char*)malloc(sizeof(char) * (len + 1));
		for (int i = 0; i <= len; i++, temp++)
		{
			s->data[i] = *temp;
		}
	}

}

void printString(String* s)
{
	for (int i = 0; i < s->len; i++)
	{
		printf(i == 0 ? "%c" : " -> %c", s->data[i]);
	}
	printf("\n");
}

//int* getNext(String* s)
//{
//	int* next = (int*)malloc(sizeof(int) * s->len); // 动态分配一个数组来存储 next 值
//	int i = 0;  //next数组的索引，代表着被比较的字符的索引，相当于模式串为主字符串
//	int j = -1;  //next数组的值代表最大公共前后缀的个数，同时代表着想要比较字符的索引，会回溯移动，相当于模式字符串的前缀，为目标字符串
//	next[i] = j;  //next数组第一个值为-1，因为第一个字符只有自身，并没有最大公共前后缀。同时用来当回溯索引
//	while (i < s->len - 1)  //当检查完模式串的最后一个字符，len-1是因为len为正整数，然而数组从索引0开始
//	{
//		if (j == -1 || s->data[i] == s->data[j]) //j为-1 或者 判断如果模式串的前缀和后缀一样，这里是从左往右（从小到大）一层一层判断 
//		{														//例如A B C D A B D， 先是AA一样然后再是BB一样，最后得知两个长度的缀
//																//当判断字符不一样时，用当前位的next值为索引的字符去对应刚才匹配失败的模式串的字符
//			i++;  //如果成功，那么继续移到右👉一位（当前位），i不会回溯，会一直走下去 （ex.0，1，2，3，4，5，6）
//			j++;	// j 向右移动，表示公共前后缀长度增加
//					//移动到字符串的第一个字符，因为-1加1等于0；相当于按顺序判断：AA，AB，AC，AD，AA，BB，CD （-1，0，0，0，0，1，2）
//			next[i] = j;	// 更新 next 数组的当前值
//							//j每往后移动一格，意味着判断出了一个公共前后缀，所以j的值代表着最大公共前后缀，如果字符判断不相等
//							//那么j只会从-1到0，依然是没有公共前后缀，如果字符相同，那j会变成1、2、3等
//		}
//		else
//		{
//			j = next[j]; 	// 当字符不匹配时，将 j 跳转到之前计算的 next 值
//						//当判断字符不相等时不匹配了，j回溯到next[-1]的位置还是等于-1，接下来还可以进行if的循环，i一直会加不会减，j会-1变0变1等			
//		} 
//	}
//	return next;  //返回next数组； next数组是PMT表（Partial Match Table) 用于记录最大公共前后缀的表向右一位的结果
//					//由于便于编程，避免与数组[0]冲突，刚好第一个字符也不会有公共前后缀，所以next[0]等于-1刚好表示将j回溯到第一个字符的位置
//					// 往右一格的结果，所以next索引是错位的，便从-1开始。
//					//例如原本是0 0 0 0 1 2 0，现在就是 -1 0 0 0 0 1 2
//}

//The second method does not use -1
int* getNext(String* s) 
{
	int* next = (int*)malloc(sizeof(int) * s->len);
	next[0] = 0;  // next 数组第一个值设置为 0

	int j = 0; // 初始比较位置设置为 0, 模式串中前缀的结束位置
	int i = 1; // 从第二个字符开始

	while (i < s->len) 
	{
		if (s->data[i] == s->data[j]) 
		{
			// 如果字符匹配，递增 i 和 j，并设置 next[i]				a b a a b c a c
															 //ab aa ba 
			j++;
			next[i] = j;
			i++;
		}
		else 
		{
			if (j == 0) 
			{
				// 字符不匹配且回溯点为0，设置 next[i] 为 0，并递增 i，需手动对准主串的后一位，让字串j去比较
				next[i] = 0;
				i++;	
			}
			else 
			{
				// 如果字符不匹配，且回溯点不为0，回溯 j。
				j = next[j - 1];
			}
		}
	}
	return next;
}

void printNext(int* next, int len)
{
	for (int i = 0; i < len; i++)
	{
		printf(i == 0 ? "%d" : " -> %d", next[i]);
	}
	printf("\n");
}

void kmpMatch(String* string, String* pattern, int* next)
{
	int i = 0;
	int j = 0;
	while (i < string->len && j < pattern->len)
	{
		if (string->data[i] == pattern->data[j]) //successful match
		{
			i++;
			j++;
		}
		else if (j != 0)
		{
			j = next[j - 1];
		}
		else
		{
			i++;
		}

	}

	if (j == pattern->len)
	{
		printf("Kmp match successfully\n");
	}
	else
	{
		printf("Kmp match failure\n");
	}
}

int main(void)
{
	String* string = initString();
	String* pattern = initString();
	stringAssign(string, "ABACCABABCABACCABABDABBCCABABD");
	printString(string);

	stringAssign(pattern, "ABABD");
	printString(pattern);
	int* next = getNext(pattern);
	printNext(next, pattern->len);

	kmpMatch(string, pattern, next);

	return 0;
}