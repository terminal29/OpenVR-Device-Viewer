#include <GuiApplication.hpp>

GuiApplication::GuiApplication() :
    m_client(std::make_unique<OpenVRClient>())
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
    /*auto drivers = m_client->getDrivers();
    std::cout << "[ Drivers ]" << std::endl;
    std::cout << std::endl;
    for (auto driver : drivers) {
        std::cout << std::left << std::setw(60) << "> " + driver.first << driver.second << std::endl;
    }
    std::cout << std::endl;
    auto poses = m_client->getPoses();
    std::cout << "[ Devices ]" << std::endl;
    std::cout << std::endl;
    for (auto pose : poses) {
        DeviceProperties props = m_client->getProperties(pose.first);
        std::string device_name = props.getProperty(vr::ETrackedDeviceProperty::Prop_ModelNumber_String).value_or("Unknown Device");
        std::cout << device_name << " (" << pose.first << ")" << std::endl;
        for (auto prop : props.m_propertyValues) {
            std::cout << std::left << std::setw(60) << "> " + props.m_propertyKeys.at(prop.first) << prop.second << std::endl;
        }
        std::cout << std::endl;
    }
    return std::nullopt;*/

    while (!glfwWindowShouldClose(this->m_window) && !this->m_doExit)
    {
        if (this->m_doRefresh) {
            this->m_doRefresh = false;
            this->m_driverInfoCache = this->m_client->getDrivers();
            this->m_devicePoseCache = this->m_client->getPoses();
            this->m_devicePropsCache.clear();
            this->m_devicePropsCache.reserve(this->m_devicePoseCache.size());

            std::for_each(this->m_devicePoseCache.begin(), this->m_devicePoseCache.end(), [&](auto pose) {this->m_devicePropsCache.push_back(std::make_pair(pose.first, this->m_client->getProperties(pose.first))); });
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
                        ImGui::MenuItem(driver.first.c_str(), NULL, &selected);
                        if (selected) {
                            // make driver window
                        }
                    }
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Devices")) {
                    for (auto device : this->m_devicePropsCache) {
                        bool selected = false;
                        ImGui::MenuItem((device.second.getProperty(vr::Prop_ModelNumber_String).value_or("Unnamed") + " (" + device.second.getProperty(vr::Prop_SerialNumber_String).value_or("") + ")").c_str(), NULL, &selected);
                        if (selected) {
                            // make device window
                        }
                    }
                    ImGui::EndMenu();
                }

                ImGui::EndMainMenuBar();
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
