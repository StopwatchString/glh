@echo off

rem Create target directories
mkdir extracted_sources\include
mkdir extracted_sources\src

rem Copy header files
copy imgui\imgui.h extracted_sources\include\
copy imgui\imconfig.h extracted_sources\include\
copy imgui\imgui_internal.h extracted_sources\include\
copy imgui\imstb_rectpack.h extracted_sources\include\
copy imgui\imstb_textedit.h extracted_sources\include\
copy imgui\imstb_truetype.h extracted_sources\include\
copy imgui\backends\imgui_impl_glfw.h extracted_sources\include\
copy imgui\backends\imgui_impl_opengl3.h extracted_sources\include\
copy imgui\backends\imgui_impl_opengl3_loader.h extracted_sources\include\

rem Copy source files
copy imgui\imgui.cpp extracted_sources\src\
copy imgui\imgui_demo.cpp extracted_sources\src\
copy imgui\imgui_draw.cpp extracted_sources\src\
copy imgui\imgui_tables.cpp extracted_sources\src\
copy imgui\imgui_widgets.cpp extracted_sources\src\
copy imgui\backends\imgui_impl_glfw.cpp extracted_sources\src\
copy imgui\backends\imgui_impl_opengl3.cpp extracted_sources\src\

echo Extraction complete.
