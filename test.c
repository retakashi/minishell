#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

volatile sig_atomic_t	g_sig;

void	sighandler(int signum)
{
	if(signum==SIGINT)
     exit(130);
     if(signum==SIGQUIT)
     exit(131);
}

void	sighandler2(int signum)
{
	if(signum==SIGINT)
	g_sig = SIGINT;
	if(signum==SIGQUIT)
	g_sig=SIGQUIT;
}


int	main(int argc,char **argv,char **envp)
{
	pid_t				pid;
	int					wstatus;
	struct sigaction	sa;
	char *args[10]={"cat",NULL};

	wstatus = 0;
	pid = fork();
	if (pid == 0)
	{
		sigemptyset(&sa.sa_mask);
		sa.sa_handler =sighandler ;
		if (sigaction(SIGQUIT, &sa, NULL) == -1)
			return (0);
		sa.sa_handler = sighandler;
		sa.sa_flags = SA_RESTART;
		if (sigaction(SIGINT, &sa, NULL) == -1)
			return (0);
		execve("/bin/cat",args,envp);
	}
	else
	{
        sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;
		sa.sa_handler = sighandler2;
		if (sigaction(SIGQUIT, &sa, NULL) == -1)
			return (0);
		sa.sa_handler = sighandler2;
		sa.sa_flags = SA_RESTART;
		if (sigaction(SIGINT, &sa, NULL) == -1)
			return (0);
		if (wait(&wstatus) < 0)
			perror("wait");
		printf("w %d\n",WIFSIGNALED(wstatus));
		printf("a %d\n",WTERMSIG(wstatus));
	}
	return (0);
}
