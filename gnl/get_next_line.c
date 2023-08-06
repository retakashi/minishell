/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:59:13 by rtakashi          #+#    #+#             */
/*   Updated: 2023/08/05 17:21:29 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

volatile sig_atomic_t	g_sig;

static char	*get_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
		i++;
	ft_strlcpy(line, line, i + 1);
	return (line);
}

static char	*get_buf(char *buf)
{
	size_t	i;

	if (buf == NULL)
	{
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return (NULL);
		buf[0] = '\0';
		return (buf);
	}
	if (!ft_strchr(buf, '\n'))
		return (buf);
	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	i++;
	ft_strlcpy(buf, buf + i, ft_strlen(buf));
	return (buf);
}

static char	*readnum_under(ssize_t read_num, char *buf, char *line, int *flg)
{
	if (read_num < 0)
		return (NULL);
	*flg = 1;
	if (line != NULL)
	{
		buf[0] = '\0';
		return (line);
	}
	return (line);
}

static char	*buf_readjoin(char *buf, char *line, int fd, int *flg)
{
	ssize_t	read_num;

	read_num = 1;
	if (buf[0] != '\0')
	{
		line = ft_strjoin(line, buf);
		if (line == NULL)
			return (NULL);
	}
	while (read_num > 0 && !ft_strchr(buf, '\n'))
	{
		if (set_signal_gnl() == FAILURE)
			return (NULL);
		read_num = read(fd, buf, BUFFER_SIZE);
		if (read_num < 1)
			return (readnum_under(read_num, buf, line, flg));
		buf[read_num] = '\0';
		line = ft_strjoin_gnl(line, buf);
		if (line == NULL)
			return (NULL);
	}
	return (get_line(line));
}

char	*get_next_line(int fd, int *flg)
{
	static char	*buf;
	char		*line;
	char		test[1];

	if (fd < 0 || BUFFER_SIZE <= 0 || 0 > read(fd, test, 0))
		return (NULL);
	if (buf == NULL)
	{
		buf = get_buf(buf);
		if (buf == NULL)
			return (NULL);
	}
	line = NULL;
	line = buf_readjoin(buf, line, fd, flg);
	if (ft_strchr(buf, '\n'))
		get_buf(buf);
	if (line == NULL)
	{
		free(buf);
		buf = NULL;
	}
	return (line);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q a.output");
// }

// int	main(void)
// {
// 	char *str;
// 	int fd;

// 	fd = open("text", O_RDONLY);
// 	if (fd == -1)
// 		return (0);
// 	while (1)
// 	{
// 		str = get_next_line(fd);
// 		printf("%s", str);
// 		free(str);
// 		if (!str)
// 			break ;
// 	}
// 	str = get_next_line(fd);
// 	close(fd);
// 	return (0);
// }
// #include <stdio.h>
// int	main(void)
// {
// 	int	fd;

// 	fd = open("text", O_RDONLY);
// 	printf("%s \n", get_next_line(42)); // ok
// 	close(fd);
// 	printf("read ret %d\n", read(fd, NULL, 0));
// 	printf("%s\n", get_next_line(fd));
// 	return (0);
// }
