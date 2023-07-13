/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 00:16:35 by reira             #+#    #+#             */
/*   Updated: 2023/07/12 18:03:49 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

//argv[0]->export
//argv[1]->aaa=hello

t_envp	*g_envp_list;

int	search_same_name(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (FALSE);
	s1_len = get_len(s1, NAME);
	s2_len = get_len(s2, NAME);
	if (s1_len == s2_len && !ft_strncmp(s1, s2, s1_len))
		return (TRUE);
	return (FALSE);
}

void	is_envp_name(char *argv, int *flg, t_envp **update_node)
{
	t_envp	*head;

	head = g_envp_list;
	while (g_envp_list != NULL)
	{
		if (search_same_name(argv, g_envp_list->envp_name) == TRUE)
		{
			*flg = UPDATE;
			*update_node = g_envp_list;
			break ;
		}
		g_envp_list = g_envp_list->next;
	}
	g_envp_list = head;
}

int	is_shell_variable(char *argv, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (search_same_name(argv, envp[i]) == FALSE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	add_envp_list(char *argv, char **envp)
{
	t_envp	*new;
	t_envp	*head;

	head = g_envp_list;
	new = NULL;
	new_node(&new, argv);
	if (is_shell_variable(argv, envp) == TRUE)
		new->shell_variable = TRUE;
	while (g_envp_list->next != NULL)
		g_envp_list = g_envp_list->next;
	g_envp_list->next = new;
	g_envp_list = head;
}

void	envp_str_update(char *argv, t_envp **update_node)
{
	size_t	name_len;
	size_t	str_len;

	if (!ft_strchr(argv, '='))
		return ;
	name_len = get_len(argv, NAME);
	str_len = get_len(&argv[name_len + 1], STR);
	free((*update_node)->envp_str);
	(*update_node)->envp_str = malloc(sizeof(char) * (str_len + 1));
	if ((*update_node)->envp_str == NULL)
		perror_free_2d_arr_exit("malloc",NULL,NULL);
	ft_strlcpy((*update_node)->envp_str, &argv[name_len + 1], str_len + 1);
}

void	export_cmd(char **argv, char **envp)
{
	t_envp	*update_node;
	int		flg;
	size_t	i;

	if (argv[1] == NULL)
		export_nooption();
	else
	{
		i = 1;
		while (argv[i] != NULL)
		{
			update_node = NULL;
			flg = ADD;
			is_envp_name(argv[i], &flg, &update_node);
			if (update_node != NULL && flg == UPDATE)
				envp_str_update(argv[i], &update_node);
			else
				add_envp_list(argv[i], envp);
			i++;
		}
		// export_nooption();
	}
}
