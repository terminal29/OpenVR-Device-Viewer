#pragma once

#include <vector>
#include <array>
#include <optional>

#include <openvr.h>
#include <openvr_capi.h>

#include <DeviceProperties.hpp>

class OpenVRClient {
public:

    /// <summary>
    /// Start up an OpenVR client and attempts to connect to the VRServer
    /// </summary>
    /// <exception cref="std::exception">When the server cannot be reached</exception>
    OpenVRClient() noexcept(false);

    /// <summary>
    /// Gets the pose for a single device
    /// </summary>
    /// <param name="device_index">Index of the device</param>
    /// <returns>Device pose</returns>
    vr::TrackedDevicePose_t getPose(vr::TrackedDeviceIndex_t device_index);

    /// <summary>
    /// Gets a list of loaded driver names and whether they are activated
    /// </summary>
    /// <returns>Vector of driver names and activation status</returns>
    std::vector<std::pair<std::string, bool>> getDrivers();

    /// <summary>
    /// Gets the properties for a device
    /// </summary>
    /// <param name="index">Index of the device</param>
    /// <returns>Filled DeviceProperties instance</returns>
    DeviceProperties getProperties(vr::TrackedDeviceIndex_t device_index);

    /// <summary>
    /// Checks if a device is currently connected
    /// </summary>
    /// <param name="index">Index of the device</param>
    /// <returns>True if the device is connected, false otherwise</returns>
    bool isDeviceConnected(vr::TrackedDeviceIndex_t device_index);

    /// <summary>
    /// Closes the OpenVR client
    /// </summary>
    ~OpenVRClient();
private:
    vr::IVRSystem* m_vrSystem = nullptr;
};