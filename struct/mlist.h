 #ifndef MLIST_H_INCLUDED
 #define MLIST_H_INCLUDED

 #include <stdlib.h>

 typedef struct MList MList;
 typedef struct MListNode MListNode;

 struct MListNode
 {
     void * info;
     MListNode * preview;
     MListNode * next;
 };

 struct MList
 {
     int size;
     MListNode * first;
     MListNode * last;
 };

MList * newMList ()
{
    MList * list = (MList *)malloc(sizeof(MList));
    list->first = NULL;
    list->last = NULL;
    list->size = 0;

    return list;
}

MListNode * newMListNode (void * info)
{
    MListNode * node = (MListNode *)malloc(sizeof(MListNode));
    node->info = info;
    node->next = NULL;
    node->preview = NULL;

    return node;
}

void deleteMListNode (MListNode ** node)
{
    (*node)->next = NULL;
    (*node)->preview = NULL;
    free(*node);
}

 void push_front (MList ** list, void * info)
 {
     MListNode * node = newMListNode(info);
     
     if ((*list)->size == 0)
        (*list)->first = (*list)->last = node;
    else
    {
        node->next = (*list)->first;
        (*list)->first->preview = node;
        (*list)->first = node;
    }

    (*list)->size++;
 }

void push_back (MList ** list, void * info)
{
    MListNode * node = newMListNode(info);

    if ((*list)->size == 0)
        (*list)->first = (*list)->last = node;
    else
    {
        node->preview = (*list)->last;
        (*list)->last->next = node;
        (*list)->last = node;
    }

    (*list)->size++;
}

void insert (MList ** list, void * info, int (*compare)(void *, void *))
{
    if ((*list)->size == 0)
    {
        push_front(list, info);
        return;
    }

    if (compare((*list)->first->info, info) > 0)
        push_front(list, info);
    else if (compare((*list)->last, info) < 0)
        push_back(list, info);
    else
    {
        MListNode * current = (*list)->first->next;
        while (current != NULL)
        {
            if (compare(current->info, info) > 0)
            {
                MListNode * node = newMListNode(info);
                current->preview->next = node;
                node->preview = current->preview;
                node->next = current;
                current->preview = node;

                (*list)->size++;
                return;
            }
            else
                current = current->next;
        }
    }
}

void * pop_front (MList ** list)
{
    if ((*list)->size > 0)
    {
        MListNode * temp = (*list)->first;
        (*list)->first = (*list)->first->next;
        if ((*list)->first == NULL)
            (*list)->last = NULL;
        (*list)->size--;

        void * result = temp->info;
        deleteMListNode(&temp);
        temp = NULL;

        return result;
    }
    return NULL;
}

void * pop_back (MList ** list)
{
    if ((*list)->size > 0)
    {
        MListNode * temp = (*list)->last;
        (*list)->last = (*list)->last->preview;
        if ((*list)->last == NULL)
            (*list)->first = NULL;
        (*list)->size--;

        void * result = temp->info;
        deleteMListNode(&temp);
        temp = NULL;

        return result;
    }
    return NULL;
}

void * peek_front (MList * list)
{
    if (list->size > 0)
        return list->first->info;

    return NULL;
}

void * peek_back (MList * list)
{
    if (list->size > 0)
        return list->first->info;
    
    return NULL;
}

void * get_item (MList * list, void * info, int (*compare)(void *, void *))
{
    if (list->size == 0)
        return NULL;
    
    if (compare(list->first->info, info) > 0 || compare(list->last->info, info) < 0)
        return NULL;
    
    MListNode * current = list->first;
    while (current != NULL)
    {
        if (compare(current->info, info) == 0)
            return current->info;
        if (compare(current->info, info) < 0)
            current = current->next;
        else
            return NULL;
    }
}

void * get_item_unordered (MList * list, void * info, int (*compare)(void *, void *))
{
    if (list->size == 0)
        return NULL;
    
    MListNode * current = list->first;
    while (current != NULL)
    {
        if (compare(current->info, info) == 0)
            return current->info;
        current = current->next;
    }

    return NULL;
}

void clearMList(MList ** list, void (*mFree)(void **))
{
    printf("Vaciando lista >>\n");
    while ((*list)->size > 0)
    {
        void * temp = pop_front(list);
        mFree(&temp);
        temp = NULL;
    }
    printf("<< Lista vacía\n");
}

 #endif // MLIST_H_INCLUDED