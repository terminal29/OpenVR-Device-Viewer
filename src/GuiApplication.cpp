#include <GuiApplication.hpp>

GuiApplication::GuiApplication() :
    m_vrClient(std::make_shared<OpenVRClient>())
{
    // GLFW init
    glfwSetErrorCallback(GuiApplication::errorCallback);
    if (int err = glfwInit(); !err)
        throw std::exception(("glfwInit() failed with " + std::to_string(err)).c_str());
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this->m_window = glfwCreateWindow(1280, 720, "OpenVR Device Viewer", NULL, NULL);
    if (this->m_window == nullptr)
        throw std::exception("glfwCreateWindow() failed");
    glfwMakeContextCurrent(this->m_window);
    glfwSwapInterval(1);

    if (GLint err = glewInit(); err != GLEW_OK)
        throw std::exception(("glewInit() failed with " + std::to_string(err)).c_str());

    // IMGUI init
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();

    if (!ImGui_ImplOpenGL3_Init(this->m_glslVersion)) {
        throw std::exception("ImGui_ImplOpenGL3_Init() failed");
    }

    if (!ImGui_ImplGlfw_InitForOpenGL(this->m_window, true)) {
        throw std::exception("ImGui_ImplGlfw_InitForOpenGL() failed");
    }
}

GuiApplication::~GuiApplication()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(this->m_window);
    this->m_window = nullptr;
    glfwTerminate();
}

std::optional<GuiApplication::ErrorCode> GuiApplication::run()
{
    while (!glfwWindowShouldClose(this->m_window) && !this->m_doExit)
    {
        if (this->m_doRefresh) {
            this->m_doRefresh = false;
            auto drivers = this->m_vrClient->getDrivers();
            this->m_driverInfoCache.clear();
            std::transform(drivers.begin(), drivers.end(), std::back_inserter(this->m_driverInfoCache), 
                [](std::pair<std::string, bool> driver)->std::tuple<std::string, bool, bool>{
                    return { driver.first, driver.second, false };
                }
            );

            this->m_deviceWindows.clear();
            for (vr::TrackedDeviceIndex_t idx = 0; idx < vr::k_unMaxTrackedDeviceCount; idx++) {
                if (this->m_vrClient->isDeviceConnected(idx)) {
                    this->m_deviceWindows.push_back(std::make_unique<DeviceWindow>(std::make_shared<OpenVRDevice>(this->m_vrClient, idx)));
                }
            }
        }

        this->beginFrame();
        {
            if (ImGui::BeginMainMenuBar()) {

                if (ImGui::BeginMenu("File")) {
                    ImGui::MenuItem("Refresh", NULL, &this->m_doRefresh);
                    ImGui::MenuItem("Exit", NULL, &this->m_doExit);
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Drivers")) {
                    for (auto driver : this->m_driverInfoCache) {
                        bool selected = false;
                        ImGui::MenuItem(std::get<0>(driver).c_str(), NULL, &selected);
                        if (selected) {
                            // make driver window
                        }
                    }
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Devices")) {
                    for (auto& deviceWindow : this->m_deviceWindows) {
                        if (ImGui::MenuItem(deviceWindow->getWindowName().c_str(), nullptr, nullptr)) {
                            deviceWindow->show();
                        }
                        
                    }
                    ImGui::EndMenu();
                }
            }
            ImGui::EndMainMenuBar();


            for (auto& deviceWindow : this->m_deviceWindows) {
                deviceWindow->draw();
            }


        }
        this->endFrame();
    }
    return std::nullopt;


}

void GuiApplication::errorCallback(int error, const char* description)
{
    std::cout << "Window Error [" << error << "]: " << description << std::endl;
}

void GuiApplication::beginFrame()
{
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GuiApplication::endFrame()
{
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(this->m_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(this->m_clearColor.x, this->m_clearColor.y, this->m_clearColor.z, this->m_clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(this->m_window);
}
