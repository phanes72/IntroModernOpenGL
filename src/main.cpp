// Lesson1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"


const char* APP_TITLE = "Introduction to Modern OpenGL - Hello Triangle";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
GLFWwindow* gWindow = NULL;

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void showFPS(GLFWwindow* window);
bool initOpenGL();

int main()
{
    if (!initOpenGL()) {
        std::cerr << "GLFW initialization failed" << std::endl;
        return -1;
    }

    //Main Loop
    while (!glfwWindowShouldClose(gWindow)) {
        showFPS(gWindow);

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(gWindow);

    }

    glfwTerminate();
    return 0;
}

bool initOpenGL() {
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    
    gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
   
    if (gWindow == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }


    glfwMakeContextCurrent(gWindow);

    glfwSetKeyCallback(gWindow, glfw_onKey);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed" << std::endl;
        return false;
    }

    glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

    return true;
}

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void showFPS(GLFWwindow* window) {
    static double previousSeconds = 0.0;
    static int frameCount = 0;
    double elapsedSeconds;
    double currentSeconds = glfwGetTime();  // returns of seconds since GLFW sarted, as double

    elapsedSeconds = currentSeconds - previousSeconds;

    // limit text update 4 times per second
    if (elapsedSeconds > 0.25) {
        previousSeconds = currentSeconds;
        double fps = (double)frameCount / elapsedSeconds;
        double msPerFrame = 1000.0 / fps;

        std::ostringstream outs;
        outs.precision(3);
        outs << std::fixed
            << APP_TITLE << " "
            << "FPS: " << fps << " "
            << "Frame Time: " << msPerFrame << " (ms)";
        glfwSetWindowTitle(window, outs.str().c_str());

        frameCount = 0;

    }

    frameCount++;
}