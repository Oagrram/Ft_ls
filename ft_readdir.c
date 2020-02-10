/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:14:09 by oagrram           #+#    #+#             */
/*   Updated: 2020/02/09 18:14:10 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	sort_and_print(t_flist *head, t_flags flags, char *name, int total)
{
	if (flags.f_l || flags.f_g)
	{
		ft_putstr("total ");
		ft_putnbr(total);
		ft_putendl("");
	}
	if (flags.f_t)
		sort_by_time(&head);
	if (!flags.f_r)
		printlist(head, flags, 1);
	else
		reverse_lst(head, flags, 1);
	if (flags.f_rm)
		ft_check_folder(head, name, flags);
	freelist(&head, 1);
}

void	get_path(char *name, char **path, char *filename)
{
	char *tmp;

	*path = ft_strjoin(name, "/");
	tmp = *path;
	*path = ft_strjoin(*path, filename);
	ft_strdel(&tmp);
}

int		ft_readdir(t_data sys, char *name, t_flags flags)
{
	int		total;

	sys.head = NULL;
	total = 0;
	while ((sys.sd = readdir(sys.dir)) != NULL)
	{
		sys.node = new_node();
		get_path(name, &sys.path, (sys.sd)->d_name);
		if (lstat(sys.path, &(sys.state)) == -1)
		{
			ft_strdel(&sys.path);
			ft_putstr("./ft_ls: ");
			perror(name);
			return (0);
		}
		stockage(sys.state, &sys.node, (sys.sd)->d_name, sys.path);
		sort_by_ascii(&sys.node, &sys.head);
		ft_strdel(&sys.path);
		total = total + sys.state.st_blocks;
	}
	closedir(sys.dir);
	sort_and_print(sys.head, flags, name, total);
	return (0);
}
