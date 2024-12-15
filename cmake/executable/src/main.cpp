#include <spdlog/spdlog.h>

#include "main.h"
#include "version.h"

void HelloWorld() {
    spdlog::info("Hello World");
}

int main(int argc, char* argv[]) {
    HelloWorld();

    spdlog::info("version: {}", VERSION_STRING);
    return 0;
}
