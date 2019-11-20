#pragma once

#include <memory>

#include <imgui.h>
#include <OpenVRDevice.hpp>

class DeviceWindow {
public:
    DeviceWindow(std::shared_ptr<OpenVRDevice> device);

    std::string getWindowName();

    void show();

    void hide();

    void draw();

    virtual ~DeviceWindow() = default;
private:
    std::shared_ptr<OpenVRDevice> m_device;
    bool m_isVisible;
    std::string m_windowName;
};