#pragma once

#include <string>
#include <iostream>

int GLFW_EXIT_CODE = -2;
int GLSL_EXIT_CODE = -4;
int GLAD_EXIT_CODE = -3;

static std::string writeConsole(std::string str = "")
{//TODO: writeConsole() actually write to some log file
    std::cout << str << "\n";
    return str;
}
void readConsole(std::string& varWrite) { std::getline(std::cin, varWrite); }

static void glfw_error_callback(int error, const char* description)
{
    writeConsole("Error: %s\n" + *description);
    exit(GLFW_EXIT_CODE);
}