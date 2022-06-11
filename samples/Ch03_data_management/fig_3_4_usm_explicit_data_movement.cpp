// Copyright (C) 2020 Intel Corporation

// SPDX-License-Identifier: MIT

#include <CL/sycl.hpp>
#include <array>

using namespace sycl;
constexpr int N { 42 };

int main() {
    queue Q;

    std::array<int, N> host_array {};
    for (size_t i { 0 }; i < N; ++i) {
        // host_array[i] = N;
        host_array.at(i) = N;
    }

    int* device_array = malloc_device<int>(N, Q);
    // We will learn how to simplify this example later
    Q.submit([&](handler& h) {  //
        // h.memcpy(device_array, &host_array[0], N * sizeof(int));
        // copy hostArray to deviceArray
        h.memcpy(device_array, host_array.data(), N * sizeof(int));
    });
    Q.wait();

    Q.submit([&](handler& h) {  // parfor
        h.parallel_for(N, [=](id<1> i) { device_array[i]++; });
    });
    Q.wait();

    Q.submit([&](handler& h) {  //
        // copy deviceArray back to hostArray
        // h.memcpy(&host_array[0], device_array, N * sizeof(int));
        h.memcpy(host_array.data(), device_array, N * sizeof(int));
    });
    Q.wait();

    free(device_array, Q);
    return 0;
}
