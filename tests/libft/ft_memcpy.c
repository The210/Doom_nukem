/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 03:44:27 by smerelo           #+#    #+#             */
/*   Updated: 2017/12/05 15:48:35 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*ss;
	size_t	i;
	char	*str;
	char	*sttr;

	str = (char*)src;
	sttr = (char*)dst;
	i = 0;
	ss = dst;
	while (i < n)
	{
		sttr[i] = str[i];
		i++;
	}
	return (ss);
}
