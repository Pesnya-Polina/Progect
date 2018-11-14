#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <locale.h>
#pragma warning(disable : 4996)
char* ReadFile(char* poem)
{
	FILE *data = fopen("onegin.txt", "r");
	struct stat st = { 0 };
	stat("onegin.txt", &st);
	unsigned long long count_of_letters = st.st_size;
	poem = (char*)calloc(count_of_letters, sizeof(char));
	if (poem == NULL)
	{
		printf("No memory\n");
		exit(1);
	}
	fread(poem, sizeof(char), count_of_letters, data);
	return poem;
}
char** CountStrings(char *poem, char **buf, int* count_strins)
{
	int i = 0, j = 0, size_buf = 1;
	buf = (char**)calloc(1, sizeof(char*));
	if (buf == NULL)
	{
		printf("No memory\n");
		exit(1);
	}
	buf[0] = poem;
	j = 1;
	while (*(poem + i) != '\0')
	{
		if (j == size_buf)
		{
			size_buf *= 2;
			buf = (char**)realloc(buf, size_buf * sizeof(char*));
		}
		if (*(poem + i) == '\n')
		{
			*(poem + i) = '\0';
			while (*(poem + i + 1) == '\n')
			{
				i++;
			}
			buf[j] = (poem + i + 1);
			j++;
		}
		i++;
	}
	*count_strins = j;
	return buf;
}
int CompareInts(void *a_ptr, void *b_ptr)
{
	return *((int*)a_ptr) - *((int*)b_ptr);
}
int CompareStrings(void *ptr1, void *ptr2)
{
	char *str1 = *((char**)ptr1);
	char *str2 = *((char**)ptr2);
	while ((*str1 != '\0') || (*str2 != '\0'))
	{
		while (!SortAlph(*str1)) str1++;
		while (!SortAlph(*str2)) str2++;
		if (SortAlph(*str1) != SortAlph(*str2)) return (SortAlph(*str1) - SortAlph(*str2));
		str1++;
		str2++;
	}
}
int SortAlph(char c)
{
	if (CastomEncoding(c) != 0) return CastomEncoding(c);
}
int CastomEncoding(char c)
{
	char alph[66] = "ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäå¸æçèéêëìíîïğñòóôõö÷øùúûüışÿ";
	for (int i = 0; i < 66; i++)
	{
		if (c == alph[i]) return i + 1;
	}
	return 0;
}
char** CountAndChange(char **buf, int count_strings)
{
	qsort(buf, count_strings, sizeof(char*), &CompareStrings);
	return buf;
}
void Print(char** buf, int count_strings)
{
	for (int i = 0; i < count_strings; i++)
	{
		puts(buf[i]);
	}
}
int main()
{
	setlocale(LC_ALL, "");
	int count_strings = 0;
	char *poem = NULL;
	poem = ReadFile(poem);
	char** buf = NULL;
	buf = CountStrings(poem, buf, &count_strings);
	buf = CountAndChange(buf, count_strings);
	Print(buf, count_strings);
	return 0;
}