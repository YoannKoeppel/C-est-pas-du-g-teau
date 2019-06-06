#pragma once

#include <vector>

static const unsigned int MENU_WIDTH = 300;

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 750 + MENU_WIDTH;
static const unsigned int WINDOW_HEIGHT = 750;

enum Menu { 
    startMenu,
    game,
    win,
    lost,
    rules
};

/*class Node {
public:
    Node(float x, float y);
    ~Node();

    // Getters 
    float getX() const { return m_x; }
    float getY() const { return m_y; }

    // Setters 
    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }

private:
    float m_x;
    float m_y;
    Node *next;
};*/