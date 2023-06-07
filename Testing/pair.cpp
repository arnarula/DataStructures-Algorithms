#include "pair.h"
#include <algorithm>

group::pair group::pair::operator+(const group::pair& other) {
    group::pair p(*this);
    p.x += other.x;
    p.y += other.y;
    return p;
}

group::pair& group::pair::operator+=(const group::pair& other) {
    x += other.x;
    y += other.y;
    return *this;
}

group::pair& group::pair::operator=(const group::pair& other) {
    this->x = other.x;
    this->y = other.y;
    return *this;
}

group::pair& group::pair::operator=(group::pair&& other) {
    std::swap(this->x, other.x);
    std::swap(this->y, other.y);
    return *this;
}

// testing types of constructor elisions (compiler optimizations)
group::pair test1() {
    group::pair p1;
    return p1;
}

group::pair test2() {
    return group::pair();
}