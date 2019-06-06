#include "../include/texture.hpp"
#include "../include/constants.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <stb_image/stb_image.h>

GLuint loadTexture (const char image_path[]){

	int imgWidth, imgHeight, imgChannels;
    unsigned char *image = stbi_load(image_path, &imgWidth, &imgHeight, &imgChannels, STBI_rgb_alpha);
    if (nullptr == image)
    {
        printf("\nça ne marche pas\n");
        return (EXIT_FAILURE);
    }
    // Autorisation de l'affichage des textures
    glEnable(GL_TEXTURE_2D);

    /* Initialisation de la texture */
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    return texture_id;
}