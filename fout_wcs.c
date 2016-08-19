/* записываем базу данных из файла в динамический
   двумерный массив мультибайтные строки*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "");
	int i, j;
	size_t flag;
	wchar_t **wbuff;
	char buff[256] = {0};
	wchar_t wcs[64] = L"";
//	char ** wbuff;
	FILE *fo;
	i = 0;
	j = 0;

	fo = fopen("bd.txt", "r");
	while(!feof(fo))
	{
		fscanf(fo, "%*[^\n]\n");
		i++;
	}
	wbuff = (wchar_t **)malloc(i * sizeof(wchar_t*));
	rewind(fo);
	while(!feof(fo))
	{
		fscanf(fo, "%255[^\n]\n", buff); 
		wbuff[j] = (wchar_t *)malloc(sizeof(buff));
		flag = mbstowcs(wcs, buff, 63);
		wprintf(L"коверт: %d\n", flag);
		wcsncpy(wbuff[j], wcs, 64);
		j++;
	}
	fclose(fo);
//	printf("%d\n", j);
	for(;j>0; j--)
	{
		wprintf(L"%ls\n", wbuff[j-1]);
		free(wbuff[j-1]);
	}
	free(wbuff);
//	printf("%d\n", i);
	return 0;
}
