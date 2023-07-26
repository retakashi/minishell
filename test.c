/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:05 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/26 15:08:03 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_word_list
{
	struct s_word_list	*next;
	char				*word;
	int					flag;
}						t_word_list;

typedef enum e_flags
{
	command,
	option,
	arguments,
	env,
	pipe_char,
	output,
	append,
	input,
	heredoc,
	meta_char,
	output_file,
	input_file,
	append_file,
	eof_num
}						t_flags;

static	int	check_sep(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

static	int	count_str(char *str, char charset)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		while (*str != '\0' && check_sep(*str, charset) == 1)
			str++;
		if (*str != '\0')
			count++;
		while (*str != '\0' && check_sep(*str, charset) == 0)
			str++;
	}
	return (count);
}

static	char	*add_str(char *str, char charset)
{
	int		i;
	int		add_count;
	char	*add;

	i = 0;
	add_count = 0;
	while (str[add_count] && check_sep(str[add_count], charset) == 0)
		add_count ++;
	add = malloc(sizeof(char) * (add_count + 1));
	if (add == NULL)
		return (NULL);
	while (i < add_count)
	{
		add[i] = str[i];
		i++;
	}
	add[i] = '\0';
	return (add);
}

static	void	*ft_free(char **result)
{
	size_t	i;

	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		result[i] = NULL;
		i++;
	}
	free(result);
	result[i] = NULL;
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**result;

	i = 0;
	if (s == NULL)
		return (NULL);
	result = malloc(sizeof(char *) * (count_str((char *)s, c) + 1));
	if (result == NULL)
		return (NULL);
	while (*s != '\0')
	{
		while (*s != '\0' && check_sep(*s, c) == 1)
			s++;
		if (*s != '\0')
		{
			result[i] = add_str((char *)s, c);
			if (result[i++] == NULL)
				return (ft_free(result));
		}
		while (*s != '\0' && check_sep(*s, c) == 0)
			s++;
	}
	result[i] = NULL;
	return (result);
}

void	new_word_node(t_word_list **node, char *argv)
{
	*node = malloc(sizeof(t_word_list));
	(*node)->next = NULL;
	(*node)->flag = arguments;
	if (!strncmp(argv, "<", 2))
		(*node)->flag = input;
	else if (!strncmp(argv, ">", 2))
		(*node)->flag = output;
	else if (!strncmp(argv, ">>", 3))
		(*node)->flag = append;
	else if (!strncmp(argv, "<<", 3))
		(*node)->flag = heredoc;
	else if (!strncmp(argv, "|", 2))
		(*node)->flag = pipe_char;
	(*node)->word = strdup(argv);
}

void	get_word_list(t_word_list **head, char *line)
{
	t_word_list	*new;
	t_word_list	*node;
	size_t		i;
	char		**argv;

	i = 0;
	argv = ft_split(line, ' ');
	new_word_node(&node, argv[i]);
	i++;
	*head = node;
	while (argv[i] != NULL)
	{
		new_word_node(&new, argv[i]);
		if (node->flag == output)
			new->flag = output_file;
		else if (node->flag == input)
			new->flag = input_file;
		else if (node->flag == heredoc)
			new->flag = eof_num;
		else if (node->flag == append)
			new->flag = append_file;
		node->next = new;
		node = new;
		i++;
	}
	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

bool	is_inequality_sign(int flag)
{
	if (flag == output_file || flag == input_file || flag == append_file
		|| flag == eof_num)
		return (true);
	return (false);
}

void	is_command(t_word_list **head)
{
	if (*head == NULL)
		return ;
	if ((*head)->flag == arguments)
		(*head)->flag = command;
	else if (is_inequality_sign((*head)->flag == true))
	{
		while ((*head != NULL && (*head)->next != NULL)
			&& (is_inequality_sign((*head)->flag) != true))
			*head = (*head)->next->next;
		if ((*head)->flag == arguments)
			(*head)->flag = command;
	}
}

void	get_command(t_word_list **head)
{
	t_word_list	*tmp;

	tmp = *head;
	is_command(head);
	while (*head != NULL)
	{
		*head = (*head)->next;
		while (*head != NULL && (*head)->flag != pipe_char)
			*head = (*head)->next;
		if ((*head) != NULL && (*head)->flag == pipe_char)
		{
			*head = (*head)->next;
			is_command(head);
		}
	}
	*head = tmp;
}

int	cnt_cmd_argv(t_word_list *word_list)
{
	int	cnt;

	cnt = 0;
	while (word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list->flag == command || word_list->flag == option
			|| word_list->flag == arguments)
			cnt++;
		word_list = word_list->next;
	}
	return (cnt);
}

char	**get_cmd_argv(t_word_list *word_list)
{
	char	**ans;
	int		cnt;
	int		i;

	cnt = cnt_cmd_argv(word_list);
	ans = calloc(cnt + 1, sizeof(char *));
	if (ans == NULL)
		perror("failed to get_cmd_argv");
	i = 0;
	while (i < cnt && word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list->flag == command)
			ans[i] = strdup(word_list->word);
		else if (word_list->flag == option)
			ans[i] = strdup(word_list->word);
		else if (word_list->flag == arguments)
			ans[i] = strdup(word_list->word);
		if ((word_list->flag == command || word_list->flag == option
				|| word_list->flag == arguments) && ans[i] == NULL)
			perror("failed to get_cmd_argv");
		if (ans[i] != NULL)
			i++;
		word_list = word_list->next;
	}
	return (ans);
}

__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}

int	main(int argc, char **argv)
{
	t_word_list	*word_list;
	char		*line = "> file ls -l < file2";
	char **ans;
	int i;
	
	get_word_list(&word_list, line);
	get_command(&word_list);
	ans=get_cmd_argv(word_list);
	i=0;
	while(ans[i]!=NULL)
	{
		printf("ans[%d] %s\n",i,ans[i]);
		i++;
	}
	exit(0);
}
