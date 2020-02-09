/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:15:19 by oagrram           #+#    #+#             */
/*   Updated: 2020/02/08 23:15:22 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_maj_min(t_flist *ptr, t_maxlength *max)
{
	print_spaces(ptr, 'a', max->maj_length, 0);
	ft_putnbr((ptr)->maj);
	ft_putstr(", ");
	print_spaces(ptr, 'i', max->min_length, 0);
	ft_putnbr((ptr)->min);
}

void	print_other(t_flist *ptr, t_maxlength *max)
{
	if ((ptr->type != 'c' && ptr->type != 'b'))
	{
		if (max->maj_length)
			print_spaces(ptr, 's', max->size_length, max->min_length);
		else
			print_spaces(ptr, 's', max->size_length, 0);
		ft_putnbr(ptr->size);
	}
	else
		print_maj_min(ptr, max);
	ft_putchar(' ');
	ft_putstr(ptr->time);
	ft_putchar(' ');
	ft_putstr(ptr->name);
	if (ptr->linkedfile && ptr->type == 'l')
	{
		ft_putstr(" -> ");
		ft_putstr(ptr->linkedfile);
		ft_strdel(&ptr->linkedfile);
	}
}

void	printnode(t_flist *ptr, t_flags flags, t_maxlength *max)
{
	if (!flags.f_l && !flags.f_g)
	{
		ft_putstr(ptr->name);
		ft_putchar('\n');
	}
	else
	{
		ft_putchar(ptr->type);
		ft_putstr(ptr->permision);
		ft_putstr("  ");
		print_spaces(ptr, 'l', max->link_length, 0);
		ft_putnbr(ptr->nlink);
		ft_putchar(' ');
		if (!flags.f_g)
		{
			ft_putstr(ptr->user);
			print_spaces(ptr, 'u', max->user_length, 2);
		}
		ft_putstr(ptr->groupe);
		print_spaces(ptr, 'g', max->groupe_length, 2);
		print_other(ptr, max);
		ft_putchar('\n');
	}
}

void	printlist(t_flist *ptr, t_flags flag, int ptr_move)
{
	t_maxlength max;

	max.link_length = get_lenght(ptr, 'l', ptr_move);
	max.user_length = get_lenght(ptr, 'u', ptr_move);
	max.groupe_length = get_lenght(ptr, 'g', ptr_move);
	max.maj_length = get_lenght(ptr, 'a', ptr_move);
	max.min_length = get_lenght(ptr, 'i', ptr_move);
	max.size_length = get_lenght(ptr, 's', ptr_move);
	while ((ptr) != NULL)
	{
		if ((!flag.f_a && (ptr)->name[0] != '.') || (flag.f_a) || ptr_move == 2)
		{
			if ((ptr->type == 'l' && ptr_move == 2 &&
			!flag.f_l && get_link(ptr->name) == 2))
				ft_putstr("");
			else if ((ptr_move == 2 && ptr->type != 'd') || ptr_move == 1)
				printnode(ptr, flag, &max);
		}
		if (ptr_move)
			ptr = ptr->next;
		else
			ptr = ptr->next_file;
	}
}
