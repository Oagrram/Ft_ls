
#include "ls.h"

void freelist(t_flist **head)
{
   t_flist *tmp;

   while (*head != NULL)
    {
       tmp = *head;
       *head = (*head)->next;
       ft_strdel(&tmp->name);
       ft_strdel(&tmp->time);
    //    ft_strdel(&tmp->user);
    //    ft_strdel(&tmp->groupe);
    //
    //    if (tmp->next_file)
    //    {
    //         ft_strdel(&tmp->name);
    //         ft_strdel(&tmp->time);
    //         ft_strdel(&tmp->user);
    //         ft_strdel(&tmp->groupe);
    //         ft_strdel(&tmp->linkedfile);
    //         ft_memdel((void**)&tmp->next_file);
    //    }
       ft_memdel((void**)&(tmp));
    }
}

void reverse_lst(t_flist      *ptr,file_flags flags,int ptr_move)
{
    maxlength max;

    max.link_length = get_lenght(ptr,'l',ptr_move);
    max.user_length = get_lenght(ptr,'u',ptr_move);
    max.groupe_length = get_lenght(ptr,'g',ptr_move);
    max.size_length = get_lenght(ptr,'s',ptr_move);
    if (ptr_move == 1)
    {
        while ((ptr)->next != NULL)
            ptr = ptr->next;
    }
    else
    {
        while ((ptr)->next_file != NULL)
            ptr = ptr->next_file;
    }
    while((ptr) != NULL)
    {
        if ((!flags.flag_a && (ptr)->name[0] != '.') || (flags.flag_a))
            printnode(ptr,flags,&max);
        if (ptr_move == 1)
           ptr = ptr->previous;
        else
            ptr = ptr->previous_file;
    }
    ft_putchar('\n');
}