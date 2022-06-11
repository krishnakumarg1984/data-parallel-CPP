// Copyright (C) 2020 Intel Corporation

// SPDX-License-Identifier: MIT

#include <CL/sycl.hpp>
#include <array>

using namespace sycl;
constexpr int N { 42 };

int main() {
    std::array<int, N> a {};
    std::array<int, N> b {};
    std::array<int, N> c {};
    for (size_t i { 0 }; i < N; ++i) {
        a.at(i) = b.at(i) = c.at(i) = 0;
    }

    // We will learn how to simplify this example later
    buffer A { a };
    buffer B { b };
    buffer C { c };

    queue Q;
    Q.submit([&](handler& h) {  //
        accessor accA(A, h, read_only);
        accessor accB(B, h, write_only);
        // compute B
        h.parallel_for(N, [=](id<1> i) { accB[i] = accA[i] + 1; });
    });

    Q.submit([&](handler& h) {  // read A
        accessor accA(A, h, read_only);
        // Useful only as an example
        h.parallel_for(N, [=](id<1> i) { int data { accA[i] }; });
    });

    Q.submit([&](handler& h) {  // RAW of buffer B
        accessor accB(B, h, read_only);
        accessor accC(C, h, write_only);
        // compute C
        h.parallel_for(N, [=](id<1> i) { accC[i] = accB[i] + 2; });
    });

    // read C on host
    host_accessor host_accC(C, read_only);
    for (size_t i { 0 }; i < N; ++i) {
        std::cout << host_accC[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}
