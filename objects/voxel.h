#pragma once

#include <glad/glad.h>

//#include <bullet/btBulletCollisionCommon.h>

#include "../manager/atlas.h"

class Voxel
{
    //unsigned int indices[] =
    //{
    //    0, 1, 3, // triangle 1
    //    1, 2, 3  // triangle 2
    //};
    //TODO: use Element Buffer(indices) instead of massive vertices array
    float vertices[180] = { -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, -0.5f,  0.5f, -0.5f,  0.0f, 1.0f };

    glm::vec3 position = glm::vec3(0.0f);
    float texture_coords[6];

    void genTexCoords(glm::vec4 coords) //Input = Top Left, Bottom Right
    { //Implement this as a hashmap in the future where the coords are associated with a title and just have the Voxel reference the title
        glm::vec2 atlasDim = getAtlasDimensions();

        float bottomLeftX = coords.x / atlasDim.x; float bottomLeftY = coords.w / atlasDim.y;
        float bottomRightX = coords.z / atlasDim.x; float bottomRightY = coords.w / atlasDim.y;
        float topCenterX = (coords.x + coords.z) / 2 / atlasDim.x; float topCenterY = coords.y / atlasDim.y;

        texture_coords[0] = bottomLeftX; texture_coords[1] = bottomLeftY;
        texture_coords[2] = bottomRightX; texture_coords[3] = bottomRightY;
        texture_coords[4] = topCenterX; texture_coords[5] = topCenterY;
    }
public:
    Voxel(glm::vec3 pos, glm::vec4 tex_coords)
    {
        position = pos;
        genTexCoords(tex_coords);

        //TODO: This can probably be done in a way where not every Voxel is responsible for doing Gen/Bind/Buffer Data stuff
        // But I don't want to move it somewhere else until the Element Buffer is properly used
        unsigned int VAO;
        unsigned int VBO;
        //unsigned int EBO;

        // Vertex Array Object
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        // Vertex Buffer Object
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // Element Buffer Object
        //glGenBuffers(1, &EBO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }

    glm::vec3 getPos()
    {
        return position;
    }

    void getTexture()
    {
        //TODO: Investigate a more memory friendly way to store a map of textures



    }
};