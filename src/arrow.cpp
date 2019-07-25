#include "arrow.h"
#include "main.h"
#include <cmath>
using namespace std;
const int L = 1e5 + 5;

Arrow::Arrow(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->flag = 0;
    this->moveflag = 0;
    this->size = 5;
    this->color = color;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
}

void Arrow::draw(glm::mat4 VP) {

    static GLfloat vertex_buffer_data[L];
    int i, n = 300;
    int count = 0, count2 = 0;
    for (i = 0; i < n; i++)
    {
        vertex_buffer_data[45 * i] = 0.0f;
        vertex_buffer_data[45 * i + 1] = -1.0f * this->size;
        vertex_buffer_data[45 * i + 2] = 0.0f;

        vertex_buffer_data[45 * i + 3] = 1.0 * this->size * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[45 * i + 4] = -1.0f * this->size;
        vertex_buffer_data[45 * i + 5] = 1.0 * this->size * (double)sin((2 * M_PI * i)/n);
        
        vertex_buffer_data[45 * i + 6] = 1.0 * this->size * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[45 * i + 7] = -1.0f * this->size;
        vertex_buffer_data[45 * i + 8] = 1.0 * this->size * (double)sin((2 * M_PI * (i + 1))/n);

        vertex_buffer_data[45 * i + 9] = 0.0f;
        vertex_buffer_data[45 * i + 10] = 1.0f * this->size;
        vertex_buffer_data[45 * i + 11] = 0.0f;

        vertex_buffer_data[45 * i + 12] = 1.0 * this->size * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[45 * i + 13] = 1.0f * this->size;
        vertex_buffer_data[45 * i + 14] = 1.0 * this->size * (double)sin((2 * M_PI * i)/n);
        
        vertex_buffer_data[45 * i + 15] = 1.0 * this->size * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[45 * i + 16] = 1.0f * this->size;
        vertex_buffer_data[45 * i + 17] = 1.0 * this->size * (double)sin((2 * M_PI * (i + 1))/n);

        vertex_buffer_data[45 * i + 18] = 1.0 * this->size * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[45 * i + 19] = 1.0f * this->size;
        vertex_buffer_data[45 * i + 20] = 1.0 * this->size * (double)sin((2 * M_PI * i)/n);

        vertex_buffer_data[45 * i + 21] = 1.0 * this->size * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[45 * i + 22] = -1.0f * this->size;
        vertex_buffer_data[45 * i + 23] = 1.0 * this->size * (double)sin((2 * M_PI * i)/n);
        
        vertex_buffer_data[45 * i + 24] = 1.0 * this->size * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[45 * i + 25] = -1.0f * this->size;
        vertex_buffer_data[45 * i + 26] = 1.0 * this->size * (double)sin((2 * M_PI * (i + 1))/n);

        vertex_buffer_data[45 * i + 27] = 1.0 * this->size * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[45 * i + 28] = -1.0f * this->size;
        vertex_buffer_data[45 * i + 29] = 1.0 * this->size * (double)sin((2 * M_PI * (i + 1))/n);

        vertex_buffer_data[45 * i + 30] = 1.0 * this->size * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[45 * i + 31] = 1.0f * this->size;
        vertex_buffer_data[45 * i + 32] = 1.0 * this->size * (double)sin((2 * M_PI * i)/n);
        
        vertex_buffer_data[45 * i + 33] = 1.0 * this->size * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[45 * i + 34] = 1.0f * this->size;
        vertex_buffer_data[45 * i + 35] = 1.0 * this->size * (double)sin((2 * M_PI * (i + 1))/n);
        
        vertex_buffer_data[45 * i + 36] = 1.4 * this->size * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[45 * i + 37] = -1.0f * this->size;
        vertex_buffer_data[45 * i + 38] = 1.4 * this->size * (double)sin((2 * M_PI * (i + 1))/n);

        vertex_buffer_data[45 * i + 39] = 1.4 * this->size * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[45 * i + 40] = -1.0f * this->size;
        vertex_buffer_data[45 * i + 41] = 1.4 * this->size * (double)sin((2 * M_PI * i)/n);
        
        vertex_buffer_data[45 * i + 42] = 0.0f;
        vertex_buffer_data[45 * i + 43] = -3.0f * this->size;
        vertex_buffer_data[45 * i + 44] = 0.0f;
        
        count += 36;
    }

    this->object = create3DObject(GL_TRIANGLES, n * 18, vertex_buffer_data, this->color, GL_FILL);
    
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

void Arrow::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Arrow::tick() {

}
