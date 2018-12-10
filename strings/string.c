#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int my_strlen(char *str)
{
	int i, count = 0;
	while(*str != '\0')
	{
		count++;
		str++;
	}
	return count;
}

int my_strcpy(char *src, char *dest)
{
	int count = 0;
	while (*src != '\0')
	{
		*dest++ = *src++;
		count++;
	}
	*dest = '\0';
	return count;
}

char * my_strrev(char *str)
{
	int len, i, j;
	char temp;
	if (!str)
	{
		return NULL;
	}
	len = my_strlen(str)-1;
	for(i = 0, j = len; i < j; i++, j--)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
	return str;
}

int my_atoi(char *str)
{
	int num = 0;
	char *p = str;
	while(*p != '\0')
	{
		num = num*10 + (*p - '0');
		p++;
	}
	return num;
}

char * my_itoa(int num, char *buf)
{
	int val = num;
	int i = 0;
	while(val)
	{
		buf[i++] = val%10 + '0';
		val = val/10;
	}
	buf[i] = '\0';
	printf("%s\n",buf);
	my_strrev(buf);
	return buf;
}

char * swap(char *arr, int start, int end)
{
	int i = start, j = end;
	char temp;
	for(;i < j; i++, j--)
	{
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	return arr;
}

char * revSentense(char *line)
{
	int start = 0, end = 0;
	char *p, *q;
	my_strrev(line);
	p = line;
	
	while(*p != '\0')
	{
		q = p;
		while(*q != '\0' && *q != ' ')
		{
			q++;
			end++;
		}
		swap(line, start, end-1);
		start = end+1;
		end = end+1;
		p = q+1;
	}
	return line;
}

int main()
{
	char *val = "12345";
	int num = 0;
	char *str;
	char buf[100] = "I am a good boy";
	
	revSentense(buf);
	printf("REV Sentense= %s\n", buf);
	my_strrev(buf);

	printf("REV = %s\n", buf);
	num = my_atoi(val);
	printf("atoi Converted val = %d\n", num);
	
	str = my_itoa(num, buf);
	printf ("itoa convert is %s\n", str);

	return 1;
}