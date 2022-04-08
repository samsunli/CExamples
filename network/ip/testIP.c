#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

int main(int aargc, char* argv[])
{
         struct in_addr addr1,addr2;
         unsigned long l1,l2;
         l1= inet_addr("192.168.0.74");
         l2 = inet_addr("211.100.21.179");
         memcpy(&addr1, &l1, 4);
         memcpy(&addr2, &l2, 4);

         printf("%s : %s \n", inet_ntoa(addr1), inet_ntoa(addr2));    //注意这一句的运行结果

         printf("%s \n", inet_ntoa(addr1));
         printf("%s \n", inet_ntoa(addr2));
         return 0;
}