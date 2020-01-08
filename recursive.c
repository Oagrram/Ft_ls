
#include "ls.h"

void ft_check_folder(t_flist **lst,char *path, file_flags flags)
{
    char *tmp;
    t_flist *ptr;

    ptr = (*lst);
   if (flags.flag_r)
   {
       while ((ptr)->next != NULL)
        (ptr)=(ptr)->next;
   }
    while ((ptr) != NULL)
    {
        if ((ptr)->type == 'd' && ft_strcmp((ptr)->name, ".") != 0 && ft_strcmp((ptr)->name, "..") != 0
        && ((!flags.flag_a && (ptr)->name[0] != '.') || (flags.flag_a)))
        {
            tmp = ft_strjoin(path,"/");
            tmp = ft_strjoin(tmp,(ptr)->name);
            printf("%s\n\n",tmp);
             ft_recursive(tmp, flags);
        }
        if (flags.flag_r)
            (ptr)=(ptr)->previous;
        else
            (ptr) = (ptr)->next;
    }
}

int ft_recursive(char *path, file_flags flags)
{
    ft_get_info(path,flags);
    return (0);
}