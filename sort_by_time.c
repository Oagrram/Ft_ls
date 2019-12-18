

#include "ls.h"

t_flist *sort_by_time(t_flist **node, t_flist **lst)
{
    t_flist *ptr;
    t_flist *tmp;

    if (!*lst)
    {
        *lst = *node;

        return (*lst);
    }
    ptr = *lst;
    tmp = NULL;
    while (((*node)->mtime <= ptr->mtime))
    {
        if ((*node)->mtime == ptr->mtime && ft_strcmp((*node)->name, ptr->name) < 0)
            break ;
        tmp = ptr;
        if (!ptr->next)
            break ;
        ptr = ptr->next;
    }
    if (!(ptr->next) && (*node)->mtime < ptr->mtime)
        ptr->next = *node;
    else
    {
        (*node)->next = ptr;
        if (tmp)
            tmp->next = *node;
        else
            *lst = *node;
    }
    return (*lst);
}