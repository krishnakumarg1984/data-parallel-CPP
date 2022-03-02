#include <CL/sycl.hpp>
#include <iostream>
#include <sycl/ext/intel/fpga_extensions.hpp>  // For fpga_selector
using namespace sycl;

int main() {
    queue my_gpu_queue(gpu_selector {});
    // queue my_fpga_queue(ext::intel::fpga_selector {});

    // std::cout << "Selected device 1: " << my_gpu_queue.get_device().get_info<info::device::name>() << "\n";

    // std::cout << "Selected device 2: " << my_fpga_queue.get_device().get_info<info::device::name>() << "\n";

    return 0;
}
