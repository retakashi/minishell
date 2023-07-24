/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_outputput_operarion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:58:02 by reira             #+#    #+#             */
/*   Updated: 2023/07/22 18:17:41 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	find_filename_to_pipe(t_word_list *word_list)
{
	while (word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list->flag == input_file)
			return (true);
		if (word_list->flag == output_file)
			return (true);
		if (word_list->flag == append_file)
			return (true);
	}
	return (false);
}

int	in_output_operation(t_word_list *word_list, t_fd **fd_list,
		t_env_list **env_list)
{
	int	tmp_fd;

	tmp_fd = 0;
	if ((*fd_list)->here_file_name != NULL)
		tmp_fd = (*fd_list)->in_fd;
	while (word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list->flag == input_file)
			(*fd_list)->in_fd = get_fd(word_list->word, input_file);
		else if (word_list->flag == output_file)
			(*fd_list)->out_fd = get_fd(word_list->word, output_file);
		else if (word_list->flag == append_file)
			(*fd_list)->out_fd = get_fd(word_list->word, append_file);
		else if (word_list->flag == heredoc)
			(*fd_list)->in_fd = tmp_fd;
		if ((*fd_list)->in_fd < 0 || (*fd_list)->out_fd < 0)
			return (put_error_update_exit_status(word_list->word, env_list));
		word_list = word_list->next;
	}
	return (SUCCESS);
}
