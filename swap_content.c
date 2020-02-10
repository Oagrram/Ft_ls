/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:52:08 by oagrram           #+#    #+#             */
/*   Updated: 2020/02/09 18:52:09 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		swap_rest(t_flist **newnode, t_flist **p, t_flist **tmp)
{
	(*tmp)->nlink = (*newnode)->nlink;
	(*newnode)->nlink = (*p)->nlink;
	(*p)->nlink = (*tmp)->nlink;
	(*tmp)->user = (*newnode)->user;
	(*newnode)->user = (*p)->user;
	(*p)->user = (*tmp)->user;
	(*tmp)->groupe = (*newnode)->groupe;
	(*newnode)->groupe = (*p)->groupe;
	(*p)->groupe = (*tmp)->groupe;
	(*tmp)->time = (*newnode)->time;
	(*newnode)->time = (*p)->time;
	(*p)->time = (*tmp)->time;
	(*tmp)->name = (*newnode)->name;
	(*newnode)->name = (*p)->name;
	(*p)->name = (*tmp)->name;
	(*tmp)->mtime = (*newnode)->mtime;
	(*newnode)->mtime = (*p)->mtime;
	(*p)->mtime = (*tmp)->mtime;
	free((*tmp));
}

int			swap_maj_size(t_flist *newnode, t_flist *p, int i)
{
	int maj;
	int min;

	if (i == 1)
	{
		maj = newnode->maj;
		min = newnode->min;
		newnode->maj = 0;
		newnode->min = 0;
		p->maj = maj;
		p->min = min;
		newnode->size = p->size;
	}
	else
	{
		maj = newnode->maj;
		newnode->maj = p->maj;
		p->maj = maj;
		min = newnode->min;
		newnode->min = p->min;
		p->min = min;
	}
	return (0);
}

int			swap_linkedfile(t_flist *newnode, t_flist *p)
{
	char *tmp;

	if (newnode->type == 'l' && p->type == 'l')
	{
		tmp = newnode->linkedfile;
		newnode->linkedfile = p->linkedfile;
		p->linkedfile = tmp;
	}
	else if (newnode->type == 'l' || (p->type == 'l'))
	{
		if (newnode->type == 'l')
		{
			tmp = newnode->linkedfile;
			p->linkedfile = tmp;
		}
		else if (p->type == 'l')
		{
			tmp = p->linkedfile;
			newnode->linkedfile = tmp;
		}
	}
	return (0);
}

int			swap_type_perm(t_flist *newnode, t_flist *p, t_flist *tmp)
{
	int i;

	i = -1;
	tmp->type = newnode->type;
	newnode->type = p->type;
	p->type = tmp->type;
	while (++i < 11)
	{
		tmp->permision[i] = newnode->permision[i];
		newnode->permision[i] = p->permision[i];
		p->permision[i] = tmp->permision[i];
	}
	return (0);
}

int			swap_content(t_flist **newnode, t_flist **p)
{
	t_flist	*tmp;

	tmp = new_node();
	if (((*newnode)->type == 'b' || (*newnode)->type == 'c') &&
	((*p)->type == 'b' || (*p)->type == 'c'))
		swap_maj_size(*newnode, *p, 2);
	else if (((*newnode)->type != 'b' || (*newnode)->type != 'c') &&
	((*p)->type != 'b' || (*p)->type != 'c'))
	{
		tmp->size = (*newnode)->size;
		(*newnode)->size = (*p)->size;
		(*p)->size = tmp->size;
	}
	else if ((*newnode)->type == 'b' || (*newnode)->type == 'c')
		swap_maj_size(*newnode, *p, 1);
	swap_linkedfile(*newnode, *p);
	swap_type_perm(*newnode, *p, tmp);
	swap_rest(newnode, p, &(tmp));
	return (0);
}
