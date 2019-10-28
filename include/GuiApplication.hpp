#pragma once

#include <memory>
#include <optional>

#include <imgui.h>
#include <OpenVRClient.hpp>

class GuiApplication {
public:
    using ErrorCode = int;

    GuiApplication();

    std::optional<ErrorCode> run();

private:
    std::unique_ptr<OpenVRClient> m_client;
};