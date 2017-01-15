/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_next_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 12:11:12 by gsotty            #+#    #+#             */
/*   Updated: 2017/01/13 15:51:47 by gsotty           ###   ########.fr       */
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

void	cut_tmp_buf(char **rest, char **tmp_buf)
{
	int		x;
	char	*rest_tmp;
	char	*tmp_buf_2;

	x = 0;
	rest_tmp = *rest;
	tmp_buf_2 = *tmp_buf;
	while (tmp_buf_2[x] != '\0')
	{
		if (tmp_buf_2[x] == '\n')
		{
			tmp_buf_2[x] = '\0';
			break ;
		}
		x++;
	}
	rest_tmp = ft_strdup(tmp_buf_2 + x + 1);
	ft_strdel(rest);
	*rest = rest_tmp;
	*tmp_buf = tmp_buf_2;
}

int		get_next_line(const int fd, char **line)
{
	int				ret;
	char			*buf;
	char			*tmp;
	char			*tmp_buf;
	char			*tmp_join;
	static char		*rest = NULL;

	buf = NULL;
	tmp_buf = NULL;
	tmp_join = NULL;
	ret = BUFF_SIZE;
	if (fd < 0 || BUFF_SIZE > 1000000)
		return (-1);
	while (verif_space(tmp_buf) == 0 && ret == BUFF_SIZE)
	{
		if (verif_space(rest) == 1)
		{
			ft_strdel(&tmp_buf);
			tmp_buf = ft_strdup(rest);
			ft_strdel(&rest);
		}
		else
		{
			tmp = ft_strdup(tmp_buf);
			ft_strdel(&tmp_buf);
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
				ft_strdel(&tmp);
			}
			if (rest != NULL)
			{
				tmp_join = ft_strjoin(rest, tmp_buf);
				ft_strdel(&tmp_buf);
				tmp_buf = ft_strdup(tmp_join);
				ft_strdel(&tmp_join);
				ft_strdel(&rest);
			}
		}
	}
	if (ret < BUFF_SIZE && verif_space(tmp_buf) == 0 && ret != 0)
	{
		ft_strdel(&buf);
		buf = ft_strdup(tmp_buf);
		ft_strdel(&tmp_buf);
		*line = buf;
	}
	else
	{
		cut_tmp_buf(&rest, &tmp_buf);
		*line = tmp_buf;
	}
	if (ret == 0 && (ft_strlen(tmp_buf) == 0))
		return (0);
	return (1);
}

/*int			main(int argc, char **argv)
{
	int		fd;
	int		ret;
	char	*line;

	if (argc != 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (-1);
		while ((ret = get_next_line(fd, &line)))
		{
			if (ret == -1)
				return (0);
//			ft_putstr("line = ");
			ft_putstr(line);
			ft_putstr("\n");
			free(line);
		}
		if (close(fd) == 1)
			return (-1);
	}
	return (0);
}*/
