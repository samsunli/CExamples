 #include <stdio.h>
 #include <string.h>
#include <time.h>

int main()
{
    time_t timep;   
    struct tm *p; 
    struct tm *p2;
   
    time(&timep);   
    p = localtime(&timep);
    localtime_r(&timep, p2);
   
    printf("%d-%d-%d %d:%d:%d\n", (1900 + p->tm_year), ( 1 + p->tm_mon), p->tm_mday,
                                p->tm_hour, p->tm_min, p->tm_sec); 

    printf("%d-%d-%d %d:%d:%d\n", (1900 + p2->tm_year), ( 1 + p2->tm_mon), p2->tm_mday,
                                p2->tm_hour, p2->tm_min, p2->tm_sec);                                

   return 0;
}