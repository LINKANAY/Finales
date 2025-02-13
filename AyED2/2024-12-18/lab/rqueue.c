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
    rqueue_t new_queue = malloc(sizeof(struct _rqueue_t));
    new_queue->orientation = 0;
    new_queue->extreme[0] = NULL;
    new_queue->extreme[1] = NULL;
    return new_queue;
}

bool rqueue_is_empty(rqueue_t q)
{
    return q->extreme[0] == NULL && q->extreme[1] == NULL;
}

static node_t create_node(elem_t e)
{
    node_t new_node = malloc(sizeof(struct _node_t));
    new_node->value = e;
    new_node->links[0] = NULL;
    new_node->links[1] = NULL;
    return new_node;
}

static node_t destroy_node(node_t node)
{
    free(node);
    return NULL;
}

rqueue_t rqueue_enqueue(rqueue_t q, elem_t e)
{
    assert(q != NULL);
    node_t new_node = create_node(e);
    orientation_t prev = current(q);
    orientation_t next = inverse(q);

    if (rqueue_is_empty(q))
    {
        q->extreme[0] = new_node;
        q->extreme[1] = new_node;
    }
    else
    {
        q->extreme[prev]->links[prev] = new_node;
        new_node->links[next] = q->extreme[prev];
        q->extreme[prev] = new_node;
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
    assert(q != NULL);
    assert(!rqueue_is_empty(q));

    orientation_t prev = current(q);
    orientation_t next = inverse(q);
    node_t aux = q->extreme[prev];

    q->extreme[prev] = q->extreme[prev]->links[next];
    if (q->extreme[prev] != NULL)
    {
        q->extreme[prev]->links[prev] = NULL;
    }
    else
    {
        q->extreme[next] = NULL;
    }
    destroy_node(aux);
}

void rqueue_revert(rqueue_t q)
{
    q->extreme[current(q)] = q->extreme[inverse(q)];
}

rqueue_t rqueue_destroy(rqueue_t q)
{
    while (!rqueue_is_empty(q))
    {
        rqueue_dequeue(q);
    }
    free(q);
    return NULL;
}

void rqueue_dump(rqueue_t q)
{
    assert(q != NULL);
    orientation_t next;
    orientation_t fst;
    node_t aux = NULL;
    elem_t elem;
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
