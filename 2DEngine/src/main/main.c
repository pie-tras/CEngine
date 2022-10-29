#include <stdio.h>
#include <time.h>

#include "global.h"
#include "main/window.h"
#include "util/fileReader.h"
#include "util/textureReader.h"
#include "render/shader.h"
#include "render/render.h"
#include "render/positional.h"
#include "render/texture.h"

int main(void) {

    GLFWwindow* window = createWindow(800, 600, "Test");

    unsigned int QUAD_VAO = loadModel();
    glBindVertexArray(QUAD_VAO);

    struct shader* quad_shader = malloc(sizeof(*quad_shader));
    createShader("quad", quad_shader);
    startShader(quad_shader);
   
    struct texture* sheep = loadTexture("res/texture/sheep.png");
    struct texture* tile = loadTexture("res/texture/tiles.png");

    struct positional* pos = malloc(sizeof(*pos));
    pos->width = 64;
    pos->height = 64;
    pos->x = 0;
    pos->y = 0;

    struct positional* pos2 = malloc(sizeof(*pos2));
    pos2->width = 64;
    pos2->height = 64;
    pos2->x = 64;
    pos2->y = 64;

    double fps = glfwGetTime();
    int frame_count = 0;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        renderTile(tile, 2, 0, 0, pos2, quad_shader);
        renderTexture(sheep, pos, quad_shader);

        glfwSwapBuffers(window);
        glfwPollEvents();

        double current = glfwGetTime();

        if (current - fps > 1) {
            printf("FPS: %d\n", frame_count);
            fps = glfwGetTime();
            frame_count = 0;
        }

        frame_count++;
    }
    
    cleanTexture(sheep);

    cleanShader(quad_shader);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}