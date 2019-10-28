#include <OpenVRClient.hpp>
#include "..\include\OpenVRClient.hpp"

OpenVRClient::OpenVRClient()
{
    vr::EVRInitError error;
    vr::VR_Init(&error, vr::EVRApplicationType::VRApplication_Background);
    if (error != vr::EVRInitError::VRInitError_None) {
        throw std::exception(vr::VR_GetVRInitErrorAsEnglishDescription(error));
    }

}

std::vector<std::pair<vr::TrackedDeviceIndex_t, vr::TrackedDevicePose_t>> OpenVRClient::getPoses()
{
    return std::vector<std::pair<vr::TrackedDeviceIndex_t, vr::TrackedDevicePose_t>>();
}

OpenVRClient::~OpenVRClient()
{
    vr::VR_Shutdown();
}
