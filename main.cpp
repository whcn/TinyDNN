#include <iostream>

#include "core.h"

int main() {
    Variable a(1);
    Variable b(2);
    auto c = Add()(a, b);
    std::cout << c.GetData() << std::endl;
    return 0;
}
