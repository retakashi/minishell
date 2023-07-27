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

void get_pipe_2darr(int ***pipe_2darr,size_t pipe_cnt)
{
	size_t i;

	i=0;
	*pipe_2darr=(int**)malloc(sizeof(int*)*pipe_cnt);
	if(*pipe_2darr==NULL)
	return;
	while(i<pipe_cnt)
	{
		(*pipe_2darr)[i]=(int*)malloc(sizeof(int)*2);
		if((*pipe_2darr)[i]==NULL)
		{
			i=0;
			while((*pipe_2darr)[i]!=NULL)
				free((*pipe_2darr)[i++]);
			free(*pipe_2darr);
			*pipe_2darr=NULL;
			return;
		}
		i++;
	}
}

void first(int *p,char **envp)
{
    char *argv[5]={"ls","-l",NULL};
    int fd;
    fd=open("file1",O_RDWR);
    dup2(p[1],STDOUT_FILENO);
    close(p[1]);
    close(p[0]);
    dup2(fd,STDOUT_FILENO);
    close(fd);
    execve("/bin/ls",argv,envp);
}

void last(int *p,char **envp)
{
    int fd;
    char *argv[5]={"cat",NULL};
     fd=open("file1",O_RDWR);
    dup2(p[0],STDIN_FILENO);
    close(p[0]);
    close(p[1]);
    dup2(fd,STDOUT_FILENO);
    close(fd);
   execve("/bin/cat",argv,envp); 
}

void middle(int *prev,int *p,char **envp)
{
     int fd=open("file3",O_RDWR);
    char *argv[5]={"ls","-l",NULL};
    dup2(prev[0],STDIN_FILENO);
    close(prev[1]);
    close(prev[0]);
    dup2(p[1],STDOUT_FILENO);
    close(p[1]);
    close(p[0]);
     dup2(fd,STDOUT_FILENO);
     close(fd);
   execve("/bin/ls",argv,envp); 
}

void parent(int *arr)
{
    
}

int main(int argc,char **argv,char **envp)
{
   int **arr;
   int i;
   pid_t pid;
   get_pipe_2darr(&arr,2);
   i=0;
   while(i<3)
   {
    if(i<2)
    pipe(arr[i]);
    pid=fork();
    if(pid==0)
    {
        if(i==0)
        first(arr[i],envp);
        else if(i==2)
        last(arr[i-1],envp);
        else
        middle(arr[i-1],arr[i],envp);
    }
    else
    {
        if(i>0&&i<2)
        {
        close(arr[i-1][0]);
    close(arr[i-1][1]);
    wait(NULL);
        }
   else
   wait(NULL);
   }
   i++;
}
return(0);
}
