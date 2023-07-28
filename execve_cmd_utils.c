/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:36:48 by reira             #+#    #+#             */
/*   Updated: 2023/07/28 13:53:47 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

char	**extract_path_from_env_2darr(char **env_2darr)
{
	char	**ans;
	int		i;

	if (env_2darr == NULL)
		return (NULL);
	i = 0;
	while (env_2darr[i] != NULL && ft_strncmp("PATH=", env_2darr[i], 5) != 0)
		i++;
	if (env_2darr[i] == NULL)
		return (NULL);
	ans = ft_split(env_2darr[i], ':');
	if (ans == NULL)
		put_error_exit("failed to extract_path_from_env_2darr");
	ft_strlcpy(ans[0], &ans[0][5], ft_strlen(&ans[0][5]) + 1);
	return (ans);
}

void	get_cmdpath_execve(t_word_list *word_list, char **env_2darr)
{
	char	**path;
	char	**cmd_argv;
	int		i;
	char	*join_path;
	char	*join_cmd;

	path = extract_path_from_env_2darr(env_2darr);
	cmd_argv = get_cmd_argv(word_list);
	i = 0;
	while (path[i] != NULL)
	{
		join_path = ft_strjoin(path[i], "/");
		if (join_path == NULL)
			put_error_exit("failed to ft_strjoin");
		join_cmd = ft_strjoin(join_path, cmd_argv[0]);
		if (join_cmd == NULL)
			put_error_exit("failed to ft_strjoin");
		if (access(join_cmd, X_OK) == 0 && execve(join_cmd, cmd_argv,
				env_2darr) < 0)
			put_error_exit("execve");
		i++;
	}
	if (path[i] == NULL)
		command_error(cmd_argv[0]);
	exit(127);
}

void	get_pipe_2darr(int ***pipe_2darr, size_t pipe_cnt)
{
	size_t	i;

	i = 0;
	*pipe_2darr = malloc(sizeof(int *) * pipe_cnt);
	if (*pipe_2darr == NULL)
		return ;
	while (i < pipe_cnt)
	{
		(*pipe_2darr)[i] = malloc(sizeof(int) * 2);
		if ((*pipe_2darr)[i] == NULL)
		{
			i = 0;
			while ((*pipe_2darr)[i] != NULL)
				free((*pipe_2darr)[i++]);
			free(*pipe_2darr);
			*pipe_2darr = NULL;
			return ;
		}
		i++;
	}
}
