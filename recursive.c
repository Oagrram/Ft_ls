
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
        if ((ptr)->type == 'd' && ft_strcmp((ptr)->name, ".") != 0 && ft_strcmp((ptr)->name, "..") != 0)
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

// int ft_readdir(data       system, char *name)
// {
//     system.head = NULL;
//     while((system.sd = readdir(system.dir)) != NULL)
//     {
//         system.node =  new_node();
//         system.path = ft_strjoin(name, "/");
//         system.path = ft_strjoin(system.path, (system.sd)->d_name);
//         lstat(system.path, &(system.fileStat)); 
//         stockage(system.fileStat,&system.node, (system.sd)->d_name);
//         //sort_by_time(&system.node, &system.head);
//         sort_by_ascii(&system.node, &system.head);
//     }
//      //printlist(&system.head);
//     // reverse_lst(&system.head);
//     ft_check_folder(&system.head,name);
//     freelist(&system.head);
//     closedir(system.dir);
//     return (0);
// }