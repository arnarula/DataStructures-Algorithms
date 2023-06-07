using namespace std;

namespace group {
    struct pair {
        int x, y;

        pair() : x(0), y(0) { cout << "default constructor" << '\n'; };
        pair(int x) : x(x), y(0) { cout << "parameterized constructor 1" << '\n'; };
        pair(int x, int y) : x(x), y(y) { cout << "parametrized constructor 2" << '\n'; };
        pair(const pair& p) : x(p.x), y(p.y) { cout << "copy constructor" << '\n'; };
        pair(pair&& p) : x(p.x), y(p.y) { cout << "move constructor" << '\n'; };
        ~pair() { cout << "deconstructor" << '\n'; };

        pair operator+(const pair& other);
        pair& operator+=(const pair& other);
        pair& operator=(const pair& other);
        pair& operator=(pair&& other);
    };
};

// compiler arguments
// -std=c++11 vs -std=c++17 - yields different compiler elision results
// -fno-elide-constructors - prevents compiler elision optimizations