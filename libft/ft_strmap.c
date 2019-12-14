/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymhabib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 21:24:35 by aymhabib          #+#    #+#             */
/*   Updated: 2019/04/08 22:50:03 by aymhabib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*a;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	a = (char *)malloc(ft_strlen(s) + 1);
	if (a == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		a[i] = f(s[i]);
		i++;
	}
	a[i] = '\0';
	return (a);
}
