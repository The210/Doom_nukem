/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 02:14:58 by smerelo           #+#    #+#             */
/*   Updated: 2017/11/28 04:25:18 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*bs;

	i = 0;
	bs = (char*)b;
	while (i < len)
	{
		bs[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
