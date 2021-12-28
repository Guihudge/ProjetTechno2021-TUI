#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "list.h"

bool est_vide(listeSC_obj l) { return l == NULL; }

listeSC_obj creer_vide() { return NULL; }

obj donnee(listeSC_obj l) {
    assert(l);
    return l->donnee;
}

listeSC_obj suivant(listeSC_obj l) {
    assert(l);
    return l->suivant;
}

static listeSC_obj creer(obj d) {
    listeSC_obj l = (listeSC_obj)malloc(sizeof(struct listeSC_obj));
    assert(l);
    l->donnee = d;
    l->suivant = NULL;
    return l;
}

void liberer(listeSC_obj l) { free(l); }

listeSC_obj inserer(listeSC_obj l, obj d) {
    listeSC_obj tmp = (listeSC_obj)malloc(sizeof(struct listeSC_obj));
    assert(tmp);
    tmp->donnee = d;
    tmp->suivant = l;
    return tmp;
}

listeSC_obj inserer_apres(listeSC_obj l, listeSC_obj p, obj d) {
    if (p != NULL) {
        listeSC_obj nouveau = creer(d);
        nouveau->suivant = suivant(p);
        p->suivant = nouveau;
    }
    return l;
}

listeSC_obj supprimer(listeSC_obj l) {
    if (l != NULL) {
        listeSC_obj tmp = l;
        l = suivant(l);
        liberer(tmp);
    }
    return l;
}

listeSC_obj supprimer_apres(listeSC_obj l, listeSC_obj p) {
    if (p != NULL) {
        listeSC_obj a_supprimer = suivant(p);
        if (a_supprimer != NULL) {
            p->suivant = suivant(a_supprimer);
            liberer(a_supprimer);
        }
    }
    return l;
}

void liberer_liste(listeSC_obj l) {
    listeSC_obj a_liberer = l;

    while (a_liberer != NULL) {
        l = suivant(l);
        liberer(a_liberer);
        a_liberer = l;
    }
}
