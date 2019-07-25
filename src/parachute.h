#include "main.h"

#ifndef PARA_H
#define PARA_H


class Para {
public:
    Para() {}
    Para(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 n_position;
    float rotation1;
    int flag;
    float speedz, speedx, speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // BALL_H
