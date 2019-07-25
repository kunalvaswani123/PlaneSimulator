#include "main.h"

#ifndef BAR_H
#define BAR_H


class Bar {
public:
    Bar() {}
    Bar(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float size;
    color_t color;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
