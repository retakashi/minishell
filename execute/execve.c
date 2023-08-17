/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 21:31:45 by reira             #+#    #+#             */
/*   Updated: 2023/07/31 17:16:41 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute_cmd.h"

static char	*get_cmd_path(char **path, int i, char **cmd_argv, char **env_2darr)
{
	char	*slash_join;
	char	*cmd_join;

	slash_join = ft_strjoin(path[i], "/");
	if (slash_join == NULL)
	{
		free_char_2darr(&path);
		perror_free_2darr_exit("ft_strjoin", &env_2darr, &cmd_argv);
	}
	cmd_join = ft_strjoin(slash_join, cmd_argv[0]);
	if (cmd_join == NULL)
	{
		free(slash_join);
		free_char_2darr(&path);
		perror_free_2darr_exit("ft_strjoin", &env_2darr, &cmd_argv);
	}
	free(slash_join);
	return (cmd_join);
}

static char	**extract_path_from_env_2darr(char **env_2darr, char **cmd_argv)
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
		perror_free_2darr_exit("ft_split", &env_2darr, &cmd_argv);
	ft_strlcpy(ans[0], &ans[0][5], ft_strlen(&ans[0][5]) + 1);
	return (ans);
}

void	execve_cmd(char **env_2darr, char **cmd_argv)
{
	char	*cmd_path;
	char	**path;
	int		i;

	if (access(cmd_argv[0], X_OK) == 0 && execve(cmd_argv[0], cmd_argv,
			env_2darr) < 0)
		perror_free_2darr_exit("execve", &env_2darr, &cmd_argv);
	path = extract_path_from_env_2darr(env_2darr, cmd_argv);
	i = 0;
	while (path[i] != NULL)
	{
		cmd_path = get_cmd_path(path, i, cmd_argv, env_2darr);
		if (access(cmd_path, X_OK) == 0 && execve(cmd_path, cmd_argv,
				env_2darr) < 0)
		{
			free(cmd_path);
			perror_free_2darr_exit("execve", &env_2darr, &cmd_argv);
		}
		free(cmd_path);
		i++;
	}
	command_error(cmd_argv[0]);
	free_char_2darr(&env_2darr);
	free_char_2darr(&cmd_argv);
	exit(127);
}
