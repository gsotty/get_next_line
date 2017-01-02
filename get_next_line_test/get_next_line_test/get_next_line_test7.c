/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_test5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:14:57 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/29 14:05:03 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		ft_bufline(t_file *file, int tmp_len)
{
	int	y;
	int	x;
	int	buf_len;

	x = 0;
	y = 1;
	buf_len = BUFF_SIZE + tmp_len;
	while (file->buf[0][x] != '\0' && y == 1)
	{
		if (file->buf[0][x] == '\n')
		{
			y = 0;
			ft_memmove(file->buf[1], (file->buf[0] + x + 1), buf_len);
			file->buf[0][x] = '\0';
		}
		x++;
	}
}

static int		ft_bufnoline(t_file *file)
{
	int		ret;
	char	*tmp2;

	ret = 0;
	if (!(tmp2 = (char *)ft_memalloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	if ((ret = read(file->fd, tmp2, BUFF_SIZE)) == 0)
		return (0);
	tmp2[ret] = '\0';
	file->buf[0] = ft_strjoin(file->buf[0], tmp2);
	free(tmp2);
	return (1);
}

static int		ft_while(t_file *file, int tmp_len)
{
	int		z;

	z = 0;
	while (file->buf[0][z] != '\0')
	{
		if (file->buf[0][z] == '\n' || file->buf[0][z] == '\0')
		{
			ft_bufline(file, tmp_len);
			return (1);
		}
		if (file->buf[0][z + 1] == '\0')
		{
			if ((ft_bufnoline(file)) == 0)
				return (1);
		}
		z++;
	}
	return (0);
}

static t_file	*ft_malloc(const int fd, t_file *file)
{
	if (file == NULL)
	{
		if (!(file = (t_file *)malloc(sizeof(t_file) * 1)))
			return (NULL);
		if (!(file->buf = (char **)malloc(sizeof(char) * 2)))
			return (NULL);
		file->buf[1] = NULL;
	}
	if (file->buf[1] == NULL)
	{
		if (!(file->buf[0] = ft_memalloc(BUFF_SIZE + 1)))
			return (NULL);
	}
	else
	{
		if (!(file->buf[0] = ft_memalloc(BUFF_SIZE + ft_strlen(file->buf[1]))))
			return (NULL);
	}
	file->fd = fd;
	return (file);
}

int				get_next_line(const int fd, char **line)
{
	int				tmp_len;
	int				ret;
	int				finish;
	static t_file	*file;

	finish = -1;
	if (fd < 0 || line == NULL)
		return (-1);
	if (!(file = ft_malloc(fd, file)))
		return (-1);
	if ((file->buf[1]) == NULL)
		if (!(file->buf[1] = ft_memalloc(BUFF_SIZE)))
			return (-1);
	if ((ret = read(file->fd, file->buf[0], BUFF_SIZE)) == -1)
		return (-1);
	file->buf[0][ret] = '\0';
	file->buf[0] = ft_strjoin(file->buf[1], file->buf[0]);
	tmp_len = ft_strlen(file->buf[1]);
	free(file->buf[1]);
	if (!(file->buf[1] = ft_memalloc(BUFF_SIZE + ft_strlen(file->buf[0]))))
		return (-1);
	finish = ft_while(file, tmp_len);
	*line = file->buf[0];
	return (finish);
}
