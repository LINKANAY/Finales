#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "card.h"

struct s_card
{
    unsigned int num;
    color_t color;
    type_t type;
};

static bool
invrep(card_t c)
{
    // Invariante de representación
    /*
     * [COMPLETAR]
     *
     * Mejorar la invariante chequeando más
     * propiedades de los campos de la estructura
     *
     */
    if (c == NULL) return false;

    bool valid_color = (c->color == red || c->color == green || 
                        c->color == blue || c->color == yellow);
    bool valid_type = (c->type == normal || c->type == change_color || 
                        c->type == skip);
    bool valid_num = (c->num < 10); // Sólo cartas normales tienen número

    return valid_color && valid_type && valid_num;
}

card_t
card_new(unsigned int num, color_t color, type_t s)
{
    card_t card = NULL;
    /*
     * [COMPLETAR]
     *
     */
    if (num >= 10 || !(color == red || color == green || color == blue || color == yellow) ||
        !(s == normal || s == change_color || s == skip)) {
        fprintf(stderr, "Error: Valores inválidos para la carta.\n");
        return NULL;
    }

    card = malloc(sizeof(struct s_card));
    if (card == NULL) {
        perror("Error al asignar memoria para la carta");
        exit(EXIT_FAILURE);
    }
    card->num = num;
    card->color = color;
    card->type = s;

    return card;
}

type_t
card_get_number(card_t card)
{
    //assert(invrep(card));
    return card->num;
}

color_t
card_get_color(card_t card)
{
    //assert(invrep(card));
    return card->color;
}

type_t
card_get_type(card_t card)
{
    if (card == NULL) {
        fprintf(stderr, "Error: card_get_type recibió un puntero NULL.\n");
        exit(EXIT_FAILURE);
    }

    //assert(invrep(card));
    return card->type;
}

bool card_samecolor(card_t c1, card_t c2)
{
    /*
     * [COMPLETAR]
     *
     */
    return (c1->color == c2->color);
}

bool card_samenum(card_t c1, card_t c2)
{
    /*
     * [COMPLETAR]
     *
     */
return (c1->num == c2->num);
}

bool card_compatible(card_t new_card, card_t pile_card)
{
    bool compatible = false;
    assert(invrep(new_card) && invrep(pile_card));
    /*
     * [COMPLETAR]
     *
     */
    if (new_card->color == pile_card->color)
    {
        compatible = true;
    }
    if(new_card->type == change_color)
    {
        compatible = true;
    }
    if((new_card->type == normal && pile_card->type == normal) &&( 
    (new_card->color == pile_card->color) || new_card->num == pile_card->num))
    {
        compatible = true;
    }
    if(new_card->type == skip && 
        (pile_card->type == skip || pile_card->color == new_card->color) )
    {
        compatible = true;
    }
    return compatible;
}

card_t
card_destroy(card_t card)
{
    /*
     * [COMPLETAR]
     *
     */
    if (card != NULL) {
        free(card);
        card = NULL; // Asegurar que el puntero no quede colgando
    }
    return card;
}
