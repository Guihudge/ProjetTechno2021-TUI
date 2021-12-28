#include "pile.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

obj valeur_pile(pile_obj P) {
    if (pile_vide(P)) {
        fprintf(stderr, " ERR: valeur d' une pile vide \n");
        exit(EXIT_FAILURE);
    }
    return donnee(P);
}

bool pile_vide(pile_obj P) { return est_vide(P); }

pile_obj creer_pile() { return creer_vide(); }

pile_obj empiler(pile_obj P, obj x) { return inserer(P, x); }

pile_obj depiler(pile_obj P) {
    if (pile_vide(P)) {
        fprintf(stderr, " ERR: depiler d' une pile vide \n");
        exit(EXIT_FAILURE);
    }
    return supprimer(P);
}

void detruire_pile(pile_obj P) { liberer(P); }
