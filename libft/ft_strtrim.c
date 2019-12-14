/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymhabib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:55:09 by aymhabib          #+#    #+#             */
/*   Updated: 2019/04/09 18:36:28 by aymhabib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int start;
	int len;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] == '\n' || s[start] == '\t' || s[start] == ' ')
		start++;
	len = ft_strlen(s) - 1;
	while (len && (s[len] == '\n' || s[len] == '\t' || s[len] == ' '))
		len--;
	return (len - start + 1 < 0 ?
			ft_strsub(s, start, 0) : ft_strsub(s, start, len - start + 1));
}
