/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:11:27 by oagrram           #+#    #+#             */
/*   Updated: 2020/02/09 17:11:28 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	getmaxint(t_flist *ptr, int *maxnlink, char type, int count)
{
	int tmp;

	if (type == 'l' || type == 's' || type == 'a' || type == 'i')
	{
		if (type == 'l')
			tmp = ptr->nlink;
		else if ((type == 's') && (ptr->type != 'c' && ptr->type != 'b'))
			tmp = ptr->size;
		else if (type == 'a' && (ptr->type == 'c' || ptr->type == 'b'))
			tmp = ptr->maj;
		else
			tmp = ptr->min;
		while (tmp != 0 && ++count)
			tmp /= 10;
	}
	else
	{
		if (type == 'u')
			count = ft_strlen(ptr->user);
		else
			count = ft_strlen(ptr->groupe);
	}
	if (count > *maxnlink)
		*maxnlink = count;
}

int		get_lenght(t_flist *ptr, char type, int ptr_move)
{
	int max;

	max = 0;
	while (ptr)
	{
		if (type == 'a' || type == 'i')
		{
			if (ptr->type == 'c' || ptr->type == 'b')
				getmaxint(ptr, &max, type, 0);
		}
		else
			getmaxint(ptr, &max, type, 0);
		if (ptr_move == 1)
			ptr = ptr->next;
		else
			ptr = ptr->next_file;
	}
	return (max);
}

void	print_spaces(t_flist *p, char type, int max, int spacead)
{
	int i;
	int length;

	length = 0;
	i = 0;
	getmaxint(p, &length, type, 0);
	if (length == 0)
		length = 1;
	length = (max - (length)) + spacead;
	while ((length)-- != 0 && (length) > -1)
	{
		++i;
		ft_putchar(' ');
	}
}
