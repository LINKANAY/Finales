#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

#include "unogame.h"
#include "card.h"

#define NO_PLAYER -1

struct s_ugame
{
    /*
     * [COMPLETAR]
     *
     */
    card_t card;
    player_t player;
    struct s_ugame *next;
    unsigned int size;
};

unogame_t
uno_newgame(card_t card)
{
    /*
     * [COMPLETAR]
     *
     */
    unogame_t newGame = malloc(sizeof(struct s_ugame));
    newGame->card = card;
    newGame->player = NO_PLAYER;
    newGame->next = NULL;
    newGame->size = 1;
    return newGame;
}

card_t
uno_topcard(unogame_t uno)
{
    /*
     * [COMPLETAR]
     *
     */
    return uno->card;
}

unogame_t
uno_addcard(unogame_t uno, card_t c)
{
    /*
     * [COMPLETAR]
     *
     */
    if (c == NULL)
    {
        fprintf(stderr, "Error: No se puede agregar una carta nula a la pila.\n");
        return uno;
    }

    struct s_ugame *newCard = malloc(sizeof(struct s_ugame));
    if (newCard == NULL)
    {
        perror("Error al asignar memoria para el nodo");
        exit(EXIT_FAILURE);
    }
    newCard->card = c;
    newCard->player = uno_nextplayer(uno);
    newCard->next = uno;
    newCard->size = uno->size + 1;

    return newCard;
}

unsigned int
uno_count(unogame_t uno)
{
    /*
     * [COMPLETAR]
     *
     */
    struct s_ugame *current = uno;
    unsigned int size = 0;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }

    return size;
}

bool uno_validpile(unogame_t uno)
{
    /*
     * [COMPLETAR]
     *
     */
    if (uno == NULL || uno->next == NULL)
        return true; // Una carta siempre es válida

    
    struct s_ugame *current = uno;
    while (current->next != NULL)
    {
        if (!card_compatible(current->card, current->next->card))
        {
            return false;
        }
        current = current->next;
    }
    return true;
}

color_t
uno_currentcolor(unogame_t uno)
{
    /*
     * [COMPLETAR]
     *
     */
    return card_get_color(uno->card);
}

player_t
uno_nextplayer(unogame_t uno)
{
    /*
     * [COMPLETAR]
     *
     */
    assert(uno != NULL);
    if (card_get_type(uno->card) == skip)
    {
        return (uno->player + 2) % NUM_PLAYERS; // Salta un jugador
    }
    return (uno->player + 1) % NUM_PLAYERS;
}

card_t *
uno_pile_to_array(unogame_t uno)
{
    /*
     * [COMPLETAR]
     *
     */
    card_t *array = malloc(uno->size * sizeof(card_t));
    if (array == NULL)
    {
        perror("Error array: al asignar memoria");
        exit(EXIT_FAILURE);
    }
    struct s_ugame *current = uno;
    unsigned int len = uno_count(uno);
    for (int i = len - 1; i >= 0; --i)
    {
        array[i] = current->card;
        current = current->next;
    }
    return array;
}

unogame_t
uno_destroy(unogame_t uno)
{
    /*
     * [COMPLETAR]
     *
     */
    while (uno != NULL) {
        struct s_ugame *tmp = uno;
        card_destroy(uno->card); // Libera la carta
        uno = uno->next;
        free(tmp);
    }
    free(uno);
    uno = NULL;
    return uno;
}
