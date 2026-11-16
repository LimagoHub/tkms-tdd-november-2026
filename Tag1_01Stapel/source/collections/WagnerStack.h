//
// Created by JoachimWagner on 16.11.2026.
//

#pragma once


class WagnerStack {

private:
    bool empty{true};
public:
    bool IsEmpty() {
        return empty;
    }

    void push(int i) {
        empty= false;
    }
};
