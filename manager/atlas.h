#pragma once

#include "../utility/debug.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../utility/stb_image.h"

#include <glm/glm.hpp>

glm::vec2 atlasDim(1280, 1280);
static glm::vec2 getAtlasDimensions() { return atlasDim; }

static void loadAtlas()
{
    int tex_width, tex_height, nrChannels;
    unsigned char* tex_data;

    unsigned int texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture);
    tex_data = stbi_load("textures/atlas.png", &tex_width, &tex_height, &nrChannels, 0);
    if (tex_data) { glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data); glGenerateMipmap(GL_TEXTURE_2D); }
    else { writeConsole("Failed to load texture"); std::cout << stbi_failure_reason(); }

    stbi_image_free(tex_data);
}