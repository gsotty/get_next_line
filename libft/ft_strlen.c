/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:42:57 by gsotty            #+#    #+#             */
/*   Updated: 2017/01/02 12:58:10 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(char const *str)
{
	char*	s;
	size_t	len;

	if (str == NULL)
		return (0);
	s = (char *)str;
	len = 0;
	while (*s)
	{
		s++;
		len++;
	}
	return (len);
}
