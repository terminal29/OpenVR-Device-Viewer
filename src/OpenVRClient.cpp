#include <OpenVRClient.hpp>
#include "..\include\OpenVRClient.hpp"

OpenVRClient::OpenVRClient()
{
    vr::EVRInitError error;
    m_vrSystem = vr::VR_Init(&error, vr::EVRApplicationType::VRApplication_Background);
    if (error != vr::EVRInitError::VRInitError_None) {
        m_vrSystem = nullptr;
        throw std::exception(vr::VR_GetVRInitErrorAsEnglishDescription(error));
    }

}

std::vector<std::pair<vr::TrackedDeviceIndex_t, vr::TrackedDevicePose_t>> OpenVRClient::getPoses()
{
    std::vector<std::pair<vr::TrackedDeviceIndex_t, vr::TrackedDevicePose_t>> poses;
    for (auto i = 0u; i < vr::k_unMaxTrackedDeviceCount; i++) {
        if (vr::VRSystem()->IsTrackedDeviceConnected(i)) {
            vr::TrackedDevicePose_t pose;
            vr::VRSystem()->GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin::TrackingUniverseRawAndUncalibrated, 0, &pose, 1);
            poses.push_back({ i, pose });
        }
    }
    return poses;
}

std::vector<std::pair<std::string, bool>> OpenVRClient::getDrivers()
{
    auto driver_count = vr::VRDriverManager()->GetDriverCount();
    std::vector<std::pair<std::string, bool>> driver_info;
    driver_info.reserve(driver_count);
    for (auto i = 0u; i < driver_count; i++) {
        vr::DriverId_t id = i;
        int len = vr::VRDriverManager()->GetDriverName(id, nullptr, 0);
        char* driver_name_cstr = new char[len];
        vr::VRDriverManager()->GetDriverName(id, driver_name_cstr, len);
        bool is_driver_enabled = vr::VRDriverManager()->IsEnabled(id);
        driver_info.push_back({ driver_name_cstr, is_driver_enabled });
        delete[] driver_name_cstr;
    }
    return driver_info;
}

DeviceProperties OpenVRClient::getProperties(vr::TrackedDeviceIndex_t index)
{
    return DeviceProperties();
}

OpenVRClient::~OpenVRClient()
{
    m_vrSystem = nullptr;
    vr::VR_Shutdown();
}
