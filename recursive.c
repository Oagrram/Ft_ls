
#include "ls.h"

// void ft_check_folder(t_flist **lst,char *path, t_flags flags)
// {
//     char *tmp;
//     t_flist *ptr;

//     ptr = (*lst);
//    if (flags.f_r)
//    {
//        while ((ptr)->next != NULL)
//         (ptr)=(ptr)->next;
//    }
//     while ((ptr) != NULL)
//     {
//         if ((ptr)->type == 'd' && ft_strcmp((ptr)->name, ".") != 0 && ft_strcmp((ptr)->name, "..") != 0
//         && ((!flags.f_a && (ptr)->name[0] != '.') || (flags.f_a)))
//         {
//             tmp = ft_strjoin(path,"/");
//             tmp = ft_strjoin(tmp,(ptr)->name);
//             printf("%s\n\n",tmp);
//              ft_recursive(tmp, flags);
//         }
//         if (flags.f_r)
//             (ptr)=(ptr)->previous;
//         else
//             (ptr) = (ptr)->next;
//     }
// }

// int ft_recursive(char *path, t_flags flags)
// {
//     get_dir(path,flags);
//     return (0);
// }

void		ft_check_folder(t_flist *p, char *path, t_flags flags)
{
	char *tmp;
	char *tofree;

	if (flags.f_r)
	{
		if (p)
			while ((p)->next != NULL)
				(p) = (p)->next;
	}
	while (p)
	{
		if (p->type == 'd' && ft_strcmp(p->name, ".") != 0 && ft_strcmp(p->name, "..") != 0
		&& ((!flags.f_a && p->name[0] != '.') || (flags.f_a)))
		{
			if (ft_strcmp(path,"/") == 0)
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

// static void show_ls_r(t_files *f, char *path, t_options *op)
// {
//     char        *path1;
//     struct stat st;
//     while (f)
//     {
//         path1 = ft_pathjoin(path, f->nom);
//         if (lstat(path1, &st) != -1)
//         {
//             if (S_ISDIR(st.st_mode))
//             {
//                 if (ft_strcmp(f->nom, "..") != 0 && ft_strcmp(f->nom, ".") != 0)
//                 {
//                     ft_putchar('\n');
//                     ft_putstr(path1);
//                     ft_putstr(":\n");
//                     ls_r(path1, op);
//                 }
//             }
//         }
//         free(path1);
//         f = f->next;
//     }
// }
// void        ls_r(char *path, t_options *op)
// {
//     t_files     *f;
//     t_files     *tmp;
//     if (!(f = solo_ls(path, op)))
//         return ;
//     tmp = f;
//     ft_order(&f, op);
//     afficher_ls(f, op, 1, path);
//     show_ls_r(f, path, op);
//     ft_del_files(&tmp);
// }
