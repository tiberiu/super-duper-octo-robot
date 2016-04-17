#include <iostream>
#include <sys/sysctl.h>

int main() {
    size_t line_size = 0;
    size_t sizeof_line_size = sizeof(line_size);
    sysctlbyname("hw.cachelinesize", &line_size, &sizeof_line_size, 0, 0);

    std::cout << line_size << std::endl;
    return 0;
}
