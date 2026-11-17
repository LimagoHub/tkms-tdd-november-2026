//
// Created by JoachimWagner on 27.01.2026.
//

#pragma once
#include "blacklist_service.h"
#include "personen_service.h"
#include "../persistence/personen_repository.h"

class personen_service_impl : public personen_service{

    personen_repository &repo_;
    blacklist_service &blacklistService;

    void speichernImpl(person &person_) {
        if (person_.get_vorname().length() < 2 ) throw personen_service_exception{"Vorname zu kurz!"};

        if (person_.get_nachname().length() < 2 ) throw personen_service_exception{"Nachname zu kurz!"};

        if (blacklistService.isBlacklisted(person_) ) throw personen_service_exception{"Unerwuensche Person"};

        person_.set_id("ABCD");
        repo_.save_or_update(person_);
    }

public:
    personen_service_impl(personen_repository &repo, blacklist_service &blacklist_service)
        : repo_(repo),

          blacklistService(blacklist_service) {
    }


    /*
     *	Vorname < 2 -> PSE
     *	Nachname < 2 -> PSE
     *
     *	Attila -> PSE
     *
     *	Alle technische Exceptions -> PSE
     *
     *	Happy Day -> person an Save_or_update Methode uebergeben
     *
     */



    void speichern(person &person_) override {

        try {
            speichernImpl(person_);
        }
        catch (personen_service_exception &e) {
            throw e;
        }
        catch (std::exception &e) {
            throw personen_service_exception{"Ein Fehler ist aufgetreten!", e};
        }
        catch (...) {
            throw personen_service_exception{"Ein Fehler ist aufgetreten!"};
        }
    }


};