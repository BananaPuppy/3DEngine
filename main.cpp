// Engine
#include "utility/debug.h"
#include "utility/IOfile.h"

#include "manager/window.h"

#include "core.h"

// Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

int main(void)
{
    glfwInit();

    GLFWwindow* window = engine_create_window(800, 800, "Window Title", NULL, NULL);

    glfwSetErrorCallback(glfw_error_callback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { writeConsole("gladLoadGLLoader() failed"); exit(GLAD_EXIT_CODE); }

    engine_game_loop(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}