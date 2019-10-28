#include <DeviceProperties.hpp>
using namespace vr;
#define MAKE_PROPNAME(name) {name, std::string(#name)}

const std::vector<std::pair<DeviceProperties::PropKey, DeviceProperties::PropName>> DeviceProperties::m_propertyKeys = {
    MAKE_PROPNAME(Prop_ManufacturerName_String),
    MAKE_PROPNAME(Prop_TrackingFirmwareVersion_String),
    MAKE_PROPNAME(Prop_HardwareRevision_String),
    MAKE_PROPNAME(Prop_AllWirelessDongleDescriptions_String),
    MAKE_PROPNAME(Prop_ConnectedWirelessDongle_String),
    MAKE_PROPNAME(Prop_DeviceIsWireless_Bool),
    MAKE_PROPNAME(Prop_DeviceIsCharging_Bool),
    MAKE_PROPNAME(Prop_DeviceBatteryPercentage_Float),
    MAKE_PROPNAME(Prop_StatusDisplayTransform_Matrix34),
    MAKE_PROPNAME(Prop_Firmware_UpdateAvailable_Bool),
    MAKE_PROPNAME(Prop_Firmware_ManualUpdate_Bool),
    MAKE_PROPNAME(Prop_Firmware_ManualUpdateURL_String),
    MAKE_PROPNAME(Prop_HardwareRevision_Uint64),
    MAKE_PROPNAME(Prop_FirmwareVersion_Uint64),
    MAKE_PROPNAME(Prop_FPGAVersion_Uint64),
    MAKE_PROPNAME(Prop_VRCVersion_Uint64),
    MAKE_PROPNAME(Prop_RadioVersion_Uint64),
    MAKE_PROPNAME(Prop_DongleVersion_Uint64),
    MAKE_PROPNAME(Prop_BlockServerShutdown_Bool),
    MAKE_PROPNAME(Prop_CanUnifyCoordinateSystemWithHmd_Bool),
    MAKE_PROPNAME(Prop_ContainsProximitySensor_Bool),
    MAKE_PROPNAME(Prop_DeviceProvidesBatteryStatus_Bool),
    MAKE_PROPNAME(Prop_DeviceCanPowerOff_Bool),
    MAKE_PROPNAME(Prop_Firmware_ProgrammingTarget_String),
    MAKE_PROPNAME(Prop_DeviceClass_Int32),
    MAKE_PROPNAME(Prop_HasCamera_Bool),
    MAKE_PROPNAME(Prop_DriverVersion_String),
    MAKE_PROPNAME(Prop_Firmware_ForceUpdateRequired_Bool),
    MAKE_PROPNAME(Prop_ViveSystemButtonFixRequired_Bool),
    MAKE_PROPNAME(Prop_ParentDriver_Uint64),
    MAKE_PROPNAME(Prop_ResourceRoot_String),
    MAKE_PROPNAME(Prop_RegisteredDeviceType_String),
    MAKE_PROPNAME(Prop_InputProfilePath_String),
    MAKE_PROPNAME(Prop_NeverTracked_Bool),
    MAKE_PROPNAME(Prop_NumCameras_Int32),
    MAKE_PROPNAME(Prop_CameraFrameLayout_Int32),
    MAKE_PROPNAME(Prop_CameraStreamFormat_Int32),
    MAKE_PROPNAME(Prop_AdditionalDeviceSettingsPath_String),
    MAKE_PROPNAME(Prop_Identifiable_Bool),
    MAKE_PROPNAME(Prop_BootloaderVersion_Uint64),
    MAKE_PROPNAME(Prop_AdditionalSystemReportData_String),
    MAKE_PROPNAME(Prop_CompositeFirmwareVersion_String),
    MAKE_PROPNAME(Prop_Firmware_RemindUpdate_Bool)
};

void DeviceProperties::setProperty(DeviceProperties::PropKey key, DeviceProperties::PropVal value)
{
    this->m_propertyValues[key] = value;
}

std::optional<DeviceProperties::PropVal> DeviceProperties::getProperty(DeviceProperties::PropKey key)
{
    if (this->m_propertyValues.count(key) == 0)
        return std::nullopt;
    return this->m_propertyValues.at(key);
}
