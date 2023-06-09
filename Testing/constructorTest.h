#include <algorithm>
#include <iostream>

namespace group {
    struct pair {
        int x, y;

        pair() : x(0), y(0) { std::cout << "default constructor" << '\n'; };
        pair(int x) : x(x), y(0) { std::cout << "parameterized constructor 1" << '\n'; };
        pair(int x, int y) : x(x), y(y) { std::cout << "parametrized constructor 2" << '\n'; };
        pair(const pair& p) : x(p.x), y(p.y) { std::cout << "copy constructor" << '\n'; };
        pair(pair&& p) : x(std::move(p.x)), y(std::move(p.y)) { std::cout << "move constructor" << '\n'; };
        ~pair() { std::cout << "deconstructor" << '\n'; };

        pair operator+(const pair& other);
        pair& operator+=(const pair& other);
        pair& operator=(const pair& other);
        pair& operator=(pair&& other);

        friend std::ostream& operator<<(std::ostream& os, const group::pair& p);
    };
};