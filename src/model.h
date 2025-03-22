#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    Vec3 norm;
    Vec3 p1;
    Vec3 p2;
    Vec3 p3;
    uint16_t attrib;
} Tri;
#pragma pack(pop)

typedef struct {
    uint32_t n;
    Tri* data;
} Model;

void Vec3_display(Vec3 const* vec);
void Vec3_negate(Vec3* vec);

void Tri_display(Tri const* tri);

void Model_init(Model* model, uint32_t n, FILE* f);
void Model_deinit(Model* model);
Vec3 Model_center(Model const* model);
void Model_translate(Model const* model, float dx, float dy, float dz);
void Model_normalize(Model* model);
void Model_display(Model const* model);
