#include "signs.h"

std::vector<int> letterU = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x07, 0xe0, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

std::vector<int> letterR = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x06, 0x60, 0x06, 0x60, 0x06, 0x40, 0x07, 0x80, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

std::vector<int> degreeSymbol = {
    0x33, 0x00, 0x00};


std::vector<int> minusSymbol = {
    0x00, 0xF0, 0x00};

std::vector<std::vector<int>> smallNumbers = {
    {0x75, 0x55, 0x70}, // 0
    {0x13, 0x11, 0x10}, // 1
    {0x71, 0x74, 0x70}, // 2
    {0x71, 0x71, 0x70}, // 3
    {0x55, 0x71, 0x10}, // 4
    {0x74, 0x71, 0x70}, // 5
    {0x74, 0x75, 0x70}, // 6
    {0x71, 0x11, 0x10}, // 7
    {0x75, 0x75, 0x70}, // 8
    {0x75, 0x71, 0x70}  // 9
};

// bitCount: 8
std::vector<std::vector<int>> bigNumbers = {
    {0x3e, 0x63, 0x73, 0x6b, 0x67, 0x63, 0x3e}, // 0
    {0x03, 0x07, 0x0f, 0x03, 0x03, 0x03, 0x03}, // 1
    {0x7e, 0x03, 0x03, 0x3e, 0x60, 0x63, 0x7f}, // 2
    {0x3e, 0x63, 0x03, 0x1f, 0x03, 0x63, 0x3e}, // 3
    {0x63, 0x63, 0x63, 0x3f, 0x03, 0x03, 0x03}, // 4
    {0x7f, 0x63, 0x60, 0x7e, 0x03, 0x63, 0x3e}, // 5
    {0x3e, 0x63, 0x60, 0x7e, 0x63, 0x63, 0x3e}, // 6
    {0x7f, 0x43, 0x07, 0x0c, 0x18, 0x18, 0x18}, // 7
    {0x3e, 0x63, 0x63, 0x3e, 0x63, 0x63, 0x3e}, // 8
    {0x3e, 0x63, 0x63, 0x3f, 0x03, 0x63, 0x3e}  // 9
};

std::vector<std::vector<int>> weatherIcons = {
    {0x03, 0x80, 0x06, 0x70, 0x1C, 0x18, 0x32, 0x06, 0x1F, 0xFC},                                     // cloudy
    {0x03, 0x80, 0x06, 0x70, 0x1C, 0x18, 0x30, 0x46, 0x1C, 0x9C, 0x01, 0xC0, 0x00, 0x80, 0x01, 0x00}, // thunderstorm
    {0x04, 0x20, 0x03, 0xc0, 0x0b, 0xd0, 0x03, 0xc0, 0x04, 0x20},                                     // clear
    {0x00, 0x38, 0x07, 0x7C, 0x0C, 0xFC, 0x38, 0x38, 0x62, 0x0C, 0x3F, 0xF8},                         // mostly or partly cloudy
    {0x03, 0x80, 0x06, 0x70, 0x1C, 0x18, 0x32, 0x06, 0x1F, 0xFC, 0x0A, 0x48, 0x0A, 0x48, 0x0A, 0x48}, // rain
    {0x03, 0x80, 0x06, 0x70, 0x1C, 0x18, 0x32, 0x06, 0x1F, 0xFC, 0x05, 0x20, 0x08, 0x48, 0x02, 0x20}, // snow
    {0x03, 0xFC, 0x3F, 0x00, 0x07, 0xFE, 0x7F, 0x00, 0x03, 0xF8, 0x3F, 0x80},                         // fog
};

// system font based on https://github.com/MakeMagazinDE/Obegraensad by DR. ARMIN ZINK
std::vector<font> fonts =
    {
        // index 0 - System font
        {"system", // name
         5,        // size x
         7,        // size y
         32,       // offset
         {
             // character data, skipped first "offest" lines
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 32 - BLANK
             {0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x20}, // 33 - !
             {0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00}, // 34 - "
             {0x50, 0x50, 0xF8, 0x50, 0xF8, 0x50, 0x50}, // 35 - #
             {0x20, 0x78, 0xA0, 0x70, 0x28, 0xF0, 0x20}, // 36 - $
             {0xC0, 0xC8, 0x10, 0x20, 0x40, 0x98, 0x18}, // 37 - %
             {0x60, 0x90, 0xA0, 0x40, 0xAA, 0x90, 0x68}, // 38 - &
             {0x60, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00}, // 39 - '
             {0x10, 0x20, 0x40, 0x40, 0x40, 0x20, 0x10}, // 40 - (
             {0x40, 0x20, 0x10, 0x10, 0x10, 0x20, 0x40}, // 41 - )
             {0x00, 0x50, 0x20, 0xF8, 0x20, 0x50, 0x00}, // 42 - *
             {0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00}, // 43 - +
             {0x00, 0x00, 0x00, 0x00, 0x60, 0x20, 0x40}, // 44 - ,
             {0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00}, // 45 - -
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60}, // 46 - .
             {0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00}, // 47 - /
             {0x30, 0x78, 0x48, 0x48, 0x48, 0x78, 0x30}, // 48 - 0
             {0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0x30}, // 49 - 1
             {0x30, 0x78, 0x08, 0x20, 0x40, 0x78, 0x78}, // 50 - 2
             {0x30, 0x78, 0x08, 0x38, 0x08, 0x78, 0x30}, // 51 - 3
             {0x48, 0x48, 0x78, 0x38, 0x08, 0x08, 0x08}, // 52 - 4
             {0x78, 0x78, 0x40, 0x70, 0x08, 0x78, 0x70}, // 53 - 5
             {0x30, 0x78, 0x40, 0x70, 0x48, 0x78, 0x30}, // 54 - 6
             {0x78, 0x78, 0x10, 0x20, 0x20, 0x20, 0x20}, // 55 - 7
             {0x30, 0x78, 0x48, 0x30, 0x48, 0x78, 0x30}, // 56 - 8
             {0x30, 0x78, 0x48, 0x38, 0x08, 0x78, 0x30}, // 57 - 9
             {0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x00}, // 58 - :
             {0x00, 0x60, 0x60, 0x00, 0x60, 0x20, 0x40}, // 59 - ;
             {0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08}, // 60 - <
             {0x00, 0x00, 0xF8, 0x00, 0xF8, 0x00, 0x00}, // 61 - =
             {0x80, 0x40, 0x20, 0x10, 0x20, 0x40, 0x80}, // 62 - >
             {0x70, 0x88, 0x08, 0x10, 0x20, 0x00, 0x20}, // 63 - ?
             {0x70, 0x88, 0x08, 0x68, 0xA8, 0xA8, 0x70}, // 64 - @
             {0x70, 0x88, 0x88, 0x88, 0xF8, 0x88, 0x88}, // 65 - A
             {0xF0, 0x88, 0x88, 0xF0, 0x88, 0x88, 0xF0}, // 66 - B
             {0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70}, // 67 - C
             {0xE0, 0x90, 0x88, 0x88, 0x88, 0x90, 0xE0}, // 68 - D
             {0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8}, // 69 - E
             {0xF8, 0x80, 0x80, 0xE0, 0x80, 0x80, 0x80}, // 70 - F
             {0x70, 0x88, 0x80, 0x80, 0x98, 0x88, 0x70}, // 71 - G
             {0x88, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x88}, // 72 - H
             {0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70}, // 73 - I
             {0x38, 0x10, 0x10, 0x10, 0x10, 0x90, 0x60}, // 74 - J
             {0x88, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x88}, // 75 - K
             {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF8}, // 76 - L
             {0x88, 0xD8, 0xA8, 0x88, 0x88, 0x88, 0x88}, // 77 - M
             {0x88, 0x88, 0xC8, 0xA8, 0x98, 0x88, 0x88}, // 78 - N
             {0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70}, // 79 - O
             {0xF0, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80}, // 80 - P
             {0x70, 0x88, 0x88, 0x88, 0xA8, 0x90, 0x68}, // 81 - Q
             {0xF0, 0x88, 0x88, 0xF0, 0xA0, 0x90, 0x88}, // 82 - R
             {0x7C, 0x80, 0x80, 0x70, 0x08, 0x08, 0xF0}, // 83 - S
             {0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20}, // 84 - T
             {0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70}, // 85 - U
             {0x88, 0x88, 0x88, 0x88, 0x88, 0x50, 0x20}, // 86 - V
             {0x88, 0x88, 0x88, 0xA8, 0xA8, 0xD8, 0x88}, // 87 - W
             {0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88}, // 88 - X
             {0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x20}, // 89 - Y
             {0xF8, 0x08, 0x10, 0x20, 0x40, 0x80, 0xF8}, // 90 - Z
             {0x38, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38}, // 91 - [
             {0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x00}, // 92 - "
             {0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0}, // 93 - ]
             {0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00}, // 94 - ^
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8}, // 95 - _
             {0x40, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00}, // 96 - `
             {0x00, 0x00, 0x70, 0x08, 0x3C, 0x88, 0x78}, // 97 - a
             {0x80, 0x80, 0xB0, 0xC8, 0x88, 0x88, 0xF0}, // 98 - b
             {0x00, 0x00, 0x70, 0x80, 0x80, 0x88, 0x70}, // 99 - c
             {0x08, 0x08, 0x68, 0x98, 0x88, 0x88, 0x78}, // 100 - d
             {0x00, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x70}, // 101 - e
             {0x30, 0x48, 0x40, 0xE0, 0x40, 0x40, 0x40}, // 102 - f
             {0x00, 0x00, 0x78, 0x88, 0x78, 0x08, 0x30}, // 103 - g
             {0x80, 0x80, 0xB0, 0xC8, 0x88, 0x88, 0x88}, // 104 - h
             {0x20, 0x00, 0x60, 0x20, 0x20, 0x20, 0x70}, // 105 - i
             {0x10, 0x00, 0x30, 0x10, 0x10, 0x90, 0x60}, // 106 - j
             {0x40, 0x40, 0x44, 0x48, 0x70, 0x48, 0x44}, // 107 - k
             {0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70}, // 108 - l
             {0x00, 0x00, 0xD0, 0xA8, 0xA8, 0x88, 0x88}, // 109 - m
             {0x00, 0x00, 0xB0, 0xC8, 0x88, 0x88, 0x88}, // 110 - n
             {0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70}, // 111 - o
             {0x00, 0x00, 0xF0, 0x88, 0xF0, 0x80, 0x80}, // 112 - p
             {0x00, 0x00, 0x68, 0x98, 0x78, 0x08, 0x08}, // 113 - q
             {0x00, 0x00, 0xB0, 0xC8, 0x80, 0x80, 0x80}, // 114 - r
             {0x00, 0x00, 0x70, 0x80, 0x70, 0x08, 0xF0}, // 115 - s
             {0x40, 0x40, 0xE0, 0x40, 0x40, 0x48, 0x30}, // 116 - t
             {0x00, 0x00, 0x88, 0x88, 0x88, 0x98, 0x68}, // 117 - u
             {0x00, 0x00, 0x88, 0x88, 0x88, 0x50, 0x20}, // 118 - v
             {0x00, 0x00, 0x88, 0x88, 0xA8, 0xA8, 0x50}, // 119 - w
             {0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88}, // 120 - x
             {0x00, 0x00, 0x88, 0x88, 0x78, 0x08, 0x70}, // 121 - y
             {0x00, 0x00, 0xF8, 0x10, 0x20, 0x40, 0xF8}, // 122 - z
             {0x10, 0x20, 0x20, 0x40, 0x20, 0x20, 0x10}, // 123 - {
             {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20}, // 124 - |
             {0x40, 0x20, 0x20, 0x10, 0x20, 0x20, 0x40}, // 125 - }
             {0x00, 0x20, 0x10, 0xF8, 0x10, 0x20, 0x00}, // 126 - ->
             {0x00, 0x20, 0x40, 0xF8, 0x40, 0x20, 0x00}, // 127 - <-
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 128
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 129
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 130
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 131
             {0x88, 0x70, 0x88, 0x88, 0xF8, 0x88, 0x88}, // 132 - Ä
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 133
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 134
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 135
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 136
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 137
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 138
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 139
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 140
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 141
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 142
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 143
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 144
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 145
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 146
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 147
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 148
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 149
             {0x88, 0x00, 0xF8, 0x88, 0x88, 0x88, 0x70}, // 150 - Ö
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 151
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 152
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 153
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 154
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 155
             {0x88, 0x00, 0x88, 0x88, 0x88, 0x88, 0x70}, // 156 - Ü
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 157
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 158
             {0x70, 0x88, 0x88, 0xF8, 0x88, 0x88, 0xB8}, // 159 - ß
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 160
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 161
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 162
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 163
             {0x00, 0x88, 0x70, 0x08, 0x78, 0x88, 0x78}, // 164 - ä
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 165
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 166
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 167
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 168
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 169
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 170
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 171
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 172
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 173
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 174
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 175
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 176
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 177
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 178
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 179
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 180
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 181
             {0x00, 0x88, 0x70, 0x88, 0x88, 0x88, 0x70}, // 182 - ö
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 183
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 184
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 185
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 186
             {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 187
             {0x00, 0x88, 0x00, 0x88, 0x88, 0x98, 0x68}, // 188 - ü
         }},

        // index 1 - bold digits
        {"boldnumber", // name
         6,            // size x
         7,            // size y
         48,           // offset
         {
             // character data, skipped first "offest" lines
             {0x78, 0xFC, 0xCC, 0xCC, 0xCC, 0xFC, 0x78}, // 48 - 0
             {0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0x30}, // 49 - 1
             {0x78, 0xFC, 0x0C, 0x38, 0x60, 0xFC, 0xFC}, // 50 - 2
             {0x78, 0xFC, 0x0C, 0x7C, 0x0C, 0xFC, 0x78}, // 51 - 3
             {0xCC, 0xCC, 0xFC, 0x7C, 0x0C, 0x0C, 0x0C}, // 52 - 4
             {0xFC, 0xFC, 0xC0, 0xF8, 0x0C, 0xFC, 0xF8}, // 53 - 5
             {0x78, 0xFC, 0xC0, 0xF8, 0xCC, 0xFC, 0x78}, // 54 - 6
             {0xFC, 0xFC, 0x18, 0x30, 0x30, 0x30, 0x30}, // 55 - 7
             {0x78, 0xFC, 0xCC, 0x78, 0xCC, 0xFC, 0x78}, // 56 - 8
             {0x78, 0xFC, 0xCC, 0x7C, 0x0C, 0xFC, 0x78}  // 57 - 9
         }},

};