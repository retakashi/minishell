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
#include <unistd.h>

void	signal_handler(int sig_num)
{
	if (sig_num == SIGINT)
		write(1, "\n", 1);
	if (sig_num == SIGQUIT)
    {
        write(1, "exit\n", 5);
        exit(EXIT_SUCCESS);
    }
}

int	main(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT,signal_handler ) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
	while (1)
	{

	}
	return (0);
}
