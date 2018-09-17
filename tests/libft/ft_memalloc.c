/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 20:11:59 by smerelo           #+#    #+#             */
/*   Updated: 2017/11/29 20:24:52 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*s;
	size_t	i;

	i = 0;
	if ((s = (void*)malloc(sizeof(void) * size)) == 0)
		return (NULL);
	while (i < size)
	{
		((unsigned char*)s)[i] = 0;
		i++;
	}
	return (s);
}
