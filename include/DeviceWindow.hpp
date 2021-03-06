#pragma once

#include <memory>

#include <imgui.h>
#include <Eigen/Eigen>
#include <imGuIZMOquat.h>
#include <OpenVRDevice.hpp>

class DeviceWindow {
public:
    DeviceWindow(std::shared_ptr<OpenVRDevice> device);

    std::string getWindowName();

    std::shared_ptr<OpenVRDevice> getDevice();

    void show();

    void hide();

    void draw();

    virtual ~DeviceWindow() = default;
private:
    std::shared_ptr<OpenVRDevice> m_device;
    bool m_isVisible;
    std::string m_windowName;
};