#pragma once

#include "../utility/debug.h"
#include "../utility/IOfile.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static GLFWwindow* engine_create_window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
    //  Versions > 3.3 only add fancy functions, no new features
    //  3.3 is also supported by quite old computers
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Mac OS X compat

    GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
    if (!window)
    {
        writeConsole("glfwCreateWindow() failed");
        exit(GLFW_EXIT_CODE);
    }

    glfwMakeContextCurrent(window);

    return window;
}

static unsigned int engine_create_shaderprogram()
{
    // No Dangling Pointers
    std::string fragment_shader_str = readFile("./shaders/shader.frag", true);
    std::string vertex_shader_str = readFile("./shaders/shader.vert", true);
    static const char* fragment_shader_source = fragment_shader_str.c_str();
    static const char* vertex_shader_source = vertex_shader_str.c_str();

    // Compile Shader
    int success;

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        writeConsole("Vertex Shader failed to compile" + std::string(infoLog));
        exit(GLSL_EXIT_CODE);
    }

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        writeConsole("Fragment Shader failed to compile" + std::string(infoLog));
        exit(GLSL_EXIT_CODE);
    }


    unsigned int shaderprogram = glCreateProgram();
    glAttachShader(shaderprogram, vertex_shader); glAttachShader(shaderprogram, fragment_shader);
    glLinkProgram(shaderprogram);
    glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderprogram, 512, NULL, infoLog);
        writeConsole("Shader Program failed to link" + std::string(infoLog));
        exit(GLSL_EXIT_CODE);
    }


    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shaderprogram;
}