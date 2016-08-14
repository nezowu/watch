#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>
 
struct termios oldt, newt;

int main()
{
	if (! setlocale(LC_ALL, "ru_RU.utf8"))
		perror("error locale"), exit(EXIT_FAILURE);
	wchar_t bd[5][80] = {L"антипов и. с.", L"антонов а. с.", L"гузман м. з.", L"звягин в. б.", L"язов а. п."};
	const wint_t c_term = L'\n';
	wchar_t wch;
	wchar_t wchl[16] = L"";
	int i;
	int j = 0;
	int l = 0;
	int dest = 0;

	tcgetattr(0, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON|ECHO);
	newt.c_cc[VMIN] = 4;
	newt.c_cc[VTIME] = 1;
	tcsetattr(0, TCSANOW, &newt);

	for(l=1; 1; l++)
	{
		if(j > 0)
			j = 0;
		wscanf(L"%lc", &wch);
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
		putwchar(c_term);
	}
	putwchar(c_term);
	wprintf(L"%ls %ls\n", L"Всем пока!", bd[dest]);
	tcsetattr(0, TCSANOW, &oldt);
	return 0;
}
