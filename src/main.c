#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "prelude.h"
#include "file_header.h"
#include "model.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: dtmg some/model.stl\n");
    }

    char* filepath = argv[1];
    FILE* f = fopen(filepath, "rb");
    if (!f) {
        fprintf(stderr, "Failed to open file '%s'.\n", filepath);
        return 1;
    }

    Header head;
    if (fread(&head, sizeof(Header), 1, f) != 1) {
        fprintf(stderr, "Failed to read header.\n");
        fclose(f);
        return 1;
    }

    Model model;
    Model_init(&model, head.n, f);

    Vec3 center = Model_center(&model);
    Vec3_negate(&center);

    Model_translate(&model, center.x, center.y, center.z);
    Model_normalize(&model);

    printf("%s", PRELUDE);

    Model_display(&model);

    Model_deinit(&model);
    fclose(f);

    return 0;
}
