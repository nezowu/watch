#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

int main(void)
{
	size_t flag;
	setlocale(LC_ALL, "");
	char mbsstr[1024] = {0};
	wchar_t wstr[256] = L"Хавронья иди";
	wchar_t wstrok[10] = L" на фик";
	char strb[] = "Yello World";
	FILE * fin;
	fin = fopen("raport.txt", "w");
	if(!fin)
		perror("fopen in"), exit(EXIT_FAILURE);

	wcsncat(wstr, wstrok, wcslen(wstrok));
	flag = wcstombs(mbsstr, wstr, wcslen(wstr) * 4);
	if(!flag)
		perror("конвертация!"), exit(EXIT_FAILURE);
	fprintf(fin, "%s\n", mbsstr);
	rewind(fin);
	fprintf(fin, "%s\n", strb);
	wprintf(L"%ls\n", wstr);
	fclose(fin);
	return 0;
}
