/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:32:25 by oagrram           #+#    #+#             */
/*   Updated: 2020/02/09 17:32:26 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_flist	*new_node(void)
{
	t_flist	*node;

	node = (t_flist*)ft_memalloc(sizeof(t_flist));
	return (node);
}

int		check_argv(t_flist *p, char c, t_flags flags)
{
	int d;
	int f;

	d = 0;
	f = 0;
	while (p != NULL)
	{
		if ((p->type == 'd') || (p->type == 'l' &&
		get_link(p->name) == 2 && !flags.f_l))
			d++;
		else
			f++;
		p = p->next;
	}
	if (c == 'd')
		return (d);
	else if (c == 'f')
		return (f);
	return (0);
}

void	get_flag(char c, t_flags *flags)
{
	if (c == 'l')
		flags->f_l = 1;
	if (c == 'a')
		flags->f_a = 1;
	if (c == 'r')
		flags->f_r = 1;
	if (c == 'R')
		flags->f_rm = 1;
	if (c == 't')
		flags->f_t = 1;
	if (c == 'g')
		flags->f_g = 1;
}

int		check_flag(char *argv, t_flags *flags)
{
	int j;
	int count;

	j = 0;
	count = 1;
	while (argv[++j] != '\0')
	{
		if (argv[j] == '-')
			++count;
		if ((argv[0] == '-' && argv[j] != 'l'
		&& argv[j] != 'a' && argv[j] != 'r'
		&& argv[j] != 'R' && argv[j] != 't'
		&& argv[j] != 'g' && argv[j] != '-')
		|| (count >= 3))
		{
			ft_putstr("ft_ls: illegal option -- ");
			ft_putchar(argv[j]);
			ft_putendl("");
			ft_putendl("usage: ls [-alrRtg] [file ...]");
			return (1);
		}
		else
			get_flag(argv[j], flags);
	}
	return (0);
}
