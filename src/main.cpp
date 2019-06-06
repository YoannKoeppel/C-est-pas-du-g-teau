#ifdef _WIN32
    #include <windows.h>
#endif
#define _USE_MATH_DEFINES
#include <cmath>
#include <stb_image/stb_image.h>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/init.hpp"
#include "../include/tower.hpp"
#include "../include/enemy.hpp"
#include "../include/map.hpp"
#include "../include/texture.hpp"
#include "../include/constants.hpp"

static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


int main(int argc, char **argv) {

    SDL_Window* window = imac::init();
    if (window == nullptr) {
        printf("[INIT] Init not achieved !");
    }

    /* Chargement des images */

    //map
    const char map_path[] = "images/texture.png";
    GLuint maptexture;
    maptexture = loadTexture (map_path);

    //tower
    const char tower_path[] = "images/cake.png";
    GLuint towerTexture;
    towerTexture = loadTexture (tower_path);

    //startMenu
    const char play_path[] = "images/play.png";
    GLuint playTexture;
    playTexture = loadTexture (play_path);

    //Enemy
    const char enemy_path[] = "images/enemy.png";
    GLuint enemyTexture;
    enemyTexture = loadTexture (enemy_path);

    //gameOver
    const char gameOver_path[] = "images/gameOver.png";
    GLuint GameOverTexture;
    GameOverTexture = loadTexture (gameOver_path);

    //win
    const char win_path[] = "images/win.png";
    GLuint winTexture;
    winTexture = loadTexture (win_path);
    
 //-----------------------------------------------

    // Entities
    std::vector<Tower*> towers;
    std::vector<Enemy*> enemies;
    /*std::vector<Node*> nodes;
    
    Node* node = new Node(175.0, 125.0);
    nodes.push_back(node);
    node->setX(175.0);
    node->setY(125.0);
    Node* node1 = new Node(625.0, 125.0);
    nodes.push_back(node1);
    node1->setX(625.0);
    node1->setY(125.0);
    Node* node2 = new Node(625.0, 275.0);
    nodes.push_back(node2);
    node2->setX(625.0);
    node2->setY(275.0);
    Node* node3 = new Node(175.0, 275.0);
    nodes.push_back(node3);
    node3->setX(175.0);
    node3->setY(275.0);
    Node* node4 = new Node(175.0, 525.0);
    nodes.push_back(node4);
    node4->setX(175.0);
    node4->setY(525.0);
    Node* node5 = new Node(475.0, 525.0);
    nodes.push_back(node5);
    node5->setX(475.0);
    node5->setY(525.0);
    Node* node6 = new Node(475.0, 625.0);
    nodes.push_back(node6);
    node6->setX(475.0);
    node6->setY(625.0);
    Node* node7 = new Node(575.0, 625.0);
    nodes.push_back(node7);
    node7->setX(575.0);
    node7->setY(625.0);*/
    float nodes[16] = {75.0, 125.0, 625.0, 125.0, 625.0, 275.0, 175.0, 275.0, 175.0, 525.0, 475.0, 525.0, 475.0, 625.0, 675.0, 625.0};


    // Map
    Map level1("data/carte.itd");

    Menu Place;
    Place = Menu::startMenu;
    bool loop = true;
    while (loop) {
        glColor4f(255, 255, 255, 1);
        Uint32 startTime = SDL_GetTicks();
        glClear(GL_COLOR_BUFFER_BIT);

        switch(Place){

            case startMenu:
                glBindTexture(GL_TEXTURE_2D, playTexture);
                glBegin(GL_QUADS);
                    glTexCoord2f(0, 1); glVertex2f(0, WINDOW_HEIGHT);   // bas gauche
                    glTexCoord2f(1, 1); glVertex2f((WINDOW_WIDTH), WINDOW_HEIGHT);    // bas droite
                    glTexCoord2f(1, 0); glVertex2f((WINDOW_WIDTH), 0);     // haut droite
                    glTexCoord2f(0, 0); glVertex2f(0, 0);    // haut gauche
                glEnd();
                glBindTexture(GL_TEXTURE_2D, 0);
                break;
        
            case game:
                glBindTexture(GL_TEXTURE_2D, maptexture);
                glBegin(GL_QUADS);
                    glTexCoord2f(0, 1); glVertex2f(0, WINDOW_HEIGHT);   // bas gauche
                    glTexCoord2f(1, 1); glVertex2f((WINDOW_WIDTH - MENU_WIDTH), WINDOW_HEIGHT);    // bas droite
                    glTexCoord2f(1, 0); glVertex2f((WINDOW_WIDTH - MENU_WIDTH), 0);     // haut droite
                    glTexCoord2f(0, 0); glVertex2f(0, 0);    // haut gauche
                glEnd();
                glBindTexture(GL_TEXTURE_2D, 0);


                /* Game updates */
                level1.draw();
                for (Tower* tower : towers) {
                    tower->update();
                    tower->draw(towerTexture);
                }
                for (Enemy* enemy : enemies) {
                    enemy->update(nodes, &Place);
                    enemy->draw(enemyTexture);
                }

                break;

            case lost:
                glBindTexture(GL_TEXTURE_2D, GameOverTexture);
                glBegin(GL_QUADS);
                    glTexCoord2f(0, 1); glVertex2f(0, WINDOW_HEIGHT);   // bas gauche
                    glTexCoord2f(1, 1); glVertex2f((WINDOW_WIDTH), WINDOW_HEIGHT);    // bas droite
                    glTexCoord2f(1, 0); glVertex2f((WINDOW_WIDTH), 0);     // haut droite
                    glTexCoord2f(0, 0); glVertex2f(0, 0);    // haut gauche
                glEnd();
                glBindTexture(GL_TEXTURE_2D, 0);
                break;

            case win:
                glBindTexture(GL_TEXTURE_2D, winTexture);
                glBegin(GL_QUADS);
                    glTexCoord2f(0, 1); glVertex2f(0, WINDOW_HEIGHT);   // bas gauche
                    glTexCoord2f(1, 1); glVertex2f((WINDOW_WIDTH), WINDOW_HEIGHT);    // bas droite
                    glTexCoord2f(1, 0); glVertex2f((WINDOW_WIDTH), 0);     // haut droite
                    glTexCoord2f(0, 0); glVertex2f(0, 0);    // haut gauche
                glEnd();
                glBindTexture(GL_TEXTURE_2D, 0);
                break;

            default:
                break;
        }

        SDL_GL_SwapWindow(window);
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                loop = false;
                break;
            }

            switch (e.type) {
                case SDL_MOUSEBUTTONUP:
                    {
                        glm::vec2 gridPos = level1.windowToGrid((float) e.button.x, (float) e.button.y);
						MapTile tile = level1.getTile(gridPos.x, gridPos.y);
                        switch (Place){
                            
                            case startMenu:
                                Place = game;
                            break;

                            case game:
                                if (tile == MapTile::constructible && e.button.x<(WINDOW_WIDTH-MENU_WIDTH)) {
                                    glm::vec2 winPos = level1.gridToWindow(gridPos.x, gridPos.y);
        							glm::vec2 center = level1.gridToWindow(1, 1);
        							center /= 2;
        							winPos += center;
                                    Tower* tower = new Tower(winPos.x, winPos.y);
                                    towers.push_back(tower);
                                    tower->setX(winPos.x);
                                    tower->setY(winPos.y);
        							level1.setTile(gridPos.x, gridPos.y, MapTile::tower);
                                } else {
                                    printf("can't construct here\n");
                                }
                            break;

                            case win:
                                Place = lost;
                            break;

                            default:
                                break;
                        }
                    
                    }
                    break;

                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    if(Place == game){
                        if(e.key.keysym.sym == SDLK_v){
                            Enemy* enemy = new Enemy(nodes[0], nodes[1]);
                            enemies.push_back(enemy);
                            enemy->setX(nodes[0]);
                            enemy->setY(nodes[1]);
                        }
                    }
                    break;

                default:
                    break;
            }
        }


        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if (elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Cleanup */
    SDL_DestroyWindow(window);
    SDL_Quit();
    for (Tower* tower : towers) {
        delete tower;
    }
    for (Enemy* enemy : enemies) {
        delete enemy;
    }

    return EXIT_SUCCESS;
}
