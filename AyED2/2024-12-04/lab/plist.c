#include <stdlib.h>  /* malloc(), free(), NULL  */
#include <stdbool.h> /* Definition of bool      */
#include <stdio.h>   /* printf()                */
#include <assert.h>  /* assert()                */

#include "plist.h" /* Iterface */

struct s_node
{
    t_elem elem;
    struct s_node *next;
};

typedef struct s_node *node_t;

struct s_plist
{
    /*
     * COMPLETAR
     */
    struct s_node *list;
    int pivot;
    unsigned int size;
};

/* Creates a single node in dynamic memory containing the element <e>. */
static node_t create_node(t_elem e)
{
    /* COMPLETAR */
    struct s_node *newNode = malloc(sizeof(struct s_node));
    newNode->elem = e;
    newNode->next = NULL;

    return newNode;
}

/* Destroys a single node */
static node_t destroy_node(node_t node)
{
    /* COMPLETAR */
    free(node);
    node = NULL;
    return node;
}

/* Representation invariant */
static bool invrep(plist l)
{
    /* COMPLETAR */
    if (l == NULL)
    {
        return true;
    }
    
    if (l->list == NULL && l->size != 0)
    {
        printf("Inconsitencia: lista vacia pero size != 0, size = %u\n", l->size);
        return false;
    }
    
    // detectar ciclos en la lista
    struct s_node *slow = l->list;
    struct s_node *fast = l->list;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
        {
            // ciclo detectado
            printf("Error: ciclo detectado en la lista.\n");
            return false;
        }
    }

    unsigned int total = 0;
    node_t current = l->list;
    while (current != NULL)
    {
        total++;
        current = current->next;
    }
    if (!(total == l->size))
    {
        return false;
    }
    

    if (plist_count(l, plist_get_pivot(l)) == 1)
    {
        return false;
    }
    

    return true;
}

/* CONSTRUCTORS */

plist plist_create(t_elem pivot)
{
    /* COMPLETAR */
    plist newList = malloc(sizeof(struct s_plist));
    newList->list = create_node(pivot);
    newList->pivot = pivot;
    newList->size = 1;
   

    assert(invrep(newList) && !plist_is_empty(newList));
    return newList;
}

plist plist_add(plist l, t_elem e)
{
    /* COMPLETAR */
    assert(invrep(l) && e != plist_get_pivot(l));
    node_t newNode = create_node(e);
    if (e < plist_get_pivot(l))
    { // elementos menores que el pivote add left
        newNode->next = l->list;
        l->list = newNode;
    }
    else
    { // elementos mayores al pivot add right
        node_t current = l->list;
        while (current != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    l->size++;
    assert(invrep(l) && !plist_is_empty(l));
    return l;
}

/* OPERATIONS   */
unsigned int plist_length(plist l)
{
    /* COMPLETAR */
    return l->size;
}

bool plist_is_empty(plist l)
{
    /* COMPLETAR */
    return (l->size == 0);
}

t_elem plist_get_pivot(plist l)
{
    /* COMPLETAR */
    return l->pivot;
}

plist plist_delete_prev(plist l)
{
    assert(invrep(l));
    if (l->list == NULL || l->list->elem >= plist_get_pivot(l))
    {
        return l;
    }

    node_t prev = NULL;
    node_t current = l->list;

    while (current != NULL && current->elem < plist_get_pivot(l))
    {
        prev = current;
        current = current->next;
    }

    if (prev != NULL)
    {
        l->list = current;
        destroy_node(prev);
        l->size--;
    }

    assert(invrep(l));
    return l;
}

plist plist_delete_next(plist l)
{
    assert(invrep(l));
    if (l == NULL || l->list == NULL)
    {
        return l;
    }

    node_t current = l->list;
    while (current != NULL && current->elem < plist_get_pivot(l))
    {
        current = current->next;
    }

    if (current != NULL && current->next != NULL)
    {
        node_t node_to_delete = current->next;
        current->next = node_to_delete->next;
        destroy_node(node_to_delete);
        l->size--;
    }

    assert(invrep(l));
    return l;
}

unsigned int plist_count(plist l, t_elem e)
{
    /* COMPLETAR */
    assert(invrep(l) && !plist_is_empty(l));
    int count = 0;
    node_t current = l->list;
    while (current != NULL)
    {
        if (current->elem == e)
        {
            count++;
        }
        current = current->next;
    }
    assert(invrep(l));
    return count;
}

t_elem *plist_to_array(plist l)
{
    /* COMPLETAR */
    assert(invrep(l));
    int *array = NULL;
    array = malloc(plist_length(l) * sizeof(int));

    node_t current = l->list;
    unsigned int i = 0;
    while (current != NULL)
    {
        array[i] = current->elem;
        current = current->next;
        i++;
    }

    assert(!plist_is_empty(l) && array != NULL);
    return array;
}

void plist_dump(plist l)
{
    assert(invrep(l));
    if (plist_is_empty(l))
    {
        printf("[]");
    }
    else
    {
        t_elem *elems = plist_to_array(l);
        printf("[ ");
        t_elem_dump(elems[0]);
        for (unsigned int i = 1; i < plist_length(l); i++)
        {
            printf(", ");
            t_elem_dump(elems[i]);
        }
        printf(" ]");
        free(elems);
    }
}

plist plist_destroy(plist l)
{
    /* COMPLETAR */
    assert(invrep(l));
    if (l == NULL)
    {
        return l;
    }
    node_t current = l->list;
    while (current != NULL)
    {
        node_t killme = current;
        current = current->next;
        free(killme);
    }
    free(l);
    l = NULL;
    assert(l == NULL);
    return l;
}
