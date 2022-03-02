#include <CL/sycl.hpp>
#include <iostream>
using namespace sycl;

void print_device_info(const sycl::queue& Q) {
    std::cout << "Selected device: " << Q.get_device().get_info<info::device::name>() << "\n";
    std::cout << "Device vendor: " << Q.get_device().get_info<info::device::vendor>() << "\n";
    std::cout << '\n';
}

int main() {
    queue Q1;                       // implicit device selection (might be the host device)
    queue Q2 { host_selector {} };  // Create queue to use the host device explicitly
    // queue Q3 { cpu_selector {} };   // Create queue to use the CPU device explicitly

    print_device_info(Q1);
    print_device_info(Q2);
    print_device_info(Q3);

    return 0;
}
