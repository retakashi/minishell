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

int	main(void)
{
	unlink("file1");
	if(access("file1",F_OK)==0)
	printf("あるよ\n");
	else
	printf("ないよ\n");
	return (0);
}
