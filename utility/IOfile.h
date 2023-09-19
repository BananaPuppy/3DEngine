#pragma once

#include "debug.h"

#include <filesystem>
#include <fstream>

std::string readFile(std::string filename, bool shouldExist = false, bool relative = false)
{
    if (!std::filesystem::exists(filename) && shouldExist) {
        writeConsole("readFile() not found");
        writeConsole("cwd: " + std::filesystem::current_path().string());
        writeConsole("target: " + filename);
        exit(EXIT_FAILURE);
    }

    std::ifstream file;
    file.open(filename);

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileString = buffer.str();

    return fileString;
}