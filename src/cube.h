// cube.h

#ifndef TMODEL_DEFINED
#define TMODEL_DEFINED

typedef struct
{
  const float (*verts)[3];
  const uint16_t (*edges)[2];
  const uint16_t (*faces)[4];
  const float (*normals)[3];
  const uint16_t *colors;
  const uint8_t *faceColorIDs;
  uint16_t numVerts;
  uint16_t numEdges;
  uint16_t numFaces;
} tModel;

#endif

#include <stdint.h>
// cube Verts
static const float cubeVerts[8][3] = {
    { 1.000000, 1.000000, 1.000000 },
    { 1.000000, 1.000000, -1.000000 },
    { 1.000000, -1.000000, 1.000000 },
    { 1.000000, -1.000000, -1.000000 },
    { -1.000000, 1.000000, 1.000000 },
    { -1.000000, 1.000000, -1.000000 },
    { -1.000000, -1.000000, 1.000000 },
    { -1.000000, -1.000000, -1.000000 },
};

// cube Edges
const uint16_t cubeEdges[12][2] = {
    {5, 7},
    {1, 5},
    {0, 1},
    {7, 6},
    {2, 3},
    {4, 5},
    {2, 6},
    {0, 2},
    {7, 3},
    {6, 4},
    {4, 0},
    {3, 1},
};

// cube Faces
const uint16_t cubeFaces[6][4] = {
    {7, 5, 1, 3},
    {2, 0, 4, 6},
    {7, 3, 2, 6},
    {3, 1, 0, 2},
    {5, 7, 6, 4},
    {1, 5, 4, 0},
};

// cube Normals
const float cubeNormals[6][3] = {
    { -0.000000, 0.000000, -1.000000 },
    { -0.000000, 0.000000, 1.000000 },
    { 0.000000, -1.000000, -0.000000 },
    { 1.000000, 0.000000, 0.000000 },
    { -1.000000, 0.000000, -0.000000 },
    { 0.000000, 1.000000, 0.000000 },
};

// Farben für jede Material-Slot (RGB565 aus BaseColor)
const uint16_t cubeColors[6] = {
    0x001F, // BLUE
    0x07E0, // GREEN
    0xF800, // RED
    0xFFE0, // YELLOW
    0xF81F, // PINK
    0x07FF, // CYAN
};

// cube Face Material IDs
const uint8_t cubeFaceColors[6] = {
    5,
    0,
    3,
    2,
    4,
    1,
};

const tModel m_cube = {
    cubeVerts,
    cubeEdges,
    cubeFaces,
    cubeNormals,
    cubeColors,
    cubeFaceColors,
    8, 12, 6
};

// EOF
