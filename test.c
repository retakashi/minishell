#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	test2(char **str)
{
	free(*str);
    *str=NULL;
    printf("str %p\n", *str);
}

void	test(char **str)
{
	test2(str);
	printf("str %p\n", *str);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }

int	main(void)
{
	char	*str;

	str = strdup("hello\n");
    printf("str %s\n", str);
	test(&str);
	printf("str %p\n", str);
	printf("`\n");
	return (0);
}
