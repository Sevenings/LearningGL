#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow*);
void clearBackground(float*);

int main() {
    glfwInit();
    // Seleciona a versão do opengl
    // No caso, eu baixei o GLAD 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Essa linha é requerida par usuários MACOS
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Cria uma GLFWwindow
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Window! :)", NULL, NULL);
    // Verifica se a janela foi criada corretamente
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Coloca o nosso contexto nessa window
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    // Viewport pelo visto controla... de quais pixels mostrar na tela. Algo assim :) 
    glViewport(0, 0, 800, 600);

    // Função que é chamada quando redimensionar a tela.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float bg_color[] = {0.3f, 0.2f, 0.4f, 1.0f};
    float speed = 0.1f;

    // render loop
    while(!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        // rendering commands here
        /*
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        */
        bg_color[2] += speed;
        if (bg_color[2] > 1.0) {
            speed = -speed;
            bg_color[2] = 1.0;
        } else if(bg_color[2] < -1.0) {
            speed = -speed;
            bg_color[2] = -1.0;
        }
        clearBackground(bg_color);

        // check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();

    return 0;
}


void clearBackground(float* color) {
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    printf("Resized to (%d, %d)", width, height);
}
