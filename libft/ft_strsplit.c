/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 17:19:45 by smerelo           #+#    #+#             */
/*   Updated: 2018/04/03 21:37:30 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static size_t		len(char *s, size_t j, char c)
{
	size_t	l;
	int		k;

	k = j;
	l = 0;
	while (s[k] && s[k] != c)
	{
		l++;
		k++;
	}
	return (l);
}

static size_t		wcount(char *s, char c)
{
	int		i;
	size_t	w;

	i = 0;
	w = 0;
	while (s[i])
	{
		if ((s[i + 1] == c || s[i + 1] == '\0') && s[i] != c)
			w++;
		i++;
	}
	return (w);
}

static char			**ssm(char **ss, int *t, char *x, char c)
{
	while (x[t[1]])
	{
		while (x[t[1]] == c && x[t[1]])
			t[1]++;
		if (x[t[1]] != '\0')
		{
			t[2] = 0;
			if ((ss[t[0]] = malloc(sizeof(char) * (len(x, t[1], c) + 1)))
					== NULL)
				return (NULL);
			while (x[t[1]] != c && x[t[1]])
				ss[t[0]][t[2]++] = x[t[1]++];
			ss[t[0]++][t[2]] = '\0';
		}
	}
	return (ss);
}

char				**ft_strsplit(char const *s, char c)
{
	char	**ss;
	char	*x;
	int		t[3];

	t[0] = 0;
	t[1] = 0;
	ss = NULL;
	if (!s)
		return (NULL);
	if ((x = ft_strtrim_2((char*)s, c)) == NULL)
		return (NULL);
	if ((ss = malloc(sizeof(ss) * wcount(x, c) + 1)) == NULL)
		return (NULL);
	ss = ssm(ss, t, x, c);
	ss[t[0]] = NULL;
	ft_strdel(&x);
	return (ss);
}*/
static int	nbw(char *s, char c)
{
	int i;
	int sym;
	int count;

	i = 0;
	sym = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] != c && s[i])
		{
			sym = 1;
			i++;
		}
		while (s[i] == c && s[i])
		{
			count += sym;
			sym = 0;
			i++;
		}
	}
	return (count + 2);
}

static int	nbc(char *s, int i, char c)
{
	int count;

	count = 0;
	while (s[i] != c && s[i])
	{
		count++;
		i++;
	}
	return (count + 1);
}

char		**ft_strsplit(char *s, char c)
{
	char	**res;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	s = ft_strtrim_2(s, c);
	if (!s || !(res = malloc(sizeof(char*) * nbw((char*)s, c))))
		return (NULL);
	while (s[i])
	{
		k = 0;
		if (!(res[j] = malloc(sizeof(c) * nbc((char*)s, i, c))))
			return (NULL);
		while (s[i] != c && s[i])
			res[j][k++] = s[i++];
		while (s[i] == c && s[i])
			i++;
		res[j++][k] = '\0';
	}
	res[j] = NULL;
	if (s)
		ft_strdel(&s);
	return (res);
}