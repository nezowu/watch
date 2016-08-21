/* записываем базу данных из файла в динамический
   двумерный массив мультибайтные строки*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>

int main(void)
{
	setlocale(LC_ALL, "");
	int i, j;
	size_t mark;
	wchar_t **bd;
	char buff[256] = {0};
//	char laja[256];
	wchar_t wcs[64] = L"";
//	char ** bd;
	FILE *fo;
	i = 0;
	j = 0;

	fo = fopen("bd.txt", "r");
	while(!feof(fo))
	{
		fscanf(fo, "%*[^\n]\n");
		i++;
	}
	bd = (wchar_t **)malloc(i * sizeof(wchar_t*));
	rewind(fo);
	while(!feof(fo))
	{
//		fscanf(fo, "%255[^\n]\n", buff); 
//		fscanf(fo, "%255[^,]%255[^\n]\n", buff, laja);
		fscanf(fo, "%255[^,]%*[^\n]%*c\n", buff);
		bd[j] = (wchar_t *)malloc(sizeof(buff));
		mark = mbstowcs(wcs, buff, strlen(buff));
		wprintf(L"конверт: %d\n", mark);
		wcsncpy(bd[j], wcs, wcslen(wcs));
		j++;
	}
	fclose(fo);
//	printf("%d\n", j);
	for(;j>0; j--)
	{
      		wprintf(L"%ls\n", bd[j-1]);
		free(bd[j-1]);
	}
	free(bd);
//	printf("%d\n", i);
	return 0;
}
