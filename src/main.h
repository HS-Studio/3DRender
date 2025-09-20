#ifndef MAIN_H
#define MAIN_H

#pragma once

#define BUTTON_PIN 0

#include <set>
#include <utility> // std::pair

#include <Arduino.h>
#include <SPI.h>
// #include <SD.h>
#include "LGFX_SPI_ILI9341.h"

// 3D-Objects
#include "models\cube.h"
#include "models\n64.h"
#include "models\ball.h"
#include "models\cone.h"

#define CANV_W 160
#define CANV_H 160

uint16_t canvYoffset = 240 / 2 - CANV_H / 2;

uint8_t mode = 0;

//float angleX = -1.57, angleY = 0, angleZ = 0;
//float rotX = 0.01, rotY = 0.03, rotZ = 0;

bool showFps = true;
unsigned long fpsMillis = 0;
uint16_t fpsCounter = 0;
uint16_t fps = 0;
unsigned long currentMillis;

extern LGFX tft;
extern LGFX_Sprite canvasL;
extern LGFX_Sprite canvasR;
extern LGFX_Sprite fpsCanvas;

uint16_t bgColor = TFT_BLACK;
uint16_t lastbgColor = bgColor;

struct Face
{
    uint8_t indices[4];
    float faceCenter[3];
    float normalDir;
    float avgDepth;
    uint8_t colorID; // Farbe speichern
};

struct _3DObject
{
    float x;
    float y;
    float z;
    float rotX;
    float rotY;
    float rotZ;
    float scale = 40;
    tModel model;
};

_3DObject o_n641;
_3DObject o_n642;
_3DObject o_ball;
_3DObject o_cube;
_3DObject o_cone;

float cameraPos[3] = {0, 0, 100};
float lightPos[3] = {-3, 4, 5};

void project3DTo2D(int16_t projected[][2], float depth[], _3DObject obj);

void drawWiredObject(LGFX_Sprite sprite, _3DObject obj, uint16_t color = TFT_WHITE);
void drawFilledObject(LGFX_Sprite sprite, _3DObject obj, bool overwriteColor = false, uint16_t color = TFT_BLACK);

void rotateNormal(_3DObject obj, const float normal[3], float rotatedNormal[3]);
float normalAngle(const float normal[3], const float faceCenter[3], const float sourcePos[3]);
bool compareFaces(const Face &a, const Face &b);

inline uint16_t shadeColor(uint16_t baseColor, float factor);

void readSerialInput();

void resetTransform(_3DObject &obj);
#endif