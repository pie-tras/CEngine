#pragma once

unsigned int loadModel();
void renderTile(struct texture* t, int tileSize, int x, int y, struct positional* p, struct shader* shader);
void renderTexture(struct texture* t, struct positional* p, struct shader* shader);