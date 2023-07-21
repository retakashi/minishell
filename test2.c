# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int main()
{
   int fd;
   int fd2;
   fd=open("file1",O_RDWR);
//    if(dup2(fd,10)<0)
//    printf("error1\n");
   fd2=open("file2",O_RDWR);
//    if(dup2(fd2,11)<0)
//    printf("error3\n");
   if(dup2(STDOUT_FILENO,12)<0)
   printf("error4\n");
   if(dup2(fd,STDOUT_FILENO)<0)
   printf("error5\n");
   if(close(fd)<0)
   printf("error6\n");
    if(dup2(fd2,STDOUT_FILENO)<0)
   printf("error7\n");
   if(close(fd2)<0)
   printf("error8\n");
   write(STDOUT_FILENO,"hello\n",strlen("hello\n"));
   dup2(12,STDOUT_FILENO);
   if(close(12)<0)
   printf("error9\n");
    write(STDOUT_FILENO,"hello2\n",strlen("hello2\n"));
    return(0);
}
