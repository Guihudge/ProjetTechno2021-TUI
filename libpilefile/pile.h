#ifndef __PILE_H__
#define __PILE_H__

#include "list.h"
#include "../libgame/game_struct.h"
#include "../libgame/game.h"

typedef obj move;

typedef listeSC_obj pile_obj;
obj valeur_pile(pile_obj P);
bool pile_vide(pile_obj P);
pile_obj creer_pile();
pile_obj empiler(pile_obj P, obj x);
pile_obj depiler(pile_obj P);
void detruire_pile(pile_obj P);

#endif
