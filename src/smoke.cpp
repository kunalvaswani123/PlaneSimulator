#include "smoke.h"
#include "main.h"
#include <cmath>
const int L = 1e5 + 5;

Smoke::Smoke(float x, float z, color_t color) {
    this->position = glm::vec3(x, rand() % 10 - 5, z);
    this->rotation = rand() % 360;
    this->flag = 0;
    this->time = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[L];
    int i, n = 300;
    int count = 0;
    for (i = 0; i < n; i++)
    {
        vertex_buffer_data[18 * i] = 3.8 * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[18 * i + 1] = 3.8 * (double)sin((2 * M_PI * i)/n);
        vertex_buffer_data[18 * i + 2] = 0.0f;

        vertex_buffer_data[18 * i + 3] = 4.2 * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[18 * i + 4] = 4.2 * (double)sin((2 * M_PI * i)/n);
        vertex_buffer_data[18 * i + 5] = 0.0f;
        
        vertex_buffer_data[18 * i + 6] = 3.8 * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[18 * i + 7] = 3.8 * (double)sin((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[18 * i + 8] = 0.0f;

        vertex_buffer_data[18 * i + 9] = 4.2 * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[18 * i + 10] = 4.2 * (double)sin((2 * M_PI * i)/n);
        vertex_buffer_data[18 * i + 11] = 0.0f;

        vertex_buffer_data[18 * i + 12] = 3.8 * (double)cos((2 * M_PI * (i + 1)/n));
        vertex_buffer_data[18 * i + 13] = 3.8 * (double)sin((2 * M_PI * (i + 1)/n));
        vertex_buffer_data[18 * i + 14] = 0.0f;
        
        vertex_buffer_data[18 * i + 15] = 4.2 * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[18 * i + 16] = 4.2 * (double)sin((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[18 * i + 17] = 0.0f;
        count += 18;
    }
    this->object = create3DObject(GL_TRIANGLES, n * 6, vertex_buffer_data, color, GL_FILL);
}

void Smoke::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.2f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Smoke::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Smoke::tick() {
    
}
