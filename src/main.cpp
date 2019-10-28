#include <GuiApplication.hpp>
#include <iostream>

int main(void) {
    try {
        GuiApplication application;
        return application.run().value_or(0);
    }
    catch (const std::exception & e) {
        std::cout << "Error: " << e.what() << std::endl;
        return -1;
    }
}