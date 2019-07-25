#include "bar.h"
#include "main.h"
#include <cmath>
const int L = 1e5 + 5;

Bar::Bar(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->size = 2;
    this->color = color;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
}

void Bar::draw(glm::mat4 VP) {
    
    if (this->size < 0.4)
        this->color = COLOR_DARKRED;
    else
        this->color = COLOR_ORANGE;

    if (this->size >= 1.2)
        this->size = 1.2;

    if (this->size <= 0)
        this->size = 0;

    GLfloat vertex_buffer_data[]={
        this->size, 0.3f, 0.0f,
        0.0f, 0.3f, 0.0f,
        0.0f, -0.1f, 0.0f,

        0.0f, -0.1f, 0.0f,
        this->size, 0.3f, 0.0f,
        this->size, -0.1f, 0.0f,
    };
    this->object = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, this->color, GL_FILL);

    Matrices.model = glm::mat4(0.2f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bar::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Bar::tick() {
}
