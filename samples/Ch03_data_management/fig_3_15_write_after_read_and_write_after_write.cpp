// Copyright (C) 2020 Intel Corporation

// SPDX-License-Identifier: MIT

#include <CL/sycl.hpp>
#include <array>

using namespace sycl;
constexpr int N { 42 };

int main() {
    std::array<int, N> a {};
    std::array<int, N> b {};
    // for (size_t i { 0 }; i < N; ++i) {
    //     a.at(i) = b.at(i) = 0;
    // }

    queue Q;
    buffer A { a };
    buffer B { b };

    Q.submit([&](handler& h) {  //
        accessor accA(A, h, read_only);
        accessor accB(B, h, write_only);
        // computeB
        h.parallel_for(N, [=](id<1> i) { accB[i] = accA[i] + 1; });
    });

    Q.submit([&](handler& h) {  // WAR of buffer A
        accessor accA(A, h, write_only);
        // rewriteA
        h.parallel_for(N, [=](id<1> i) { accA[i] = 21 + 21; });
    });

    Q.submit([&](handler& h) {  // WAW of buffer B
        accessor accB(B, h, write_only);
        // rewriteB
        h.parallel_for(N, [=](id<1> i) { accB[i] = 30 + 12; });
    });

    host_accessor host_accA(A, read_only);
    host_accessor host_accB(B, read_only);
    for (size_t i { 0 }; i < N; ++i) {
        std::cout << "host_accA: " << host_accA[i] << '\n';
        std::cout << "host_accB: " << host_accB[i] << '\n';
        std::cout << '\n';
    }
    std::cout << '\n';

    return 0;
}
