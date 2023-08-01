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

int		g_sig_num;

void	signal_handler(int sig)
{
	g_sig_num = sig;
	signal(sig, SIG_DFL);
}

int	main(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		perror("signal");
		exit(0);
	}
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
	{
		perror("signal");
		exit(0);
	}
	fprintf(stderr, "hogehoge\n");
	while (1)
	{
		sleep(1);
		fprintf(stderr, "g_sig %d\n", g_sig_num);
	}
	return (0);
}
