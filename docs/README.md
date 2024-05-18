# DisassemblerAVR
DisassemblerAVR is a C++ written software used for reverse engineering `.hex` files compiled for AVR MCUs, such as the `ATmega328P`.
We developed the software in three versions, all of which can be run on `Windows 10/11`, `MacOS` and `Linux`:

 - **GUI**
 - **Command Line**
 - **Debug Command line**
 
## Versions overview
### GUI
 The GUI-based version is based on GLFW+OpenGL using [`IMGUI`](https://github.com/ocornut/imgui), a library that offer to develop with ease a gui interface-based applications. 
The other libraries used are:
 - [`ImGuiFileDialog`](https://github.com/aiekick/ImGuiFileDialog) for the file selection window
 - [`imgui_memory_editor`](https://github.com/ocornut/imgui_club) for the hex visualizer
 
### Command Line
The Command line-based version is a more simple software, all the code is written by ourselfes without any third-party libraries. 
To disassemble a file it's necessary to manually provide the full path to it.
Once the disassembly process is complete you will find a `.asm` file in the same directory as the original file.

### Debug Command Line
The Debug version is built in the same way as the command-line version, the only difference being that instead of creating a new file, the output is printed directly in the console and without branch labels.

## Building from source
### Windows pre-requirements

 - Visual Studio 2022 with C++ tools installed
 - Git
### MacOS and Linux pre-requirements
 
 - GCC
 - Make
 - Git

### Step 1.  Cloning the Repository

    git clone --recursive https://gitea.paolihomelab.xyz/IlPaoli/DisassemblerAVR
### Step 2. Build
On Windows: 

 - Open the `.sln` with Visual Studio
 - Choose the desired version in the **solution configurations** 

On Mac or Linux:
After cloning the repository use `cd {repository folder}`
Use:

 - `make gui`  to compile the **GUI**
 - `make nogui` to compile the **Command Line**
 - `make nogui` to compile the **Debug**

### Step 3. Execute
On Windows: 
 - Hit the **empty green arrow**  or **double-click** the `.exe` under `/x64/{version}`

On Mac or Linux:

 - **double-click** the `.exe` under `/x64/{version}`

## Usage
### GUI

 - To open a file **click** on `Open...` under `File` in the top bar
![GuiOpenFile](https://github.com/IlPaoli/DisassemblerAVR/assets/74500944/86e5ca1b-1d82-4294-be33-28f9f954591e)

 - Use the 'Disassemble' button at the bottom of the GUI to start the
   disassembly process.
![GuiDisassembleFile](https://github.com/IlPaoli/DisassemblerAVR/assets/74500944/9685e003-b108-4e68-8dbe-8859c205e2da)
### Command Line

 - If you don't know the file full path you can simply use the command
   `PWD` or just **drag-n-drop** the file into the console
 - To disassemble the file, input the **file full path** and press
   **Enter**
 ![CommandLineFile](https://github.com/IlPaoli/DisassemblerAVR/assets/74500944/07bc5aa8-229d-49e6-8722-c4f0b58b5d49)
 
 
## LICENSE
See [LICENSE](../LICENSE)
