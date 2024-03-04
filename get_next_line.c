/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:09:20 by pepaloma          #+#    #+#             */
/*   Updated: 2023/06/21 15:09:24 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **lines)
{
	free(*lines);
	*lines = 0;
}

void	clear_lines(char **lines)
{
	char	*nl_indicator;
	int		len;
	char	*new;

	nl_indicator = ft_strchr(*lines, 10);
	if (!nl_indicator)
	{
		*lines = 0;
		return ;
	}
	len = (nl_indicator - *lines) + 1;
	if (!(*lines)[len])
	{
		free(*lines);
		*lines = 0;
		return ;
	}
	new = ft_substr(*lines, len, ft_strlen(nl_indicator));
	free(*lines);
	*lines = new;
}

char	*stract_line(char *lines)
{
	char	*output_line;
	char	*nl_indicator;

	nl_indicator = ft_strchr(lines, 10);
	if (!nl_indicator)
		return (lines);
	output_line = ft_substr(lines, 0, (nl_indicator - lines) + 1);
	return (output_line);
}

void	store_lines(int fd, char **lines)
{
	ssize_t	bytes_read;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		*lines = 0;
		return ;
	}
	buffer[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, 10))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = 0;
			*lines = ft_strjoin(*lines, buffer);
		}
	}
	free(buffer);
	if (bytes_read == -1)
	{
		ft_free(lines);
	}
}

char	*get_next_line(int fd)
{
	static char	*lines = 0;
	char		*output_line;

	if (fd < 0)
		return (NULL);
	if (!lines || !ft_strchr(lines, 10))
		store_lines(fd, &lines);
	if (!lines)
		return (NULL);
	output_line = stract_line(lines);
	if (!output_line)
	{
		free(lines);
		return (NULL);
	}
	clear_lines(&lines);
	return (output_line);
}
/*
int	main(void)
{
	int	fd;
	char	*line;

	fd = open("example.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("\n--------------\n%s\n", line);
	line = get_next_line(fd);
	printf("\n%s\n", line);
	free(line);
	return (0);
} */