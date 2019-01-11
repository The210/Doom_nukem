/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:49:54 by smerelo           #+#    #+#             */
/*   Updated: 2017/12/05 20:24:27 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		puis(int no, int i)
{
	int x;
	int y;

	x = 1;
	y = 1;
	while (y <= i)
	{
		x *= no;
		y++;
	}
	return (x);
}

void			ft_putnbr(int n)
{
	int	count;
	int nb;

	count = 1;
	if (n == 0)
		ft_putchar('0');
	if (n == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		n = (n * -1) - 2000000000;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	nb = n;
	while (nb >= 1)
	{
		nb = nb / 10;
		count++;
	}
	while (--count > 0)
		ft_putchar((n / puis(10, (count - 1))) % 10 + '0');
}
