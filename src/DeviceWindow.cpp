#include <DeviceWindow.hpp>

DeviceWindow::DeviceWindow(std::shared_ptr<OpenVRDevice> device):
    m_device(device),
    m_isVisible(false),
    m_windowName((this->m_device->getProperties().getProperty(vr::Prop_ModelNumber_String).value_or("Unnamed") + " (" + this->m_device->getProperties().getProperty(vr::Prop_SerialNumber_String).value_or("") + ")"))
{
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

    }
    ImGui::End();
    if (!doKeepOpen)
        this->m_isVisible = false;

}
