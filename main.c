/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 15:27:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/01/15 13:48:57 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int		fd;
	int		ret;
	char	*line;

	if (argc != 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (-1);
		while ((ret = get_next_line(fd, &line) > 0))
		{
			if (ret == -1)
				return (0);
			ft_putstr(line);
			ft_putstr("\n");
			free(line);
		}
		if (close(fd) == 1)
			return (-1);
	}
	return (0);
}
