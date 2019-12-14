/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymhabib <aymhabib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 21:19:05 by aymhabib          #+#    #+#             */
/*   Updated: 2019/05/19 01:27:50 by aymhabib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		sign = (*(str++) == '-' ? -1 : 1);
	while (*str >= '0' && *str <= '9')
		nb = nb * 10 + *(str++) - '0';
	if (nb > 2147483647)
		return (sign == 1 ? -1 : 0);
	return (sign * nb);
}
