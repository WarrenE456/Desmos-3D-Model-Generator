#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "prelude.h"
#include "file_header.h"
#include "tri.h"

int main() {
    FILE* f = fopen("cube.stl", "rb");
    if (!f) {
        fprintf(stderr, "Failed to open file.\n");
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

    Vec3 center = Model_center(model);
    Vec3_negate(&center);

    Model_translate(&model, center.x, center.y, center.z);
    Model_normalize(&model);

    printf("%s", PRELUDE);

    for (uint32_t i = 0; i < head.n; ++i) {
        Tri_display(&model.data[i]);
    }

    Model_deinit(&model);
    fclose(f);

    return 0;
}

