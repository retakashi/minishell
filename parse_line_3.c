/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:44:21 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/07 10:57:17 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	len_of_string(t_word_list *string)
{
	int	i;

	i = 0;
	while (string)
	{
		i++;
		string = string->next;
	}
	return (i);
}

void	one_string(t_word_list *string, t_env_list *env)
{
	if (string->flag >= 5 && string->flag < 10)
	{
		if (is_just_meta(string->word) == 5)
			printf("syntax error near unexpected token '%s'\n", string->word);
		else if (string->flag > 5 && string->flag < 10)
			printf("syntax error near unexpected token `newline'\n");
		free(env->env_value);
		env->env_value = malloc(sizeof (char) * (4));
		env->env_value = duplicate(env->env_value, "258", 3);
	}
	// exit(0);
}

void	command_error(t_word_list *string, t_env_list *env)
{
	if (string->next != NULL)
	{
		if (string->flag == 1 && (string->next->flag
			> 5 && string->next->flag < 10) && string->next->next == NULL)
		{
			printf("syntax error near unexpected token `newline'\n");
			free(env->env_value);
			env->env_value = malloc(sizeof (char) * (4));
			env->env_value = duplicate(env->env_value, "258", 3);
		}
		return ;
	}
	return ;
}

void	redirect_error(t_word_list *string, t_env_list *env)
{
	if (string->next != NULL)
	{
		if (string->flag > 5 && string->flag < 10)
			if (string->next->flag > 5 && string->next->flag < 10)
			{
				printf("syntax error near unexpected token '%s'\n", string->word);
				free(env->env_value);
				env->env_value = malloc(sizeof (char) * (4));
				env->env_value = duplicate(env->env_value, "258", 3);
			}
		return ;
	}
	return ;
}

void	last_error(t_word_list *string, t_env_list *env)
{
	if (string->next != NULL)
	{
		if (string->flag > 5 && string->flag < 10)
		{
			printf("syntax error near unexpected token `newline'\n");
			free(env->env_value);
			env->env_value = malloc(sizeof (char) * (4));
			env->env_value = duplicate(env->env_value, "258", 3);
		}
		return ;
	}
	return ;
}

t_word_list	*check_error(t_word_list *string, t_env_list *env)
{
	int			s_len;
	t_word_list	*tmp;

	tmp = string;
	s_len = len_of_string(string);
	if (s_len == 1 && string->flag != 0)
		one_string(string, env);
	while (string)
	{
		command_error(string, env);
		redirect_error(string, env);
		if (string->next == NULL)
			last_error(string, env);
		string = string->next;
	}
	return (tmp);
}