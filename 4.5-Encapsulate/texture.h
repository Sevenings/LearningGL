#ifndef TEXTURE_H
#define TEXTURE_H

// #include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Texture {
public:
    unsigned int ID;
    int width, height;
    unsigned int unit;
    // constructor generates the texture on the fly
    // ------------------------------------------------------------------------
    Texture(const char* imagePath) {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
        if (!data) {
            std::cout << "Failed to load texture" << ID << std::endl;
            return;
        }
        if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }

    void bindToUnit(unsigned int gl_unit_id) {
        glActiveTexture(gl_unit_id);
        glBindTexture(GL_TEXTURE_2D, ID);
        unit = gl_unit_id;
    }

};

#endif

