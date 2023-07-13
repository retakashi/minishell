/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:28:09 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/13 13:36:11 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// bool is_alpha(char )
// {

// }

bool	is_argument(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '"' && str[ft_strlen(str - 1)] == '"')
		return (true);
	if (str[i] == '\'' && str[ft_strlen(str - 1)] == '\'')
		return (true);
	return (false);
}

char	*is_meta_in_arguments(char *str)
{
	t_flags	flag;
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		flag = is_meta(str[i]);
		if (flag)
			break;
		i++;
		str++;
	}
	return (str);
}


bool	is_meta(char *str)
{
	t_flags	meta_num;

	meta_num = 0;

	if (ft_strncmp(str, '|', ft_strlen(str)))
		meta_num = pipe_char;
	if (ft_strncmp(str, '>', ft_strlen(str)))
		meta_num = great;
	if (ft_strncmp(str, ">>", ft_strlen(str)))
		meta_num = great_great;
	if (ft_strncmp(str, '<', ft_strlen(str)))
		meta_num = less;
	if (ft_strncmp(str, "<<", ft_strlen(str)))
		meta_num = less_less;
	return (meta_num);
}