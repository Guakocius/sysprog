#ifndef FACHNOTE_H
#define FACHNOTE_H

#include <string>

#include "benotung.h"

class fachnote {
    public:
    const std::string fach;
    const benotung note;

    fachnote(const std::string& fach, const benotung& note);

    fachnote() = delete;
    fachnote(std::string&, benotung&(int)) = delete;
    fachnote& operator=(const fachnote&) = delete;
};
#endif // !FACHNOTE_H