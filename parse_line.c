/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:39:25 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/28 20:59:26 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"execve_cmd.h"
#include"libft/libft.h"

int	check_sp(char *line)
{
	int	i;
	int	len;

	len = ft_strlen(line);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (i == len)
		return (1);
	return (0);
}

t_word_list	*parse_line(char *line)
{
	t_word_list	*string;

	if (check_sp(line))
		return (NULL);
	/*ここに環境変装の展開を入れるgetenvにするかリスト型で持つかあとで決める
		mallocして文字列の長さを変えていくようにする
	*/
	string = make_list(line);
	string = set_flags(string);
	// print_words(tmp);
	return(string);
}

// void	print_words(t_word_list *string)
// {
// 	while (string != NULL)
// 	{
// 		printf("string->word = %s , string->flag = %i \n", string->word, string->flag);
// 		string = string->next;
// 	}
// 	return ;
// }