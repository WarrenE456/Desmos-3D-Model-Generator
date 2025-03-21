#include <stdio.h>

#include "tri.h"

void Vec3_display(Vec3* vec) {
    printf("t((%.4f,%.4f,%.4f))", vec->x, vec->y, vec->z);
}

void Vec3_negate(Vec3* vec) {
    vec->x *= -1.0f;
    vec->y *= -1.0f;
    vec->z *= -1.0f;
}

void Tri_display(Tri* tri) {
    printf("polygon(");
    Vec3_display(&tri->p1);
    printf(",");
    Vec3_display(&tri->p2);
    printf(",");
    Vec3_display(&tri->p3);
    printf(")\n");
}

void Model_init(Model* model, uint32_t n, FILE* f) {
    model->n = n;
    model->data = (Tri*)malloc(sizeof(Tri) * n);
    if (!model->data) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(f);
        exit(1);
    }

    for (uint32_t i = 0; i < n; ++i) {
        if (fread(model->data + i, sizeof(Tri), 1, f) != 1) {
            fprintf(stderr, "Failed to read triangle %u\n.", i);
            free(model->data);
            fclose(f);
            exit(1);
        }
    }
}

void Model_deinit(Model* model) {
    free(model->data);
}

Vec3 Model_center(Model model) {
    float sum_x = 0, sum_y = 0,sum_z = 0;
    for (uint32_t i = 0; i < model.n; ++i) {
        sum_x += model.data[i].p1.x;
        sum_y += model.data[i].p1.y;
        sum_z += model.data[i].p1.z;

        sum_x += model.data[i].p2.x;
        sum_y += model.data[i].p2.y;
        sum_z += model.data[i].p2.z;

        sum_x += model.data[i].p3.x;
        sum_y += model.data[i].p3.y;
        sum_z += model.data[i].p3.z;
    }
    uint32_t n = model.n * 3;
    Vec3 center = { .x = sum_x / n, .y = sum_y / n, .z = sum_z / n};
    return center;
}

void Model_translate(Model* model, float dx, float dy, float dz) {
    for (uint32_t i = 0; i < model->n; ++i) {
        model->data[i].p1.x += dx;
        model->data[i].p1.y += dy;
        model->data[i].p1.z += dz;

        model->data[i].p2.x += dx;
        model->data[i].p2.y += dy;
        model->data[i].p2.z += dz;

        model->data[i].p3.x += dx;
        model->data[i].p3.y += dy;
        model->data[i].p3.z += dz;
    }
}

static float max(float a, float b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

static float min(float a, float b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

void Model_normalize(Model* model) {
    float   x_min = 0, x_max = 0,
            y_min = 0, y_max = 0,
            z_min = 0, z_max = 0;

    for (uint32_t i = 0; i < model->n; ++i) {
        x_min = min(model->data[i].p1.x, x_min);
        y_min = min(model->data[i].p1.y, y_min);
        z_min = min(model->data[i].p1.z, z_min);

        x_min = min(model->data[i].p2.x, x_min);
        y_min = min(model->data[i].p2.y, y_min);
        z_min = min(model->data[i].p2.z, z_min);

        x_min = min(model->data[i].p3.x, x_min);
        y_min = min(model->data[i].p3.y, y_min);
        z_min = min(model->data[i].p3.z, z_min);

        x_max = max(model->data[i].p1.x, x_max);
        y_max = max(model->data[i].p1.y, y_max);
        z_max = max(model->data[i].p1.z, z_max);

        x_max = max(model->data[i].p2.x, x_max);
        y_max = max(model->data[i].p2.y, y_max);
        z_max = max(model->data[i].p2.z, z_max);

        x_max = max(model->data[i].p3.x, x_max);
        y_max = max(model->data[i].p3.y, y_max);
        z_max = max(model->data[i].p3.z, z_max);
    }

    float x_range = x_max - x_min, y_range = y_max - y_min, z_range = z_max - z_min;
    float scale_factor = 2.0f / max(max(x_range, y_range), z_range);

    for (uint32_t i = 0; i < model->n; ++i) {
        model->data[i].p1.x *= scale_factor;
        model->data[i].p1.y *= scale_factor;
        model->data[i].p1.z *= scale_factor;

        model->data[i].p2.x *= scale_factor;
        model->data[i].p2.y *= scale_factor;
        model->data[i].p2.z *= scale_factor;

        model->data[i].p3.x *= scale_factor;
        model->data[i].p3.y *= scale_factor;
        model->data[i].p3.z *= scale_factor;
    }
}
