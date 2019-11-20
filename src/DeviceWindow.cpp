#include <DeviceWindow.hpp>

DeviceWindow::DeviceWindow(std::shared_ptr<OpenVRDevice> device):
    m_device(device),
    m_isVisible(false),
    m_windowName((this->m_device->getProperties().getProperty(vr::Prop_ModelNumber_String).value_or("Unnamed") + " (" + this->m_device->getProperties().getProperty(vr::Prop_SerialNumber_String).value_or("") + ")"))
{
}

std::string DeviceWindow::getWindowName()
{
    return this->m_windowName;
}

std::shared_ptr<OpenVRDevice> DeviceWindow::getDevice()
{
    return this->m_device;
}

void DeviceWindow::show()
{
    this->m_isVisible = true;
}

void DeviceWindow::hide()
{
    this->m_isVisible = false;
}

void DeviceWindow::draw()
{
    if (!this->m_isVisible)
        return;
    bool doKeepOpen = true;
    if (ImGui::Begin(this->m_windowName.c_str(), &doKeepOpen)) {

        if (ImGui::CollapsingHeader("Device Properties"))
        {
            auto props = this->m_device->getProperties();
            ImGui::Columns(2);
            for (auto prop : props.m_propertyValues) {
                ImGui::Text("%s", props.m_propertyKeys.at(prop.first).c_str());
            }
            ImGui::NextColumn();
            for (auto prop : props.m_propertyValues) {
                ImGui::Text("%s", prop.second.c_str());
            }
            ImGui::EndColumns();
        }

        if (ImGui::CollapsingHeader("Device Pose"))
        {
            auto pose = OpenVRDevice::toEigenPose(this->m_device->getPose().mDeviceToAbsoluteTracking);
            ImVec2 region = ImGui::GetContentRegionAvail();
            ImGui::gizmo3D("DeviceGizmo", quat(pose.first.w(), pose.first.x(), pose.first.y(), pose.first.z()), region.x);
        }

    }
    ImGui::End();
    if (!doKeepOpen)
        this->hide();

}
