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
    /// Gets the index and pose of each connected device
    /// </summary>
    /// <returns>Vector of index and pose of connected devices</returns>
    std::vector<std::pair<vr::TrackedDeviceIndex_t, vr::TrackedDevicePose_t>> getPoses();

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
    DeviceProperties getProperties(vr::TrackedDeviceIndex_t index);

    /// <summary>
    /// Closes the OpenVR client
    /// </summary>
    ~OpenVRClient();
private:
    vr::IVRSystem* m_vrSystem = nullptr;
};