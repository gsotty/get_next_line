/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_test3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 11:38:23 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/23 05:21:19 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

/*static char	*ft_bufnoline(const int fd, char *buf)
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

static int	ft_while(const int fd, char **tmp)
{
	int		x;

	x = 0;
	while (tmp[0][x] != '\0')
	{
		if (tmp[0][x] == '\n')
		{
			//ft_strsplit(tmp[0], '\n');
			return (1);
		}
		else if (tmp[0][x + 1] == '\0')
			if ((tmp[0] = ft_bufnoline(fd, tmp[0])) == NULL)
				return (-1);
		x++;
	}
	return (0);
}*/

int			get_next_line(const int fd, char **line)
{
	int			ret;
	int			finish;
	char		*tab;
	static char	**tmp;

	ret = 0;
	finish = 0;
	if (fd <= -1)
		return (-1);
	if (!(tab = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	ret = read(fd, tab, BUFF_SIZE);
	tab[ret] = '\0';
	if (tmp != NULL)
		tab = ft_strjoin(tmp[1], tab);
	tmp = ft_strsplit(tab, '\n');
	*line = tmp[0];
	//finish = ft_while(fd, tmp);
	return (ret);
}
