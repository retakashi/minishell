/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:14:41 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/26 12:41:36 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "execve_cmd.h"

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

static long long	ft_atoll(char *str, int *error_flg)
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

static bool	is_valid_number(char *word, long long *num)
{
	size_t	i;
	int		error_flg;

	if (word[0] == '\0')
		return (false);
	i = 0;
	error_flg = 0;
	if (word[i] == '-' || word[i] == '+')
		i++;
	if (word[i] == '\0' || !ft_isdigit(word[i]))
		return (false);
	while (word[i] != '\0')
	{
		if (word[i] != '\0' && !ft_isdigit(word[i]))
			return (false);
		i++;
	}
	*num = ft_atoll(word, &error_flg);
	if (error_flg == 1)
		return (false);
	return (true);
}

void	exit_cmd(t_word_list *word_list)
{
	long long	num;

	if (word_list->next == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	num = 0;
	word_list = word_list->next;
	if (is_valid_number(word_list->word, &num) == false)
	{
		exit_error(word_list->word);
		exit(2);
	}
	if (num > 255 || num < -255)
		num = num % 256;
	if (num < 0)
		num += 256;
	if (num == 0)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	else
		ft_putstr_fd("exit\n", STDERR_FILENO);
	exit((int)num);
}
