#include "fastlog.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define _POSIX_C_SOURCE 200809L
#include <sys/time.h>
struct entry {
    pid_t pid;
    struct timespec time;
    LEVEL lvl; 
    char message[MAX_MSG_LENGTH+1];
}entry;
struct entry buffer[MAX_LOG_ENTRY];
int oldest;

void fastlog_init(void)
{
    //buffer = (struct entry *)malloc(sizeof(struct entry)*MAX_LOG_ENTRY);
	oldest = 0;
}


void fastlog_write(LEVEL lvl, char *text)
{
	/*
    HINT: 
    Don't forget that you should be copying stuff!!!
    String assignments in C don't work the same as in 
    java.
     */
	//printf("%d ", oldest);
	struct entry e1 = { .pid = getpid(), .lvl = lvl};
	size_t size = MAX_MSG_LENGTH;
	if(text != NULL)
		strncpy ( e1.message, text, size);
	else
	{
		char * m = "";
		strcpy(e1.message,m);
	}
	if(text && strlen(text) >= MAX_MSG_LENGTH)
		e1.message[MAX_MSG_LENGTH] = '\0';
	//printf("%s\n",e1.message);
	//clock_gettime(CLOCK_REALTIME,&e1.time);
	buffer[oldest] = e1;
	if(oldest < MAX_LOG_ENTRY-1)
		oldest++;
	else
		oldest = 0;
}
void fastlog_dump(void)
{
	//printf("[%d]-[%s]-[%d]-<%s>",,,,);
	int i = oldest;
	printf("\n[%d]-[timestamp]-[%d]-<%s>",buffer[i].pid,buffer[i].lvl,buffer[i].message);
	if(i < MAX_LOG_ENTRY-1)
		i++;
	else
		i = 0;
	while(i!=oldest)
	{
		
		printf("\n[%d]-[timestamp]-[%d]-<%s>",buffer[i].pid,buffer[i].lvl,buffer[i].message);
		
		if(i < MAX_LOG_ENTRY-1)
			i++;
		else
			i = 0;
	}
}