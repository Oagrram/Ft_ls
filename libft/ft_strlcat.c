/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymhabib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:13:39 by aymhabib          #+#    #+#             */
/*   Updated: 2019/04/15 00:37:09 by aymhabib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t a;
	size_t b;
	size_t i;

	a = ft_strlen(dest);
	b = ft_strlen(src);
	if (size <= a)
		return (size + b);
	i = 0;
	while (dest[i] && i < size - 1)
		i++;
	while (*src && i < size - 1)
		dest[i++] = *(src++);
	dest[i] = '\0';
	return (a + b);
}
