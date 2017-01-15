/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 11:50:34 by gsotty            #+#    #+#             */
/*   Updated: 2017/01/14 12:02:12 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int		verif_space(char *str)
{
	int		x;

	x = 0;
	if (str == NULL)
		return (0);
	while (str[x] != '\0')
	{
		if (str[x] == '\n')
			return (1);
		x++;
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	int			x;
	int			ret;
	char		*buf;
	char		*tmp_buf;
	char		*tmp_join;
	static char	*tmp = NULL;

	ret = 1;
	buf = NULL;
	tmp_buf = NULL;
	if (fd < 0 || BUFF_SIZE > 10000000)
		return (-1);
	while (verif_space(tmp_buf) == 0)
	{
		if (verif_space(tmp) == 1)
		{
			buf = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		else
		{
			tmp_buf = ft_strnew(BUFF_SIZE);
			if ((ret = read(fd, tmp_buf, BUFF_SIZE)) == -1)
				return (-1);
			tmp_buf[ret] = '\0';
			if (tmp != NULL)
			{
				tmp_join = ft_strjoin(tmp, tmp_buf);
				ft_strdel(&tmp_buf);
				tmp_buf = ft_strdup(tmp_join);
				ft_strdel(&tmp_join);
			}
			if (buf == NULL && ret != 0)
				buf = ft_strdup(tmp_buf);
			else if (buf != NULL)
			{
				tmp_join = ft_strjoin(buf, tmp_buf);
				ft_strdel(&buf);
				buf = ft_strdup(tmp_join);
				ft_strdel(&tmp_join);
			}
			else
			{
				buf = ft_strdup(tmp_buf);
				ft_strdel(&tmp_buf);
			}
		}
		x = 0;
		ft_strdel(&tmp);
		ft_strdel(&tmp_buf);
		while (buf[x] != '\0' && buf != NULL)
		{
			if (buf[x] == '\n')
			{
				tmp_buf = ft_strdup(buf);
				buf[x] = '\0';
				tmp = ft_strdup(buf + x + 1);
				break ;
			}
			x++;
		}
	}
	if (buf == NULL && (ft_strlen(tmp_buf) == 0))
		ret = 0;
	else
		ret = 1;
	ft_strdel(&tmp_buf);
	*line = buf;
	return (ret);
}

int		main(int argc, char **argv)
{
	int		x;
	int		fd;
	int		ret;
	char	*line;

	x = 0;
	if (argc != 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (-1);
		while ((ret = get_next_line(fd, &line)))
		{
			if (ret == -1)
				return (0);
			ft_putstr(line);
			ft_putstr("\n");
			free(line);
			x++;
		}
		if (close(fd) == 1)
			return (-1);
	}
	return (0);
}
