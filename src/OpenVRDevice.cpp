#include <OpenVRDevice.hpp>

OpenVRDevice::OpenVRDevice(std::shared_ptr<OpenVRClient> openvr_client, vr::TrackedDeviceIndex_t device_index):
    m_vrClient(openvr_client), 
    m_deviceIndex(device_index), 
    m_props(this->m_vrClient->getProperties(this->m_deviceIndex)) // Only need to get props once because they dont change
{
}

DeviceProperties OpenVRDevice::getProperties()
{
    return this->m_props;
}

bool OpenVRDevice::isConnected()
{
    return this->m_vrClient->isDeviceConnected(this->m_deviceIndex);
}

vr::TrackedDevicePose_t OpenVRDevice::getPose()
{
    return this->m_vrClient->getPose(this->m_deviceIndex);
}
