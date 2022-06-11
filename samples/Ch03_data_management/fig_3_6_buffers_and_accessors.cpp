// Copyright (C) 2020 Intel Corporation
// SPDX-License-Identifier: MIT

#include <CL/sycl.hpp>
#include <array>

using namespace sycl;
constexpr int N { 42 };

int main() {
    std::array<int, N> my_data {};

    {
        queue q;
        buffer my_buffer(my_data);

        q.submit([&](handler& h) {  //
            // create an accessor to update the buffer on the device
            accessor my_accessor(my_buffer, h);

            h.parallel_for(N, [=](id<1> i) { my_accessor[i]++; });
        });

        // create host accessor
        host_accessor my_host_accessor(my_buffer);

        for (size_t i { 0 }; i < N; ++i) {
            // access myBuffer on host
            std::cout << my_host_accessor[i] << " ";
        }
        std::cout << '\n';
    }

    std::cout << '\n';
    // myData is updated when myBuffer is destroyed upon exiting scope
    for (size_t i { 0 }; i < N; ++i) {
        std::cout << my_data.at(i) << " ";
    }
    std::cout << '\n';

    return 0;
}
