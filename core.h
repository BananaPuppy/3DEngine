#pragma once

#include "manager/atlas.h"

#include "objects/camera.h"
#include "objects/voxel.h"

#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

GLFWwindow* window;

static void window_render_setup(GLFWwindow* w)
{
    // Texture wrapping/filter options
    stbi_set_flip_vertically_on_load(true);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //TODO: Investiage MIN/MAG Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    window = w;
    glfwSetCursorPos(window, 0, 0);

    glfwSwapInterval(0); //v-sync bad >:(


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0, 0, 0, 1);
}

unsigned int shader_program;
static void shader_program_setup()
{
    shader_program = engine_create_shaderprogram();
    glUniform1i(glGetUniformLocation(shader_program, "texture1"), 0); // Send Atlas to GPU
    glUseProgram(shader_program);
}

static void vertex_attribute_setup()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Which vertex attribute do we want to configure? (location = 0)
    // What is the size of the vertex attribute (we are using a vec3)
    // What is the type of the data (a vec* in GLSL consists of floats)
    // Should the data be normalized?
    // What is the "stride"(spacing) of the data buffer?
    // Where does the offset of where the data begins in the data buffer?
}

float fpsMax = 609, fps_target = 300; float spf_target = 1.0f / fps_target;
int tick = 0, tps = 64.0f; //TODO: implement tps server-side once networking is implemented
float lastFrame = 0.0f, deltaTime = 0.0f;

bool is_cursorlocked = false;
Camera cam(window);
static void updateCursorLock(GLFWwindow* window, bool lock) {
    is_cursorlocked = lock;
    if (lock) { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); cam.firstMouse = true; }
    else { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); glfwSetCursorPos(window, 0, 0); }
}
static void updateFps(float change = 16.0f)
{
    fps_target += change; fps_target = std::clamp(fps_target, 1.0f, fpsMax); spf_target = 1 / fps_target; writeConsole("Target FPS: " + std::to_string(fps_target));
}

bool is_fullscreen = false;
glm::ivec4 windowed_settings(0.0f);
static void callback_keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        if (is_cursorlocked) { updateCursorLock(window, false); }
        else { glfwSetWindowShouldClose(window, GLFW_TRUE); }
    }
    if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
    {
        cam.firstMouse = true;
        if (!is_fullscreen)
        {
            glfwGetWindowPos(window, &windowed_settings.x, &windowed_settings.y);
            glfwGetWindowSize(window, &windowed_settings.z, &windowed_settings.w);

            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, 1980, 720, 60);
            is_fullscreen = true;
        }
        else if (is_fullscreen) { glfwSetWindowMonitor(window, NULL, windowed_settings.x, windowed_settings.y, windowed_settings.z, windowed_settings.w, 60); is_fullscreen = false; }
    }
}
static void callback_mouse(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE && is_cursorlocked == false) { updateCursorLock(window, true); }
}

static void callback_cursor(GLFWwindow* window, double xpos, double ypos)
{
    if (is_cursorlocked) {
        // Camera Rotation
        cam.Rotate(xpos, ypos);
    }
}

static void processInput(GLFWwindow* w)
{
    if (is_cursorlocked) {
        // Camera Movement
        glm::vec4 movement(0.0f);
        if (glfwGetKey(w, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) { movement.w = 1.0f; }
        if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) { movement.z++; }
        if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) { movement.z--; }
        if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS) { movement.x--; }
        if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) { movement.x++; }
        cam.Move(movement, deltaTime);
    }
}

glm::mat4 mat4Identity(1.0f);
glm::vec3 vec3Identity(1.0f);

float windowW;
float windowH;
float fov = 110.0f;
float nearPlane = 0.00001f, farPlane = 100.0f; //TODO: investigate how much nearPlane precision is needed
glm::mat4 projection = glm::perspective(glm::radians(fov), 1.0f / 1.0f, nearPlane, farPlane);
// FOV
// Aspect Ratio
// Near&Far Clipping Planes

static void glfw_framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
    windowW = w; windowH = h;
    glViewport(0, 0, windowW, windowH);
    projection = glm::perspective(glm::radians(fov), windowW / windowH, nearPlane, farPlane);
}

glm::mat4 model = mat4Identity;


// Really only the below function should be in here

static void engine_game_loop(GLFWwindow* w)
{
    // Setup
    window_render_setup(w);
    glfwSetKeyCallback(window, callback_keyboard);
    glfwSetMouseButtonCallback(window, callback_mouse);
    glfwSetCursorPosCallback(window, callback_cursor);

    glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);

    loadAtlas();

    //std::unordered_map<glm::vec2[3], int> texture_atlas;



    //stbi_image_free(tex_data); THIS SHOULD BE INCLUDED IN REWORK

    std::vector<Voxel> voxels = {
        Voxel(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(glm::vec2(0), glm::vec2(100))),
        Voxel(glm::vec3(2.0f, 5.0f, -15.0f), glm::vec4(glm::vec2(0), glm::vec2(100))),
        Voxel(glm::vec3(2.0f, 5.0f, -15.0f), glm::vec4(glm::vec2(0), glm::vec2(100))),
        Voxel(glm::vec3(-3.8f, -2.0f, -12.3f), glm::vec4(glm::vec2(0), glm::vec2(100))),
        Voxel(glm::vec3(2.4f, -0.4f, -3.5f), glm::vec4(glm::vec2(0), glm::vec2(100))),
        Voxel(glm::vec3(-1.7f,  3.0f, -7.5f), glm::vec4(glm::vec2(0), glm::vec2(100))),
        Voxel(glm::vec3(1.3f, -2.0f, -2.5f), glm::vec4(glm::vec2(0), glm::vec2(100))),
        Voxel(glm::vec3(1.5f,  2.0f, -2.5f), glm::vec4(glm::vec2(0), glm::vec2(100))),
        Voxel(glm::vec3(1.5f,  0.2f, -1.5f), glm::vec4(glm::vec2(0), glm::vec2(100))),
        Voxel(glm::vec3(-1.3f, 1.0f, -1.5f), glm::vec4(glm::vec2(0), glm::vec2(100)))
    };

    shader_program_setup();

    vertex_attribute_setup();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#pragma warning( push )
#pragma warning( disable : 4244 )
        float currentFrame = glfwGetTime();
#pragma warning( pop )
        //float stime = glm::max(2 * (-abs(glm::mod(runTime, 1.0f)) + 1), 1.0f) * glm::max(2 * (abs(glm::mod(runTime, 1.0f))), 1.0f); stime -= 1;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //Game Logic
        processInput(window);


        glm::mat4 view = glm::lookAt(cam.cameraPos, cam.cameraPos + cam.cameraFront, cam.cameraUp);

        //Render Logic //TODO: Limit framerate to target fps
        // Shader Uniforms
        glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader_program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        for (int i = 0; i < voxels.size(); i++)
        {
            voxels[i].getTexture();
            model = glm::translate(mat4Identity, voxels[i].getPos());
            //model = glm::rotate(model, glm::mod(currentFrame, 360.0f), glm::vec3(1));
            glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            // Drawing Mode
            // Element Count
            // Indices Type
            // Element Buffer Offset

        glfwSwapBuffers(window);


        glfwPollEvents();
    }
}