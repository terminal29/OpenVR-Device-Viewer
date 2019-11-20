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

vr::TrackedDevicePose_t OpenVRClient::getPose(vr::TrackedDeviceIndex_t device_index)
{
    std::array<vr::TrackedDevicePose_t, vr::k_unMaxTrackedDeviceCount> poses;
    vr::VRSystem()->GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin::TrackingUniverseRawAndUncalibrated, 0, poses.data(), vr::k_unMaxTrackedDeviceCount);
    return poses.at(device_index);
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
    DeviceProperties props;
    for (auto propKey : DeviceProperties::m_propertyKeys) {
        vr::ETrackedPropertyError error;

        // Get if it is a bool value
        if (bool value = vr::VRSystem()->GetBoolTrackedDeviceProperty(index, propKey.first, &error); error == vr::ETrackedPropertyError::TrackedProp_Success) {
            props.setProperty(propKey.first, std::to_string(value));
            continue;
        }
        if (error == vr::ETrackedPropertyError::TrackedProp_UnknownProperty)
            continue;
        
        // Get if it is a string value
        if (auto len = vr::VRSystem()->GetStringTrackedDeviceProperty(index, propKey.first, nullptr, 0, &error);  len > 0) {
            std::unique_ptr<char> strValue(new char[len]);
            vr::VRSystem()->GetStringTrackedDeviceProperty(index, propKey.first, strValue.get(), len, &error);
            if (error == vr::ETrackedPropertyError::TrackedProp_Success) {
                props.setProperty(propKey.first, strValue.get());
                continue;
            }
        }
        if (error == vr::ETrackedPropertyError::TrackedProp_UnknownProperty)
            continue;

        // Get if it is a uint64
        if (auto value = vr::VRSystem()->GetUint64TrackedDeviceProperty(index, propKey.first, &error); error == vr::ETrackedPropertyError::TrackedProp_Success) {
            props.setProperty(propKey.first, std::to_string(value));
            continue;
        }
        if (error == vr::ETrackedPropertyError::TrackedProp_UnknownProperty)
            continue;

        // Get if it is an float
        if (auto value = vr::VRSystem()->GetFloatTrackedDeviceProperty(index, propKey.first, &error); error == vr::ETrackedPropertyError::TrackedProp_Success) {
            props.setProperty(propKey.first, std::to_string(value));
            continue;
        }
        if (error == vr::ETrackedPropertyError::TrackedProp_UnknownProperty)
            continue;

        // Get if it is an int32
        if (auto value = vr::VRSystem()->GetInt32TrackedDeviceProperty(index, propKey.first, &error); error == vr::ETrackedPropertyError::TrackedProp_Success) {
            props.setProperty(propKey.first, std::to_string(value));
            continue;
        }
        if (error == vr::ETrackedPropertyError::TrackedProp_UnknownProperty)
            continue;



        // Get unknown value
        props.setProperty(propKey.first, "<unknown value type>");
    }
    return props;
}

bool OpenVRClient::isDeviceConnected(vr::TrackedDeviceIndex_t index)
{
    return vr::VRSystem()->IsTrackedDeviceConnected(index);
}

OpenVRClient::~OpenVRClient()
{
    m_vrSystem = nullptr;
    vr::VR_Shutdown();
}
