/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:46 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/16 00:33:30 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	remove_node(t_env_list **env_list,t_env_list *tmp)
{
	t_env_list *head;
	t_env_list	*prev;

	head=*env_list;
	prev=*env_list;
	if(head==tmp)
	head=(*env_list)->next;
	while(*env_list!=NULL&&ft_strcmp((*env_list)->env_name,tmp->env_name)!=0)
	{
		prev=*env_list;
		*env_list=(*env_list)->next;
	}
	if((*env_list)->next==NULL)
	prev->next=NULL;
	else
	prev->next=(*env_list)->next;
	free((*env_list)->env_name);
	free((*env_list)->env_str);
	free(env_list);
	*env_list=head;
}

void	unset_cmd(t_word_list **word_list ,t_env_list **env_list)
{
	t_env_list *head;
	t_env_list *tmp;
	
	head=*env_list;
	if (*env_list == NULL)
		return ;
	if (search_env_name((*word_list)->word, env_list) == false)
		return ;
	tmp=*env_list;
	*env_list=head;
	remove_node(env_list,tmp);
	// export_nooption();
}
