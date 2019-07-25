#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 n_position;
    float rotation1;
    float yaw;
    float roll;
    float speedz, speedx, speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // BALL_H
