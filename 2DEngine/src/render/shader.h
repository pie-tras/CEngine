#pragma once

struct shader {
    unsigned int programID;
    unsigned int vertexShaderID;
    unsigned int fragmentShaderID;
};

void createShader(char* key, struct shader* shader);

void startShader(struct shader* shader);

void stopShader();

void cleanShader(struct shader* shader);