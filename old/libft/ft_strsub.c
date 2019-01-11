/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 23:12:47 by smerelo           #+#    #+#             */
/*   Updated: 2017/12/06 02:16:02 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	i;

	if (s != NULL)
	{
		i = 0;
		if ((s1 = ft_strnew(len)) == NULL)
			return (NULL);
		while (i < len)
		{
			s1[i] = s[start];
			i++;
			start++;
		}
		s1[i] = '\0';
		return (s1);
	}
	return (NULL);
}
