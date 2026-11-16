//
// Created by JoachimWagner on 16.11.2026.
//

#pragma once
#include <stdexcept>
#include <ostream>

class Schwein {

    inline static constexpr int initial_weight{ 10};
    std::string name;
    int gewicht;

    void set_gewicht(int gewicht) {
        this->gewicht = gewicht;
    }

public:
    explicit Schwein(const std::string &name = "Nobody")
        : name(name), gewicht(INITIAL_WEIGHT) {

    }



    void set_name(const std::string &name) {
        if (name == "Elsa") throw std::invalid_argument("Name verstoesst gegen die Schweinewuerde!");
        this->name = name;
    }


    void fuettern() {
        set_gewicht(get_gewicht() + 1);
    }



    // ---------------------- generated Code --------------------

    [[nodiscard]] std::string get_name() const {
        return name;
    }

    [[nodiscard]] int get_gewicht() const {
        return gewicht;
    }

    friend std::ostream & operator<<(std::ostream &os, const Schwein &obj) {
        return os
               << "name: " << obj.name
               << " gewicht: " << obj.gewicht;
    }

    friend bool operator==(const Schwein &lhs, const Schwein &rhs) {
        return lhs.name == rhs.name
               && lhs.gewicht == rhs.gewicht;
    }

    friend bool operator!=(const Schwein &lhs, const Schwein &rhs) {
        return !(lhs == rhs);
    }
};
