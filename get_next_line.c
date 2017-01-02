/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 11:50:34 by gsotty            #+#    #+#             */
/*   Updated: 2017/01/02 14:19:43 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

int		ft_str_line(char *line, int len)
{
	int		x;

	x = 0;
	while (x < len)
	{
		if (line[x] == '\0')
			return (0);
		if (line[x] == '\n')
			return (1);
		x++;
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	int			ret;
	char		*buf;
	char		*tmp_buf;
	static char	tmp[BUFF_SIZE + 1];

	buf = NULL;
	ret = 0;
	if (fd < 0)
		return (-1);
	if (!(buf = (char *)malloc(sizeof(char) *
					(BUFF_SIZE + ft_strlen(tmp) + 1))))
		return (-1);
	buf = NULL;
	while (ret == 0)
	{
		if (!(tmp_buf = (char *)malloc(sizeof(char) *
						(BUFF_SIZE + ft_strlen(tmp_buf) + 1))))
			return (-1);
		if (!(ret = read(fd, tmp_buf, BUFF_SIZE)))
			return (0);
		//ft_memmove(tmp, buf, BUFF_SIZE);
		tmp_buf[ret] = '\0';
		ft_putstr("buf = ");
		ft_putstr(buf);
		ft_putstr("\n");
		ft_putstr("tmp_buf = ");
		ft_putstr(tmp_buf);
		ft_putstr("\n");
		if (buf == NULL)
		{
			buf = tmp_buf;
			ret = 0;
		}
		else if ((ft_str_line(tmp_buf, ft_strlen(tmp_buf)) == 0))
		{
			buf = ft_strjoin(buf, tmp_buf);
		//	ft_putstr("buf 2 = ");
		//	ft_putstr(buf);
		//	ft_putstr("\n");
		//	ft_putstr("tmp_buf 2 = ");
		//	ft_putstr(tmp_buf);
		//	ft_putstr("\n");
			ret = 0;
		}
	}
	*line = buf;
//	free(buf);
	return (1);
}

int		main(int argc, char **argv)
{
	int		x;
	int		fd;
	char	*line;

	x = 0;
	if (argc != 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (-1);
		while (get_next_line(fd, &line))
		{
		//	ft_putstr("333\n");
	//		ft_putstr(line);
	//		ft_putstr("\n");
			free(line);
			x++;
		}
		if (close(fd) == 1)
			return (-1);
	}
	return (0);
}
