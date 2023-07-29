#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// typedef struct s_data
// {
//     char **arg;
// } t_data;

void	test(char **ans)
{
	// data.argが指すポインタが3つの要素を持つ配列を解放
	for (int i = 0; i < 3; i++)
	{
		free(ans[i]);
	}
	// data.argが指すポインタが2つの要素を持つ配列を解放
	free(ans);
	ans = NULL;
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }

int	main(int argc, char **argv)
{
	char	**ans;
	int		i;

	i = 0;
	ans = calloc(3, sizeof(char *));
	while (i < 2)
	{
		ans[i] = strdup("hello");
		i++;
	}
	test(ans);
    // printf("%s\n",ans[0]);
	return (0);
}
