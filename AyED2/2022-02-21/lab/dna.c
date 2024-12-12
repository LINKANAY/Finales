#include "dna.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct _node
{
    nucleobase_t elem;
    struct _node *next;
};

struct _dna_t
{
    struct _node *chain;
    unsigned int lenght;
};

static struct _node *single_node(nucleobase_t e)
{
    struct _node *node = calloc(1, sizeof(struct _node));
    if (node == NULL)
    {
        perror("Error en single_node() al asignar memoria");
        exit(EXIT_FAILURE);
    }
    node->elem = e;
    node->next = NULL;
    return (node);
}

dna_t dna_T()
{
    dna_t res = NULL;
    /** COMPLETAR ACÁ */
    res = malloc(sizeof(struct _dna_t));
    if (res == NULL)
    {
        perror("Error en dna_T() al asignar memoria");
        exit(EXIT_FAILURE);
    }
    
    res->chain = single_node('T');
    res->lenght = 1;
    return res;
}

dna_t dna_C()
{
    dna_t res = NULL;
    /** COMPLETAR ACÁ */
    res = malloc(sizeof(struct _dna_t));
    if (res == NULL)
    {
        perror("Error en dna_C() al asignar memoria");
        exit(EXIT_FAILURE);
    }
    res->chain = single_node('C');
    res->lenght = 1;
    return res;
}

dna_t dna_A()
{
    dna_t res = NULL;
    /** COMPLETAR ACÁ */
    res = malloc(sizeof(struct _dna_t));
    if (res == NULL)
    {
        perror("Error en dna_A() al asignar memoria");
        exit(EXIT_FAILURE);
    }
    res->chain = single_node('A');
    res->lenght = 1;
    return res;
}

dna_t dna_G()
{
    dna_t res = NULL;
    /** COMPLETAR ACÁ */
    res = malloc(sizeof(struct _dna_t));
    if (res == NULL)
    {
        perror("Error en dna_G() al asignar memoria");
        exit(EXIT_FAILURE);
    }
    res->chain = single_node('G');
    res->lenght = 1;
    return res;
}

dna_t dna_join(dna_t first, dna_t second)
{
    // dna_t res = NULL;
    /** COMPLETAR ACÁ */
    if (first == NULL)
    {
        return second;
    }
    if (second == NULL)
    {
        return first;
    }
    if (first != second)
    {
        struct _node *current = first->chain;
        while (current->next != NULL)
        {
            current = current->next;
        }
        struct _node *current2 = second->chain;
        while (current2 != NULL)
        {
            current->next = single_node(current2->elem);
            current = current->next;
            first->lenght++;
            current2 = current2->next;
        }
    }
    else
    {
        perror("Error join: los dna son iguales.\n");
    }
    return first;
}

unsigned int dna_length(dna_t dna)
{
    // unsigned int res = 0u;
    /** COMPLETAR ACÁ */
    return dna->lenght;
}

void dna_print(dna_t dna)
{
    /** COMPLETAR ACÁ */
    printf("=== DNA Sequence ===\n");
    if (dna == NULL || dna->chain == NULL)
    {
        printf("[empty]\n");
    }
    else
    {
        struct _node *current = dna->chain;
        printf("Sequence: ");
        while (current != NULL)
        {
            printf("%c", current->elem);
            current = current->next;
        }
        printf("\n");
        printf("Length: %u\n", dna->lenght);
    }
    printf("====================\n");
}

bool dna_is_prefix(dna_t first, dna_t second)
{
    //bool is_prefix = true;
    /** COMPLETAR ACÁ */
    if (first == NULL || second == NULL)
    {
        return false;
    }
    
    struct _node *current1 = first->chain;
    struct _node *current2 = second->chain;

    while (current1 != NULL)
    {
        if (current2 == NULL || current1->elem != current2->elem)
        {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    return true;
}

bool dna_is_equal(dna_t first, dna_t second)
{
    bool is_equal = false;
    /** COMPLETAR ACÁ */
    if (first->lenght == second->lenght)
    {
        struct _node *cFirst = first->chain;
        struct _node *cSecond = second->chain;
        is_equal = true;

        while (cFirst != NULL && cSecond != NULL)
        {
            if (cFirst->elem != cSecond->elem)
            {
                is_equal = false;
            }
            cFirst = cFirst->next;
            cSecond = cSecond->next;
        }
    }
    else
    {
        is_equal = false;
    }
    return is_equal;
}

dna_t *dna_cut(dna_t dna, unsigned int count)
{
    dna_t *res = NULL;
    /** COMPLETAR ACÁ */
    if (dna == NULL || count >= dna->lenght)
    {
        return NULL;
    }
    
    res = malloc(2 * sizeof(dna_t));
    if (res == NULL)
    {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }

    res[0] = malloc(sizeof(struct _dna_t));
    res[1] = malloc(sizeof(struct _dna_t));
    if (res[0] == NULL || res[1] == NULL)
    {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }
    res[0]->chain = NULL;
    res[0]->lenght = 0;
    res[1]->chain = NULL;
    res[1]->lenght = 0;

    struct _node *current = dna->chain;
    struct _node *prev = NULL;

    for (size_t i = 0; i < dna_length(dna); i++)
    {
        struct _node *newNode = single_node(current->elem);

        if (i < count)
        {
            if (res[0]->chain == NULL)
            {
                res[0]->chain = newNode;
            }
            else
            {
                prev->next = newNode;
            }
            res[0]->lenght++;
        }
        else
        {
            if (res[1]->chain == NULL)
            {
                res[1]->chain = newNode;
            }
            else
            {
                prev->next = newNode;
            }
            res[1]->lenght++;
        }
        prev = newNode;
        current = current->next;
    }

    return res;
}

dna_t dna_destroy(dna_t dna)
{
    /** COMPLETAR ACÁ */
    if (dna == NULL)
    {
        return NULL;
    }

    struct _node *current = dna->chain;
    while (current != NULL)
    {
        struct _node *killme = current;
        current = current->next;
        free(killme);
    }
    free(dna);
    dna = NULL;

    return dna;
}

