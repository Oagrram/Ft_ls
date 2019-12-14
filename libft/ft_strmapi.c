/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymhabib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:34:02 by aymhabib          #+#    #+#             */
/*   Updated: 2019/04/08 22:47:04 by aymhabib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*a;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	a = (char *)ft_strnew(ft_strlen(s));
	if (a == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		a[i] = (*f)(i, s[i]);
		i++;
	}
	return (a);
}
