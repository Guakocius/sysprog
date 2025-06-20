#ifndef BENOTUNG_H
#define BENOTUNG_H

#include <stdexcept>

struct benotung {
    private:

    int note;

    public:

    explicit benotung(int note);

    static const benotung beste, schlechteste;

    int int_value() const;
    bool ist_bestanden() const;
    bool is_valid_grade(int note) const;
    friend bool operator==(benotung, benotung);

};
#endif // !BENOTUNG_H