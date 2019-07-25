#include "main.h"

#ifndef SMOKE_H
#define SMOKE_H


class Smoke {
public:
    Smoke() {}
    Smoke(float x, float z, color_t color);
    glm::vec3 position;
    float rotation;
    int flag;
    long long time;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
