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

std::pair<Eigen::Quaternionf, Eigen::Vector3f> OpenVRDevice::toEigenPose(const vr::HmdMatrix34_t& mat)
{
    Eigen::Vector3f device_translation(mat.m[0][3], mat.m[1][3], mat.m[2][3]);
    Eigen::Matrix3f device_rotmat = (Eigen::Matrix3f() << mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[2][0], mat.m[2][1], mat.m[2][2]).finished();
    Eigen::Quaternionf device_rotation(device_rotmat);

    return std::make_pair(device_rotation, device_translation);
}

vr::TrackedDeviceIndex_t OpenVRDevice::getIndex()
{
    return this->m_deviceIndex;
}
