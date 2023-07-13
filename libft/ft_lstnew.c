/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:36:17 by rtakashi          #+#    #+#             */
/*   Updated: 2023/02/12 17:48:51 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ndptr;

	ndptr = malloc(sizeof(t_list));
	if (ndptr == NULL)
		return (NULL);
	ndptr->content = content;
	ndptr->next = NULL;
	return (ndptr);
}
