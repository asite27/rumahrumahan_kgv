#include <glfw3.h>
#include <stdlib.h>]
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "rain.h"
#include "kincir.h"

int biru[3] = { 15, 12, 26 };
int kaca[3] = { 168,163,160 };
int kayu[3] = { 36,12,3 };

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void setup_view(GLFWwindow* window) {
    //float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    //ratio = width / (float) height;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 50, 50, 0, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void bg() {
    glBegin(GL_POLYGON); //Sky
    glColor3f(0.4f, 0.5f, 1.0f);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glColor3f(0.7, 0.7, 1.0);
    glVertex2f(1, -.1);
    glVertex2f(-1, -.1);
    glEnd();
}


void persegi(float a, float b, float c, float d, int x[]) {
    glBegin(GL_POLYGON);
    glColor3ub(x[0], x[1], x[2]);
    glVertex2f(a, c);
    glVertex2f(a, d);
    glVertex2f(b, d);
    glVertex2f(b, c);
    glEnd();
}

void lingkar(float xpos, float ypos, float x, float y, int warna[])
{
    int N = 50;
    float pX, pY;
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_POLYGON);
    glColor4ub(warna[0], warna[1], warna[2], warna[3]);
    for (int i = 0; i < N; i++)
    {
        pX = xpos + sin(i * 2 * 3.14 / N);
        pY = ypos + cos(i * 2 * 3.14 / N);
        glVertex2f(pX * x, pY * y);
    }
    glEnd();
}

//Tanah Bawah
void tanah() {
    int x[3] = { 153, 102, 51 };
    persegi(0.f, 50.f, 50.f, 40.f, x);
}


void kinciran() {
    persegi(44.8f, 45.2f, 40.f, 34.8f, kayu);
    glTranslated(45, 35, 0);
    callkincir();
    glTranslated(-45, -35, 0);
}

//MEMANGGIL Class
void display() {
    bg();
    tanah();
    kinciran();
    glTranslated(-43, 0, 0);
    kinciran();
    glTranslated(43, 0, 0);
    init();
    Hujan();
}

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "C-Coons || Kincir Hujan", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    while (!glfwWindowShouldClose(window))
    {
        setup_view(window);

        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
