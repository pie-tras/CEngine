#include "global.h"
#include "fileReader.h"

struct loaded_file* readFile(const char* path) {
    FILE* fp;
    long size;
    char* buffer;

    fp = fopen(path, "rb");

    if (!fp) {
        printf("Could not load file at path: %s", path);
        return NULL;
    }

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    buffer = calloc(1, size + 1);
    if (!buffer) {
        fclose(fp);
        printf("Memory alloc failed.");
        return NULL;
    }

    if (1 != fread(buffer, size, 1, fp)) {
        fclose(fp);
        free(buffer);
        printf("Copy to buffer failed");
    }

    fclose(fp);

    struct loaded_file* loaded = malloc(sizeof(*loaded));
    if (!loaded) {
        free(buffer);
        printf("File struct alloc failed");
        return NULL;
    }

    loaded->content = calloc(1, size + 1);
    if (!loaded->content) {
        free(buffer);
        printf("File struct content alloc failed");
        return NULL;
    }
    strcpy(loaded->content, buffer);
    loaded->size = size;

    free(buffer);

    return loaded;
}

void cleanLoadedFile(struct loaded_file* loaded) {
    free(loaded->content);
    free(loaded);
}