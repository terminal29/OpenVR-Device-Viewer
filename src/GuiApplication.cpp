#include "..\include\GuiApplication.hpp"

GuiApplication::GuiApplication():
    m_client(std::make_unique<OpenVRClient>())
{
}

std::optional<GuiApplication::ErrorCode> GuiApplication::run()
{
    auto drivers = m_client->getDrivers();
    for (auto driver : drivers) {
        std::cout << driver.first.c_str() << "\t:\t" << driver.second << std::endl;
    }
    return std::nullopt;
}
