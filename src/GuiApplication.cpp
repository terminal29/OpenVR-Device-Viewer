#include <GuiApplication.hpp>

GuiApplication::GuiApplication():
    m_client(std::make_unique<OpenVRClient>())
{
}

std::optional<GuiApplication::ErrorCode> GuiApplication::run()
{
    auto drivers = m_client->getDrivers();
    std::cout << "[ Drivers ]" << std::endl;
    std::cout << std::endl;
    for (auto driver : drivers) {
        std::cout << std::left << std::setw(60) << "> " + driver.first << driver.second << std::endl;
    }
    std::cout << std::endl;
    auto poses = m_client->getPoses();
    std::cout << "[ Devices ]" << std::endl;
    std::cout << std::endl;
    for (auto pose : poses) {
        DeviceProperties props = m_client->getProperties(pose.first);
        std::string device_name = props.getProperty(vr::ETrackedDeviceProperty::Prop_ModelNumber_String).value_or("Unknown Device");
        std::cout << device_name << " (" << pose.first << ")" << std::endl;
        for (auto prop : props.m_propertyValues) {
            std::cout << std::left << std::setw(60) << "> " + props.m_propertyKeys.at(prop.first) << prop.second << std::endl;
        }
        std::cout << std::endl;
    }
    return std::nullopt;
}
