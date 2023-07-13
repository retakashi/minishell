/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:40:12 by rtakashi          #+#    #+#             */
/*   Updated: 2023/02/26 19:28:45 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*frontlst;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	frontlst = ft_lstnew((*f)(lst->content));
	if (frontlst == NULL)
		return (NULL);
	lst = lst->next;
	while (lst != NULL)
	{
		newlst = ft_lstnew((*f)(lst->content));
		if (newlst == NULL)
		{
			ft_lstclear(&frontlst, del);
			return (NULL);
		}
		ft_lstadd_back(&frontlst, newlst);
		lst = lst->next;
	}
	return (frontlst);
}
