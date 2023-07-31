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


int	get_pipe_2darr(int ***pipe_2darr, int pipe_cnt)
{
	int	i;

	*pipe_2darr = malloc(sizeof(int *) * (pipe_cnt));
	if (*pipe_2darr == NULL)
		return (1);
	i = 0;
	while (i < pipe_cnt)
	{
		(*pipe_2darr)[i] = malloc(sizeof(int) * 2);
		if(i==3)
		(*pipe_2darr)[i]=NULL;
		if ((*pipe_2darr)[i]==NULL)
		{
			while (i>0)
				free((*pipe_2darr)[i--]);
			free(*pipe_2darr);
			*pipe_2darr = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }

int	main(int argc, char **argv)
{
	int	**ans;

	ans=NULL;
	get_pipe_2darr(&ans,5);
	if (ans != NULL)
    {
        for (int i = 0; i < 5; i++)
        {
            free(ans[i]);
        }
        free(ans);
    }
	return (0);
}
