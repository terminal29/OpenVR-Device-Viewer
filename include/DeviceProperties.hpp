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

    /// <summary>
    /// Sets a property
    /// </summary>
    /// <param name="key">Property key</param>
    /// <param name="value">Property value</param>
    void setProperty(PropKey key, PropVal value);

    /// <summary>
    /// Gets a property
    /// </summary>
    /// <param name="key">Property key</param>
    /// <returns>Property value, or nullopt if not set</returns>
    std::optional<PropVal> getProperty(PropKey key);

    const static std::map<PropKey, PropName> m_propertyKeys;
    std::map<PropKey, PropVal> m_propertyValues;
};