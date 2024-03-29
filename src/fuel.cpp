#include "fuel.h"
#include "main.h"
#include <cmath>
using namespace std;
const int L = 1e5 + 5;

Fuel::Fuel(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->flag = 0;
    this->rotation1 = 0;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n = 30;
    static GLfloat vertex_buffer_data[]={
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 5.0f, 0.0f,

        1.0f, 5.0f, 0.0f,
        0.0f, 5.0f, 0.0f,
        0.0f, 0.0f, 0.0f,

        1.0f, 5.0f, 0.0f,
        4.0f, 5.0f, 0.0f,
        4.0f, 4.0f, 0.0f,

        1.0f, 5.0f, 0.0f,
        1.0f, 4.0f, 0.0f,
        4.0f, 4.0f, 0.0f,

        1.0f, 3.0f, 0.0f,
        1.0f, 2.0f, 0.0f,
        4.0f, 2.0f, 0.0f,

        4.0f, 2.0f, 0.0f,
        4.0f, 3.0f, 0.0f,
        1.0f, 3.0f, 0.0f,

        //----

        0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, -1.0f,
        1.0f, 5.0f, -1.0f,

        1.0f, 5.0f, -1.0f,
        0.0f, 5.0f, -1.0f,
        0.0f, 0.0f, -1.0f,

        1.0f, 5.0f, -1.0f,
        4.0f, 5.0f, -1.0f,
        4.0f, 4.0f, -1.0f,

        1.0f, 5.0f, -1.0f,
        1.0f, 4.0f, -1.0f,
        4.0f, 4.0f, -1.0f,

        1.0f, 3.0f, -1.0f,
        1.0f, 2.0f, -1.0f,
        4.0f, 2.0f, -1.0f,

        4.0f, 2.0f, -1.0f,
        4.0f, 3.0f, -1.0f,
        1.0f, 3.0f, -1.0f,
        
        //---

        4.0f, 3.0f, 0.0f,
        4.0f, 3.0f, -1.0f,
        4.0f, 2.0f, 0.0f,

        4.0f, 2.0f, 0.0f,
        4.0f, 2.0f, -1.0f,
        4.0f, 3.0f, -1.0f,

        4.0f, 5.0f, 0.0f,
        4.0f, 5.0f, -1.0f,
        4.0f, 4.0f, 0.0f,

        4.0f, 4.0f, 0.0f,
        4.0f, 4.0f, -1.0f,
        4.0f, 5.0f, -1.0f,

        //---

        4.0f, 5.0f, 0.0f,
        4.0f, 5.0f, -1.0f,
        0.0f, 5.0f, 0.0f,

        4.0f, 5.0f, -1.0f,
        0.0f, 5.0f, -1.0f,
        0.0f, 5.0f, 0.0f,

        4.0f, 4.0f, 0.0f,
        4.0f, 4.0f, -1.0f,
        0.0f, 4.0f, 0.0f,

        4.0f, 4.0f, -1.0f,
        0.0f, 4.0f, -1.0f,
        0.0f, 4.0f, 0.0f,

        4.0f, 3.0f, 0.0f,
        4.0f, 3.0f, -1.0f,
        0.0f, 3.0f, 0.0f,

        4.0f, 3.0f, -1.0f,
        0.0f, 3.0f, -1.0f,
        0.0f, 3.0f, 0.0f,

        4.0f, 2.0f, 0.0f,
        4.0f, 2.0f, -1.0f,
        0.0f, 2.0f, 0.0f,

        4.0f, 2.0f, -1.0f,
        0.0f, 2.0f, -1.0f,
        0.0f, 2.0f, 0.0f,

        //--

        0.0f, 0.0f, 0.0f,
        0.0f, 5.0f, 0.0f,
        0.0f, 5.0f, -1.0f,

        0.0f, 5.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        1.0f, 5.0f, 0.0f,
        1.0f, 5.0f, -1.0f,

        1.0f, 5.0f, -1.0f,
        1.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f,

        //--

        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, -1.0f,

        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, -1.0f,
    };
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Fuel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.2f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation1 * M_PI / 180.0f), glm::vec3(rotx,roty,rotz));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate * rotate);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Fuel::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fuel::tick() {
    this->rotation1 += 2;
}
