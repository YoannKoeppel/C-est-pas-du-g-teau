#include "../include/enemy.hpp"
#include "../include/constants.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

Enemy::Enemy(float x, float y) : m_x(x), m_y(y) {
    printf("Enemy created ! \n");
}

Enemy::~Enemy() {
    printf("Enemy destructed !\n");
}

void Enemy::update(float nodes[], Menu *Place) {
    glColor4f(255, 0, 0, 1);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glVertex2f(m_x, m_y);
    glEnd();
    glPointSize(1.0f);

    if (j<15){
        if(m_x == nodes[j] && m_y == nodes[j+1]) j=j+2;
        else{
            if(m_x < nodes[j]) m_x++;
            else if (m_x > nodes[j]) m_x--;
            if(m_y < nodes[j+1]) m_y++;
            else if (m_y > nodes[j+1]) m_y--;
        }
    }
    else *Place = win;

}

/*void Enemy::update(float nodes[]) {
    glColor4f(255, 0, 0, 1);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glVertex2f(m_x, m_y);
    glEnd();
    glPointSize(1.0f);

    int i;
    if (i!=16){
        if(m_x == nodes[i]->getX() && m_y == nodes[i+1]->getY()) i=i+2;
        else{
            if(m_x < nodes[i]->getX() m_x++;
            else if (m_x > nodes[i]->getX()) m_x--;
            if(m_y < nodes[i+1]->getY()) m_y++;
            else if (m_y > nodes[i+1]->getY()) m_y--;
        }
    }
    else glColor4f(1, 1, 1, 0);

}*/


void Enemy::draw(GLuint texture_id){

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

