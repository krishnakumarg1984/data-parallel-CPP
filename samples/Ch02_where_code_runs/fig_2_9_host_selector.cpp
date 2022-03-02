#include <CL/sycl.hpp>
#include <iostream>
using namespace sycl;

void print_device_info(const sycl::queue& Q) {
    std::cout << "Selected device: " << Q.get_device().get_info<info::device::name>() << "\n";
    std::cout << "Device vendor: " << Q.get_device().get_info<info::device::vendor>() << "\n";
    std::cout << '\n';
}

int main() {
    queue Q1 { host_selector {} };  // Create queue to use the host device explicitly
    queue Q2;                       // implicit device selection (might be the host device)

    print_device_info(Q1);
    print_device_info(Q2);

    return 0;
}
