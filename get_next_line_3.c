/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 12:03:33 by gsotty            #+#    #+#             */
/*   Updated: 2017/01/14 15:18:40 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_join_no_leaks(char **tmp_buf, char **buf)
{
	char	*tmp;

	tmp = ft_strjoin(*tmp_buf, *buf);
	ft_strdel(buf);
	*buf = ft_strdup(tmp);
	ft_strdel(&tmp);
}

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
	t_file			*tmp_file;
	static t_file	*file = NULL;

	if (file == NULL)
	{
		ft_putstr("111\n");
		file = ft_memalloc(1);
		file->buf = NULL;
		file->next = NULL;
		file->tmp_buf = NULL;
		file->ret = BUFF_SIZE;
		tmp_file = file;
	}
	else
	{
		tmp_file = file;
		while (tmp_file != NULL)
		{
			if (tmp_file->fd == fd)
				break ;
			tmp_file = tmp_file->next;
		}
		if (tmp_file == NULL)
		{
			file->fd = fd;
		}
	}
	while (verif_space(tmp_file->tmp_buf) == 0 && tmp_file->ret == BUFF_SIZE)
	{
		if (verif_space(tmp_file->rest) == 1)
		{
			ft_strdel(&tmp_file->tmp_buf);
			tmp_file->tmp_buf = ft_strdup(tmp_file->rest);
			ft_strdel(&tmp_file->rest);
		}
		else
		{
			tmp_file->tmp = ft_strdup(tmp_file->tmp_buf);
			ft_strdel(&tmp_file->tmp_buf);
			tmp_file->tmp_buf = ft_strnew(BUFF_SIZE);
			if ((tmp_file->ret = read(fd, tmp_file->tmp_buf, BUFF_SIZE)) == -1)
				return (-1);
			tmp_file->tmp_buf[tmp_file->ret] = '\0';
			if (tmp_file->tmp != NULL)
			{
				ft_join_no_leaks(&tmp_file->tmp, &tmp_file->tmp_buf);
				ft_strdel(&tmp_file->tmp);
			}
			if (tmp_file->rest != NULL)
			{
				ft_join_no_leaks(&tmp_file->rest, &tmp_file->tmp_buf);
				ft_strdel(&tmp_file->rest);
			}
		}
	}
	return (0);
}

#include <fcntl.h>
#include <stdlib.h>

int		main(int argc, char **argv)
{
	int		x;
	int		fd;
	int		ret;
	char*	line;

	x = 0;
	if (argc != 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (-1);
		while (/*(ret = get_next_line(fd, &line))*/ x < ft_atoi(argv[2]))
		{
			ret = get_next_line(fd, &line);
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
