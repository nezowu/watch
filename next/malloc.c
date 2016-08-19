#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	char buff1[12] = "hello world";
	char buff2[12] = "good by";
	char **wbuff;
	wbuff = (char **)malloc(2);
	wbuff[0] = (char *)malloc(12);
	wbuff[1] = (char *) malloc(12);
	strncpy(wbuff[0], buff1, 12);
	strncpy(wbuff[1], buff2, 12);
	printf("%zd\n", sizeof(wbuff));
	printf("%s\n", wbuff[0]);
	printf("%s\n", wbuff[1]);
	return 0;
}
