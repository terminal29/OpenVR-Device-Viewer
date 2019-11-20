#pragma once

#include <memory>

#include <OpenVRClient.hpp>

class OpenVRDevice {
public:
    OpenVRDevice(std::shared_ptr<OpenVRClient> openvr_client, vr::TrackedDeviceIndex_t device_index);

    DeviceProperties getProperties();

    bool isConnected();

    vr::TrackedDevicePose_t getPose();

    virtual ~OpenVRDevice() = default;

private:
    std::shared_ptr<OpenVRClient> m_vrClient;
    vr::TrackedDeviceIndex_t m_deviceIndex;
    DeviceProperties m_props;
};