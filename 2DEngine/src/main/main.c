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
#include "util/timer.h"

void tick(struct stopwatchData* fps, int* frame_count) {

    stopwatch(fps);
    if (fps->elapsed > 1) {
        printf("FPS: %d, Elapsed: %f\n", *frame_count, fps->elapsed);
        clearStopwatch(fps);
        *frame_count = 0;
    }

    (*frame_count)++;
}

void render() {
}

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int frame_count = 0;
    struct stopwatchData* fps = malloc(sizeof(*fps));
    struct stopwatchData* sd = malloc(sizeof(*sd));
    clearStopwatch(fps);
    clearStopwatch(sd);

    while (!glfwWindowShouldClose(window)) {
        stopwatch(sd);
        if (sd->elapsed > 0.016) {
            tick(fps, &frame_count);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

            render();
            renderTile(tile, 2, 0, 0, pos2, quad_shader);
            renderTexture(sheep, pos, quad_shader);

            glfwSwapBuffers(window);
            glfwPollEvents();

            clearStopwatch(sd);
        }
    }
    
    cleanTexture(sheep);

    cleanShader(quad_shader);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}