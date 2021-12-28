#ifndef __LIST__
#define __LIST__

#include "../libgame/game_struct.h"

typedef move_pile obj;

struct listeSC_obj {
    obj donnee;
    struct listeSC_obj* suivant;
};

typedef struct listeSC_obj* listeSC_obj;

bool est_vide(listeSC_obj l);
listeSC_obj creer_vide();
obj donnee(listeSC_obj l);
listeSC_obj suivant(listeSC_obj l);
listeSC_obj creer(obj d);
void liberer(listeSC_obj l);
listeSC_obj inserer(listeSC_obj l, obj d);
listeSC_obj inserer_apres(listeSC_obj l, listeSC_obj p, obj d);
listeSC_obj supprimer(listeSC_obj l);
listeSC_obj supprimer_apres(listeSC_obj l, listeSC_obj p);
void liberer_liste(listeSC_obj l);

#endif