#include "global.h"
#include "render/texture.h"
#include "textureReader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct texture* loadTexture(const char* path) {
	unsigned int texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		printf("Failed to load texture!\n");
		return NULL;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	
	struct texture* loaded = malloc(sizeof(*loaded));
	if (!loaded) {
		printf("Failed to load texture!\n");
		return NULL;
	}

	loaded->width = width;
	loaded->height = height;
	loaded->texID = texID;

	stbi_image_free(data);

	return loaded;
}

void cleanTexture(struct texture* t) {
	free(t);
}