#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 n_position;
    float rotation1;
    int flag;
    float size;
    int moveflag;
    color_t color;
    float speedz, speedx, speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // BALL_H
