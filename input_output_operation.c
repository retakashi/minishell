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

int	save_stdfd(int fd)
{
	int	save_fd;

	save_fd = dup(fd);
	if (save_fd < 0)
		return (FAILURE);
	if (close(fd) < 0)
		return (FAILURE);
	return (save_fd);
}

void	new_fd_node(t_fd **fd_node, int save_fd, int red_flg)
{
	*fd_node = malloc(sizeof(t_fd));
	if (*fd_node == NULL)
		put_error_exit("malloc");
	(*fd_node)->fd = save_fd;
	(*fd_node)->fd_flg = red_flg;
	(*fd_node)->next = NULL;
	(*fd_node)->prev = NULL;
}

void	get_fd_list_back(t_fd **fd_list)
{
	while ((*fd_list)->next != NULL)
		*fd_list = (*fd_list)->next;
}

void	get_fd_cnt(t_word_list *word_list, int red_flg, int *cnt)
{
	while (word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list->flag == red_flg)
			*cnt += 1;
		word_list = word_list->next;
	}
}

int	get_fd_arr(int **fd_arr, t_word_list *word_list, int red_flg, int *cnt)
{
	int	i;

	get_fd_cnt(word_list, red_flg, cnt);
	*fd_arr = malloc(sizeof(int) * (*cnt));
	if (*fd_arr == NULL)
		put_error_exit("malloc");
	i = 0;
	while (word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list->flag == red_flg)
		{
			(*fd_arr)[i] = get_fd(word_list->word, red_flg);
			printf("fd %d\n",(*fd_arr)[i]);
			if ((*fd_arr)[i] < 0)
				return (put_error(word_list->word, 0));
			i++;
		}
		word_list = word_list->next;
	}
	return (SUCCESS);
}

int	do_dup2_output(t_word_list *word_list, t_fd **fd_list)
{
	int		*fd_arr;
	int		cnt;
	int		save_fd;
	t_fd	*head;
	t_fd	*node;
	t_fd	*new;
	int		i;

	cnt = 0;
	i = 0;
	if (get_fd_arr(&fd_arr, word_list, output_file, &cnt) == FAILURE)
		return (FAILURE);
	if (*fd_list == NULL)
	{
		save_fd = save_stdfd(STDOUT_FILENO);
		new_fd_node(fd_list, save_fd, SAVE_STDOUT);
		if (dup2(fd_arr[i], STDOUT_FILENO) < 0)
			return (put_error("dup2", 0) < 0);
		if (close(fd_arr[i]) < 0)
			return (put_error("close", 0));
		i++;
		cnt--;
	}
	head = *fd_list;
	while (cnt > 0)
	{
		get_fd_list_back(fd_list);
		node = *fd_list;
		save_fd = save_stdfd(STDOUT_FILENO);
		if (save_fd < 0)
			return (put_error("dup", 0));
		new_fd_node(&new, save_fd, SAVE_STDOUT);
		new->prev = node;
		node->next = new;
		node = new;
		if (dup2(fd_arr[i], STDOUT_FILENO) < 0)
			return (put_error("dup2", 0));
		if(close(fd_arr[i]<0))
		return(put_error("close",0));
		cnt--;
		i++;
	}
	*fd_list = head;
	return (SUCCESS);
}

int	input_output_operation(t_word_list *word_list, t_fd **fd_list, int red_flg)
{
	if (red_flg == output)
		do_dup2_output(word_list, fd_list);
	// else if (red_flg == output)
	// 	do_dup2_output();
	// else
	// 	do_dup2_append();
	return (SUCCESS);
}
