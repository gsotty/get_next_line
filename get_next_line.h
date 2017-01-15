/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 11:50:12 by gsotty            #+#    #+#             */
/*   Updated: 2017/01/14 15:09:35 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 10
# include "./libft/libft.h"
# include <unistd.h>

typedef struct s_file
{
	int				fd;
	int				ret;
	char			*tmp;
	char			*buf;
	char			*tmp_buf;
	char			*rest;
	struct s_file	*next;
}				t_file;

int		get_next_line(const int fd, char **line);

#endif
