#ifndef FACHNOTE_H
#define FACHNOTE_H

#include <string>

#include "benotung.h"

class fachnote {
    public:
    const std::string fach;
    const benotung note;

    fachnote();

    fachnote(const std::string& fach, const benotung& note)
    : fach(fach), note(note) {
        if (fach.length() == 0) throw std::invalid_argument("Fach darf nicht die Länge 0 haben!");
    };

    fachnote(const std::string&&, const benotung&&) = delete;
    int &length() = delete;
    bool operator==(std::string&&) = delete;


    virtual ~fachnote();
};
#endif // !FACHNOTE_H