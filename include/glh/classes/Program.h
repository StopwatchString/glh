#ifndef GLH_PROGRAM_H
#define GLH_PROGRAM_H

#include "glh/functionWrappers.h"

#include <filesystem>

class Program
{
public:
    Program(std::filesystem::path vertSourceFile, std::filesystem::path fragSourceFile);
    ~Program();

    void bind();
    void unbind();

    void reload();
    void isValid();

private:
    GLuint m_ProgramName{ 0 };
};

#endif