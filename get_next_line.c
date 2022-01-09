/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdark <mdark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:28:29 by mdark             #+#    #+#             */
/*   Updated: 2022/01/09 18:49:45 by mdark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line_ft(int fd, char *buff, char *remainder)
{
	long	count;
	char	*tmp;

	count = 1;
	while (count)
	{
		count = read(fd, buff, BUFFER_SIZE);
		if (count == 0)
			break ;
		buff[count] = '\0';
		if (!remainder)
			remainder = ft_strdup("");
		tmp = remainder;
		remainder = ft_strjoin(tmp, buff);
		tmp = NULL;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (remainder);
}

char	*subline_ft(char *line)
{
	long	len;
	char	*new_remainder;

	len = 0;
	while (line[len] != '\n' && line[len] != '\0')
		len++;
	if (line[len] == '\0')
		return (NULL);
	new_remainder = ft_substr(line, len + 1, ft_strlen(line) - len);
	if (*new_remainder == '\0')
	{
		free(new_remainder);
		new_remainder = NULL;
	}
	line[len + 1] = '\0';
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	line = get_line_ft(fd, buff, remainder);
	free(buff);
	buff = NULL;
	if (!line)
		return (NULL);
	remainder = subline_ft(line);
	return (line);
}
