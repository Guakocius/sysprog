#include "fachnoten_liste.h"

//----------------------------------------------------- Klasse fachnoten_liste::element
class fachnoten_liste::element final {
    element *next;
    fachnote* note;

    element(element *e, fachnote* f)
    : next(e), note(f) {};

    friend class fachnoten_liste;
    friend class fachnoten_liste::iterator;
};

//----------------------------------------- Member-Funktionen fachnoten_liste::iterator
fachnoten_liste::iterator::iterator(element *e)
: current(e) {};

bool fachnoten_liste::iterator::iterator::operator!=(const iterator &i) const { return this->current != i.current; };

fachnote* &fachnoten_liste::iterator::operator*() const { return this->current->note; };

fachnoten_liste::iterator& fachnoten_liste::iterator::operator++() {
    this->current = this->current->next;
    return *this;
};

//--------------------------------------------------- Member-Funktionen fachnoten_liste
fachnoten_liste::fachnoten_liste(void (*) (fachnote*))
: head(nullptr), note(nullptr) {};

fachnoten_liste::~fachnoten_liste() {
    element *e = this->head;
    fachnote *f = this->note;
    while (e != nullptr) {
        element *x = e;
        fachnote *fx = f;
        e = e->next;
        f = e->next->note;
        delete x;
        delete fx;
    }
}

fachnoten_liste &fachnoten_liste::insert(fachnote *f) {
    this->head = new element(this->head, f);
    return *this;
}

fachnoten_liste::iterator fachnoten_liste::begin() { return fachnoten_liste::iterator(this->head); };

fachnoten_liste::iterator fachnoten_liste::end() { return fachnoten_liste::iterator(nullptr); };
