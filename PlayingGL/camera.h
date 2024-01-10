#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    
    float phi;   // 0 até 180
    float theta;  // 0 até 360
    float fov = 45.f;
    float aspect;

    glm::mat4 view;
    glm::mat4 projection;


    Camera(float px, float py, float pz, float theta_o, float phi_o, float screen_aspect) {
        // Instantiate pos
        pos = glm::vec3(px, py, pz);
        // Instantiate front
        setFront(theta_o, phi_o);
        // Instantiate up (up for default)
        up = glm::vec3(0.f, 1.f, 0.f);
        // Instantiate Aspect
        aspect = screen_aspect;


        // Instantiate the view matrix
        updateViewMatrix();
    }


    glm::mat4 getViewMatrix() {
        return view;
    }

    glm::mat4 getProjectionMatrix() {
        return projection;
    }


    void setPos(float x, float y, float z) {
        pos.x = x;
        pos.y = y;
        pos.z = z;
        updateViewMatrix();
    }

    void translate(float dx, float dy, float dz) {
        setPos(pos.x + dx, pos.y + dy, pos.z + dz);
    }

    void setAngle(float t, float p) {
        theta = t;
        phi = p;
        updateFront();
        updateViewMatrix();
    }

    void rotate(float dt, float dp) {
        setAngle(theta + dt, phi + dp); 
    }

    void setFov(float f) {
        fov = f;
    }


private:
    void updateViewMatrix() {
        view = glm::mat4(1.0f);
        view = glm::lookAt(pos, pos + front, up);
    }

    void updateProjectionMatrix() {
        projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
    }

    void updateFront() {
        setFront(theta, phi);
    }

    void setFront(float t, float p) {
        front.x = sin(p)*cos(t);
        front.z = sin(p)*sin(t);
        front.y = cos(p);
        front = glm::normalize(front);
    }

}

#endif
