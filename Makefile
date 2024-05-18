# Makefile for MacOS Linux

EXE = disassembler
IMGUI_DIR = vendor/imgui

SOURCES =  src/disassembler.cpp
gui_SOURCES = src/main.cpp $(SOURCES) $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl2.cpp vendor/lib/ImGuiFileDialog/ImGuiFileDialog.cpp

nogui_OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
gui_OBJS = $(addsuffix .o, $(basename $(notdir $(gui_SOURCES))))

UNAME_S := $(shell uname -s)

CXXFLAGS = -std=c++20 -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -Ivendor/lib**
CXXFLAGS += -g -Wall -Wformat

LIBS =

#--BUILD--
ifeq ($(UNAME_S), Linux)
	ECHO_MESSAGE = "Linux"
	LIBS += -lGL `pkg-config --static --libs glfw3`

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS"
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
	LIBS += -L/usr/local/lib -L/opt/homebrew/lib
	#LIBS += -L/opt/local/lib
	#LIBS += -lglfw3
	LIBS += -lglfw

	CXXFLAGS += -I/usr/local/include -I/opt/local/include -I/opt/homebrew/include
	CFLAGS = $(CXXFLAGS)
endif

addGlobalDefinesGUI:
	$(eval CXXFLAGS += -DGUI)

addGlobalDefinesNOGUI:
	$(eval CXXFLAGS += -DNOGUI)

addGlobalDefinesDEBUG:
	$(eval CXXFLAGS += -DDEBUG)

gui: addGlobalDefinesGUI $(EXE)
	@mkdir -p x64
	@mkdir -p x64/gui
	@mkdir -p obj
	@mkdir -p obj/gui
	for i in $(gui_OBJS); do \
		mv $$i obj/gui/$$i; \
	done
	mv $(EXE) x64/gui/$(EXE)
	@echo Build gui complete for $(ECHO_MESSAGE)
nogui: addGlobalDefinesNOGUI $(EXE)_nogui
	@mkdir -p x64
	@mkdir -p x64/nogui
	@mkdir -p obj
	@mkdir -p obj/nogui
	for i in $(nogui_OBJS); do \
		mv $$i obj/nogui/$$i; \
	done
	mv $(EXE)_nogui x64/nogui/$(EXE)_nogui
	@echo Build nogui complete for $(ECHO_MESSAGE)

debug: addGlobalDefinesDEBUG $(EXE)_nogui
	@mkdir -p x64
	@mkdir -p x64/debug
	@mkdir -p obj
	@mkdir -p obj/debug
	for i in $(nogui_OBJS); do \
		mv $$i obj/debug/$$i; \
	done
	mv $(EXE)_nogui x64/debug/$(EXE)_nogui
	@echo Build debug nogui complete for $(ECHO_MESSAGE)


%.o:src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:vendor/lib/ImGuiFileDialog/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(EXE): $(gui_OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

$(EXE)_nogui: $(nogui_OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -r x64
	rm -r obj
	rm -f $(EXE) $(gui_OBJS) $(EXE)_nogui $(nogui_OBJS) 