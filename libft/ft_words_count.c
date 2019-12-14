/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymhabib <aymhabib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 22:54:18 by aymhabib          #+#    #+#             */
/*   Updated: 2019/05/20 22:54:20 by aymhabib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_words_count(const char *str, char c)
{
	unsigned int	i;
	unsigned int	nb;

	nb = 0;
	i = 1;
	if (str[0] && str[0] != c)
		nb++;
	while (str[i])
	{
		if (str[i] != c && str[i - 1] == c)
			nb++;
		i++;
	}
	return (nb);
}
