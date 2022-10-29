#include "global.h"
#include "texture.h"
#include "positional.h"
#include "shader.h"

unsigned int loadModel() {
    float quad[8] = { -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), quad, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vao;
}

void loadUniforms(vec3 position, vec3 scale, vec3 cameraPos, struct shader* shader, int texture_type, int tileSize, int tileLoc_x, int tileLoc_y) {
    mat4 projection;
    mat4 model;
    mat4 view;
    glm_mat4_identity(projection);
    glm_mat4_identity(model);
    glm_mat4_identity(view);

    glm_ortho(-800.0f/2, 800.0f/2, -600.0f/2, 600.0f/2, -1.0f, 1.0f, projection);
    glm_translate(model, position);
    glm_scale(model, scale);

    glm_translate(view, cameraPos);

    mat4 mvp;
    glm_mat4_mulN((mat4 * []) { &projection, & view, & model }, 3, mvp);

    unsigned int mvp_location = glGetUniformLocation(shader->programID, "u_mvp");
    unsigned int tex_type_location = glGetUniformLocation(shader->programID, "texture_type");
    unsigned int tileSize_location = glGetUniformLocation(shader->programID, "tileSize");
    unsigned int tileLoc_location = glGetUniformLocation(shader->programID, "tileLoc");

    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, mvp[0]);
    glUniform1i(tex_type_location, texture_type);
    glUniform1i(tileSize_location, tileSize);
    glUniform2i(tileLoc_location, tileLoc_x, tileLoc_y);

}

void renderTile(struct texture* t, int tileSize, int x, int y, struct positional* p, struct shader* shader) {
    vec3 pos = { p->x, p->y, 0 };
    vec3 scale = { p->width, p->height, 0 };
    vec3 camera = { 0, 0, 0 };

    loadUniforms(pos, scale, camera, shader, 1, tileSize, x, y);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, t->texID);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void renderTexture(struct texture* t, struct positional* p, struct shader* shader) {
    vec3 pos = { p->x, p->y, 0};
    vec3 scale = { p->width, p->height, 0};
    vec3 camera = { 0, 0, 0 };

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, t->texID);
    loadUniforms(pos, scale, camera, shader, 0, 0, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}