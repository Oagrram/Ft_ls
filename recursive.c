/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:32:36 by oagrram           #+#    #+#             */
/*   Updated: 2020/02/09 17:32:37 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_path(char *path, t_flist *p, t_flags flags)
{
	char *tmp;
	char *tofree;

	if (ft_strcmp(path, "/") == 0)
	{
		tmp = path;
		tmp = ft_strjoin(tmp, p->name);
	}
	else
	{
		tmp = ft_strjoin(path, "/");
		tofree = tmp;
		tmp = ft_strjoin(tmp, p->name);
		ft_strdel(&tofree);
	}
	ft_putstr("\n");
	ft_putstr(tmp);
	ft_putstr(":\n");
	ft_recursive(tmp, flags);
	ft_strdel(&tmp);
}

void	ft_check_folder(t_flist *p, char *path, t_flags flags)
{
	if (flags.f_r)
	{
		if (p)
			while ((p)->next != NULL)
				(p) = (p)->next;
	}
	while (p)
	{
		if (p->type == 'd' && ft_strcmp(p->name, ".") != 0
		&& ft_strcmp(p->name, "..") != 0
		&& ((!flags.f_a && p->name[0] != '.') || (flags.f_a)))
			print_path(path, p, flags);
		if (flags.f_r)
			p = p->previous;
		else
			p = p->next;
	}
}

int		ft_recursive(char *path, t_flags flags)
{
	get_dir(path, flags);
	return (0);
}
