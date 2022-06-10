#include <iostream>

void print_values(const int& i, const int& j, const int& k, const int& l) {
    std::cout << "i is: " << i << "\n";
    std::cout << "j is: " << j << "\n";
    std::cout << "k is: " << k << "\n";
    std::cout << "l is: " << l << "\n";
}

int main() {
    // START BOOK SNIP
    int i { 1 };
    int j { 10 };
    int k { 100 };
    int l { 1000 };

    auto lambda = [i, &j](int k0, int& l0) -> int
    {
        j  = 2 * j;              // 1st: 20, 2nd: 40
        k0 = 2 * k0;             // 1st: 200, 2nd: 200
        l0 = 2 * l0;             // 1st: 2000, 2nd: 4000
        return i + j + k0 + l0;  // 1st: 1 + 20 + 200 + 2000 = 2221, 2nd: 1 + 40 + 200 + 4000 = 4241
    };

    print_values(i, j, k, l);
    std::cout << "First call returned " << lambda(k, l) << "\n";   // 2221
    print_values(i, j, k, l);                                      // i: 1, j: 20, k: 100, l: 2000
    std::cout << "Second call returned " << lambda(k, l) << "\n";  // 4241
    print_values(i, j, k, l);                                      // i: 1, j: 40, k: 100, l:4000
    // END BOOK SNIP

    return 0;
}
