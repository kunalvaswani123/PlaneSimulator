#include "missile.h"
#include "main.h"
#include <cmath>
using namespace std;
const int L = 1e5 + 5;

Missile::Missile(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->time = 0;
    this->flag = 0;
    this->yaw = 0;
    this->speedz = 0;
    this->speedx = 0;
    this->speed = 10;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[L];
    int i, n = 300;
    int count = 0;
    for (i = 0; i < n; i++)
    {
        vertex_buffer_data[36 * i] = 0.0f;
        vertex_buffer_data[36 * i + 1] = 0.0f;
        vertex_buffer_data[36 * i + 2] = -6.0f;

        vertex_buffer_data[36 * i + 3] = 0.8 * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[36 * i + 4] = 0.8 * (double)sin((2 * M_PI * i)/n);
        vertex_buffer_data[36 * i + 5] = -6.0f;
        
        vertex_buffer_data[36 * i + 6] = 0.8 * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[36 * i + 7] = 0.8 * (double)sin((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[36 * i + 8] = -6.0f;

        vertex_buffer_data[36 * i + 9] = 0.0f;
        vertex_buffer_data[36 * i + 10] = 0.0f;
        vertex_buffer_data[36 * i + 11] = -10.0f;

        vertex_buffer_data[36 * i + 12] = 0.8 * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[36 * i + 13] = 0.8 * (double)sin((2 * M_PI * i)/n);
        vertex_buffer_data[36 * i + 14] = -10.0f;
        
        vertex_buffer_data[36 * i + 15] = 0.8 * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[36 * i + 16] = 0.8 * (double)sin((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[36 * i + 17] = -10.0f;

        vertex_buffer_data[36 * i + 18] = 0.8 * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[36 * i + 19] = 0.8 * (double)sin((2 * M_PI * i)/n);
        vertex_buffer_data[36 * i + 20] = -10.0f;

        vertex_buffer_data[36 * i + 21] = 0.8 * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[36 * i + 22] = 0.8 * (double)sin((2 * M_PI * i)/n);
        vertex_buffer_data[36 * i + 23] = -6.0f;
        
        vertex_buffer_data[36 * i + 24] = 0.8 * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[36 * i + 25] = 0.8 * (double)sin((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[36 * i + 26] = -6.0f;

        vertex_buffer_data[36 * i + 27] = 0.8 * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[36 * i + 28] = 0.8 * (double)sin((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[36 * i + 29] = -6.0f;

        vertex_buffer_data[36 * i + 30] = 0.8 * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[36 * i + 31] = 0.8 * (double)sin((2 * M_PI * i)/n);
        vertex_buffer_data[36 * i + 32] = -10.0f;
        
        vertex_buffer_data[36 * i + 33] = 0.8 * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[36 * i + 34] = 0.8 * (double)sin((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[36 * i + 35] = -10.0f;
        count += 36;
    }
    this->object = create3DObject(GL_TRIANGLES, n * 12, vertex_buffer_data, color, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.2f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation1 * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 yaw  = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate * rotate);
    Matrices.model *= translate * yaw;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Missile::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Missile::tick() {
    this->position.z -= this->speedz * 0.1;
    this->position.x -= this->speedx * 0.1;
    this->speedz = this->speed * (double)cos((M_PI * this->yaw / 180.0f));
    this->speedx = this->speed * (double)sin((M_PI * this->yaw / 180.0f));
    time++;
}
