/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:23:44 by rtakashi          #+#    #+#             */
/*   Updated: 2023/02/08 18:02:36 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_casted_putnbr(unsigned int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_casted_putnbr((unsigned int)-n, fd);
	}
	else
		ft_casted_putnbr(n, fd);
}

static void	ft_casted_putnbr(unsigned int n, int fd)
{
	if (n > 9)
	{
		ft_casted_putnbr(n / 10, fd);
		ft_casted_putnbr(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int	i;

// 	i = -1;
// 	ft_putnbr_fd(i, 1);
// 	return (0);
// }
