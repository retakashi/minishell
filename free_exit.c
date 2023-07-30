/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 23:01:19 by reira             #+#    #+#             */
/*   Updated: 2023/07/30 18:04:53 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

void	free_list_exit(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list)
{
	free_all_list(word_list, env_list, here_list);
	exit(EXIT_FAILURE);
}

void	perror_free_list_exit(char *str, t_word_list **word_list,
		t_env_list **env_list, t_here_list **here_list)
{
	ft_perror(str);
	free_all_list(word_list, env_list, here_list);
	exit(EXIT_FAILURE);
}

void	free_list_pipe2darr_exit(t_p_data p_data, t_word_list **word_list,
		t_env_list **env_list, t_here_list **here_list)
{
	free_int_2darr(&p_data.pipe_2darr, p_data.i);
	free_all_list(word_list, env_list, here_list);
	exit(EXIT_FAILURE);
}

void	free_char_2darr_exit(char ***arr, char ***arr2)
{
	free_char_2darr(arr);
	free_char_2darr(arr2);
	exit(EXIT_FAILURE);
}

void	perror_free_2darr_exit(char *err_msg, char ***arr, char ***arr2)
{
	ft_perror(err_msg);
	free_char_2darr(arr);
	free_char_2darr(arr2);
	exit(EXIT_FAILURE);
}
