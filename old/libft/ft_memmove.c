/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 05:01:02 by smerelo           #+#    #+#             */
/*   Updated: 2017/12/06 06:12:38 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*srcs;

	dest = (char*)dst;
	srcs = (char*)src;
	if (srcs < dest)
	{
		while (len--)
			dest[len] = srcs[len];
	}
	else
		ft_memcpy(dest, srcs, len);
	return (dest);
}
