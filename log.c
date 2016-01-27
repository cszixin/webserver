#include "parse.h"
#include "wrap.h"

FILE* logfp=NULL;
pthread_mutex_t mutex;
void init_mutex()
{
    if(pthread_mutex_init(&mutex,NULL)) {
        writelog(ERROR,"log.c:init_mutex:pthread_mutex_init() error\n");
    }

}

void initlog(const char* logp)
{
	logfp=Fopen(logp,"a+");
}

static int getmonth(struct tm* local)   // return month index ,eg. Oct->10
{
	char buf[8];
	int i;
	static char *months[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sept","Oct","Nov","Dec"};

	strftime(buf,127,"%b",local);
	for(i=0;i<12;++i)
	{
		if(!strcmp(buf,months[i]))
			return i+1;
	}
	return 0;
}

void writetime()
{
	time_t timeval;
	char other[24];
	char year[8];
	char together[64];
	int month;

	(void)time(&timeval);
	struct tm *local=localtime(&timeval);

/* get year */
	strftime(year,7,"%Y",local);
/*get month */
	month=getmonth(local);
/*get other */
	strftime(other,23,"%d %H:%M:%S",local);
/*together all */
	sprintf(together,"\n%s/%d/%s\r\n",year,month,other);
    pthread_mutex_lock(&mutex);
	fwrite(together,strlen(together),1,logfp);
    pthread_mutex_unlock(&mutex);
}

char* timeModify(time_t timeval,char *time)
{
	char other[24];
	char year[8];
	int month;

	struct tm *local=localtime(&timeval);

/* get year */
	strftime(year,7,"%Y",local);
/*get month */
	month=getmonth(local);
/*get other */
	strftime(other,23,"%d %H:%M:%S",local);
/*together all */
	sprintf(time,"%s/%d/%s\r\n",year,month,other);
	return time;
}

void writelog(int level,const char* buf)
{
	time_t timeval;
	char other[24];
	char year[8];
	char together[64];
	int month;

	(void)time(&timeval);
	struct tm *local=localtime(&timeval);

/* get year */
	strftime(year,7,"%Y",local);
/*get month */
	month=getmonth(local);
/*get other */
	strftime(other,23,"%d %H:%M:%S",local);
	sprintf(together,"%s/%d/%s",year,month,other);
/*together all */
    char b[MAXLINE];
    char *s=NULL;
    switch(level){
        case INFO:
        s = "[INFO:] ";
        break;
        case WARNING:
        s = "[WARNING:] ";
        break;

        case DEBUG:
        s = "[DEBUG:] ";
        break;

        case ERROR:
        s = "[ERROR:] ";
        break;  
        
    }
    sprintf(b,"[%s]%s %s",together,s,buf);
    pthread_mutex_lock(&mutex);
	fwrite(b,strlen(b),1,logfp);
	fflush(logfp);
    pthread_mutex_unlock(&mutex);
}



