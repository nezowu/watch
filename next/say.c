#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "");
	size_t flag;
	wchar_t wbuff[] = L"Привет";
	char buff[80];
//	char *sbuff;
	flag = wcstombs(buff, wbuff, 80);
	printf("%s %zd\n", buff, flag);
//	sprintf(buff, "%ls", wbuff);
//	printf("%s\n", buff);
}
