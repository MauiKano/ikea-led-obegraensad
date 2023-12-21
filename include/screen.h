#pragma once

#include <Arduino.h>
#include <vector>
#include "PluginManager.h"
#include "signs.h"
#include "constants.h"
#include "storage.h"
class Screen_
{
private:
  Screen_() = default;
  int findPosition(uint8_t count);
  void rotate();
  uint8_t brightness = 255;
  uint8_t renderBuffer_[ROWS * COLS];
  uint8_t rotatedRenderBuffer_[ROWS * COLS];
  uint8_t cache[ROWS * COLS];
  #ifndef FREKVENS
  uint8_t positions[ROWS * COLS] = {
      0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
      0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
      0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0x20, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
      0x2f, 0x2e, 0x2d, 0x2c, 0x2b, 0x2a, 0x29, 0x28, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
      0x4f, 0x4e, 0x4d, 0x4c, 0x4b, 0x4a, 0x49, 0x48, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
      0x47, 0x46, 0x45, 0x44, 0x43, 0x42, 0x41, 0x40, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
      0x67, 0x66, 0x65, 0x64, 0x63, 0x62, 0x61, 0x60, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
      0x6f, 0x6e, 0x6d, 0x6c, 0x6b, 0x6a, 0x69, 0x68, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
      0x8f, 0x8e, 0x8d, 0x8c, 0x8b, 0x8a, 0x89, 0x88, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
      0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
      0xa7, 0xa6, 0xa5, 0xa4, 0xa3, 0xa2, 0xa1, 0xa0, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
      0xaf, 0xae, 0xad, 0xac, 0xab, 0xaa, 0xa9, 0xa8, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
      0xcf, 0xce, 0xcd, 0xcc, 0xcb, 0xca, 0xc9, 0xc8, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
      0xc7, 0xc6, 0xc5, 0xc4, 0xc3, 0xc2, 0xc1, 0xc0, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
      0xe7, 0xe6, 0xe5, 0xe4, 0xe3, 0xe2, 0xe1, 0xe0, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
      0xef, 0xee, 0xed, 0xec, 0xeb, 0xea, 0xe9, 0xe8, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff};
   #endif
 #ifdef FREKVENS
   uint8_t positions[ROWS * COLS] = {
       0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA, 0xE9, 0xE8,
       0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8, 0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8,
       0xBF, 0xBE, 0xBD, 0xBC, 0xBB, 0xBA, 0xB9, 0xB8, 0xAF, 0xAE, 0xAD, 0xAC, 0xAB, 0xAA, 0xA9, 0xA8,
       0x9F, 0x9E, 0x9D, 0x9C, 0x9B, 0x9A, 0x99, 0x98, 0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x8A, 0x89, 0x88,
       0x7F, 0x7E, 0x7D, 0x7C, 0x7B, 0x7A, 0x79, 0x78, 0x6F, 0x6E, 0x6D, 0x6C, 0x6B, 0x6A, 0x69, 0x68,
       0x5F, 0x5E, 0x5D, 0x5C, 0x5B, 0x5A, 0x59, 0x58, 0x4F, 0x4E, 0x4D, 0x4C, 0x4B, 0x4A, 0x49, 0x48,
       0x3F, 0x3E, 0x3D, 0x3C, 0x3B, 0x3A, 0x39, 0x38, 0x2F, 0x2E, 0x2D, 0x2C, 0x2B, 0x2A, 0x29, 0x28,
       0x1F, 0x1E, 0x1D, 0x1C, 0x1B, 0x1A, 0x19, 0x18, 0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A, 0x09, 0x08,
       0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE1, 0xE0,
       0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0, 0xC7, 0xC6, 0xC5, 0xC4, 0xC3, 0xC2, 0xC1, 0xC0,
       0xB7, 0xB6, 0xB5, 0xB4, 0xB3, 0xB2, 0xB1, 0xB0, 0xA7, 0xA6, 0xA5, 0xA4, 0xA3, 0xA2, 0xA1, 0xA0,
       0x97, 0x96, 0x95, 0x94, 0x93, 0x92, 0x91, 0x90, 0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80,
       0x77, 0x76, 0x75, 0x74, 0x73, 0x72, 0x71, 0x70, 0x67, 0x66, 0x65, 0x64, 0x63, 0x62, 0x61, 0x60,
       0x57, 0x56, 0x55, 0x54, 0x53, 0x52, 0x51, 0x50, 0x47, 0x46, 0x45, 0x44, 0x43, 0x42, 0x41, 0x40,
       0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0x20,
       0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00};
 #endif
  static void onScreenTimer();
  void _render();

public:
  static Screen_ &getInstance();

  Screen_(const Screen_ &) = delete;
  Screen_ &operator=(const Screen_ &) = delete;

  bool isCacheEmpty();
  int currentRotation;

  uint8_t getCurrentBrightness() const;
  void setBrightness(uint8_t brightness);

  void setRenderBuffer(const uint8_t *renderBuffer, bool grays = false);
  uint8_t *getRenderBuffer();
  uint8_t *getRotatedRenderBuffer();

  void clear();
  void drawLine(uint8_t line, bool isHorizontal);
  void setPixel(uint8_t x, uint8_t y, uint8_t value, uint8_t brightness = 255);
  void setPixelAtIndex(uint8_t index, uint8_t value, uint8_t brightness = 255);
  void setup();
  void loadFromStorage();
  void persist();
  void cacheCurrent();
  void restoreCache();
  uint8_t getBufferIndex(int index);

  void drawLine(int x1, int y1, int x2, int y2, int ledStatus, uint8_t brightness = 255);
  void drawRectangle(int x, int y, int width, int height, bool outline, int ledStatus, uint8_t brightness = 255);
  void drawCharacter(int x, int y, std::vector<int> bits, int bitCount, uint8_t brightness = 255);
  void drawNumbers(int x, int y, std::vector<int> numbers, uint8_t brightness = 255);
  void drawBigNumbers(int x, int y, std::vector<int> numbers, uint8_t brightness = 255);
  void drawWeather(int x, int y, int weather, uint8_t brightness = 255);
  std::vector<int> readBytes(std::vector<int> bytes);

  void scrollText(std::string text, int delayTime = 30, uint8_t brightness = 255);
  void scrollGraph(std::vector<int> graph = {}, int miny = 0, int maxy = 15, int delayTime = 60, uint8_t brightness = 255);
};

extern Screen_ &Screen;
