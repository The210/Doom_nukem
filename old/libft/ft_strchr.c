/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 01:20:34 by smerelo           #+#    #+#             */
/*   Updated: 2017/11/28 21:20:00 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t i;

	i = 0;
	if (c == 0)
		return (ft_strlen(s) + (char*)s);
	while (s[i])
	{
		if (s[i] == c)
			return ((char*)s + i);
		i++;
	}
	return (NULL);
}
