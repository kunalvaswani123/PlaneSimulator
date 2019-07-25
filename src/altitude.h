#include "main.h"

#ifndef ALTITUDE_H
#define ALTITUDE_H


class Altitude {
public:
    Altitude() {}
    Altitude(float x, float y, color_t color);
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
