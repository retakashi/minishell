/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:49:00 by reira             #+#    #+#             */
/*   Updated: 2023/07/25 23:40:03 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	new_fd_node(t_fd_list **node,
					int i)
{
	*node = malloc(sizeof(t_fd_list));
	if (*node == NULL)
		put_error_exit("failed to new_fd_node");
	(*node)->in_fd = STDIN_FILENO;
	(*node)->out_fd = STDOUT_FILENO;
	(*node)->here_file_name = NULL;
	(*node)->pipe_cnt = i;
	(*node)->next = NULL;
}

void add_new_fd_node(t_fd_list **fd_list,int i)
{
	t_fd_list *new;
	t_fd_list *head;
	
	new=NULL;
	new_fd_node(&new,i);
	head=*fd_list;
	while((*fd_list)->next!=NULL)
		*fd_list=(*fd_list)->next;
	(*fd_list)->next=new;
	*fd_list=head;
}

void	update_fd_node(t_fd_list **fd_list, int i, int *here_flg)
{
	t_fd_list	*head;

	*here_flg = true;
	head = *fd_list;
	while (*fd_list != NULL && (*fd_list)->pipe_cnt == 0)
		*fd_list = (*fd_list)->next;
	(*fd_list)->pipe_cnt = i;
	*fd_list = head;
}

void	get_fd_list(t_word_list *word_list, t_fd_list **fd_list, int pipe_cnt)
{
	int	i;
	int	here_flg;

	if (*fd_list == NULL)
		new_fd_node(fd_list, 0);
	i = 0;
	while (i < pipe_cnt)
	{
		here_flg = false;
		while (word_list != NULL && word_list->flag != pipe_char)
		{
			if (word_list != NULL && word_list->flag == heredoc)
				update_fd_node(fd_list, i, &here_flg);
			word_list = word_list->next;
		}
		if (here_flg == false)
			add_new_fd_node(fd_list, i);
		if (word_list != NULL && word_list->flag == pipe_char)
			word_list = word_list->next;
		i++;
	}
}
