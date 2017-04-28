/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_next_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 12:11:12 by gsotty            #+#    #+#             */
/*   Updated: 2017/01/18 16:48:48 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	cut_tmp_buf(char **rest, char **tmp_buf, char **line)
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
	*rest = rest_tmp;
	*tmp_buf = tmp_buf_2;
	*line = tmp_buf_2;
}

char	*ft_while_2(int fd, int *ret, char *tmp_buf, char *tmp_join)
{
	char	*tmp;

	tmp = NULL;
	if (tmp_buf != NULL)
	{
		tmp = ft_strdup(tmp_buf);
		ft_strdel(&tmp_buf);
		tmp_buf = ft_memalloc(BUFF_SIZE);
		if ((*ret = read(fd, tmp_buf, BUFF_SIZE)) == -1)
			return (NULL);
		tmp_buf[*ret] = '\0';
		tmp_join = ft_strjoin(tmp, tmp_buf);
		ft_strdel(&tmp_buf);
		tmp_buf = ft_strdup(tmp_join);
		ft_strdel(&tmp_join);
		ft_strdel(&tmp);
	}
	else
	{
		tmp_buf = ft_strnew(BUFF_SIZE);
		if ((*ret = read(fd, tmp_buf, BUFF_SIZE)) == -1)
			return (NULL);
		tmp_buf[*ret] = '\0';
	}
	return (tmp_buf);
}

char	*ft_while(char **rest, int fd, int *ret, char *tmp_buf)
{
	char	*tmp_join;

	tmp_join = NULL;
	while (*ret == BUFF_SIZE && verif_space(tmp_buf) == 0)
	{
		if (verif_space(*rest) != 1)
		{
			tmp_buf = ft_while_2(fd, ret, tmp_buf, tmp_join);
			if (*rest != NULL)
			{
				tmp_join = ft_strjoin(*rest, tmp_buf);
				ft_strdel(&tmp_buf);
				tmp_buf = ft_strdup(tmp_join);
				ft_strdel(&tmp_join);
				ft_strdel(rest);
			}
		}
		else
		{
			ft_strdel(&tmp_buf);
			tmp_buf = ft_strdup(*rest);
			ft_strdel(rest);
		}
	}
	return (tmp_buf);
}

int		get_next_line(const int fd, char **line)
{
	int				ret;
	char			*buf;
	char			*tmp_buf;
	static char		*rest = NULL;

	buf = NULL;
	tmp_buf = NULL;
	ret = BUFF_SIZE;
	if (fd < 0 || BUFF_SIZE <= 0)
		return (-1);
	if ((tmp_buf = ft_while(&rest, fd, &ret, tmp_buf)) == NULL)
		return (-1);
	if (ret < BUFF_SIZE && verif_space(tmp_buf) == 0)
	{
		ft_strdel(&buf);
		buf = ft_strdup(tmp_buf);
		ft_strdel(&tmp_buf);
		*line = ft_strdup(buf);
	}
	else
		cut_tmp_buf(&rest, &tmp_buf, line);
	if (ret == 0 && ft_strlen(buf) == 0)
		return (0);
	return (1);
}
