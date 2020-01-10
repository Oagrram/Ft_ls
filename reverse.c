
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

void reverse_lst(t_flist      *lst,file_flags flags)
{
    t_flist *ptr;
    maxlength max;

    ptr = lst;
    max.link_length = get_lenght(ptr,'l');
    max.user_length = get_lenght(ptr,'u');
    max.groupe_length = get_lenght(ptr,'g');
    max.size_length = get_lenght(ptr,'s');
    while ((ptr)->next != NULL)
        (ptr)=(ptr)->next;
    while((ptr) != NULL)
    {
        if ((!flags.flag_a && (ptr)->name[0] != '.') || (flags.flag_a))
            printnode(ptr,flags,&max);
        (ptr)=(ptr)->previous;
    }
    ft_putchar('\n');
}