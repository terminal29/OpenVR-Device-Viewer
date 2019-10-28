#pragma once
#include <string>
#include <optional>
#include <map>
#include <vector>

#include <openvr.h>

struct DeviceProperties {
    using PropKey = vr::ETrackedDeviceProperty;
    using PropName = std::string;
    using PropVal = std::string;

    void setProperty(PropKey key, PropVal value);

    std::optional<PropVal> getProperty(PropKey key);

    const static std::map<PropKey, PropName> m_propertyKeys;
    std::map<PropKey, PropVal> m_propertyValues;
};