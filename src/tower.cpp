#include "../include/tower.hpp"

#ifdef _WIN32
#include <windows.h>
#endif
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

Tower::Tower(float x, float y) : m_x(x), m_y(y), m_radius(60)
{
    printf("Tower created ! \n");
}

Tower::~Tower() {
    printf("Tower destructed ! \n");
}

void Tower::update() {
    /*glColor4f(255, 0, 0, 1);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glVertex2f(m_x, m_y);
    glEnd();
    glPointSize(1.0f);*/
    
    glColor4f(255, 0, 0, 1);
	// Draw collision circle
	float segments = 16.0f;
	float increment = 2.0f * M_PI / segments;
	float theta = 0.0f;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < segments; i++) {
		float x = m_x + m_radius * cos(theta);
		float y = m_y + m_radius * sin(theta);
		glVertex2f(x, y);
		theta += increment;
	}
	glEnd();

}

void Tower::draw(GLuint texture_id){

	glColor4f(255, 255, 255, 1);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;

	glBindTexture(GL_TEXTURE_2D, texture_id);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(m_x-25, m_y+25);   // bas gauche
        glTexCoord2f(1, 1); glVertex2f(m_x+25, m_y+25);    // bas droite
        glTexCoord2f(1, 0); glVertex2f(m_x+25, m_y-25);     // haut droite
        glTexCoord2f(0, 0); glVertex2f(m_x-25, m_y-25);    // haut gauche
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_BLEND);
}