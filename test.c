/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:05 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/18 21:07:15 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_word_list
{
	struct s_word_list	*next;
	char				*word;
	int					flag;
}						t_word_list;

typedef struct s_env_list
{
	char				*env_name;
	char				*env_str;
	int					write_flg;
	bool				shell_variable;
	struct s_env_list	*next;
}						t_env_list;

typedef struct s_fd
{
	int					in_fd;
	int					out_fd;
	int					pipe_fd[2];
	int					here_fd;
}						t_fd;

typedef struct s_execve_args
{
	char				**env_path;
	char				**argv;
}						t_execve_args;

typedef struct s_shell
{
	t_word_list			*word_head;
	t_env_list			*env_head;
	char				**envp_2d_arr;
	t_execve_args		*execve_args_p;
	t_fd				*fd_struct;
	int					exit_status;

}						t_shell;

typedef enum e_flags
{
	command,
	option,
	arguments,
	env,
	pipe_char,
	great,
	great_great,
	less,
	less_less,
	meta_char,
}						t_flags;

t_shell			*g_shell_struct;

size_t get_name_len(char *str)
{
	size_t len;

	len=0;
	while (str[len] != '\0' && str[len] != '=')
		len++;
	return(len);
}

void	new_node(t_env_list **node, char *envp)
{
	size_t	len;

	*node = malloc(sizeof(t_env_list));
	len = get_name_len(envp);
	(*node)->env_name = malloc(sizeof(char) * (len + 1));
	strlcpy((*node)->env_name, envp, len + 1);
	if (strchr(envp, '='))
	{
		(*node)->env_str = strdup(&envp[len + 1]);
	}
	else
		(*node)->env_str = NULL;
	(*node)->write_flg = false;
	(*node)->shell_variable = false;
	(*node)->next = NULL;
}

void	get_env_list(char **envp, t_env_list **head)
{
	t_env_list	*new;
	t_env_list	*node;
	size_t		i;

	new_node(&node, envp[0]);
	*head = node;
	i = 1;
	while (envp[i] != NULL)
	{
		new_node(&new, envp[i]);
		node->next = new;
		node = new;
		i++;
	}
}

void	ft_get_env(char *str, t_env_list *env_list, t_env_list **tmp)
{
	if (env_list == NULL)
		return ;
	while (env_list != NULL && strcmp(env_list->env_name, str) != 0)
		env_list = env_list->next;
	if (env_list != NULL && strcmp(env_list->env_name, str) == 0)
		*tmp = env_list;
}

void	new_word_node(t_word_list **node, char *argv)
{
	*node = malloc(sizeof(t_word_list));
	(*node)->next = NULL;
	if (strchr(argv, '<'))
		(*node)->flag = less;
	else if (strchr(argv, '>'))
		(*node)->flag = great;
	else if (!strncmp(argv, ">>", 2))
		(*node)->flag = great_great;
	else if (!strncmp(argv, "<<", 2))
		(*node)->flag = less_less;
	else
		(*node)->flag = arguments;
	(*node)->word = strdup(argv);
}

void	get_word_list(t_word_list **head, char **argv)
{
	t_word_list *new;
	t_word_list *node;
	size_t i;

	i = 0;
	new_word_node(&node,argv[i]);
	i++;
	*head = node;
	while (argv[i] != NULL)
	{
		new_word_node(&new, argv[i]);
		node->next = new;
		node = new;
		i++;
	}
}

bool	is_inequality_sign(int flag)
{
	if (flag == great || flag == great || flag == less || flag == less_less)
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
			&& (is_inequality_sign((*head)->flag) == true
				&& (*head)->next->flag == arguments))
			*head = (*head)->next->next;
		if ((*head)->flag == arguments)
			(*head)->flag = command;
	}
}

void	traverse_list_until_pipe(t_word_list **head)
{
	is_command(head);
	while (*head != NULL)
	{
		*head = (*head)->next;
		while (*head != NULL && (*head)->flag != pipe_char)
			*head = (*head)->next;
		if ((*head)!= NULL && (*head)->flag == pipe_char)
		{
			*head = (*head)->next;
			is_command(head);
		}
	}
	printf("word_head %p\n",g_shell_struct->word_head);
	*head = g_shell_struct->word_head;
}

// __attribute__((destructor))
// void destrucor() {
// 	system("leaks a.out");
// }

// int	main(int argc, char **argv, char **envp)
int main()
{
	t_word_list *head;
	
	char *argv[4]={"a.out","echo","hello"};
	g_shell_struct=malloc(sizeof(t_shell));
	get_word_list(&head,&argv[1]);
	g_shell_struct->word_head=head;
	printf("head %s\n",head->word);
	traverse_list_until_pipe(&head);	
	printf("tmp %s\n",head->word);
	printf("tmp %s\n",head->word);
	exit(0);
}
