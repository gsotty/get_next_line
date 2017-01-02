/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:21:51 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/30 10:17:16 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 1

typedef struct		s_file
{
	int				fd;
	char			**buf;
}					t_file;

int					get_next_line(const int fd, char **line);

#endif
