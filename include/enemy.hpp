#pragma once

#include "constants.hpp"
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <GL/glu.h>

class Enemy {
public:
    Enemy(float x, float y);
    ~Enemy();

    void update(float nodes[], Menu *Place);
    void draw(GLuint texture_id);

    /* Getters */
    float getX() const { return m_x; }
    float getY() const { return m_y; }

    /* Setters */
    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }

private:
    float m_x;
    float m_y;
    int j = 0;
};
