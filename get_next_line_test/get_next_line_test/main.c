/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 10:40:49 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/29 17:48:36 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int			main(int argc, char **argv)
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
			ft_putstr(line);
			ft_putstr("\n");
			free(line);
			x++;
		}
		ft_putnbr(x);
		ft_putchar('\n');
		if (close(fd) == -1)
			return (-1);
	}
	return (0);
}
