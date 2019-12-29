
#include "ls.h"

int ft_check_folder(t_flist **lst,char *path)
{
    char *tmp;
    t_flist *lsttmp;
    lsttmp = (*lst);
   // printf("path == %s\n",path);
    while ((lsttmp) != NULL)
    {
        if ((lsttmp)->type == 'd' && ft_strcmp((lsttmp)->name, ".") != 0 && ft_strcmp((lsttmp)->name, "..") != 0)
        {
            tmp = ft_strjoin(path,"/");
            tmp = ft_strjoin(tmp,(lsttmp)->name);
            printf("%s\n\n",tmp);
             ft_recursive(tmp);
        }
        (lsttmp) = (lsttmp)->next;
    }
    return 0;

}

// int ft_recursive(char *path)
// {
//     ft_get_info(path);
//     return (0);
// }

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