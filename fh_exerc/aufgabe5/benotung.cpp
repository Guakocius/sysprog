#include "benotung.h"

int note;

bool benotung::is_valid_grade(int note) const {
    const int valid_grades[] = {10, 13, 17, 20, 23, 27, 30, 33, 37, 40, 50};
    for (int n : valid_grades) {
        if (note == n) {
            return true;
        } else {
            throw(std::invalid_argument("unzulaessige Note %d"), note);
            return false;
        }
    }
    return false;
}
const benotung benotung::beste = benotung(10);

const benotung benotung::schlechteste = benotung(50);

int benotung::int_value() const {
    return this->note;
}

bool benotung::ist_bestanden() const {
    return this->note <= 40;
}

bool operator==(benotung n1, benotung n2) {
    return n1.note - n2.note == 0;
}