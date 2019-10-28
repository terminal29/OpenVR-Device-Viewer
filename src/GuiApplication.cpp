#include "..\include\GuiApplication.hpp"

GuiApplication::GuiApplication():
    m_client(std::make_unique<OpenVRClient>())
{
}

std::optional<GuiApplication::ErrorCode> GuiApplication::run()
{
    return std::nullopt;
}
