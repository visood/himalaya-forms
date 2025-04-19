// test_glad.cpp - Minimal test for glad.h inclusion
#include <iostream>

// Include glad.h to test if it compiles correctly
#include <glad/glad.h>

int main() {
    std::cout << "Testing glad.h inclusion" << std::endl;

    // Try to use a GLAD function (won't actually run without a GL context)
    // but should compile if the header is correctly included
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << "GLAD inclusion test successful" << std::endl;
    return 0;
}
