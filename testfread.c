#include <stdio.h>
#include <string.h>
 
int main()
{
   FILE *fp;
   char c[] = "This is runoob";
   char buffer[20];
   size_t ret_code;
 
   /* 打开文件用于读写 */
   fp = fopen("file.txt", "w+");
 
   /* 写入数据到文件 */
   fwrite(c, strlen(c) + 1, 1, fp);
 
   /* 查找文件的开头 */
   fseek(fp, 0, SEEK_SET);
 
   /* 读取并显示数据 */
   ret_code =  fread(buffer, strlen(c)+1, 1, fp);
   printf("%d\n", ret_code);
   printf("%s\n", buffer);
   fclose(fp);
   
   return(0);
}