/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:32:31 by oagrram           #+#    #+#             */
/*   Updated: 2020/02/09 17:32:32 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	freelist(t_flist **head, int i)
{
	t_flist *tmp;

	while (*head != NULL)
	{
		tmp = *head;
		*head = (*head)->next;
		if (i == 2)
		{
			ft_strdel(&tmp->name);
			ft_memdel((void**)&(tmp));
		}
		else
		{
			ft_strdel(&tmp->name);
			ft_strdel(&tmp->time);
			ft_memdel((void**)&(tmp));
		}
	}
}

int		p_move(t_flist **p, int ptr_move)
{
	if (ptr_move == 1)
	{
		while ((*p)->next != NULL)
			(*p) = (*p)->next;
	}
	else
	{
		while ((*p)->next_file != NULL)
			(*p) = (*p)->next_file;
	}
	return (0);
}

void	reverse_lst(t_flist *p, t_flags flags, int ptr_move)
{
	t_maxlength max;

	max.link_length = get_lenght(p, 'l', ptr_move);
	max.user_length = get_lenght(p, 'u', ptr_move);
	max.groupe_length = get_lenght(p, 'g', ptr_move);
	max.maj_length = get_lenght(p, 'a', ptr_move);
	max.min_length = get_lenght(p, 'i', ptr_move);
	max.size_length = get_lenght(p, 's', ptr_move);
	p_move(&(p), ptr_move);
	while (p != NULL)
	{
		if ((!flags.f_a && p->name[0] != '.') || (flags.f_a) || ptr_move == 2)
		{
			if (p->type == 'l' && ptr_move == 2 &&
			!flags.f_l && get_link(p->name) == 2)
				get_dir(p->name, flags);
			else
				printnode(p, flags, &max);
		}
		if (ptr_move == 1)
			p = p->previous;
		else
			p = p->previous_file;
	}
}
