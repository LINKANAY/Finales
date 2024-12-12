#include <stdlib.h>   /* malloc(), free(), NULL  */
#include <stdbool.h>  /* Definition of bool      */
#include <stdio.h>    /* printf()                */
#include <assert.h>   /* assert()                */

#include "plist.h"      /* Iterface */

struct s_node {
    t_elem elem;
    struct s_node *next;
};

typedef struct s_node * node_t;

struct s_plist {
    /*
     * COMPLETAR
     */
};

/* Creates a single node in dynamic memory containing the element <e>. */
static node_t create_node(t_elem e) {
    /* COMPLETAR */
}

/* Destroys a single node */
static node_t destroy_node(node_t node) {
    /* COMPLETAR */
}

/* Representation invariant */
static bool invrep(plist l) {
    /* COMPLETAR */
}

/* CONSTRUCTORS */

plist plist_create(t_elem pivot) {
    /* COMPLETAR */
}

plist plist_add(plist l, t_elem e) {
    /* COMPLETAR */
}

/* OPERATIONS   */
unsigned int plist_length(plist l) {
     /* COMPLETAR */
}

bool plist_is_empty(plist l) {
    /* COMPLETAR */
}

t_elem plist_get_pivot(plist l) {
    /* COMPLETAR */
}

plist plist_delete_prev(plist l) {
    /* COMPLETAR */
}

plist plist_delete_next(plist l) {
    /* COMPLETAR */
}

unsigned int plist_count(plist l, t_elem e) {
    /* COMPLETAR */
}

t_elem * plist_to_array(plist l) {
    /* COMPLETAR */
}

void plist_dump(plist l) {
    assert(invrep(l));
    if (plist_is_empty(l)) {
        printf("[]");
    } else {
        t_elem *elems = plist_to_array(l);
        printf("[ ");
        t_elem_dump(elems[0]);
        for (unsigned int i=1; i < plist_length(l); i++) {
            printf(", ");
            t_elem_dump(elems[i]);
        }
        printf(" ]");
        free(elems);
    }
}

plist plist_destroy(plist l) {
    /* COMPLETAR */
}

