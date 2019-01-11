/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 20:57:20 by smerelo           #+#    #+#             */
/*   Updated: 2017/12/05 18:25:30 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*s;

	i = 0;
	if ((s = (char*)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	while (i < size)
	{
		((unsigned char*)s)[i] = 0;
		i++;
	}
	((unsigned char*)s)[i] = '\0';
	return (s);
}
