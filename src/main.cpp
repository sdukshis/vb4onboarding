#include <fmt/core.h>
#include <string>

int main(int argc, char** argv) {
    const std::string name = (argc > 1) ? argv[1] : "World";
    fmt::print("Hello, {}!\\n", name);
    return 0;
}


