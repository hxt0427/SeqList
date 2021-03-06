// SeqList.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include"String.h"
#include"time.h"
#include"stdio.h"

int Index(char*S, char *T, int pos)			//简单匹配
{
	int n = strlen(S), m = strlen(T);
	int i = pos, j = 0;
	while (i < n && j < m)
	{
		if (S[i] == T[j])
		{
			i++;
			j++;
		}
		else						//失配
		{
			i = i - j + 1;			//回到当前起始位并后移一位
			j = 0;
		}
	}
	if (j == m)					//成功匹配
		return i - m;			//返回主串的起始位置
	return -1;					//匹配失败
}
int Next[20];		//	Next[j]表示T[j]前的最长前后缀相等的长度
void get_next(char *T, int next[])
{
	int i = 0;
	next[i] = -1;
	int j = -1;
	int m = strlen(T);
	while (i < m)
	{
		if (j == -1 || T[i] == T[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else
			j = next[j];
	}
}
int Index_KMP(char*S, char *T, int pos)
{
	int n = strlen(S), m = strlen(T);
	int i = pos, j = 0;
	while (i < n && j < m)
	{
		if (S[i] == T[j])
		{
			i++;
			j++;
		}
		else						//失配
		{
			j = Next[j];
		}
	}
	if (j == m)					//成功匹配
		return i - m;			//返回主串的起始位置
	return -1;					//匹配失败
}
int Index_KMP2(char*S, char *T, int pos)		//short加快
{
	int n = strlen(S), m = strlen(T);
	int i = pos, j = 0;
	short* p = (short*)S;
	short* q = (short*)T;
	while (i < (n/2 + n%2 )  && j < (m / 2 + m % 2) )		//余数为0或1
	{
		if (p[i] == q[j])
		{
			i++;
			j++;
		}
		else						//失配
		{
			j = Next[j*2] / 2;
		}

	}
	if (j == (m / 2 + m % 2))					//成功匹配
		return 2*i - (m + m%2);			//返回主串的起始位置 ,m为奇数，则多减1
	return -1;					//匹配失败
}
int Index_Horspool(char*S, char *T,int pos)
{
	int n = strlen(S);
	int m = strlen(T);
	int table[256];
	for (int i = 0; i < 256; i++)
		table[i] = m + 1;
	for (int i = 0; i < m - 1 ; i++) //模式串最后一个字符不参与，否则移动0
	{
		table[T[i]] = m - 1 - i;//模式串中每个字符的移动距离，从左至右扫描模式，相同字符的最后一次改写恰好是该字符在模式串的最右边
	}

	int i = m - 1;
	while (i <= n - 1)
	{
		int k = 0;
		while (k <= m - 1 && T[m - 1 - k] == S[i - k])
			k++;

		if (k == m)
			return i - m + 1;//匹配成功，返回索引
		else
			i += table[S[i]];//主串向右移动
	}

	return -1;//匹配失败
}

int skipTable[256];
void fill_skip_table_sunday(char *T)
{
	int m = strlen(T);
	for (int i = 0; i < 256; i++)		//	如果一个字符未在模式串中出现过，则模式串需要移动m+1的长度
	{
		skipTable[i] = m + 1;
	}
	for (int i = 0; i < m; i++)			//	如果一个字符在模式串中出现过，则模式串需要移动的距离=串长度-该字符最后出现的位置
	{
		skipTable[T[i]] = m - i;
	}
}
int Index_Sunday(char *S, char*T, int pos)
{
	int n = strlen(S);
	int m = strlen(T);
	int i = 0;
	int n_m = n - m;
	while (i <= n_m)
	{
		if (memcmp(S + i, T, m) == 0)	//如果匹配，则返回位置i
			return i;
		i += skipTable[S[i + m]];		//i+m为主串和模式串对齐后，在模式串右边的第一个字符的下标
	}
	return -1;
}

int main()
{
	char S[] = "000000000000000000000000000000000000001";
	char T[] = "0000000000001";
	get_next(T, Next);
	fill_skip_table_sunday(T);
	int pos;
	int index;
	int repeats = 10000000;
	time_t tBegin, tEnd;
	clock_t t1, t2;
	time(&tBegin);	//记录当前时间   简单匹配
	t1 = clock();
	for (int i = 0; i < repeats; i++)
		pos = Index(S, T, 0);
	t2 = clock();
	time(&tEnd);
	float cost = tEnd - tBegin;
	printf("简单匹配：	子串搜索结果是： %d , 耗时%.2fs\t%dms \n", pos, cost, t2 - t1);

	time(&tBegin);	//记录当前时间    KMP
	t1 = clock();
	for (int i = 0; i < repeats; i++)
		pos = Index_KMP(S, T, 0);
	t2 = clock();
	time(&tEnd);
	float cost2 = tEnd - tBegin;
	printf("KMP：	\t子串搜索结果是： %d , 耗时%.2fs\t\t%dms  \n", pos, cost2,t2-t1);

	time(&tBegin);	//记录当前时间    Horspool
	t1 = clock();
	for (int i = 0; i < repeats; i++)
		pos = Index_Horspool(S, T, 0);
	t2 = clock();
	time(&tEnd);
	float cost4 = tEnd - tBegin;
	printf("Horspool：	子串搜索结果是： %d , 耗时%.2fs\t\t%dms  \n", pos, cost4, t2 - t1);

	time(&tBegin);	//记录当前时间    KMP  short
	t1 = clock();
	for (int i = 0; i < repeats; i++)
		pos = Index_KMP2(S, T, 0);
	t2 = clock();
	time(&tEnd);
	float cost5 = tEnd - tBegin;
	printf("KMP-short指针：	子串搜索结果是： %d , 耗时%.2fs\t\t%dms  \n", pos, cost5, t2 - t1);

	time(&tBegin);	//记录当前时间    Sunday
	t1 = clock();
	for (int i = 0; i < repeats; i++)
		pos = Index_Sunday(S, T, 0);
	t2 = clock();
	time(&tEnd);
	float cost3 = tEnd - tBegin;
	printf("Sunday：	子串搜索结果是： %d , 耗时%.2fs\t\t%dms  \n", pos, cost3, t2 - t1);

	/*	String A("hello ");				//String  测试
	String B = "world!";
	A.concat(B).outputWithoutLenth();
	A.output();
	B.output();
	printf("A-B=%d\n", A.compare(B));

	String S("acabaabaabcacaabc");
	String T = "abaabc";
	S.outputWithoutLenth();
	T.outputWithoutLenth();

	printf("子串搜索结果是： %d \n", S.index(T));

	SeqList<String> subs;
	S.split(subs, 'b');
	//subs.output();
	for (int i = 0; i < subs.length; i++)
	{
		subs.items[i].output();
	}*/

/*SeqList<char>list1;				//SeqList 测试
	list1.addpend('w');
	list1.addpend('h');
	list1.addpend('t');

	list1.insertAt(2, 'a');
	list1.output();*/
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
