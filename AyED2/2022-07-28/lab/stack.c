#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "stack.h"

#define CHUNK_CAPACITY 5

struct s_node
{
    // COMPLETAR
    int *chunk;        /*apunta a un arreglo que es donde se guardan los elementos*/
    unsigned int used; /*size*/
    struct s_node *next;
};

struct _s_stack
{
    // COMPLETAR
    struct s_node *top;
    unsigned int size;
};

static bool
valid_chunks(stack s)
{
    bool valid = true;
    struct s_node *check = s->top;
    if (check != NULL)
    {
        // Completar
        while (check != NULL)
        {
            if (check->chunk == NULL)
            {
                valid = false;
                break;
            }
            if (check->used > CHUNK_CAPACITY)
            {
                valid = false;
                break;
            }
            check = check->next;
        }
    }
    return valid;
}

static bool
invrep(stack s)
{
    // COMPLETAR
    // return (s != NULL && valid_chunks(s));
    if (s == NULL)
    {
        printf("stack vacio.\n");
        return true;
    }
    if (s->top == NULL && s->size != 0)
    {
        printf("Inconsitencia: stack vacio pero size != 0, size = %u\n", s->size);
        return false;
    }

    if (!valid_chunks(s))
    {
        printf("Inconsistencia con los datos del chunk.\n");
        return false;
    }

    // detectar ciclos en la lista
    struct s_node *slow = s->top;
    struct s_node *fast = s->top;
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

    /*verificar size con el conteo*/
    // Verificar consistencia entre `size` y número total de elementos
    unsigned int total_elements = 0;
    struct s_node *current = s->top;

    while (current != NULL)
    {
        if (current->chunk == NULL || current->used > CHUNK_CAPACITY)
            return false;

        total_elements += current->used;
        current = current->next;
    }
    if (!(total_elements == s->size))
    {
        return false;
    }
    
    return true;
}

static struct s_node *
create_node(void)
{
    /*
     * COMPLETAR
     *
     */
    struct s_node *newNodo = malloc(sizeof(struct s_node));
    newNodo->chunk = NULL;
    newNodo->next = NULL;
    newNodo->used = 0;

    return newNodo;
}

static struct s_node *
destroy_node(struct s_node *node)
{
    /*
     * COMPLETAR
     *
     */
    if (node != NULL)
    {
        free(node->chunk);
        free(node);
        node = NULL;
    }
    return node;
}

stack stack_empty(void)
{
    stack new = malloc(sizeof(struct _s_stack));
    if (new == NULL)
    {
        perror("Error al asignar memoria para la pila.\n");
        exit(EXIT_FAILURE);
    }
    new->top = NULL;
    new->size = 0;
    assert(invrep(new) && stack_is_empty(new));
    return new;
}

stack stack_push(stack s, stack_elem e)
{
    /*
     * COMPLETAR
     */
    assert(invrep(s));
    if (s->top == NULL || s->top->used == CHUNK_CAPACITY)
    {
        /*creo nodo si la pila esta vacia o el chink esta lleno*/
        struct s_node *newNode = create_node();
        if (newNode == NULL)
        {
            perror("Error en asignar memoria.\n");
            exit(EXIT_FAILURE);
        }
        newNode->chunk = malloc(CHUNK_CAPACITY * sizeof(int));
        if (newNode->chunk == NULL)
        {
            perror("Error al asignar memoria para el chunk.\n");
            free(newNode);
            exit(EXIT_FAILURE);
        }
        /*iniciar capos del nodo*/
        newNode->used = 0;
        newNode->next = s->top;
        s->top = newNode;
    }
    /*agregar el elemento al chunk del nodo superior*/
    s->top->chunk[s->top->used] = e;
    s->top->used++;
    s->size++;
    assert(invrep(s) && !stack_is_empty(s));
    return s;
}

stack stack_pop(stack s)
{
    /*
     * COMPLETAR
     *
     */
    assert(invrep(s) && !stack_is_empty(s));
    /*Eliminar el elemento del nodo mas alto*/
    s->top->used--;
    s->size--;

    /*Si el nodo queda vacio, eliminar el nodo*/
    if (s->top->used == 0)
    {
        struct s_node *old = s->top;
        s->top = s->top->next;
        old = destroy_node(old);
    };

    assert(invrep(s));
    return s;
}

unsigned int stack_size(stack s)
{
    /*
     * COMPLETAR
     *
     */
    return s->size;
}

void stack_top(stack s, stack_elem *top)
{
    /*
     * COMPLETAR
     *
     */
    assert(invrep(s) && !stack_is_empty(s) && top != NULL);
    *top = s->top->chunk[s->top->used - 1];
}

bool stack_is_empty(stack s)
{
    /*
     * COMPLETAR
     *
     */
    return (s->size == 0);
}

stack_elem *stack_to_array(stack s)
{
    /*
     * COMPLETAR
     *
     */
    stack_elem *array = malloc(s->size * sizeof(stack_elem));
    if (array == NULL)
    {
        perror("Error al asignar memoria para el arreglo.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = s->size;

    struct s_node *current = s->top;
    while (current != NULL)
    {
        for (int j = current->used - 1; j >= 0; --j)
        {
            array[--i] = current->chunk[j];
        }
        current = current->next;
    }
    return array;
}

stack stack_destroy(stack s)
{
    /*
     * COMPLETAR
     *
     */
    while (s->top != NULL)
    {
        struct s_node *killme = s->top;
        s->top = s->top->next;
        killme = destroy_node(killme);
    }
    free(s);
    s = NULL;
    return s;
}
