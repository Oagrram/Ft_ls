
#include "ls.h"

void freelist(t_flist **head)
{
   t_flist *tmp;

   while (*head != NULL)
    {
       tmp = *head;
       *head = (*head)->next;
       ft_memdel((void**)&(tmp));
    }
}

void reverse_lst(t_flist      *lst,file_flags flags,int ptr_move)
{
    t_flist *ptr;
    maxlength max;

    ptr = lst;
    max.link_length = get_lenght(ptr,'l',ptr_move);
    max.user_length = get_lenght(ptr,'u',ptr_move);
    max.groupe_length = get_lenght(ptr,'g',ptr_move);
    max.size_length = get_lenght(ptr,'s',ptr_move);
    while ((ptr)->next != NULL)
    {
        if (ptr_move == 1)
            ptr = ptr->next;
        else
            ptr = ptr->next_file;
    }
    while((ptr) != NULL)
    {
        if ((!flags.flag_a && (ptr)->name[0] != '.') || (flags.flag_a))
            printnode(ptr,flags,&max);
        if (ptr_move == 1)
           ptr =ptr->previous;
        else
            ptr = ptr->previous_file;
        
    }
    ft_putchar('\n');
}