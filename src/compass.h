#include "main.h"

#ifndef COMP_H
#define COMP_H


class Comp {
public:
    Comp() {}
    Comp(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
