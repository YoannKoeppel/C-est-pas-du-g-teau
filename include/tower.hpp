#pragma once

#include <GL/gl.h>
#include <GL/glu.h>

class Tower
{
public:
    Tower(float x, float y);
    ~Tower();

    void update();
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
	float m_radius;
};

