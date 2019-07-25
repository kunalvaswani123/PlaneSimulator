#include "main.h"

#ifndef CANON_H
#define CANON_H


class Canon {
public:
    Canon() {}
    Canon(float x, float y, float z, color_t color);
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
