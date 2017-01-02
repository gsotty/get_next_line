/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_test8.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 14:11:43 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/30 10:16:22 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	int		x;
	int		ret;
	char	*tmp;
	static char	*buf;

	ret = 1;
	buf = NULL;
	x = 0;
	tmp = *line;
	if (buf == NULL)
	{
	//	ft_putstr("222\n");
		buf = ft_memalloc(BUFF_SIZE + 1);
	}
	tmp = ft_memalloc(BUFF_SIZE + 1);
	while (ret != 0)
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		buf[ret] = '\0';
		while (buf[x] != '\0')
		{
			if (buf[x] == '\n')
			{
				return (ret);
			}
			if (buf[x] != '\n' && buf[x + 1] == '\0')
			{
			//	ft_putnbr(x);
			//	ft_putstr("\n");
			//	ft_putstr("buf = ");
			//	ft_putstr(buf);
			//	ft_putstr("\n");
			//	ft_putstr("line = ");
			//	ft_putstr(*line);
			//	ft_putstr("\n");
				tmp = *line;
			//	ft_putstr("tmp = ");
			//	ft_putstr(tmp);
			//	ft_putstr("\n");
				tmp = ft_strjoin(tmp, buf);
			//	ft_putstr("tmp2 = ");
			//	ft_putstr(tmp);
			//	ft_putstr("\n");
			//	ft_putstr("buf2 = ");
			//	ft_putstr(buf);
			//	ft_putstr("\n");
			//	ft_putstr("line2 = ");
			//	ft_putstr(*line);
			//	ft_putstr("\n");
				if (tmp == NULL)
				{
					*line = buf;
				}
				else
					*line = tmp;
			//	ft_putstr("buf3 = ");
			///	ft_putstr(buf);
			//	ft_putstr("\n");
			//	ft_putstr("line3 = ");
			//	ft_putstr(*line);
			//	ft_putstr("\n");
				get_next_line(fd, line);
			}
			x++;
		}
		return (ret);
	}
	return (0);
}
