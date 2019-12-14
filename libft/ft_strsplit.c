/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymhabib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:03:47 by aymhabib          #+#    #+#             */
/*   Updated: 2019/04/12 19:31:39 by aymhabib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words(char const *str, char c)
{
	int		i;
	int		nb;

	nb = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
			nb++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (nb);
}

static int	lenght(char const *str, char c)
{
	int		len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

char		**ft_strsplit(char const *str, char c)
{
	char	**tab;
	int		pos;
	int		i;
	int		j;

	if (!str || !(tab = (char **)malloc((words(str, c) + 1) * sizeof(char *))))
		return (NULL);
	pos = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			if (!(tab[pos] = (char *)malloc(lenght(str + i, c) * sizeof(char))))
				return (NULL);
			j = 0;
			while (str[i] && str[i] != c)
				tab[pos][j++] = str[i++];
			tab[pos++][j] = '\0';
		}
	}
	tab[pos] = NULL;
	return (tab);
}
