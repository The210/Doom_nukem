/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 00:53:19 by smerelo           #+#    #+#             */
/*   Updated: 2017/12/07 01:39:42 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;

	i = 0;
	if (ft_strlen(needle) == 0)
		return ((char*)haystack);
	if (needle == haystack)
		return ((char*)haystack);
	if (ft_strlen(needle) == 0 || ft_strlen(haystack) == 0
							|| len < ft_strlen(needle))
		return (NULL);
	while (haystack[i] && i <= len - ft_strlen(needle))
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strncmp(needle, haystack + i, ft_strlen(needle)) == 0)
				return ((char*)haystack + i);
		}
		i++;
	}
	return (NULL);
}
