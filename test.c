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
		puts("error locale"), exit(1);

//	wchar_t wc[80] = L"ща";
//	wint_t ch = L'щ';
	wint_t terminate = L'\n';
	wchar_t wch;
	tcgetattr(0, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON|ECHO);
	newt.c_cc[VMIN] = 4;
	newt.c_cc[VTIME] = 1;
	tcsetattr(0, TCSANOW, &newt);
	while((wch = getwchar()) != terminate)
	{
		putwchar(wch);
		putwchar(terminate);
//		wprintf(L"%lc %d %zd\n", wch, wch, sizeof(wch));
	}
	tcsetattr(0, TCSANOW, &oldt);
	return 0;
}
