#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 n_position;
    float rotation1;
    float yaw;
    int flag;
    float speedz, speedx, speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // BALL_H
