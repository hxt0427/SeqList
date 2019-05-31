#pragma once
#include"SeqList.h"

struct String :SeqList<char>
{
	String(int c = 100) :SeqList(c)
	{

	}
	String(const char* chars)
	{
		while (*chars)
		{
			addpend(*chars);
			chars++;
		}
	}
	String *subString(int pos, int len)
	{
		String *result = new String(len);
		memcpy(result->items, items, sizeof(char)*len);
		length = len;
		return result;

	}
	String & concat(String &T)
	{
		int len = length + T.length;
		if (capacity < len)
			resize(len);
		memcpy(items + length, T.items, sizeof(char)*T.length);
		length = len;
		return *this;
	}
	int compare(String &T)
	{
		int n = length;
		int m = T.length;
		int i = 0, j = 0;
		while (i < n && j < m)
		{
			if (items[i] != T.items[i])
				return items[i] - T.items[i];
			i++;
			j++;
		}
		return n - m;
	}
	bool operator == (String & T)
	{
		return compare(T) == 0;
	}
	void operator = (const String & T)
	{
		length = T.length;
		resize(length);
		memcpy(items , T.items, sizeof(char)*T.length);
	}
	void split(SeqList <String> & subs, char splitter)
	{
		int i = 0,j = 0;
		subs.length++;
		for (; i < length; i++)
		{
			if (items[i] != splitter)
				subs.items[j].addpend(items[i]);
			else 
			{
				j++;
				subs.length++;
			}
				
		}

	}
	void replace(String A, String B)
	{
		int i = 0, j = 0;
		while (items[i])
		{
			if (items[i] == A.items[j])
			{
				i++;
				j++;
			}
			if (j == A.length)
			{
				remove(i - j, A.length);
				insert(B, i - j);
				j = 0;
			}
		}
	}
	void remove(int pos, int len)
	{
		for (int i = 0; i < len; i++)
		{
			deleteAt(pos + i);
		}
	}
	void insert(String A, int pos)
	{
		while (*A.items)
		{
			insertAt(pos, *A.items);
			pos++;
			A.items++;
		}	
	}
	int index(String &T, int pos=0)
	{
		int i;
		for ( i = 0; i < T.length; i++)
		{
			if (items[pos + i] != T.items[i])
			{
				pos++;
				i = 0;
			}
		}
		if (i == T.length)
			return pos;
		return -1;
	}
	friend ostream& operator <<(ostream &os, String &st);
};

ostream& operator <<(ostream &os, String &st)
{
	for (int i = 0; i < st.length; i++)
		os << st.items[i];
	return os;
}