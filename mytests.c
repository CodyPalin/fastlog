#include "fastlog.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main (void)

{
	fastlog_init();
	for(int i = 0; i<MAX_LOG_ENTRY+20; i++)
	{
		
		char test[16];;
		//char num[16];
		//itoa(i, num, 10);
		snprintf(test, 16, "test%d", i);
		fastlog_write(rand() % 3, test);
	}
	fastlog_write(rand() % 3, NULL);
    fastlog_write(rand() % 3, "test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 test14 test15 test16");
    fastlog_dump();
	return 0;
}