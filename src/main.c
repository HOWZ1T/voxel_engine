#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void glfwErrorCallback(int code, const char* msg) {
    fprintf(stderr, "GLFW Error [%d]: %s\n", code, msg);
}

int main()
{
    glfwInit();
    glfwSetErrorCallback(glfwErrorCallback);

    // glfw initialize and configure
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // set this window hint if on macOS
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // create window
    GLFWwindow* window;
    window = glfwCreateWindow(960, 540, "Voxel Engine", NULL, NULL);
    if (window == NULL) {
        fprintf( stderr, "failed to create glfw window\n" );
        glfwTerminate();
        return -1;
    }

    // set the open gl context to the window
    glfwMakeContextCurrent(window);
    glewExperimental=GL_TRUE;

    // initialize glew
    const GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "failed to initialize GLEW [%d]: %s\n", res, glewGetErrorString(res));
        return -1;
    }

    fprintf(stdout, "status: using GLEW %s\n", glewGetString(GLEW_VERSION));

    // ensure the escape key being pressed can be captured
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
        // clear screen
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

        // swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}