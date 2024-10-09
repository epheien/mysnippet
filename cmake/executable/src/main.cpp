#include <spdlog/spdlog.h>

#include "main.h"

void HelloWorld() {
    spdlog::info("Hello World");
}

int main(int argc, char* argv[]) {
    HelloWorld();
    return 0;
}
