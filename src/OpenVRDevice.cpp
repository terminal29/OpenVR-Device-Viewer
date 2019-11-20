#include <OpenVRDevice.hpp>

OpenVRDevice::OpenVRDevice(std::shared_ptr<OpenVRClient> openvr_client, vr::TrackedDeviceIndex_t device_index):
    m_vrClient(openvr_client), 
    m_deviceIndex(device_index)
{
}

DeviceProperties OpenVRDevice::getProperties()
{
    return this->m_vrClient->getProperties(this->m_deviceIndex);
}

bool OpenVRDevice::isConnected()
{
    return this->m_vrClient->isDeviceConnected(this->m_deviceIndex);
}

vr::TrackedDevicePose_t OpenVRDevice::getPose()
{
    return this->m_vrClient->getPose(this->m_deviceIndex);
}

vr::TrackedDeviceIndex_t OpenVRDevice::getIndex()
{
    return this->m_deviceIndex;
}
