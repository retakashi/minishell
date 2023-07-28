/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:33:52 by reira             #+#    #+#             */
/*   Updated: 2023/07/28 17:34:28 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

static bool	check_sign(char c, int *neg)
{
	if (c == '-')
		*neg = 1;
	if (c != '+' && c != '-')
		return (false);
	return (true);
}

static bool	is_within_long(long long num, char c, int neg)
{
	if ((neg == 0 && num > LONG_MAX / 10) || (neg == 0 && num == LONG_MAX / 10
			&& (c - '0') > LONG_MAX % 10))
		return (false);
	if ((neg == 1 && num > LONG_MIN / 10 * -1) || (neg == 1 && num == LONG_MIN
			/ 10 * -1 && (c - '0') > LONG_MIN % 10 * -1))
		return (false);
	return (true);
}

long long	ft_atoll(char *str, int *error_flg)
{
	long long	num;
	size_t		i;
	int			neg;

	num = 0;
	i = 0;
	neg = 0;
	if (check_sign(str[i], &neg) == true)
		i++;
	while (str[i] != '\0')
	{
		if (is_within_long(num, str[i], neg) == false)
		{
			*error_flg = 1;
			return (-1);
		}
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (neg == 1)
		num *= -1;
	return (num);
}
