/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_test5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:14:57 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/24 09:30:04 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		ft_bufline(t_file *file)
{
	int	y;
	int	x;
	int	buf_len;

	x = 0;
	y = 1;
	buf_len = BUFF_SIZE + ft_strlen(file->buf[1]);
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

static int		ft_bufnoline(t_file *file, const int fd)
{
	int		x;
	int		ret;
	char	*tmp2;

	x = 0;
	ret = 0;
	if (!(tmp2 = (char *)ft_memalloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	while (file->fd[x] != fd)
		x++;
	if ((ret = read(file->fd[x], tmp2, BUFF_SIZE)) == 0)
		return (0);
	tmp2[ret] = '\0';
	file->buf[0] = ft_strjoin(file->buf[0], tmp2);
	free(tmp2);
	return (1);
}

static int		ft_while(t_file *file, const int fd)
{
	int		z;

	z = 0;
	while (file->buf[0][z] != '\0')
	{
		if (file->buf[0][z] == '\n' || file->buf[0][z] == '\0')
		{
			ft_bufline(file);
			return (1);
		}
		if (file->buf[0][z + 1] == '\0')
		{
			if ((ft_bufnoline(file, fd)) == 0)
				return (1);
		}
		z++;
	}
	return (0);
}

static t_file	*ft_malloc(const int fd, t_file *file)
{
	int		*fd_tmp;

	if (file == NULL)
	{
		if ((file = (t_file *)malloc(sizeof(t_file) * 1)) == NULL)
			return (NULL);
		file->cont = 0;
		if ((file->buf = (char **)malloc(sizeof(char) * 2)) == NULL)
			return (NULL);
		if ((file->fd = (int *)malloc(sizeof(int) * 1)) == NULL)
			return (NULL);
		file->fd[0] = fd;
		file->buf[1] = NULL;
	}
	if (file->fd[file->cont] != fd)
	{
		fd_tmp = file->fd;
		free(file->fd);
		if ((file->fd = (int *)malloc(sizeof(int) * file->cont + 1)) == NULL)
			return (NULL);
		file->fd = fd_tmp;
		file->fd[file->cont + 1] = fd;
		file->cont++;
	}
	return (file);
}

int				get_next_line(const int fd, char **line)
{
	int				x;
	int				ret;
	int				finish;
	static t_file	*file;

	x = 0;
	finish = -1;
	if (fd < 0 || line == NULL)
		return (-1);
	if ((file = ft_malloc(fd, file)) == NULL)
		return (-1);
	if ((file->buf[0] = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)) == NULL)
		return (-1);
	if ((file->buf[1]) == NULL)
		if (!(file->buf[1] = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
			return (-1);
	while (file->fd[x] != fd)
		x++;
	if ((ret = read(file->fd[x], file->buf[0], BUFF_SIZE)) == -1)
		return (-1);
	file->buf[0][ret] = '\0';
	file->buf[0] = ft_strjoin(file->buf[1], file->buf[0]);
	finish = ft_while(file, fd);
	*line = file->buf[0];
	return (finish);
}
