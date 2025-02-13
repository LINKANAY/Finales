#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "rqueue.h"
#include "assert.h"

struct _node_t
{
    struct _node_t *links[2];
    elem_t value;
};

typedef struct _node_t *node_t;
typedef int orientation_t;

struct _rqueue_t
{
    node_t extreme[2];
    orientation_t orientation;
};

static orientation_t current(rqueue_t q)
{
    return q->orientation;
}

static orientation_t inverse(rqueue_t q)
{
    return 1 - q->orientation;
}

rqueue_t rqueue_empty()
{
    // complete here!
    rqueue_t new_queue = malloc(sizeof(struct _rqueue_t));
    new_queue->orientation = 0;
    new_queue->extreme[0] = NULL;
    new_queue->extreme[1] = NULL;

    return new_queue;
}

bool rqueue_is_empty(rqueue_t q)
{
    // complete here!
    return q->extreme[0] == NULL && q->extreme[1] == NULL;
}

static node_t create_node(elem_t e)
{
    // complete here!
    node_t new_node = malloc(sizeof(struct _node_t));
    new_node->value = e;
    new_node->links[0] = NULL;
    new_node->links[1] = NULL;

    return new_node;
}

static node_t destroy_node(node_t node)
{
    free(node);
    node = NULL;
    return node;
}

rqueue_t rqueue_enqueue(rqueue_t q, elem_t e)
{
    node_t new_node = NULL;
    node_t aux = NULL;
    orientation_t prev;
    orientation_t next;
    orientation_t lst;
    assert(q != NULL);
    new_node = create_node(e);
    if (rqueue_is_empty(q))
    {
        q->extreme[current(q)] = new_node;
        q->extreme[inverse(q)] = new_node;
    }
    else
    {
        // complete here!
        // a quien encola el primero y el ultimo
        prev = current(q);
        next = inverse(q);
        lst = (prev == 0) ? 1 : 0;
        if (lst == 0)
        {
            aux = q->extreme[prev];
            while (aux->links[next] != NULL)
            {
                aux = aux->links[next];
            }
            aux->links[next] = new_node;
        }
        if (lst == 1)
        {
            aux = q->extreme[prev];
            while (aux->links[next] != NULL)
            {
                aux = aux->links[next];
            }
            aux->links[lst] = new_node;
        }
    }

    return q;
}

elem_t rqueue_fst(rqueue_t q)
{
    assert(q != NULL);
    assert(!rqueue_is_empty(q));
    return q->extreme[current(q)]->value;
}

void rqueue_dequeue(rqueue_t q)
{
    // complete here!
    if (q != NULL)
    {
        node_t aux = NULL;
        orientation_t prev = current(q);
        orientation_t next = inverse(q);
        aux = q->extreme[prev];
        if (aux != NULL)
        {
            q->extreme[prev] = q->extreme[prev]->links[next];
            destroy_node(aux);
        }
        else
        {
            printf("Error: queue is NULL\n");
            exit(EXIT_FAILURE);
        }
    }
}

void rqueue_revert(rqueue_t q)
{
    // complete here!
    q->extreme[current(q)] = q->extreme[inverse(q)];
}

rqueue_t rqueue_destroy(rqueue_t q)
{
    // complete here!
    node_t aux = q->extreme[current(q)];
    while (aux != NULL)
    {
        node_t killme = aux;
        aux = aux->links[current(q)];
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    return q;
}

void rqueue_dump(rqueue_t q)
{
    orientation_t next;
    orientation_t fst;
    node_t aux = NULL;
    elem_t elem;
    assert(q != NULL);
    next = inverse(q);
    fst = current(q);
    aux = q->extreme[fst];
    printf("\n Queue:");
    while (aux != NULL)
    {
        elem = aux->value;
        printf("%d ", elem);
        aux = aux->links[next];
    }
    printf("\n");
}
