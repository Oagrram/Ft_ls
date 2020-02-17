/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:32:42 by oagrram           #+#    #+#             */
/*   Updated: 2020/02/17 15:06:53 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_error(t_flist *head)
{
	t_data	sys;

	while (head != NULL)
	{
		if (lstat(head->name, &(sys.state)) == -1)
		{
			ft_putstr("./ft_ls: ");
			perror(head->name);
		}
		head = head->next;
	}
}

int		sort_eroor(char **t, int i)
{
	int		j;
	t_flist *head;
	t_flist *node;
	t_data	sys;

	head = NULL;
	j = 0;
	i--;
	while ((t[++i] != NULL))
	{
		if (lstat(t[i], &sys.state) == -1 && ++j)
		{
			node = new_node();
			node->name = t[i];
			sort_by_ascii(&(node), &(head));
		}
	}
	sys.node = head ? head : NULL;
	print_error(head);
	if (sys.node)
		freelist(&(sys.node), 2);
	if (j > 0)
		return (1);
	return (0);
}

int		sort_by_time(t_flist **head)
{
	t_flist *p;
	t_flist *h;

	h = *head;
	while (h)
	{
		p = h;
		while (p)
		{
			if ((h->mtime == p->mtime && (ft_strcmp(h->name, p->name) > 0))
			|| h->mtime < p->mtime)
				swap_content(&h, &p);
			p = p->next;
		}
		h = h->next;
	}
	return (0);
}

void	check_head(t_flist *node, t_flist *ptr, t_flist *tmp, t_flist **head)
{
	while (ft_strcmp(node->name, ptr->name) > 0)
	{
		tmp = ptr;
		if (!(ptr->next))
			break ;
		ptr = ptr->next;
	}
	if (!(ptr->next) && ft_strcmp(node->name, (ptr->name)) > 0)
	{
		ptr->next = node;
		node->previous = ptr;
	}
	else
	{
		node->next = ptr;
		ptr->previous = node;
		if (tmp)
		{
			tmp->next = node;
			node->previous = tmp;
		}
		else
			*head = node;
	}
}

int		sort_by_ascii(t_flist **node, t_flist **head)
{
	t_flist *ptr;
	t_flist *tmp;

	if (!*head)
	{
		*head = *node;
		return (0);
	}
	ptr = *head;
	tmp = NULL;
	check_head(*node, ptr, tmp, &(*head));
	return (0);
}
