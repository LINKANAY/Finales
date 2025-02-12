#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "war_match.h"
#include "card.h"

struct _s_match
{
    /*
     * COMPLETAR
     *
     */
    unsigned int size;
    card card_data;
    struct _s_match *next;
};

war_match match_new(void)
{
    /*
     * COMPLETAR
     *
     */
    war_match new_match = malloc(sizeof(struct _s_match));
    new_match->card_data = NULL;
    new_match->next = NULL;
    new_match->size = 0;

    return new_match;
}

war_match match_add(war_match match, card c)
{
    /*
     * COMPLETAR
     *
     */
    if (match_size(match) == 0)
    {
        match->card_data = c;
        match->next = NULL;
        match->size = 1;
    }
    else
    {
        war_match new_node = malloc(sizeof(struct _s_match));
        new_node->card_data = c;
        new_node->next = NULL;
        war_match temp = match;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
        match->size++;
    }
    return match;
}

unsigned int match_size(war_match match)
{
    /*
     * COMPLETAR
     *
     */
    return match->size;
}

unsigned int match_length(war_match match)
{
    /*
     * COMPLETAR
     *
     */
    unsigned int res = 0;
    if ((match->size % 2 == 0) && is_match_correct(match))
    {
        res = match->size / 2;
    }
    else if (!is_match_correct(match))
    {
        res = 0;
    }
    return res;
}

bool is_match_correct(war_match match)
{
    if (match == NULL || match_size(match) % 2 != 0)
    {
        return false;
    }

    bool valid = true;
    war_match temp = match;

    // Check if the first card belongs to player 1
    if (card_player(temp->card_data) != 1)
    {
        return false;
    }

    while (temp != NULL && temp->next != NULL)
    {
        if (card_player(temp->card_data) == card_player(temp->next->card_data))
        {
            valid = false;
            break;
        }
        temp = temp->next;
    }

    return valid;
}

static unsigned int player_score(war_match match, unsigned int player)
{
    unsigned int score = 0;
    war_match temp = match;

    while (temp != NULL && temp->next != NULL)
    {
        card card1 = temp->card_data;
        card card2 = temp->next->card_data;

        if (card_player(card1) == player && card_number(card1) > card_number(card2))
        {
            score += card_number(card2);
        }
        else if (card_player(card2) == player && card_number(card2) > card_number(card1))
        {
            score += card_number(card1);
        }

        temp = temp->next->next;
    }

    return score;
}

unsigned int winner_total_points(war_match match)
{
    if (!is_match_correct(match))
    {
        return 0;
    }

    unsigned int player1_score = player_score(match, 1);
    unsigned int player2_score = player_score(match, 2);

    return player1_score > player2_score ? player1_score : player2_score;
}

card *match_to_array(war_match match)
{
    /*
     * COMPLETAR
     *
     */
    card *listCard = malloc(match->size * sizeof(card));
    if (listCard == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0;
    war_match temp = match;
    while (temp != NULL)
    {
        listCard[i] = temp->card_data;
        temp = temp->next;
        i++;
    }
    return listCard;
}

void match_dump(war_match match)
{
    card *array = match_to_array(match);
    for (unsigned int i = 0u; i < match_size(match); i++)
    {
        card_dump(array[i]);
    }
    free(array);
}

war_match match_destroy(war_match match)
{
    /*
     * COMPLETAR
     *
     */
    while (match != NULL)
    {
        card killme = match->card_data;
        war_match next = match->next;
        killme = card_destroy(killme);
        free(match);
        match = next;
    }
    return NULL;
}
