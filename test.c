#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
 
struct termios oldt, newt;

int main()
{
	if (! setlocale(LC_ALL, ""))
		perror("error locale"), exit(EXIT_FAILURE);
	wchar_t bd[7][80] = {L"Антипов И С", L"Антипов П В", L"Антонов А С", L"Гузман М З", L"Звягин В Б", L"Язов А П", L"Нальгиев М В"};

	const wint_t c_term = L'\n';
	wchar_t wch;
	wchar_t flag;
	wchar_t wchl[16];
	int i, j, l, dest;
	char sbuffstr[256];

	tcgetattr(0, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON|ECHO);
	newt.c_cc[VMIN] = 4;
	newt.c_cc[VTIME] = 1;
	tcsetattr(0, TCSANOW, &newt);

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
		for(i=0; i< sizeof(bd)/sizeof(bd[0]); i++)
		{
			if(! wcsncmp(bd[i], wchl, l))
			{
				wprintf(L"%ls %ls\n", bd[i], wchl);
				j++;
				dest = i;
			}
		}
		if(j == 1)
			break;
		else if(j > 1)
			j = 0;
		else
		{
			wprintf(L"%ls\n\a", L"Не найдено или ошибка в наборе");
			usleep(100000);
//			break;
			goto start;
		}
		putwchar(c_term);
	}
//	putwchar(c_term);
	if(wch == c_term)
	{
		tcsetattr(0, TCSANOW, &oldt);
		return 0;
	}
	wprintf(L"%ls %ls\a\n", L"Всем пока!", bd[dest]);
	if(!fork())
	{
		wcstombs(sbuffstr, bd[dest], 255);
		execlp("spd-say", "spd-say", "-l", "ru", sbuffstr,  NULL);
	}
	goto start;
}
