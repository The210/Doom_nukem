/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:40:13 by smerelo           #+#    #+#             */
/*   Updated: 2017/12/06 01:57:28 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f) (char *))
{
	int i;

	i = 0;
	if (s != NULL && f != NULL)
	{
		i = 0;
		while (s[i])
		{
			f(&s[i]);
			i++;
		}
	}
}
