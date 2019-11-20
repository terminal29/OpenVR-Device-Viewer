#pragma once

#include <memory>
#include <optional>
#include <iostream>
#include <iomanip>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <OpenVRClient.hpp>
#include <OpenVRDevice.hpp>

class GuiApplication {
public:
    using ErrorCode = int;

    GuiApplication();
    ~GuiApplication();

    std::optional<ErrorCode> run();

    static void errorCallback(int error, const char* description);

private:
    std::shared_ptr<OpenVRClient> m_vrClient;

    constexpr const static auto m_glslVersion{ "#version 130" };
    GLFWwindow* m_window = nullptr;
    ImVec4 m_clearColor{ 0.05f, 0.05f, 0.05f, 1.00f };

    void beginFrame();

    void endFrame();

    bool m_doRefresh = true;
    bool m_doExit = false;

    std::vector<std::tuple<std::string, bool, bool>> m_driverInfoCache;

    std::vector<OpenVRDevice> m_devices;

};