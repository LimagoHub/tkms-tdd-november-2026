//
// Created by JoachimWagner on 16.11.2026.
//

#pragma once
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

class Schwein {
    inline static constexpr int initial_weight{10};
    inline static constexpr std::string_view verbotener_name{"Elsa"};
    inline static constexpr std::string_view fehlermeldung{"Name verstoesst gegen die Schweinewuerde!"};

    std::string name;
    int gewicht;

    // Prueft den Namen und gibt ihn bei Erfolg unveraendert zurueck.
    [[nodiscard]] static auto pruefe_name(std::string name) -> std::string {
        if (name == verbotener_name) throw std::invalid_argument(std::string{fehlermeldung});
        return name;
    }

    auto set_gewicht(int gewicht) noexcept -> void {
        this->gewicht = gewicht;
    }

public:


    explicit Schwein(std::string name = "Nobody")
        : name(pruefe_name(std::move(name))), gewicht(initial_weight) {
    }

    auto set_name(std::string name) -> void {
        this->name = pruefe_name(std::move(name));
    }

    auto fuettern() noexcept -> void {
        set_gewicht(get_gewicht() + 1);
    }

    // ---------------------- generated Code --------------------

    [[nodiscard]] auto get_name() const noexcept -> const std::string & {
        return name;
    }

    [[nodiscard]] auto get_gewicht() const noexcept -> int {
        return gewicht;
    }

    friend auto operator<<(std::ostream &os, const Schwein &obj) -> std::ostream & {
        return os
               << "name: " << obj.name
               << " gewicht: " << obj.gewicht;
    }

    friend auto operator==(const Schwein &lhs, const Schwein &rhs) noexcept -> bool {
        return lhs.name == rhs.name
               && lhs.gewicht == rhs.gewicht;
    }

    friend auto operator!=(const Schwein &lhs, const Schwein &rhs) noexcept -> bool {
        return !(lhs == rhs);
    }
};
