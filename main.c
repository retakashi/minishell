/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:02:28 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/07 21:57:46 by sraza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include"minishell.h"



// void	parse_line(const char *line)
// {
// 	char	**line2;
// 	int		i;

// 	if (*line == '#' || line[strlen(line) - 1] == '|')
// 	{
// 		printf(" comment out or End with pipe!\n");
// 		return ;
// 	}
// 	i = 0;
// 	line2 = ft_split(line, ' ');
// 	while (line2[i] != NULL)
// 	{
// 		printf("line[%i] = %s \n", i, line2[i]);
// 		i++;
// 	}
// 	return ;
// }
/*
1　readlineで文字の受け取り　					　　<-できている

2  最初に検証するのはエラー処理						 <- 手をつけていない
	（””の数が偶数か、’’の数が偶数か、コメントアウトに対応するのか）
	エラーになる条件
	>対応しない文字がメタ文字として使用されているとき
	>””,''が奇数で文字列として認識ができないとき
	>?
	>?

3　メタ文字で区切っていく　　　								 <- 手をつけていない
	やり方のイメージ
		対象となる文字を洗い出す
		ここでスペースやパイプ等で区切る

echo "raza |" | echo '"reira"'
		
4　識別をして文字を区切る（3-4の種類の番号付きで識別する）　 　　<- 手をつけていない
	ここでは２で区切られた文字がword_listにあるので、それに番号をふる
	for example　（識別番号　対応文字）
	1 meta
	2 command
	3 words
		3-1 何にも区切られていない
		3-2 ""区切り
		3-3 ''区切り
	4 環境変数
	5 特殊文字　（これは課題読んで精査しないといけないかも）

5　parserで文字やコマンドとして組み立てる
   ここでの状態としてはもらえる値はそれぞれの値が分裂している状態
   それをもう一度確認しながら、上記の番号を振り分ける
   

*/




// int	main(void)
// {
// 	char	*line;

// 	rl_outstream = stderr;
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (line == NULL)
// 			break ;
// 		// TODO: intepret line as a command
// 		if (*line)
// 		{
// 			parse_line(line);
// 			add_history(line);
// 		}
// 		if (*line == '1')
// 		{
// 			free(line);
// 			break ;
// 		}
// 		free(line);
// 	}
// 	exit(0);
// }

t_word_list	*ft_newlst(void *content)
{
	t_word_list	*new;

	new = malloc(sizeof(t_word_list));
	if (new == NULL)
		return (NULL);
	new->word = content;
	new->next = NULL;
	return (new);
}

int	main(int argc, char **argv)
{
	char		**list;
	int			i;
	t_word_list	*string;
	t_word_list	*new;
	t_word_list	*tmp;

	i = 1;
	if (argc == 1)
		return (0);

	list = ft_split(argv, ' ');
	string = ft_newlst(list[0]);
	tmp = string;
	while (list[i] != NULL)
	{
		new = ft_newlst(list[i]);
		new->flag = i;
		string->next = new;
		string = new;
		i++;
	}
	while ()
	printf("%s \n", string->word);
	printf("%i \n", string->flag);
	return (0);
}


__attribute__((destructor))
static void destructor()
{
	system("leaks -q minishell");
}