// =====================
// Texturas encapsuladas
// =====================


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <stdio.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow*, double, double);
void processInput(GLFWwindow *window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
unsigned int SCR_WIDTH = 1000;
unsigned int SCR_HEIGHT = 600;

const float camSpeed = 0.1f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);  
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 projection = glm::mat4(1.0f);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float phi = glm::radians(90.f);   // 0 até 180
float theta = glm::radians(-90.f);  // 0 até 360
float mouseLastX = SCR_WIDTH/2, mouseLastY = SCR_HEIGHT/2;
bool firstTimeMouseInput = true;
float fov = 45.f;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);  
    glfwSetScrollCallback(window, scroll_callback); 
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);  

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("vertexShader.glsl", "fragShader.glsl"); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

    Texture boxTex("container.jpg");
    Texture headTex("lukashead.png");

    boxTex.bindToUnit(GL_TEXTURE0);
    headTex.bindToUnit(GL_TEXTURE1);

    // Load Shaders uniforms
    ourShader.use();
    ourShader.setInt("boxTex", boxTex.unit);
    ourShader.setInt("headTex", headTex.unit);
    ourShader.set2Float("box_size", boxTex.width, boxTex.height);
    

    // Posições dos cubos
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    // Transformações

    projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(fov), float(SCR_WIDTH)/float(SCR_HEIGHT), 0.1f, 100.0f);

    
    // Camera Inicial
    cameraFront = glm::vec3(0, 0, -1);
    cameraUp = glm::vec3(0, 1, 0);

    // render loop
    // -----------

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        deltaTime = glfwGetTime() - lastFrame;    
        lastFrame = glfwGetTime();
        
        // theta += 1 * deltaTime;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        ourShader.set2Float("screenSize", SCR_WIDTH, SCR_HEIGHT); 
        ourShader.setFloat("time", glfwGetTime());


        // View Matriz

        glm::mat4 view = glm::mat4(1.0f);

        cameraFront.x = sin(phi)*cos(theta);
        cameraFront.z = sin(phi)*sin(theta);
        cameraFront.y = cos(phi);
        cameraFront = glm::normalize(cameraFront);

        view = glm::lookAt(cameraPos, 
                           cameraPos + cameraFront,
                           cameraUp);


        float amplitude = 1.0f;
        glm::vec3 global_move = glm::vec3(0.0, amplitude * sin(glfwGetTime()), 0.0);


        for (int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);

            model = glm::translate(model, global_move);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, float(glfwGetTime() + 5*i) * glm::radians(40.0f), glm::vec3(0.5f, 1.0f, 0.0f));  

            int modelLoc = glGetUniformLocation(ourShader.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            int viewLoc = glGetUniformLocation(ourShader.ID, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

            int projLoc = glGetUniformLocation(ourShader.ID, "projection");
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

            ourShader.use();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    float camSpeed = 2.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
        cameraPos += cameraFront * camSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
        cameraPos += -glm::normalize(glm::cross(cameraFront, cameraUp))  * camSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        cameraPos += -cameraFront * camSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * camSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
        cameraPos += glm::vec3(0, -1, 0) * camSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
        cameraPos += glm::vec3(0, 1, 0) * camSpeed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstTimeMouseInput) {
        mouseLastX = xpos;
        mouseLastY = ypos;
        firstTimeMouseInput = false;
    }
    float xoffset = xpos - mouseLastX;
    float yoffset = ypos - mouseLastY; // reversed since y-coordinates range from bottom to top
    mouseLastX = xpos;
    mouseLastY = ypos;

    const float sensitivity = 0.01f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    theta += xoffset;
    phi += yoffset;

    if (phi < 0.01f) {
        phi = 0.01f;
    } else if (phi > glm::radians(179.9f)) {
        phi = glm::radians(179.9f);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    fov += (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f; 
    projection = glm::perspective(glm::radians(fov), float(SCR_WIDTH)/float(SCR_HEIGHT), 0.1f, 100.0f);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(fov), float(SCR_WIDTH)/float(SCR_HEIGHT), 0.1f, 100.0f);
}

