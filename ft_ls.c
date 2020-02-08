/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 21:42:48 by oagrram           #+#    #+#             */
/*   Updated: 2020/02/08 21:42:51 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		get_argument(t_flist **argument, char *argv, t_flist **head)
{
	t_data	sys;

	if (lstat(argv, &(sys.state)) != -1)
	{
		stockage(sys.state, &(*argument), argv, argv);
		sort_by_ascii(&(*argument), &(*head));
	}
	return (0);
}

void	struct_ins(t_ftls *str, char **argv, int i, t_flags flags)
{
	int j;

	j = 0;
	str->head = NULL;
	str->nero = sort_eroor(argv, i);
	while (argv[i] && ((str->node = new_node()) != NULL))
		if (get_argument(&str->node, argv[i++], &str->head) == 1)
			j++;
	if (j == str->argc || str->head == NULL)
		return ;
	str->nf = check_argv(str->head, 'f', flags);
	str->nd = check_argv(str->head, 'd', flags);
	get_files(&str->head, flags);
	if (flags.f_r)
		while (str->head->next != NULL)
			str->head = str->head->next;
}

void	ft_ls(char **argv, int argc, t_flags flags, int i)
{
	t_ftls str;

	str.argc = argc;
	struct_ins(&str, argv, i, flags);
	while (str.head != NULL)
	{
		if ((str.head->type == 'd') || (str.head->type == 'l' &&
		get_link(str.head->name) == 2 && !flags.f_l))
		{
			if (str.c != 0 || (str.c == 0 && str.nf >= 1 && str.nd >= 1))
				ft_putstr("\n");
			if ((str.nf >= 1 && str.nd >= 1) ||
			str.nd >= 2 || (str.nero == 1 && str.c == 0))
			{
				ft_putstr(str.head->name);
				ft_putstr(":\n");
			}
			get_dir(str.head->name, flags);
		}
		if (!flags.f_r)
			str.head = str.head->next;
		else
			str.head = str.head->previous;
		++str.c;
	}
}

void	ft_zero(t_flags *flags)
{
	flags->f_g = 0;
	flags->f_r = 0;
	flags->f_rm = 0;
	flags->f_t = 0;
	flags->f_a = 0;
	flags->f_l = 0;
}

int		main(int argc, char **argv)
{
	t_flags		flags;
	int			i;

	i = 0;
	ft_zero(&flags);
	while (argv[++i] && argv[i][0] == '-')
		if (check_flag(argv[i], &flags))
			return (0);
	if (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1] == '-' && !argv[i][2])
		{
			if (!argv[i + 1])
			{
				get_dir(".", flags);
				return (0);
			}
			else
				i++;
		}
	}
	else if (!argv[i])
		get_dir(".", flags);
	ft_ls(argv, argc, flags, i);
	return (0);
}
