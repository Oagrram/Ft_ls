/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ilen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymhabib <aymhabib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 22:51:18 by aymhabib          #+#    #+#             */
/*   Updated: 2019/05/20 22:51:24 by aymhabib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ilen(int n)
{
	unsigned int	len;
	unsigned int	nb;
	int				signe;

	len = 1;
	signe = 1;
	if (n < 0)
	{
		signe = -1;
		len++;
	}
	nb = n * signe;
	while (nb > 9)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}
