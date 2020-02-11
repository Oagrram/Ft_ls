/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymhabib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:42:31 by aymhabib          #+#    #+#             */
/*   Updated: 2019/12/17 16:56:41 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*check_arg(char const *s1, char const *s2)
{
	if (s1)
		return (ft_strdup(s1));
	if (s2)
		return (ft_strdup(s2));
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*a;

	if (s1 == NULL || s2 == NULL)
		return (check_arg(s1, s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	a = (char *)ft_memalloc(sizeof(char) * (len + 1));
	if (a == NULL)
		return ((char *)NULL);
	ft_strcpy(a, s1);
	ft_strcat(a, s2);
	return (a);
}
