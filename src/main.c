#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

const char* PRELUDE =
    "d_{ist}=3\n"
    "\\theta_{0}=0\n"
    "\\phi_{0}=1.57\n"
    "p_{roj}\\left(p\\right)=\\left\\{p.z+d_{ist}>0:\\left(\\frac{p.x}{p.z+d_{ist}},\\frac{p.y}{p.z+d_{ist}}\\right)\\right\\}\n"
    "r_{otX}\\left(p,\\theta\\right)=\\left(p.x,p.y\\cos\\theta-p.z\\sin\\theta,p.y\\sin\\theta+p.z\\cos\\theta\\right)\n"
    "r_{otY}\\left(p,\\theta\\right)=\\left(p.x\\cos\\theta+p.z\\sin\\theta,p.y,p.z\\cos\\theta-p.x\\sin\\theta\\right)\n"
    "t\\left(p\\right)=p_{roj}\\left(r_{otX}\\left(r_{otY}\\left(p,-\\phi_{0}\\right),-\\theta_{0}\\right)\\right)\n"
;

#pragma pack(push, 1)
typedef struct {
    uint8_t head[80];
    uint32_t n;
} Header;

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

void Vec3_display(Vec3* vec) {
    printf("t((%.4f,%.4f,%.4f))", vec->x, vec->y, vec->z);
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

    printf("Triangles: %u\n", head.n);

    Tri* tri = (Tri*)malloc(sizeof(Tri) * head.n);
    if (!tri) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(f);
        return 1;
    }

    for (uint32_t i = 0; i < head.n; ++i) {
        if (fread(&tri[i], sizeof(Tri), 1, f) != 1) {
            fprintf(stderr, "Failed to read triangle %u\n", i);
            free(tri);
            fclose(f);
            return 1;
        }
    }

    printf("%s", PRELUDE);

    for (uint32_t i = 0; i < head.n; ++i) {
        Tri_display(&tri[i]);
    }

    free(tri);
    fclose(f);

    return 0;
}

