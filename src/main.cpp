#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "speed.h"
#include "altitude.h"
#include "islands.h"
#include "missile.h"
#include "bomb.h"
#include "canon.h"
#include "bullet.h"
#include "parachute.h"
#include "smoke.h"
#include "arrow.h"
#include "volcano.h"
#include "fuel.h"
#include "7-segment.h"
#include "dashboard.h"
#include "bar.h"
#include "compass.h"

#define pb push_back

using namespace std;

typedef long long ll;

GLMatrices Matrices;
GLMatrices Matrices2;

GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Platform platform;
Seven display;
Speed speed;
Altitude alt;
Arrow arrow;
Dash dash;
Bar bar;
vector<Island> island;
vector<Missile> missile;
vector<Bomb> bomb;
vector<vector<Canon> >enemies;
vector<Bullet> bullets;
vector<Para> paras;
vector<Smoke> smoke;
vector<Volcano> volc;
vector<Fuel> fuel;
Comp comp;

int current_checkpoint = 0;
ll played = 1;
int dash_flag = 1;
int cam = 1;
int loop = 0;
double hradius = 40;
double angle = 0;
double startx = 0, starty = 0, startz = 0, staryaw = 0;;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float view_x = 0, view_y = 0, view_z = 0;
float hx = 0, hy = 0, hz = hradius;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // follow cam
    if (cam == 1)
    {
        float camera_x = ball1.position.x + 20 * (double)sin((M_PI * ball1.yaw / 180.0f));
        float camera_y = ball1.position.y + 8;
        float camera_z = ball1.position.z + 20 * (double)cos((M_PI * ball1.yaw / 180.0f));
        glm::vec3 eye ( camera_x, camera_y, camera_z );
        glm::vec3 target (ball1.position.x, ball1.position.y, ball1.position.z);
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }
    else if (cam == 2)
    {
        float camera_x = ball1.position.x;
        float camera_y = ball1.position.y + 200;
        float camera_z = ball1.position.z;
        glm::vec3 eye ( camera_x, camera_y, camera_z );
        glm::vec3 target (ball1.position.x, ball1.position.y, ball1.position.z);
        glm::vec3 up (0, 0, -1);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D   
    }
    else if (cam == 3)
    {
        float camera_x = 0;
        float camera_y = 50;
        float camera_z = 100;
        glm::vec3 eye ( camera_x, camera_y, camera_z );
        glm::vec3 target (ball1.position.x, ball1.position.y, ball1.position.z);
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D   
    }
    else if (cam == 4)
    {
        float camera_x = ball1.position.x - 10 * (double)sin((M_PI * ball1.yaw / 180.0f));
        float camera_y = ball1.position.y;
        float camera_z = ball1.position.z - 10 * (double)cos((M_PI * ball1.yaw / 180.0f));

        float target_x = ball1.position.x - 10.2 * (double)sin((M_PI * ball1.yaw / 180.0f));
        float target_y = ball1.position.y;
        float target_z = ball1.position.z - 10.2 * (double)cos((M_PI * ball1.yaw / 180.0f));

        glm::vec3 eye ( camera_x, camera_y, camera_z );
        glm::vec3 target (target_x, target_y, target_z);
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }
    else if (cam == 5)
    {
        double cursorx, cursory;
        glfwGetCursorPos(window, &cursorx, &cursory); 
        double valx = ((cursorx - 895)) / 960;  
        double valy = ((cursory - 488)) / 540;  
        hy = ball1.position.y - valy * hradius;
        double temp_radius = sqrt(hradius * hradius - hy * hy);
        hz = -(abs(valx) * 2 - 1) * hradius;
        if(valx > 0)
            hx = sqrt(abs(hradius * hradius - hz * hz));
        else
            hx = -sqrt(abs(hradius * hradius - hz * hz));
        hz += ball1.position.z;
        hx += ball1.position.x;
        glm::vec3 eye ( hx, hy, hz );
        glm::vec3 target (ball1.position.x, ball1.position.y, ball1.position.z);
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }
    else if (cam == 6)
    {
        float camera_x = 0;
        float camera_y = 0;
        float camera_z = 50;
        glm::vec3 eye ( camera_x, camera_y, camera_z );
        glm::vec3 target (0, 0, 0);
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D   
    }
    glm::vec3 eye2 ( 0, 0, 5 );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target2 (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up2 (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices2.view = glm::lookAt( eye2, target2, up2 ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP2 = Matrices2.projection * Matrices2.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    int i, j;
    ball1.draw(VP);
    platform.draw(VP);
    arrow.draw(VP);
    for(i=0;i<enemies.size();i++)
    {
        for(j=0;j<enemies[i].size();j++)
        {
            if(enemies[i][j].flag == 0)
                enemies[i][j].draw(VP);
        }
    }
    for(i = 0;i < island.size();i++)
        island[i].draw(VP);
    for(i = 0;i < missile.size();i++)
    {
        if(missile[i].flag == 0)
            missile[i].draw(VP);
    }
    for(i = 0;i < bomb.size();i++)
    {
        if(bomb[i].flag == 0)
            bomb[i].draw(VP);
    }
    for(i = 0;i < bullets.size();i++)
    {
        if(bullets[i].flag == 0)
            bullets[i].draw(VP);
    }
    for(i = 0;i < paras.size();i++)
    {
        if(paras[i].flag == 0)
            paras[i].draw(VP);
    }
    for(i = 0;i < smoke.size();i++)
    {
        if(smoke[i].flag == 0)
            smoke[i].draw(VP);
    }
    for(i=0;i<fuel.size();i++)
    {
        if(fuel[i].flag == 0)
            fuel[i].draw(VP);
    }
    for(i=0;i<volc.size();i++)
        volc[i].draw(VP);

    if(dash_flag == 1)
    {
        speed.draw(VP2);
        alt.draw(VP2);
        dash.draw(VP2);
        bar.draw(VP2);
        display.draw(VP2);
        comp.draw(VP2);
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        missile.pb(Missile(ball1.position.x, ball1.position.y, ball1.position.z, COLOR_DARKRED));
        missile.back().yaw = ball1.yaw;
        missile.back().speed += ball1.speed;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        bomb.pb(Bomb(ball1.position.x, ball1.position.y, ball1.position.z, COLOR_BLACK));
        bomb.back().yaw = ball1.yaw;
        bomb.back().speed += ball1.speed;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if(cam == 5)
    {
        if(hradius <= 200 && hradius >= 2)
            hradius += yoffset * -1;
        if(hradius <= 2)
            hradius = 2;
        if(hradius >= 200)
            hradius = 200;
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int tilt_l = glfwGetKey(window, GLFW_KEY_LEFT);
    int tilt_r = glfwGetKey(window, GLFW_KEY_RIGHT);
    int move = glfwGetKey(window, GLFW_KEY_W);
    int on = glfwGetKey(window, GLFW_KEY_TAB);
    int off = glfwGetKey(window, GLFW_KEY_O);
    int followcam = glfwGetKey(window, GLFW_KEY_1);
    int top = glfwGetKey(window, GLFW_KEY_2);
    int tower = glfwGetKey(window, GLFW_KEY_3);
    int plane = glfwGetKey(window, GLFW_KEY_4);
    int heli = glfwGetKey(window, GLFW_KEY_5);
    int loopball = glfwGetKey(window, GLFW_KEY_L);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    if (cam == 5)
        glfwSetScrollCallback(window, scroll_callback);
    
    if (up) {
        ball1.position.y += 0.05;
        if (ball1.position.y >= 10)
            ball1.position.y = 10;
        bar.size -= 0.0003;
    }
    if (down) {
        ball1.position.y -= 0.05;
        if (ball1.position.y <= -15)
            ball1.position.y = -15;
        bar.size -= 0.0003;
    }
    if (left) { 
        ball1.yaw += 0.5 + ball1.roll / 60;
    }
    if (right) {
        ball1.yaw -= 0.5 - ball1.roll / 60;
    }
    if (tilt_l) {
        ball1.roll += 0.5;
        if (ball1.roll >= 20)
            ball1.roll = 20;
    }
    if (tilt_r) {
        ball1.roll -= 0.5;
        if (ball1.roll <= -20)
            ball1.roll = -20;
    }
    if (move) {
        ball1.speed += 0.05;
        if (ball1.speed >= 4)
            ball1.speed = 4;
        played++;
        bar.size -= 0.0003;
    }
    if (!move) {
        ball1.speed -= 0.05;
        if (ball1.speed <= 0)
            ball1.speed = 0;
    }
    if (on) {
        dash_flag = 1;
    }
    if (off) {
        dash_flag = 0;
    }
    if (followcam) {
        cam = 1;
    }
    if (top) {
        cam = 2;   
    }
    if (tower) {
        cam = 3;
    }
    if (plane) {
        cam = 4;
    }
    if (heli) {
        cam = 5;
    }
    if (loopball && loop == 0) {
        loop = 1;
        startx = ball1.position.x;
        starty = ball1.position.y;
        startz = ball1.position.z;
        staryaw = ball1.yaw;
        ball1.position.x = ball1.position.y = ball1.position.z = ball1.yaw = 0;
        cam = 6;
    } 
}

void check_smoke_ring_deletion()
{
    ll i;
    for(i=0;i<smoke.size();i++)
    {
        if(abs(played - smoke[i].time) > 1000)
            smoke[i].flag = 1;
    }
}

void check_smoke_ring_collision()
{
    ll i;
    for(i=0;i<smoke.size();i++)
    {
        int plane_angle = ((int)ball1.yaw % 360 + 360) % 360;
        int check_rotation = smoke[i].rotation;
        if(plane_angle > 180) plane_angle -= 180;
        if(smoke[i].rotation > 180) check_rotation -= 180;
        if(abs(check_rotation - plane_angle) < 50)
        {
            int f1 = 0, f2 = 0, f3 = 0;
            if(abs(ball1.position.x - smoke[i].position.x) < 6)
                f1 = 1;
            if(abs(ball1.position.y - smoke[i].position.y) < 6)
                f2 = 1;
            if(abs(ball1.position.z - smoke[i].position.z) < 6)
                f3 = 1;
            if(f1 == 1 && f2 == 1 && f3 == 1)
            {
                if(smoke[i].flag == 0)
                    display.score += 50;
                smoke[i].flag = 1;
            }
        }
    }
}

void check_arrow_position()
{
    if(current_checkpoint == 0)
        arrow = Arrow(410, 1.5, 410, COLOR_DARKRED);
    else if(current_checkpoint == 1)
        arrow = Arrow(410, 1.5, -410, COLOR_DARKRED);
    else if(current_checkpoint == 2)
        arrow = Arrow(-410, 1.5, 410, COLOR_DARKRED);
    else
        arrow = Arrow(-410, 1.5, -410, COLOR_DARKRED);
    cout << "Go to checkpoint " << current_checkpoint + 1 << endl;
    cout << "---------------------" << endl; 
}

void check_arrow_size()
{
    float pos_x = arrow.position.x - ball1.position.x;
    float pos_z = arrow.position.z - ball1.position.z;
    float dist = sqrt(pos_x * pos_x + pos_z * pos_z);
    arrow.size = dist / 100 + 1;
    arrow.position.y = dist / 40 + 1.5;
}

void check_fuel_collision(bounding_box_t play)
{
    int i;
    for(i=0;i<fuel.size();i++)
    {
        bounding_box_t fuel_box;
        fuel_box.x = fuel[i].position.x + 2;
        fuel_box.y = fuel[i].position.y + 2.5;
        fuel_box.z = fuel[i].position.z - 0.5;
        fuel_box.height = 5.0;
        fuel_box.width = 4.0;
        fuel_box.depth = 1.0;
        if(detect_collision(fuel_box, play))
        {
            if(fuel[i].flag == 0)
                bar.size += 0.6;
            fuel[i].flag = 1;
        }
    }
}

void hit()
{
    display.lives -= 1;
    ball1.position.x = 0;
    ball1.position.y = 0;
    ball1.position.z = 0;
    ball1.yaw = 0;
    ball1.roll = 0;
    ball1.speed = 0;
    ball1.speedx = 0;
    ball1.speedz = 0;
    ball1.yaw = 0;
    bar.size = 2;
    bar.color = COLOR_ORANGE;
    cam = 1;
}

void check_parachute_plane_collision(bounding_box_t play)
{
    int i;
    for(i=0;i<paras.size();i++)
    {
        if (paras[i].flag == 0)
        {
            bounding_box_t para_box;
            para_box.x = paras[i].position.x;
            para_box.y = paras[i].position.y;
            para_box.z = paras[i].position.z;
            para_box.height = para_box.width = para_box.depth = 6;
            if(detect_collision(para_box, play))
            {
                cout << "Hit by a parachute" << endl;
                cout << "------------------" << endl;
                hit();
            }
        }
    }
}

void check_bullet_plane_collision(bounding_box_t play)
{
    int i;
    for(i=0;i<bullets.size();i++)
    {
        if (bullets[i].flag == 0)
        {
            bounding_box_t bullet_box;
            bullet_box.x = bullets[i].position.x;
            bullet_box.y = bullets[i].position.y + 2.25;
            bullet_box.z = bullets[i].position.z;
            bullet_box.height = 1.5;
            bullet_box.width = 4;
            bullet_box.depth = 4;
            if(detect_collision(bullet_box, play))
            {
                if(bullets[i].flag == 0)
                {
                    cout << "Hit by enemy bullets" << endl;
                    cout << "--------------------" << endl;
                    bar.size -= 0.5;
                }
                bullets[i].flag = 1;
            }
        }
    }
}

void check_plane_depth()
{
    if(ball1.position.y <= -15)
        hit();
}

void check_bomb_canon_collision()
{
    int i, j;
    int flagcheck = 0;
    for(i=0;i<enemies[current_checkpoint].size();i++)
    {
        for(j=0;j<bomb.size();j++)
        {
            if(enemies[current_checkpoint][i].flag == 0 && bomb[j].flag == 0)
            {
                bounding_box_t bomb_box, canon_box;
                bomb_box.depth = 0.5;
                bomb_box.height = 1.6;
                bomb_box.width = 1.6;
                bomb_box.x = bomb[j].position.x;
                bomb_box.y = bomb[j].position.y;
                bomb_box.z = bomb[j].position.z + 0.25;
                canon_box.depth = 4;
                canon_box.height = 3;
                canon_box.width = 4;
                canon_box.x = enemies[current_checkpoint][i].position.x;
                canon_box.y = enemies[current_checkpoint][i].position.y + 1.5;
                canon_box.z = enemies[current_checkpoint][i].position.z;
                if(detect_collision(canon_box, bomb_box))
                {
                    if(enemies[current_checkpoint][i].flag == 0)
                        display.score += 50;
                    enemies[current_checkpoint][i].flag = 1;
                    
                }
            }
        }
        if(enemies[current_checkpoint][i].flag == 0)
            flagcheck = 1;
    }
    if(flagcheck == 0)
    {
        current_checkpoint++;
        check_arrow_position();
    }
}

void check_missile_canon_collision()
{
    int i, j;
    int flagcheck = 0;
    for(i=0;i<enemies[current_checkpoint].size();i++)
    {
        for(j=0;j<missile.size();j++)
        {
            if(enemies[current_checkpoint][i].flag == 0 && missile[j].flag == 0)
            {
                bounding_box_t missile_box, canon_box;
                missile_box.depth = 4;
                missile_box.height = 1.6;
                missile_box.width = 1.6;
                missile_box.x = missile[j].position.x;
                missile_box.y = missile[j].position.y;
                missile_box.z = missile[j].position.z - 8;
                canon_box.depth = 4;
                canon_box.height = 3;
                canon_box.width = 4;
                canon_box.x = enemies[current_checkpoint][i].position.x;
                canon_box.y = enemies[current_checkpoint][i].position.y + 1.5;
                canon_box.z = enemies[current_checkpoint][i].position.z;
                if(detect_collision(canon_box, missile_box))
                {
                    if(enemies[current_checkpoint][i].flag == 0)
                        display.score += 50;
                    enemies[current_checkpoint][i].flag = 1;
                }
            }
        }
        if(enemies[current_checkpoint][i].flag == 0)
            flagcheck = 1;
    }
    if(flagcheck == 0)
    {
        current_checkpoint++;
        check_arrow_position();
    }
}

void check_parachute_missile_collision()
{
    int i, j;
    for(i=0;i<paras.size();i++)
    {
        for(j=0;j<missile.size();j++)
        {
            if(paras[i].flag == 0 && missile[j].flag == 0)
            {
                bounding_box_t missile_box, para_box;
                missile_box.depth = 4;
                missile_box.height = 1.6;
                missile_box.width = 1.6;
                missile_box.x = missile[j].position.x;
                missile_box.y = missile[j].position.y;
                missile_box.z = missile[j].position.z - 8;
                para_box.x = paras[i].position.x;
                para_box.y = paras[i].position.y;
                para_box.z = paras[i].position.z;
                para_box.height = para_box.width = para_box.depth = 6;
                if(detect_collision(para_box, missile_box))
                {
                    if(paras[i].flag == 0)
                        display.score += 100;
                    paras[i].flag = 1;
                }
            }
        }
    }
}

void check_parachute_bomb_collision()
{
    int i, j;
    for(i=0;i<paras.size();i++)
    {
        for(j=0;j<bomb.size();j++)
        {
            if(paras[i].flag == 0 && bomb[j].flag == 0)
            {
                bounding_box_t bomb_box, para_box;
                bomb_box.depth = 0.5;
                bomb_box.height = 1.6;
                bomb_box.width = 1.6;
                bomb_box.x = bomb[j].position.x;
                bomb_box.y = bomb[j].position.y;
                bomb_box.z = bomb[j].position.z + 0.25;
                para_box.x = paras[i].position.x;
                para_box.y = paras[i].position.y;
                para_box.z = paras[i].position.z;
                para_box.height = para_box.width = para_box.depth = 6;
                if(detect_collision(para_box, bomb_box))
                {
                    if(paras[i].flag == 0)
                        display.score += 100;
                    paras[i].flag = 1;
                }
            }
        }
    }
}

void check_volcano_distance()
{
    int i;
    if(ball1.position.y > 0)
        return;
    for(i=0;i<volc.size();i++)
    {
        double distx = volc[i].position.x - ball1.position.x;
        double distz = volc[i].position.z - ball1.position.z;
        double dist = sqrt(distx * distx + distz * distz);
        if(dist < 10)
            display.lives = 0;
    }
}

void tick_elements() {
    int i;

    if(loop == 1)
    {
        if(angle >= 360)
        {
            ball1.rotation1 = 0;
            ball1.position.x = startx;
            ball1.position.y = starty;
            ball1.position.z = startz;
            ball1.yaw = staryaw;
            angle = 0;
            loop = 0;
            cam = 1;
        }
        else
        {
            ball1.rotation1 = angle;
            angle += 2;
            ball1.position.y = -10 * (double)cos((M_PI * angle / 180.0f));
            ball1.position.z = -10 * (double)sin((M_PI * angle / 180.0f));
            ball1.position.x = 0;
        }
        return;
    }
    ball1.tick();
    arrow.tick();
    for(i=0;i<missile.size();i++)
    {
        if(missile[i].time == 100)
            missile[i].flag = 1;
        if(missile[i].flag == 0)
            missile[i].tick();
    }
    for(i=0;i<bomb.size();i++)
    {
        if(bomb[i].position.y <= -15)
            bomb[i].flag = 1;
        if(bomb[i].flag == 0)
            bomb[i].tick();
    }
    for(i=0;i<bullets.size();i++)
    {
        if(bullets[i].position.y >= 2)
            bullets[i].flag = 1;
        if(bullets[i].flag == 0)
            bullets[i].tick();
    }
    for(i=0;i<paras.size();i++)
    {
        if(paras[i].position.y <= -10)
            paras[i].flag = 1;
        if(paras[i].flag == 0)
            paras[i].tick();
    }
    for(i=0;i<fuel.size();i++)
    {
        if(fuel[i].flag == 0)
            fuel[i].tick();
    }
    int j;
    if(bullets.size() == 0 || played % 250 == 0)
    {
        for(j=0;j<enemies[current_checkpoint].size();j++)
        {
            if(enemies[current_checkpoint][j].flag == 0)
                bullets.pb(Bullet(enemies[current_checkpoint][j].position.x, -14.5, enemies[current_checkpoint][j].position.z, COLOR_DARKBLUE));
        }
        played++;
    }
    if(paras.size() == 0 || played % 150 == 0)
    {
        int rand_x = rand() % 800 - 400;
        int rand_z = rand() % 800 - 400;
        if(abs(ball1.position.x - rand_x) < 20 && abs(ball1.position.z - rand_z) < 20)
            rand_x += 50;
        paras.pb(Para(rand_x, 15, rand_z, COLOR_GREEN));
        played++;
    }
    if(played % 100 == 0)
    {
        int randval = rand() % 600 - 300;
        int randval2 = rand() % 600 - 300;
        smoke.pb(Smoke(randval, randval2, COLOR_GREY));
        smoke.back().time = played;
        played++;
    }
    if(bar.size <= 0)
        hit();

    bounding_box_t play;
    play.x = ball1.position.x - 5 * (double)sin((M_PI * ball1.yaw / 180.0f));
    play.y = ball1.position.y;
    play.z = ball1.position.z - 5 * (double)cos((M_PI * ball1.yaw / 180.0f));
    play.height = 1.6;
    play.width = 1.6;
    play.depth = 10;

    check_smoke_ring_deletion();

    check_smoke_ring_collision();

    check_arrow_size();    

    check_fuel_collision(play);

    check_parachute_plane_collision(play);

    check_bullet_plane_collision(play);

    check_plane_depth();

    check_bomb_canon_collision();

    check_missile_canon_collision();

    check_parachute_missile_collision();

    check_parachute_bomb_collision();

    check_volcano_distance();

    view_x = ball1.position.x;
    view_z = ball1.position.z;
    speed.rotation = -ball1.speed * 360 / 4;
    alt.rotation = -(ball1.position.y + 15) * 360 / 25;
    comp.rotation = -ball1.yaw;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(0, 0, 0, COLOR_RED);
    platform = Platform(0, 0, COLOR_LIGHTBLUE);
    speed = Speed(-3.6, -1.4, COLOR_GREEN);
    alt = Altitude(-2.8, -1.4, COLOR_ORANGE);
    arrow = Arrow(410, 1.5, 410, COLOR_DARKRED);
    dash = Dash(-4, -4, COLOR_DARK);
    bar = Bar(-3.8, -2.2, COLOR_ORANGE);
    display = Seven(-6.5, -8, COLOR_WHITE);
    comp = Comp(-3.2, -3.1, COLOR_WHITE);

    vector<Canon> topright;
    topright.pb(Canon(400, -14.5, 400, COLOR_GREY));
    topright.pb(Canon(420, -14.5, 400, COLOR_GREY));
    topright.pb(Canon(400, -14.5, 420, COLOR_GREY));
    vector<Canon> bottomright;
    bottomright.pb(Canon(400, -14.5, -400, COLOR_GREY));
    bottomright.pb(Canon(420, -14.5, -400, COLOR_GREY));
    bottomright.pb(Canon(400, -14.5, -420, COLOR_GREY));
    vector<Canon> topleft;
    topleft.pb(Canon(-400, -14.5, 400, COLOR_GREY));
    topleft.pb(Canon(-420, -14.5, 400, COLOR_GREY));
    topleft.pb(Canon(-400, -14.5, 420, COLOR_GREY));
    vector<Canon> bottomleft;
    bottomleft.pb(Canon(-400, -14.5, -400, COLOR_GREY));
    bottomleft.pb(Canon(-420, -14.5, -400, COLOR_GREY));
    bottomleft.pb(Canon(-400, -14.5, -420, COLOR_GREY));
    enemies.pb(topright);
    enemies.pb(bottomright);
    enemies.pb(topleft);
    enemies.pb(bottomleft);

    int i, j;
    for(i=-350;i<350;i+=10)
    {
        int rand_z = (rand() % 800) - 400;
        island.pb(Island(i, rand_z, COLOR_GOLDENROD));
    }
    for(i=300,j=300;i>100,j>100;i-=50,j-=50)
        volc.pb(Volcano(i, -14.5, j, COLOR_LIGHTRED));
    for(i=300,j=-300;i>100,j<-100;i-=50,j+=50)
        volc.pb(Volcano(i, -14.5, j, COLOR_LIGHTRED));
    for(i=-300,j=300;i<-100,j>100;i+=50,j-=50)
        volc.pb(Volcano(i, -14.5, j, COLOR_LIGHTRED));
    for(i=-300,j=-300;i<-100,j<-100;i+=50,j+=50)
        volc.pb(Volcano(i, -14.5, j, COLOR_LIGHTRED));
    
    for(i=600;i>=-600;i-=200)
    {
        for(j=600;j>=-600;j-=200)
        {
            if(abs(i) != abs(j))
                fuel.pb(Fuel(i, 0, j, COLOR_GOLDENROD));    
        }
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices2.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    cout << "Jet Fighter Plane Game" << endl;
    cout << "----------------------" << endl;
    check_arrow_position();

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        
        if(current_checkpoint >= 4)
        {
            cout << "YOU WON" << endl;
            cout << "YOUR SCORE: " << display.score << endl;
            cout << "---------------" << endl;
            break;
        }
        if(display.lives <= 0)
        {
            cout << "YOU LOST" << endl;
            cout << "--------" << endl;
            break;
        }
        // Process timers
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.depth + b.depth));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(50.0*3.1459/180.0, 1.0, 0.1, 1000.0);
    Matrices2.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
