#include <string>

#include "app_framework.hpp"

#ifdef _WIN32
    #include "ImGuiFileDialog/ImGuiFileDialog.h"
    #include "MemEditor/imgui_memory_editor.h"
#else
    #include "../vendor/lib/ImGuiFileDialog/ImGuiFileDialog.h"
    #include "../vendor/lib/MemEditor/imgui_memory_editor.h"
#endif

#include "disassemblerHeader.h"

/*V2.0 --> for all comments see  5058edebcb*/

void explorerWindow(bool&, std::string&, std::string&);
void bufferDealloc(char*&, size_t&, std::string&, std::string&);
void bufferIntoFile(char*&, size_t&, std::string&, std::string&);
void openFile(std::string&, char*&, size_t&, bool&, size_t&);
/*v2.0 --> dataInEditBuffer*/

class Deassembler : public App<Deassembler>
{
public:
    using App::App;
    ~Deassembler() = default;

    void StartUp() {
        clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f); //FIX WITH UNIVERSAL THEME RECON
        (void)io;
    }

    void Update() {
        //Fullscreen window
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        //Frame to render
        {
            ImGui::Begin("Disassembler", nullptr, flags);
            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    ImGui::MenuItem("Open...", NULL, &showFileExplorerWindow);
                    if (filePathCurrentLength > 0) {
                        /*v2.0 --> Save file for edit mode*/
                        if (ImGui::MenuItem("Close", NULL, &deleteBuffer)) {bufferDealloc(data, data_size, filePathName, filePathCurrent); deleteBuffer = false; filePathCurrentLength = 0;}
                    }
                    if (ImGui::MenuItem("Quit")) { quit = true; }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Settings")) {
                    ImGui::MenuItem("Style", NULL, &showStyleEditorWindow);
                    /*v2.0 --> memory buffer dim window with showMemorySettingsWindow*/
                    ImGui::EndMenu();
                }

                /*V2.0 --> Edit mode here*/

                ImGui::EndMenuBar();

            }
            if (filePathName != "") {
                ImGui::Text("%s", filePathName.c_str());
                ImGui::Separator();
            }
            {
                std::string filePathTemp = filePathName;
                explorerWindow(showFileExplorerWindow, filePathName, filePathCurrent);
                if (filePathName != filePathTemp) {
                    if (filePathTemp == "")
                        fileOpen = true;
                    else
                        isFileChanged = true;
                }

            }

            /*V2.0 --> showMemorySettingsWindow*/

            if (showStyleEditorWindow) { //TODO current style do not shows
                ImGui::Begin("Settings/Style", &showStyleEditorWindow, floatingWindowFlags);
                if (ImGui::Combo("Theme##Selector", &styleTypeIndex, "Dark\0Light\0Classic\0")) {
                    switch (styleTypeIndex) { //TODO ADD BACKGROUND COLOR MATCH
                    case 0: ImGui::StyleColorsDark(); clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f); break;
                    case 1: ImGui::StyleColorsLight(); clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f); break;
                    case 2: ImGui::StyleColorsClassic(); clear_color = ImVec4(0.54f, 0.63f, 0.98f, 1.00f); break;
                    }
                }
                ImGui::ColorEdit3("Background", (float*)&clear_color);
                if (ImGui::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f"))
                    style.GrabRounding = style.FrameRounding;
                ImGui::End();
            }

            if (fileOpen) {
                if (isFileChanged) {
                    bufferDealloc(data, data_size, filePathName, filePathCurrent);
                    isFileChanged = false;
                }
                openFile(filePathName, data, data_size, fileOpen, filePathCurrentLength);
            }

            if (&(*data) != nullptr) {
                /*V2.0 --> ReadOnly mem_edit settings*/
                mem_edit.DrawContents(data, data_size);
                ImGui::SameLine();
                if (ImGui::Button("Disassemble"))//TOCONTINUE
                    disassemble(filePathName);
            }


            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - 60);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetContentRegionAvail().y - 10);
            ImGui::Text("%.1f FPS", io.Framerate);
            ImGui::End();
        }
    }
private:
    //Windows flags
    ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar |
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoBackground;

    ImGuiWindowFlags floatingWindowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;
    //state vars
    bool   showFileExplorerWindow = false;
    bool    showStyleEditorWindow = false;
    bool             deleteBuffer = false;
    bool            isFileChanged = false;
    bool                 fileOpen = false;
    
    /*V2.0 --> saveFile and showMemorySettingsWindow vars*/
    
    //ImGui structures
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    //settings
    int styleTypeIndex = 0;
    
    /*V2.0 --> fileEditBufferSize and *fileEditBufferSizeTmp vars*/
    
    //open file paths
    std::string    filePathName = "";
    std::string filePathCurrent = "";
    size_t filePathCurrentLength = 0;
    //editor mem
    MemoryEditor mem_edit;

    /*V2.0 --> isEditorReadOnly var*/

    bool isEditorReadOnly = true;
    char* data = NULL;
    size_t data_size = 0;

};

#ifdef _WIN32
int WinMain(){
#else
int main(){
#endif
    Deassembler app("DisassemblerAVR", 640, 360);
    app.Run();

    return 0;
}

void explorerWindow(bool& open, std::string& fileAbsPath, std::string& directoryPath) {
    IGFD::FileDialogConfig config;
    config.path = ".";

    if (open)
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".hex", config);
    else
        ImGuiFileDialog::Instance()->Close();

    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            fileAbsPath = ImGuiFileDialog::Instance()->GetFilePathName();
            directoryPath = ImGuiFileDialog::Instance()->GetCurrentPath();
        }
        open = false;
    }
}

void bufferDealloc(char*& buffer, size_t& buffer_size, std::string& pathName, std::string& pathCurrent) {
    delete[] buffer;
    buffer = nullptr;
    buffer_size = 0;
    pathName = "";
    pathCurrent = "";
}

void bufferIntoFile(char*& buffer, size_t& buffer_size, std::string& pathName, std::string& pathCurrent) {
    std::ofstream file(pathName, std::ofstream::binary);
    file.seekp(0, file.end);
    file.write(buffer, buffer_size);
    file.close();
}

void openFile(std::string& filePath, char*& data, size_t& data_size, bool& fileOpen, size_t& filePathCurrentLength) {
    std::string content = "";
    std::ifstream file(filePath, std::ifstream::binary);
    file.seekg(0, file.end);
    data_size = size_t(file.tellg());
    file.seekg(0, file.beg);
    data = new char[data_size];
    file.read(data, data_size);
    file.close();
    fileOpen = false;
    filePathCurrentLength = filePath.length();
}

/*V2.0 --> dataInEditBuffer func*/