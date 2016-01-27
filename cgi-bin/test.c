#include <stdio.h>  
#include <stdlib.h>  
  
int main(void)  
{  
    char *data;  
    char query_env[255];
    long m=0,n=0;  
    //sprintf(query_env,"QUERY_STRING=%s\n","m=3&n=4");
    //printf("%s\n",query_env);
   // putenv(query_env);
    data = getenv("QUERY_STRING");  
    //printf("data:%s\n",data);
    printf("Content-type:text/html\n\n");
    printf("<div align='center'><h1> This is CGI Program which will return the sum of two numbers </h1></div>");

    sscanf(data,"m=%d&n=%d",&m,&n);
    printf("<div style='text-align:center'><h2>number is %d&%d</h2></div>",m,n);
    if(data == NULL)  
        printf("<p>错误！数据没有被输入或者数据传输有问题\n");  
    else if(sscanf(data,"m=%d&n=%d",&m,&n) != 2)  
        printf("<p>错误！输入数据非法。表单中输入的必须是数字。\n");  
    else  
        printf("<div align='center'><h2>%d+%d=%d\n</h2></div>",m,n,m+n);  
    return 0;  
}  
