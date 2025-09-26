#include "main.h"

LGFX tft;
LGFX_Sprite canvasL(&tft);
LGFX_Sprite canvasR(&tft);
LGFX_Sprite fpsCanvas(&tft);

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting...");
  Serial.println();

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  tft.begin();
  tft.invertDisplay(true);
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  canvasL.setColorDepth(16);
  canvasL.createSprite(CANV_W, CANV_H);

  canvasR.setColorDepth(16);
  canvasR.createSprite(CANV_W, CANV_H);

  fpsCanvas.setColorDepth(16);
  fpsCanvas.createSprite(18, 8);

  mode = 0;

  o_n641.model = m_n64;
  o_n642.model = m_n64;
  o_ball.model = m_ball;
  o_cube.model = m_cube;
  o_cone.model = m_cone;

  // canvasL.setRotation(tft.getRotation());
}

void loop()
{

  readSerialInput();

  canvasL.fillSprite(bgColor);
  canvasR.fillSprite(bgColor);

  if (showFps)
  {
    currentMillis = millis();

    fpsCounter++;

    if (currentMillis - fpsMillis >= 1000)
    {
      fpsCanvas.fillSprite(bgColor);

      fps = fpsCounter;
      // Serial.println(fps);

      fpsCanvas.setCursor(0, 0);
      fpsCanvas.setTextColor(TFT_DARKGRAY);
      fpsCanvas.setTextSize(1);
      fpsCanvas.print(fps);
      fpsCanvas.pushSprite(0, 0);
      // Zurücksetzen des Zählers und der Zeit
      fpsCounter = 0;
      fpsMillis = currentMillis;
    }
  }

  if (digitalRead(BUTTON_PIN) == LOW)
  {
    if (buttonUp)
    {
      mode++;
      if (mode == 18)
        mode = 0;
      tft.fillScreen(bgColor);
      buttonUp = false;
      // delay(100);
    }
  }
  else
  {
    buttonUp = true;
  }

  if (bgColor != lastbgColor)
  {
    tft.fillScreen(bgColor);
    lastbgColor = bgColor;
  }

  switch (mode)
  {
  case 0:
    bgColor = TFT_WHITE;
    drawFilledObject(canvasL, o_n641);
    canvasL.pushSprite(80, canvYoffset);
    break;

  case 1:
    bgColor = TFT_WHITE;
    drawFilledObject(canvasL, o_n641, 1);
    canvasL.pushSprite(80, canvYoffset);
    break;

  case 2:
    bgColor = TFT_WHITE;
    drawWiredObject(canvasL, o_n641, TFT_BLACK);
    canvasL.pushSprite(80, canvYoffset);
    break;

  case 3:
    bgColor = TFT_WHITE;
    o_n641.x = 80;
    o_n642.x = -80;
    drawFilledObject(canvasL, o_n641);
    drawWiredObject(canvasR, o_n642, TFT_BLACK);
    canvasL.pushSprite(0, canvYoffset);
    canvasR.pushSprite(CANV_W, canvYoffset);
    break;

  case 4:
    bgColor = TFT_WHITE;
    drawFilledObject(canvasL, o_n641);
    drawWiredObject(canvasR, o_n641, TFT_BLACK);
    canvasL.pushSprite(0, canvYoffset);
    canvasR.pushSprite(CANV_W, canvYoffset);
    break;

  case 5:
    bgColor = TFT_WHITE;
    drawFilledObject(canvasL, o_n641);
    drawWiredObject(canvasL, o_n641, TFT_BLACK);
    canvasL.pushSprite(80, canvYoffset);
    break;

  case 6:
    bgColor = TFT_WHITE;
    drawFilledObject(canvasL, o_cube);
    canvasL.pushSprite(80, canvYoffset);
    break;

  case 7:
    bgColor = TFT_WHITE;
    drawFilledObject(canvasL, o_cube, 1);
    canvasL.pushSprite(80, canvYoffset);
    break;

  case 8:
    bgColor = TFT_WHITE;
    drawWiredObject(canvasL, o_cube, TFT_BLACK);
    canvasL.pushSprite(80, canvYoffset);
    break;

  case 9:
    bgColor = TFT_WHITE;
    drawFilledObject(canvasL, o_cone);
    canvasL.pushSprite(80, canvYoffset);
    break;

  case 10:
    bgColor = TFT_WHITE;
    drawFilledObject(canvasL, o_cone, 1);
    canvasL.pushSprite(80, canvYoffset);
    break;

  case 11:
    bgColor = TFT_WHITE;
    drawWiredObject(canvasL, o_cone, TFT_BLACK);
    canvasL.pushSprite(80, canvYoffset);
    break;

  case 12:
    bgColor = TFT_WHITE;
    drawFilledObject(canvasL, o_ball);
    canvasL.pushSprite(80, canvYoffset);
    break;

  case 13:
    bgColor = TFT_WHITE;
    drawFilledObject(canvasL, o_ball, 1);
    canvasL.pushSprite(80, canvYoffset);
    break;

  case 14:
    bgColor = TFT_WHITE;
    drawWiredObject(canvasL, o_ball, TFT_BLACK);
    canvasL.pushSprite(80, canvYoffset);
    break;

  case 15:
    bgColor = TFT_WHITE;

    o_n641.x = -40;
    o_n641.y = -40;
    o_n641.scale = 20;

    o_ball.x = -40;
    o_ball.y = 40;
    o_ball.scale = 20;

    o_cube.x = 40;
    o_cube.y = -40;
    o_cube.scale = 20;

    o_cone.x = 40;
    o_cone.y = 40;
    o_cone.scale = 20;

    drawFilledObject(canvasL, o_n641);
    drawFilledObject(canvasL, o_ball);
    drawFilledObject(canvasL, o_cube);
    drawFilledObject(canvasL, o_cone);
    canvasL.pushSprite(80, canvYoffset);
    break;

  case 16:
    bgColor = TFT_WHITE;

    o_n641.x = -40;
    o_n641.y = -40;
    o_n641.scale = 20;

    o_ball.x = -40;
    o_ball.y = 40;
    o_ball.scale = 20;

    o_cube.x = 40;
    o_cube.y = -40;
    o_cube.scale = 20;

    o_cone.x = 40;
    o_cone.y = 40;
    o_cone.scale = 20;

    drawFilledObject(canvasL, o_n641);
    drawFilledObject(canvasL, o_ball);
    drawFilledObject(canvasL, o_cube);
    drawFilledObject(canvasL, o_cone);

    drawFilledObject(canvasR, o_n641);
    drawFilledObject(canvasR, o_ball);
    drawFilledObject(canvasR, o_cube);
    drawFilledObject(canvasR, o_cone);

    canvasL.pushSprite(0, canvYoffset);
    canvasR.pushSprite(CANV_W, canvYoffset);
    break;

  case 17:
    bgColor = TFT_CYAN;

    o_n641.scale = 43;
    drawFilledObject(canvasL, o_n641, 2, TFT_BLACK);
    drawFilledObject(canvasL, o_n642);
    canvasL.pushSprite(80, canvYoffset);
    break;
  }

  // Rotation
  o_n641.rotX += 0.01;
  o_n641.rotY += 0.03;

  o_n642.rotX = o_n641.rotX;
  o_n642.rotY = o_n641.rotY;

  o_ball.rotX += 0.02;
  o_ball.rotY += 0.01;

  o_cube.rotX += 0.03;
  o_cube.rotY += 0.01;

  o_cone.rotX += 0.025;
  o_cone.rotY += 0.015;

  resetTransform(o_n641);
  resetTransform(o_n642);
  resetTransform(o_ball);
  resetTransform(o_cube);
  resetTransform(o_cone);

  // canvasL.pushSprite(0, 0);
  // canvasR.pushSprite(CANV_W, 0);
}

void project3DTo2D(int16_t projected[][2], float depth[], _3DObject obj)
{
  for (uint16_t i = 0; i < obj.model.numVerts; i++)
  {
    float x = obj.model.verts[i][0] * obj.scale;
    float y = obj.model.verts[i][1] * obj.scale;
    float z = obj.model.verts[i][2] * obj.scale;

    // Rotation um X-Achse
    float tempY = y * cos(obj.rotX) - z * sin(obj.rotX);
    float tempZ = y * sin(obj.rotX) + z * cos(obj.rotX);
    y = tempY;
    z = tempZ;

    // Rotation um Y-Achse
    float tempX = x * cos(obj.rotY) + z * sin(obj.rotY);
    z = -x * sin(obj.rotY) + z * cos(obj.rotY);
    x = tempX;

    // Perspektivische Projektion
    float scale = 200 / (200 + z);
    projected[i][0] = CANV_W / 2 + x * scale + obj.x;
    projected[i][1] = CANV_H / 2 + y * scale + obj.y;

    z += obj.z;

    // Speichern der Z-Tiefe für die Tiefensortierung
    depth[i] = z;
  }
}

void drawWiredObject(LGFX_Sprite sprite, _3DObject obj, uint16_t color)
{
  int16_t projected[obj.model.numVerts][2]; // Puffer für 2D-Punkte
  float depth[obj.model.numVerts];

  project3DTo2D(projected, depth, obj);

  // Linien zeichnen
  for (uint8_t i = 0; i < obj.model.numEdges; i++)
  {
    uint16_t p1 = obj.model.edges[i][0];
    uint16_t p2 = obj.model.edges[i][1];
    sprite.drawLine(projected[p1][0], projected[p1][1], projected[p2][0], projected[p2][1], color);
  }
}

void drawFilledObject(LGFX_Sprite sprite, _3DObject obj, uint8_t colorMode, uint16_t color)
{
  int16_t projected[obj.model.numVerts][2];
  float depth[obj.model.numVerts];

  // Projektion aller Vertices
  project3DTo2D(projected, depth, obj);

  // Faces vorbereiten
  Face sortedFaces[obj.model.numFaces];

  for (uint8_t i = 0; i < obj.model.numFaces; i++)
  {
    uint16_t p1 = obj.model.faces[i][0];
    uint16_t p2 = obj.model.faces[i][1];
    uint16_t p3 = obj.model.faces[i][2];
    uint16_t p4 = obj.model.faces[i][3];

    // Indices speichern
    sortedFaces[i].indices[0] = p1;
    sortedFaces[i].indices[1] = p2;
    sortedFaces[i].indices[2] = p3;
    sortedFaces[i].indices[3] = p4;
    sortedFaces[i].colorID = obj.model.faceColorIDs[i];

    // Z-Tiefen der vier Punkte
    float z1 = depth[p1];
    float z2 = depth[p2];
    float z3 = depth[p3];
    float z4 = depth[p4];

    float minZ = std::min(std::min(z1, z2), std::min(z3, z4));
    float maxZ = std::max(std::max(z1, z2), std::max(z3, z4));

    // Face-Tiefe als Mittelpunkt
    sortedFaces[i].avgDepth = (minZ + maxZ) * 0.5f;

    // Flächenmittelpunkt berechnen
    float faceCenter[3] = {
        (obj.model.verts[p1][0] + obj.model.verts[p2][0] + obj.model.verts[p3][0] + obj.model.verts[p4][0]) / (float)4.0,
        (obj.model.verts[p1][1] + obj.model.verts[p2][1] + obj.model.verts[p3][1] + obj.model.verts[p4][1]) / (float)4.0,
        (obj.model.verts[p1][2] + obj.model.verts[p2][2] + obj.model.verts[p3][2] + obj.model.verts[p4][2]) / (float)4.0};

    // Vorgefertigte Normale drehen

    float rotatedNormal[3];
    rotateNormal(obj, obj.model.normals[i], rotatedNormal);

    sortedFaces[i].normalAngle = normalAngle(rotatedNormal, faceCenter, lightPos);
    sortedFaces[i].normal[0] = (rotatedNormal[0] + 1) / 2 * 255;
    sortedFaces[i].normal[1] = ((rotatedNormal[1] + 1) / 2 * 255) * -1;
    sortedFaces[i].normal[2] = ((rotatedNormal[2] + 1.01) / 2 * 255) * -1;

    if (normalAngle(rotatedNormal, faceCenter, cameraPos) < 0)
    {
      sortedFaces[i].avgDepth = -9999; // Unsichtbar setzen
    }
  }

  // Nach Tiefe sortieren (hinten → vorne)
  std::sort(sortedFaces, sortedFaces + obj.model.numFaces, compareFaces);

  // Faces zeichnen
  for (uint8_t i = 0; i < obj.model.numFaces; i++)
  {
    if (sortedFaces[i].avgDepth == -9999)
      continue; // Unsichtbare Flächen überspringen

    uint16_t p1 = sortedFaces[i].indices[0];
    uint16_t p2 = sortedFaces[i].indices[1];
    uint16_t p3 = sortedFaces[i].indices[2];
    uint16_t p4 = sortedFaces[i].indices[3];

    uint16_t col;

    if (colorMode > 2) colorMode = 0;

    switch (colorMode)
    {
    case 0:
      col = shadeColor(obj.model.colors[sortedFaces[i].colorID], sortedFaces[i].normalAngle);
      break;
    case 1:
      col = lgfx::color565(sortedFaces[i].normal[0], sortedFaces[i].normal[1], sortedFaces[i].normal[2]);
      break;
    case 2:
      col = color;
      break;
    }

    sprite.fillTriangle(projected[p1][0], projected[p1][1],
                        projected[p2][0], projected[p2][1],
                        projected[p3][0], projected[p3][1], col);

    sprite.fillTriangle(projected[p3][0], projected[p3][1],
                        projected[p4][0], projected[p4][1],
                        projected[p1][0], projected[p1][1], col);
  }
}

void rotateNormal(_3DObject obj, const float normal[3], float rotatedNormal[3])
{
  float x = normal[0];
  float y = normal[1];
  float z = normal[2];

  // Rotation um X-Achse
  float tempY = y * cos(obj.rotX) - z * sin(obj.rotX);
  float tempZ = y * sin(obj.rotX) + z * cos(obj.rotX);
  y = tempY;
  z = tempZ;

  // Rotation um Y-Achse
  float tempX = x * cos(obj.rotY) + z * sin(obj.rotY);
  z = -x * sin(obj.rotY) + z * cos(obj.rotY);
  x = tempX;

  // Ergebnis speichern
  rotatedNormal[0] = x;
  rotatedNormal[1] = y;
  rotatedNormal[2] = z;
}

float normalAngle(const float normal[3], const float faceCenter[3], const float sourcePos[3])
{
  float viewDir[3] = {faceCenter[0] - sourcePos[0],
                      faceCenter[1] - sourcePos[1],
                      faceCenter[2] - sourcePos[2]};

  // Normalisieren
  float length = sqrt(viewDir[0] * viewDir[0] + viewDir[1] * viewDir[1] + viewDir[2] * viewDir[2]);
  if (length > 0)
  {
    viewDir[0] /= length;
    viewDir[1] /= length;
    viewDir[2] /= length;
  }

  float dot = normal[0] * viewDir[0] + normal[1] * viewDir[1] + normal[2] * viewDir[2];
  // Serial.println(dot);
  return dot; // Positiver Wert = Fläche zeigt zur Kamera
}

inline uint16_t shadeColor(uint16_t baseColor, float factor)
{

  if (factor < 0)
    factor = 0;
  if (factor > 1)
    factor = 1;

  // RGB565 -> R,G,B (8bit)
  uint8_t r = ((baseColor >> 11) & 0x1F) << 3;
  uint8_t g = ((baseColor >> 5) & 0x3F) << 2;
  uint8_t b = (baseColor & 0x1F) << 3;

  // mit Faktor multiplizieren
  r = (uint8_t)(r * factor);
  g = (uint8_t)(g * factor);
  b = (uint8_t)(b * factor);

  return lgfx::color565(r, g, b);
}

// Vergleichsfunktion für Sortierung (absteigend nach Z-Tiefe)
bool compareFaces(const Face &a, const Face &b)
{
  return a.avgDepth > b.avgDepth;
}

void resetTransform(_3DObject &obj)
{
  obj.x = 0;
  obj.y = 0;
  obj.z = 0;
  // obj.rotX = 0;
  // obj.rotY = 0;
  // obj.rotZ = 0;
  obj.scale = 40;
}

void readSerialInput()
{
  if (Serial.available())
  {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    // Beispiel-Befehl: "light 1.0 0.5 -0.2"
    if (cmd.startsWith("light"))
    {
      float lx, ly, lz;
      int n = sscanf(cmd.c_str(), "light %f %f %f", &lx, &ly, &lz);
      if (n == 3)
      {
        lightPos[0] = lx;
        lightPos[1] = ly;
        lightPos[2] = lz;
        Serial.printf("Neue Lichtposition: %.2f %.2f %.2f\n", lx, ly, lz);
      }
      else
      {
        Serial.printf("Lichtposition: %.2f %.2f %.2f\n", lightPos[0], lightPos[1], lightPos[2]);
      }
    }
  }
}