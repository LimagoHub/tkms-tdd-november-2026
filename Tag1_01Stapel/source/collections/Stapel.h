//
// Created by JoachimWagner on 16.11.2026.
//

#pragma once


class Stapel {

private:
    static constexpr int capacity{10};
    int data[capacity];
    int index{0};
public:
    Stapel() = default;
    auto push(int value)->void;
    auto pop()->int;

    auto isEmpty() const -> bool;
    auto isFull() const -> bool;
};
