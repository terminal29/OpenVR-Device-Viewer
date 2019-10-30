#include <GuiApplication.hpp>

GuiApplication::GuiApplication():
    m_client(std::make_unique<OpenVRClient>())
{
    // GLFW init
    glfwSetErrorCallback(GuiApplication::errorCallback);
    if (!glfwInit())
        throw std::exception("glfwInit() failed");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    this->m_window = glfwCreateWindow(1280, 720, "OpenVR Device Viewer", NULL, NULL);
    if (this->m_window == nullptr)
        throw std::exception("glfwCreateWindow() failed");
    glfwMakeContextCurrent(this->m_window);
    glfwSwapInterval(1);

    // IMGUI init
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(this->m_window, true);
    ImGui_ImplOpenGL3_Init(this->m_glslVersion);



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

    while (!glfwWindowShouldClose(this->m_window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }


        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(this->m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(this->m_clearColor.x, this->m_clearColor.y, this->m_clearColor.z, this->m_clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(this->m_window);
    }
    return std::nullopt;


}

void GuiApplication::errorCallback(int error, const char* description)
{
    std::cout << "Window Error [" << error << "]: " << description << std::endl;
}
