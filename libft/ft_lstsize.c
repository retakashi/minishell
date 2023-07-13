/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:12:55 by rtakashi          #+#    #+#             */
/*   Updated: 2023/02/12 20:42:09 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		cnt;
	t_list	*node;

	if (lst == NULL)
		return (0);
	if (lst->next == NULL)
		return (1);
	cnt = 0;
	node = lst;
	while (node != NULL)
	{
		node = node->next;
		cnt++;
	}
	return (cnt);
}
