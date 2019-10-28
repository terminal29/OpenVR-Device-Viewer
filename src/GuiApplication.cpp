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
    auto poses = m_client->getPoses();
    for (auto pose : poses) {
        std::cout << "Device: " << pose.first << std::endl;
    }
    return std::nullopt;
}
