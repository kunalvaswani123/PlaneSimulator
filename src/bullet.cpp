#include "bullet.h"
#include "main.h"
#include <cmath>
using namespace std;
const int L = 1e5 + 5;

Bullet::Bullet(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->flag = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[L];
    int i, n = 300;
    int count = 0, count2 = 0;
    for (i = 0; i < n; i++)
    {
        vertex_buffer_data[36 * i] = 0.0f;
        vertex_buffer_data[36 * i + 1] = 1.5f;
        vertex_buffer_data[36 * i + 2] = 0.0f;

        vertex_buffer_data[36 * i + 3] = 2.0 * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[36 * i + 4] = 1.5f;
        vertex_buffer_data[36 * i + 5] = 2.0 * (double)sin((2 * M_PI * i)/n);
        
        vertex_buffer_data[36 * i + 6] = 2.0 * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[36 * i + 7] = 1.5f;
        vertex_buffer_data[36 * i + 8] = 2.0 * (double)sin((2 * M_PI * (i + 1))/n);

        vertex_buffer_data[36 * i + 9] = 0.0f;
        vertex_buffer_data[36 * i + 10] = 3.0f;
        vertex_buffer_data[36 * i + 11] = 0.0f;

        vertex_buffer_data[36 * i + 12] = 2.0 * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[36 * i + 13] = 3.0f;
        vertex_buffer_data[36 * i + 14] = 2.0 * (double)sin((2 * M_PI * i)/n);
        
        vertex_buffer_data[36 * i + 15] = 2.0 * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[36 * i + 16] = 3.0f;
        vertex_buffer_data[36 * i + 17] = 2.0 * (double)sin((2 * M_PI * (i + 1))/n);

        vertex_buffer_data[36 * i + 18] = 2.0 * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[36 * i + 19] = 3.0f;
        vertex_buffer_data[36 * i + 20] = 2.0 * (double)sin((2 * M_PI * i)/n);

        vertex_buffer_data[36 * i + 21] = 2.0 * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[36 * i + 22] = 1.5f;
        vertex_buffer_data[36 * i + 23] = 2.0 * (double)sin((2 * M_PI * i)/n);
        
        vertex_buffer_data[36 * i + 24] = 2.0 * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[36 * i + 25] = 1.5f;
        vertex_buffer_data[36 * i + 26] = 2.0 * (double)sin((2 * M_PI * (i + 1))/n);

        vertex_buffer_data[36 * i + 27] = 2.0 * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[36 * i + 28] = 1.5f;
        vertex_buffer_data[36 * i + 29] = 2.0 * (double)sin((2 * M_PI * (i + 1))/n);

        vertex_buffer_data[36 * i + 30] = 2.0 * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[36 * i + 31] = 3.0f;
        vertex_buffer_data[36 * i + 32] = 2.0 * (double)sin((2 * M_PI * i)/n);
        
        vertex_buffer_data[36 * i + 33] = 2.0 * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[36 * i + 34] = 3.0f;
        vertex_buffer_data[36 * i + 35] = 2.0 * (double)sin((2 * M_PI * (i + 1))/n);
        count += 36;
    }

    this->object = create3DObject(GL_TRIANGLES, n * 12, vertex_buffer_data, color, GL_FILL);
}

void Bullet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.2f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation1 * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate * rotate);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bullet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Bullet::tick() {
    this->position.y += 0.1;
}
