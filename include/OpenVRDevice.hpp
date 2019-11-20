#pragma once

#include <memory>

#include <Eigen/Eigen>
#include <OpenVRClient.hpp>

class OpenVRDevice {
public:
    OpenVRDevice(std::shared_ptr<OpenVRClient> openvr_client, vr::TrackedDeviceIndex_t device_index);

    DeviceProperties getProperties();

    bool isConnected();

    vr::TrackedDevicePose_t getPose();

    static std::pair<Eigen::Quaternionf, Eigen::Vector3f> toEigenPose(const vr::HmdMatrix34_t& mat);

    vr::TrackedDeviceIndex_t getIndex();

    virtual ~OpenVRDevice() = default;

private:
    std::shared_ptr<OpenVRClient> m_vrClient;
    vr::TrackedDeviceIndex_t m_deviceIndex;
};