/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 20:16:20 by sraza             #+#    #+#             */
/*   Updated: 2023/08/11 22:10:15 by sraza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_error(t_word_list *string, t_env_list **env)
{
	printf("syntax error near unexpected token '%s'\n", string->word);
	free((*env)->env_value);
	(*env)->env_value = malloc(sizeof (char) * (4));
	(*env)->env_value = duplicate((*env)->env_value, "258", 3);
	return (FAILURE);
}
