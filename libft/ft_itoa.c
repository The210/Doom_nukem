/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 02:42:27 by smerelo           #+#    #+#             */
/*   Updated: 2018/12/11 13:18:16 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		p(int a, int b)
{
	int i;
	int c;

	c = a;
	i = 1;
	if (b == 0)
		return (1);
	while (i < b)
	{
		a = a * c;
		i++;
	}
	return (a);
}

static char		*final(char *s, int long c, int j, int i)
{
	if (c == 0)
	{
		s[0] = '0';
		return (s);
	}
	while (i >= 1)
	{
		s[j] = (((c / p(10, (i - 1))) % 10) + '0');
		i--;
		j++;
	}
	return (s);
}

static char		*extra(int i, int long c, int j, int k)
{
	char	*s;

	k = i;
	if (c < 0)
	{
		k = k + 1;
		j = j + 1;
	}
	if ((s = ft_strnew(k)) == NULL)
		return (NULL);
	if (c < 0)
	{
		s[0] = '-';
		c = c * -1;
	}
	s = final(s, c, j, i);
	return (s);
}

char			*ft_itoa(int n)
{
	int long	c;
	int	long	i;
	char		*s;
	int			j;
	int	long	k;

	k = 0;
	c = n;
	i = 0;
	j = 0;
	if (c == 0)
	{
		if ((s = ft_strnew(1)) == NULL)
			return (NULL);
		s[0] = '0';
		return (s);
	}
	while (c != 0)
	{
		c = c / 10;
		i++;
	}
	c = n;
	s = extra(i, c, j, k);
	return (s);
}
