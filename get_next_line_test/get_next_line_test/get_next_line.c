/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 10:21:46 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/21 10:36:59 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

#include <stdio.h>

static void	ft_bufline(char *buf, char *tmp)
{
	int	y;
	int	x;

	x = 0;
	y = 1;
	while (buf[x] != '\0' && y == 1)
	{
		if (buf[x] == '\n')
		{
			y = 0;
//			ft_putstr("tmp = ");
//			ft_putstr(tmp);
//			ft_putstr("\nbuf = ");
//			ft_putstr(buf);
//			ft_putstr("\ntmp2 = ");
			ft_memmove(tmp, buf + x + 1, BUFF_SIZE + ft_strlen(tmp));
			buf[x] = '\0';
//			ft_putstr(tmp);
//			ft_putstr("\nbuf2 = ");
//			ft_putstr(buf);
//			ft_putstr("\n");
		}
		x++;
	}
}

static char	*ft_bufnoline(const int fd, char *buf)
{
	int		ret;
	char	*tmp2;

	ret = 0;
	if (!(tmp2 = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (NULL);
	if ((ret = read(fd, tmp2, BUFF_SIZE)) == 0)
		return (0);
	tmp2[ret] = '\0';
	buf = ft_strjoin(buf, tmp2);
	free(tmp2);
	return (buf);
}

static int	ft_while(const int fd, char *buf, char *tmp, char **line)
{
	int	x;

	x = 0;
	while (buf[x] != '\0')
	{
		if (buf[x] == '\n')
		{
			ft_bufline(buf, tmp);
			*line = buf;
			free(buf);
			return (1);
		}
		if (buf[x + 1] == '\0')
			if ((buf = ft_bufnoline(fd, buf)) == NULL)
				return (-1);
		x++;
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	int			finish;
	int			ret;
	char		*buf;
	static char	*tmp;

	ret = 0;
	finish = 0;
	if (fd <= -1)
		return (-1);
	if (!(buf = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	if (tmp == NULL)
		if (!(tmp = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
			return (-1);
	ret = read(fd, buf, BUFF_SIZE);
	buf[ret] = '\0';
	buf = ft_strjoin(tmp, buf);
	finish = ft_while(fd, buf, tmp, line);
	return (finish);
}
