/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:28:09 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/02 09:45:11 by razasharuku      ###   ########.fr       */
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
