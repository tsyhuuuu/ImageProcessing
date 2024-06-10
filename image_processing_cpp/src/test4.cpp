#include <iostream>
#include <sys/resource.h>
#include <sys/time.h>


long getMemoryUsage() {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) != 0) {
        std::cerr << "Error in getrusage()" << std::endl;
        return -1;
    }

    // The maximum resident set size used (in kilobytes).
    return usage.ru_maxrss;
}


class MyObject {
    int* data;
    size_t size;

public:
    MyObject(size_t s) : size(s) {
        data = new int[size];
    }

    ~MyObject() {
        delete[] data;
    }
};

int main() {
    long memoryBefore = getMemoryUsage();
    if (memoryBefore == -1) {
        return 1; // Exit if error in getrusage()
    }

    int data[1000000]; // Create an object

    long memoryAfter = getMemoryUsage();
    if (memoryAfter == -1) {
        return 1; // Exit if error in getrusage()
    }

    std::cout << "Memory before object creation: " << memoryBefore << " KB" << std::endl;
    std::cout << "Memory after object creation: " << memoryAfter << " KB" << std::endl;
    std::cout << "Memory used by the object: " << (memoryAfter - memoryBefore) << " KB" << std::endl;

    return 0;
}
