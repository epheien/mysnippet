#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>

#include "main.h"
#include "version.h"

void HelloWorld() {
    spdlog::info("Hello World");
}

int main(int argc, char* argv[]) {
    CLI::App app{argv[0]};
    bool version = false;
    std::string config;
    app.add_flag("-v,--version", version, "print version and exit");
    app.add_option("-c,--config", config, "config file to read");
    CLI11_PARSE(app, argc, argv);

    if (version) {
        fmt::println("{} version: {}", argv[0], VERSION_STRING);
        return 0;
    }

    HelloWorld();

    spdlog::info("version: {}", VERSION_STRING);
    return 0;
}
