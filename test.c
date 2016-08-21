#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include <stdio_ext.h>
#include <signal.h>
#include <string.h>
 
struct termios oldt, newt;

int main()
{
	if (! setlocale(LC_ALL, ""))
		perror("error locale"), exit(EXIT_FAILURE);
	wchar_t ** bd;
	size_t mark;
	char buff[256] = {0};
	wchar_t wcs[64] = L"";
	FILE * fo;

	const wint_t c_term = L'\n';
	wchar_t wch;
	wchar_t flag;
	wchar_t wchl[16];
	int i, j, l, m, z, dest;
	pid_t addr;
	char sbuffstr[256];

	tcgetattr(0, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON|ECHO);
	newt.c_cc[VMIN] = 4;
	newt.c_cc[VTIME] = 1;
	tcsetattr(0, TCSANOW, &newt);

	z = 0;
	m = 0;
        fo = fopen(".bd.txt", "r");
        while(!feof(fo))
        {
                fscanf(fo, "%*[^\n]\n");
                z++;
        }
        bd = (wchar_t **)malloc(z * sizeof(wchar_t*));
	rewind(fo);
        while(!feof(fo))
        {
//                fscanf(fo, "%255[^\t]%*[^\n]%*c\n", buff); 
                fscanf(fo, "%255[^\t]%*s\n", buff); 
                bd[m] = (wchar_t *)malloc(sizeof(wcs));
                mark = mbstowcs(wcs, buff, strlen(buff));
		if(!mark)
		{
			perror("!mbstowcs");
			tcsetattr(0, TCSANOW, &oldt);
			exit(EXIT_FAILURE);
		}
                wcsncpy(bd[m], wcs, wcslen(wcs));
                m++;
        }
        fclose(fo);	

start:	flag = L'a';
	j = 0;
	l = 0;
	dest = 0;
	for(i=0;i<16;i++)
		wchl[i] = L'\0';

	for(l=1; 1; l++)
	{
		if(j > 0)
			j = 0;
		wscanf(L"%lc", &wch);
		if(l == 1 || iswspace(flag))
			wch = towupper(wch);
		else if(iswprint(wch))
			wch = towlower(wch);
		flag = wch;
		if(wch == c_term)
			break;
		wcsncat(wchl, &wch, 1);

		for(i=0; i< z; i++)
		{
			if(! wcsncmp(bd[i], wchl, l))
			{
				wprintf(L"%ls\n", bd[i]);
				j++;
				dest = i;
			}
		}
		wprintf(L"%ls\n", wchl);
		if(j == 1)
			break;
		else if(j > 1)
			j = 0;
		else
		{
			wprintf(L"\e[1;1H\e[2J%ls\n\a", L"Не найдено или ошибка в наборе");
			if(!fork())
				execlp("spd-say", "spd-say", "-l", "ru", "Стой! Стрелять буду! Раапатый, разберись с ним", NULL);
			goto start;
		}
	}
	if(wch == c_term)
	{
		tcsetattr(0, TCSANOW, &oldt);
		for(;m>0; m--)
			free(bd[m-1]);
		free(bd);
		return 0;
	}
	wprintf(L"\e[1;1H\e[2J%ls %ls\a\n", bd[dest], L"Записано в реестр!");
	if(! (addr = fork()))
	{
		wscanf(L"%*[^\n]");
		wscanf(L"%*lc");
	}
	else
	{
		if(!fork())
		{
			wcstombs(sbuffstr, bd[dest], 255);
			execlp("spd-say", "spd-say", "-l", "ru", sbuffstr,  NULL);
		}
		sleep(1);
		kill(addr, 2);
	}	
	goto start;
}
