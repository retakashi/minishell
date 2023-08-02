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

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }

int	main()
{
	char *line;
	line=readline("prompt ");
	if(line[0]=='\0')
	printf("hello\n");
	else
	printf("p %p\n",line);
	return (0);
}
