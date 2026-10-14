// Generated NEC V20/V30 tables. Do not edit.
#include "GeneratedCpu.h"

namespace marty::nec {
using Cpu = GeneratedCpu;
const GeneratedCpu::Model GeneratedCpu::defaultModel = GeneratedCpu::Model::V30;

static const uint16_t columns[][4] = {
    {0, 65535, 65535, 65535},
    {4, 65535, 65535, 65535},
    {12, 65535, 65535, 65535},
    {8, 65535, 65535, 65535},
    {65535, 65535, 65535, 65535},
    {16, 65535, 65535, 65535},
    {20, 65535, 65535, 65535},
    {24, 28, 65535, 65535},
    {32, 28, 65535, 65535},
    {36, 65535, 65535, 65535},
    {40, 65535, 65535, 65535},
    {44, 65535, 65535, 65535},
    {564, 65535, 65535, 65535},
    {584, 65535, 65535, 65535},
    {628, 632, 636, 65535},
    {48, 65535, 65535, 65535},
    {644, 65535, 65535, 65535},
    {652, 65535, 65535, 65535},
    {640, 65535, 65535, 65535},
    {656, 65535, 65535, 65535},
    {668, 65535, 65535, 65535},
    {52, 56, 65535, 65535},
    {60, 64, 65535, 65535},
    {68, 65535, 65535, 65535},
    {72, 65535, 65535, 65535},
    {76, 65535, 65535, 65535},
    {80, 65535, 65535, 65535},
    {84, 65535, 65535, 65535},
    {88, 65535, 65535, 65535},
    {92, 65535, 65535, 65535},
    {96, 65535, 65535, 65535},
    {100, 65535, 65535, 65535},
    {104, 65535, 65535, 65535},
    {108, 112, 65535, 65535},
    {116, 65535, 65535, 65535},
    {120, 65535, 65535, 65535},
    {124, 65535, 65535, 65535},
    {128, 65535, 65535, 65535},
    {132, 65535, 65535, 65535},
    {136, 65535, 65535, 65535},
    {140, 152, 65535, 65535},
    {156, 160, 65535, 65535},
    {180, 65535, 65535, 65535},
    {184, 65535, 65535, 65535},
    {196, 65535, 65535, 65535},
    {208, 212, 65535, 65535},
    {224, 65535, 65535, 65535},
    {648, 65535, 65535, 65535},
    {228, 232, 65535, 65535},
    {240, 65535, 65535, 65535},
    {248, 65535, 65535, 65535},
    {252, 65535, 65535, 65535},
    {256, 65535, 65535, 65535},
    {604, 65535, 65535, 65535},
    {624, 65535, 65535, 65535},
    {228, 236, 65535, 65535},
    {244, 65535, 65535, 65535},
    {260, 65535, 65535, 65535},
    {264, 65535, 65535, 65535},
    {268, 65535, 65535, 65535},
    {272, 65535, 65535, 65535},
    {276, 65535, 65535, 65535},
    {280, 65535, 65535, 65535},
    {284, 288, 65535, 65535},
    {292, 296, 65535, 65535},
    {300, 65535, 65535, 65535},
    {304, 65535, 65535, 65535},
    {308, 312, 65535, 65535},
    {316, 312, 65535, 65535},
    {320, 312, 65535, 65535},
    {324, 65535, 65535, 65535},
    {328, 65535, 65535, 65535},
    {332, 336, 65535, 65535},
    {340, 65535, 65535, 65535},
    {348, 352, 65535, 65535},
    {344, 65535, 65535, 65535},
    {356, 65535, 65535, 65535},
    {360, 65535, 65535, 65535},
    {660, 664, 65535, 65535},
    {672, 676, 65535, 65535},
    {148, 152, 65535, 65535},
    {164, 168, 172, 65535},
    {188, 192, 65535, 65535},
    {200, 204, 65535, 65535},
    {164, 216, 220, 65535},
    {364, 65535, 65535, 65535},
    {372, 65535, 65535, 65535},
    {368, 65535, 65535, 65535},
    {376, 380, 384, 65535},
    {388, 65535, 65535, 65535},
    {392, 396, 400, 404},
    {408, 412, 65535, 65535},
    {440, 65535, 65535, 65535},
    {444, 65535, 65535, 65535},
    {448, 65535, 65535, 65535},
    {452, 65535, 65535, 65535},
    {456, 65535, 65535, 65535},
    {460, 65535, 65535, 65535},
    {680, 65535, 65535, 65535},
    {696, 65535, 65535, 65535},
    {688, 65535, 65535, 65535},
    {704, 65535, 65535, 65535},
    {684, 65535, 65535, 65535},
    {700, 65535, 65535, 65535},
    {692, 65535, 65535, 65535},
    {708, 65535, 65535, 65535},
    {712, 716, 720, 724},
    {728, 732, 65535, 65535},
    {712, 716, 736, 724},
    {712, 716, 65535, 724},
    {712, 716, 740, 724},
    {744, 748, 752, 65535},
    {756, 748, 752, 65535},
    {788, 792, 796, 800},
    {760, 764, 768, 772},
    {776, 780, 508, 65535},
    {788, 832, 796, 800},
    {784, 764, 768, 772},
    {836, 65535, 65535, 65535},
    {1020, 65535, 65535, 65535},
    {1016, 65535, 65535, 65535},
    {840, 65535, 65535, 65535},
    {852, 65535, 65535, 65535},
    {876, 65535, 65535, 65535},
    {904, 65535, 65535, 65535},
    {896, 65535, 65535, 65535},
    {900, 65535, 65535, 65535},
    {848, 65535, 65535, 65535},
    {932, 65535, 65535, 65535},
    {920, 65535, 65535, 65535},
    {872, 65535, 65535, 65535},
    {908, 65535, 65535, 65535},
    {868, 65535, 65535, 65535},
    {924, 65535, 65535, 65535},
    {864, 65535, 65535, 65535},
    {928, 65535, 65535, 65535},
    {860, 65535, 65535, 65535},
    {856, 65535, 65535, 65535},
    {844, 65535, 65535, 65535},
    {912, 65535, 65535, 65535},
    {972, 976, 65535, 65535},
    {992, 65535, 65535, 65535},
    {940, 944, 65535, 65535},
    {936, 65535, 65535, 65535},
    {960, 964, 65535, 65535},
    {980, 65535, 65535, 65535},
    {916, 65535, 65535, 65535},
    {948, 65535, 65535, 65535},
    {968, 65535, 65535, 65535},
    {952, 956, 65535, 65535},
    {1008, 65535, 65535, 65535},
    {1012, 65535, 65535, 65535},
    {996, 65535, 65535, 65535},
    {880, 65535, 65535, 65535},
    {984, 65535, 65535, 65535},
    {888, 65535, 65535, 65535},
    {884, 65535, 65535, 65535},
    {1000, 1004, 65535, 65535},
    {988, 65535, 65535, 65535},
    {892, 65535, 65535, 65535},
    {472, 65535, 65535, 65535},
    {476, 65535, 65535, 65535},
    {464, 468, 65535, 65535},
    {480, 484, 65535, 65535},
    {488, 492, 496, 500},
    {504, 65535, 65535, 65535},
    {488, 492, 144, 500},
    {512, 65535, 65535, 65535},
    {516, 65535, 65535, 65535},
    {520, 524, 528, 176},
    {532, 65535, 65535, 65535},
    {520, 524, 528, 536},
    {540, 544, 65535, 65535},
    {548, 65535, 65535, 65535},
    {608, 612, 616, 620},
    {568, 572, 576, 580},
    {588, 592, 596, 600},
    {552, 556, 65535, 65535},
    {804, 808, 812, 816},
    {820, 824, 828, 65535},
    {416, 420, 65535, 65535},
    {560, 65535, 65535, 65535},
    {424, 428, 432, 436},
};
static const uint16_t directory[2048] = {
    0, 0, 0, 0, 1, 1, 2, 3, 0, 0, 0, 0, 1, 1, 2, 3,
    0, 0, 0, 0, 1, 1, 2, 3, 0, 0, 0, 0, 1, 1, 2, 3,
    0, 0, 0, 0, 1, 1, 4, 5, 0, 0, 0, 0, 1, 1, 4, 6,
    0, 0, 0, 0, 1, 1, 4, 7, 0, 0, 0, 0, 1, 1, 4, 8,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11,
    12, 13, 14, 4, 4, 4, 15, 15, 16, 17, 18, 17, 19, 19, 20, 20,
    21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
    22, 22, 22, 22, 23, 23, 24, 24, 25, 25, 25, 25, 26, 27, 26, 28,
    29, 29, 29, 29, 29, 29, 29, 29, 30, 31, 32, 33, 34, 35, 36, 37,
    38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45,
    46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
    47, 47, 48, 49, 50, 51, 52, 52, 53, 54, 55, 56, 57, 58, 59, 60,
    61, 61, 62, 62, 63, 64, 4, 65, 66, 66, 66, 66, 66, 66, 66, 66,
    67, 67, 68, 69, 70, 70, 71, 71, 72, 73, 74, 75, 76, 76, 77, 77,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    0, 0, 0, 0, 1, 1, 2, 3, 0, 0, 0, 0, 1, 1, 2, 3,
    0, 0, 0, 0, 1, 1, 2, 3, 0, 0, 0, 0, 1, 1, 2, 3,
    0, 0, 0, 0, 1, 1, 4, 5, 0, 0, 0, 0, 1, 1, 4, 6,
    0, 0, 0, 0, 1, 1, 4, 7, 0, 0, 0, 0, 1, 1, 4, 8,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11,
    12, 13, 14, 4, 4, 4, 15, 15, 16, 17, 18, 17, 78, 78, 79, 79,
    21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
    22, 22, 22, 22, 23, 23, 24, 24, 25, 25, 25, 25, 26, 27, 26, 28,
    29, 29, 29, 29, 29, 29, 29, 29, 30, 31, 32, 33, 34, 35, 36, 37,
    38, 38, 39, 39, 80, 80, 81, 81, 42, 42, 82, 82, 83, 83, 84, 84,
    46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
    47, 47, 48, 49, 50, 51, 52, 52, 53, 54, 55, 56, 57, 58, 59, 60,
    61, 61, 62, 62, 63, 64, 4, 65, 66, 66, 66, 66, 66, 66, 66, 66,
    67, 67, 68, 69, 70, 70, 71, 71, 72, 73, 74, 75, 76, 76, 77, 77,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85,
    86, 86, 86, 86, 86, 86, 86, 86, 87, 87, 87, 87, 87, 87, 87, 87,
    88, 88, 88, 88, 88, 88, 88, 88, 89, 89, 89, 89, 89, 89, 89, 89,
    90, 90, 90, 90, 90, 90, 90, 90, 91, 91, 91, 91, 91, 91, 91, 91,
    85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85,
    86, 86, 86, 86, 86, 86, 86, 86, 87, 87, 87, 87, 87, 87, 87, 87,
    88, 88, 88, 88, 88, 88, 88, 88, 89, 89, 89, 89, 89, 89, 89, 89,
    90, 90, 90, 90, 90, 90, 90, 90, 91, 91, 91, 91, 91, 91, 91, 91,
    85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85,
    86, 86, 86, 86, 86, 86, 86, 86, 87, 87, 87, 87, 87, 87, 87, 87,
    88, 88, 88, 88, 88, 88, 88, 88, 89, 89, 89, 89, 89, 89, 89, 89,
    90, 90, 90, 90, 90, 90, 90, 90, 91, 91, 91, 91, 91, 91, 91, 91,
    85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85,
    86, 86, 86, 86, 86, 86, 86, 86, 87, 87, 87, 87, 87, 87, 87, 87,
    88, 88, 88, 88, 88, 88, 88, 88, 89, 89, 89, 89, 89, 89, 89, 89,
    90, 90, 90, 90, 90, 90, 90, 90, 91, 91, 91, 91, 91, 91, 91, 91,
    92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
    93, 93, 93, 93, 93, 93, 93, 93, 94, 94, 94, 94, 94, 94, 94, 94,
    95, 95, 95, 95, 95, 95, 95, 95, 96, 96, 96, 96, 96, 96, 96, 96,
    97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97,
    92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
    93, 93, 93, 93, 93, 93, 93, 93, 94, 94, 94, 94, 94, 94, 94, 94,
    95, 95, 95, 95, 95, 95, 95, 95, 96, 96, 96, 96, 96, 96, 96, 96,
    97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97,
    92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
    93, 93, 93, 93, 93, 93, 93, 93, 94, 94, 94, 94, 94, 94, 94, 94,
    95, 95, 95, 95, 95, 95, 95, 95, 96, 96, 96, 96, 96, 96, 96, 96,
    97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97,
    92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
    93, 93, 93, 93, 93, 93, 93, 93, 94, 94, 94, 94, 94, 94, 94, 94,
    95, 95, 95, 95, 95, 95, 95, 95, 96, 96, 96, 96, 96, 96, 96, 96,
    97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    98, 98, 99, 99, 100, 100, 101, 101, 102, 102, 103, 103, 104, 104, 105, 105,
    106, 107, 108, 107, 109, 107, 110, 107, 111, 4, 112, 4, 4, 4, 4, 4,
    4, 113, 4, 114, 115, 4, 4, 4, 4, 116, 4, 117, 115, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 118,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 119, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 120, 4, 4,
    121, 122, 123, 124, 125, 126, 127, 128, 4, 129, 130, 131, 125, 126, 127, 128,
    4, 122, 123, 124, 125, 126, 127, 128, 4, 129, 130, 131, 125, 126, 127, 128,
    4, 122, 132, 124, 125, 126, 127, 133, 4, 129, 134, 131, 125, 126, 127, 135,
    4, 122, 136, 124, 125, 126, 127, 4, 4, 129, 137, 131, 125, 126, 127, 4,
    138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,
    138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,
    138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,
    138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,
    139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139,
    139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139,
    139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139,
    139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139,
    140, 141, 142, 143, 144, 145, 146, 147, 140, 148, 142, 4, 144, 149, 146, 147,
    140, 141, 142, 150, 144, 145, 146, 147, 140, 4, 142, 151, 144, 4, 146, 147,
    140, 152, 142, 153, 144, 154, 146, 147, 140, 155, 142, 156, 144, 4, 146, 147,
    140, 157, 142, 4, 144, 158, 146, 147, 140, 159, 142, 4, 144, 4, 146, 147,
    160, 4, 161, 162, 4, 4, 4, 4, 163, 4, 4, 4, 4, 4, 4, 4,
    164, 165, 4, 4, 4, 4, 4, 4, 166, 165, 4, 4, 4, 4, 4, 4,
    167, 4, 4, 4, 4, 4, 4, 4, 168, 4, 4, 4, 4, 4, 4, 4,
    169, 170, 4, 4, 4, 4, 4, 4, 171, 4, 4, 4, 4, 4, 4, 4,
    172, 4, 4, 4, 4, 4, 4, 4, 173, 4, 4, 4, 4, 4, 4, 4,
    174, 4, 4, 4, 4, 4, 4, 4, 175, 4, 4, 4, 4, 4, 4, 4,
    176, 4, 4, 4, 4, 4, 4, 4, 177, 4, 4, 4, 4, 4, 4, 4,
    178, 179, 4, 4, 4, 4, 4, 4, 180, 4, 4, 4, 4, 4, 4, 4,
    181, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    182, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
};

const Cpu::Alu GeneratedCpu::xiBanks[][8] = {
    {Cpu::Alu::Add, Cpu::Alu::Or, Cpu::Alu::Adc, Cpu::Alu::Sbb, Cpu::Alu::And, Cpu::Alu::Sub, Cpu::Alu::Xor, Cpu::Alu::Cmp},
    {Cpu::Alu::Inc, Cpu::Alu::Dec, Cpu::Alu::Not, Cpu::Alu::Neg, Cpu::Alu::Inc2, Cpu::Alu::Dec2, Cpu::Alu::MulDiv, Cpu::Alu::Pass},
    {Cpu::Alu::Pass, Cpu::Alu::Pass, Cpu::Alu::Pass, Cpu::Alu::Pass, Cpu::Alu::Pass, Cpu::Alu::Pass, Cpu::Alu::Pass, Cpu::Alu::Pass},
    {Cpu::Alu::Rol, Cpu::Alu::Ror, Cpu::Alu::Rcl, Cpu::Alu::Rcr, Cpu::Alu::Shl, Cpu::Alu::Shr, Cpu::Alu::Shl, Cpu::Alu::Sar},
    {Cpu::Alu::And, Cpu::Alu::And, Cpu::Alu::Not, Cpu::Alu::Neg, Cpu::Alu::Mul, Cpu::Alu::Mul, Cpu::Alu::Div, Cpu::Alu::Div},
    {Cpu::Alu::Inc, Cpu::Alu::Dec, Cpu::Alu::Inc, Cpu::Alu::Dec, Cpu::Alu::Inc, Cpu::Alu::Dec, Cpu::Alu::Inc, Cpu::Alu::Dec},
};

const Cpu::InstructionInfo GeneratedCpu::opcodeDecodeTable[1024] = {
    {0x0000, false, true, true, false, false, false, false, false, 0, 0}, // native 00
    {0x0010, true, true, true, false, false, false, false, false, 0, 0}, // native 01
    {0x0020, false, true, true, false, true, false, false, false, 0, 0}, // native 02
    {0x0030, true, true, true, false, true, false, false, false, 0, 0}, // native 03
    {0x0040, false, false, true, false, false, true, false, false, 0, 0}, // native 04
    {0x0050, true, false, true, false, false, true, false, false, 0, 0}, // native 05
    {0x0060, true, false, true, false, false, false, false, false, 0, 0}, // native 06
    {0x0070, true, false, true, false, false, false, false, false, 1, 0}, // native 07
    {0x0080, false, true, true, false, false, false, false, false, 0, 0}, // native 08
    {0x0090, true, true, true, false, false, false, false, false, 0, 0}, // native 09
    {0x00a0, false, true, true, false, true, false, false, false, 0, 0}, // native 0A
    {0x00b0, true, true, true, false, true, false, false, false, 0, 0}, // native 0B
    {0x00c0, false, false, true, false, false, true, false, false, 0, 0}, // native 0C
    {0x00d0, true, false, true, false, false, true, false, false, 0, 0}, // native 0D
    {0x00e0, true, false, true, false, false, false, false, false, 0, 0}, // native 0E
    {0x00f0, true, false, true, false, false, false, false, true, 1, 0}, // native 0F
    {0x0100, false, true, true, false, false, false, false, false, 0, 0}, // native 10
    {0x0110, true, true, true, false, false, false, false, false, 0, 0}, // native 11
    {0x0120, false, true, true, false, true, false, false, false, 0, 0}, // native 12
    {0x0130, true, true, true, false, true, false, false, false, 0, 0}, // native 13
    {0x0140, false, false, true, false, false, true, false, false, 0, 0}, // native 14
    {0x0150, true, false, true, false, false, true, false, false, 0, 0}, // native 15
    {0x0160, true, false, true, false, false, false, false, false, 0, 0}, // native 16
    {0x0170, true, false, true, false, false, false, false, false, 1, 0}, // native 17
    {0x0180, false, true, true, false, false, false, false, false, 0, 0}, // native 18
    {0x0190, true, true, true, false, false, false, false, false, 0, 0}, // native 19
    {0x01a0, false, true, true, false, true, false, false, false, 0, 0}, // native 1A
    {0x01b0, true, true, true, false, true, false, false, false, 0, 0}, // native 1B
    {0x01c0, false, false, true, false, false, true, false, false, 0, 0}, // native 1C
    {0x01d0, true, false, true, false, false, true, false, false, 0, 0}, // native 1D
    {0x01e0, true, false, true, false, false, false, false, false, 0, 0}, // native 1E
    {0x01f0, true, false, true, false, false, false, false, false, 1, 0}, // native 1F
    {0x0200, false, true, true, false, false, false, false, false, 0, 0}, // native 20
    {0x0210, true, true, true, false, false, false, false, false, 0, 0}, // native 21
    {0x0220, false, true, true, false, true, false, false, false, 0, 0}, // native 22
    {0x0230, true, true, true, false, true, false, false, false, 0, 0}, // native 23
    {0x0240, false, false, true, false, false, true, false, false, 0, 0}, // native 24
    {0x0250, true, false, true, false, false, true, false, false, 0, 0}, // native 25
    {0x0260, true, false, true, false, false, false, false, true, 0, 0}, // native 26
    {0x0270, false, false, true, false, false, false, false, false, 10, 0}, // native 27
    {0x0280, false, true, true, false, false, false, false, false, 0, 0}, // native 28
    {0x0290, true, true, true, false, false, false, false, false, 0, 0}, // native 29
    {0x02a0, false, true, true, false, true, false, false, false, 0, 0}, // native 2A
    {0x02b0, true, true, true, false, true, false, false, false, 0, 0}, // native 2B
    {0x02c0, false, false, true, false, false, true, false, false, 0, 0}, // native 2C
    {0x02d0, true, false, true, false, false, true, false, false, 0, 0}, // native 2D
    {0x02e0, true, false, true, false, false, false, false, true, 0, 0}, // native 2E
    {0x02f0, false, false, true, false, false, false, false, false, 10, 0}, // native 2F
    {0x0300, false, true, true, false, false, false, false, false, 0, 0}, // native 30
    {0x0310, true, true, true, false, false, false, false, false, 0, 0}, // native 31
    {0x0320, false, true, true, false, true, false, false, false, 0, 0}, // native 32
    {0x0330, true, true, true, false, true, false, false, false, 0, 0}, // native 33
    {0x0340, false, false, true, false, false, true, false, false, 0, 0}, // native 34
    {0x0350, true, false, true, false, false, true, false, false, 0, 0}, // native 35
    {0x0360, true, false, true, false, false, false, false, true, 0, 0}, // native 36
    {0x0370, false, false, true, false, false, false, false, false, 10, 0}, // native 37
    {0x0380, false, true, true, false, false, false, false, false, 0, 0}, // native 38
    {0x0390, true, true, true, false, false, false, false, false, 0, 0}, // native 39
    {0x03a0, false, true, true, false, true, false, false, false, 0, 0}, // native 3A
    {0x03b0, true, true, true, false, true, false, false, false, 0, 0}, // native 3B
    {0x03c0, false, false, true, false, false, true, false, false, 0, 0}, // native 3C
    {0x03d0, true, false, true, false, false, true, false, false, 0, 0}, // native 3D
    {0x03e0, true, false, true, false, false, false, false, true, 0, 0}, // native 3E
    {0x03f0, false, false, true, false, false, false, false, false, 10, 0}, // native 3F
    {0x0400, true, false, true, false, false, false, false, false, 12, 1}, // native 40
    {0x0410, true, false, true, false, false, false, false, false, 12, 1}, // native 41
    {0x0420, true, false, true, false, false, false, false, false, 12, 1}, // native 42
    {0x0430, true, false, true, false, false, false, false, false, 12, 1}, // native 43
    {0x0440, true, false, true, false, false, false, false, false, 12, 1}, // native 44
    {0x0450, true, false, true, false, false, false, false, false, 12, 1}, // native 45
    {0x0460, true, false, true, false, false, false, false, false, 12, 1}, // native 46
    {0x0470, true, false, true, false, false, false, false, false, 12, 1}, // native 47
    {0x0480, true, false, true, false, false, false, false, false, 12, 1}, // native 48
    {0x0490, true, false, true, false, false, false, false, false, 12, 1}, // native 49
    {0x04a0, true, false, true, false, false, false, false, false, 12, 1}, // native 4A
    {0x04b0, true, false, true, false, false, false, false, false, 12, 1}, // native 4B
    {0x04c0, true, false, true, false, false, false, false, false, 12, 1}, // native 4C
    {0x04d0, true, false, true, false, false, false, false, false, 12, 1}, // native 4D
    {0x04e0, true, false, true, false, false, false, false, false, 12, 1}, // native 4E
    {0x04f0, true, false, true, false, false, false, false, false, 12, 1}, // native 4F
    {0x0500, true, false, true, false, false, false, false, false, 0, 2}, // native 50
    {0x0510, true, false, true, false, false, false, false, false, 0, 2}, // native 51
    {0x0520, true, false, true, false, false, false, false, false, 0, 2}, // native 52
    {0x0530, true, false, true, false, false, false, false, false, 0, 2}, // native 53
    {0x0540, true, false, true, false, false, false, false, false, 0, 2}, // native 54
    {0x0550, true, false, true, false, false, false, false, false, 0, 2}, // native 55
    {0x0560, true, false, true, false, false, false, false, false, 0, 2}, // native 56
    {0x0570, true, false, true, false, false, false, false, false, 0, 2}, // native 57
    {0x0580, true, false, true, false, false, false, false, false, 0, 2}, // native 58
    {0x0590, true, false, true, false, false, false, false, false, 0, 2}, // native 59
    {0x05a0, true, false, true, false, false, false, false, false, 0, 2}, // native 5A
    {0x05b0, true, false, true, false, false, false, false, false, 0, 2}, // native 5B
    {0x05c0, true, false, true, false, false, false, false, false, 0, 2}, // native 5C
    {0x05d0, true, false, true, false, false, false, false, false, 0, 2}, // native 5D
    {0x05e0, true, false, true, false, false, false, false, false, 0, 2}, // native 5E
    {0x05f0, true, false, true, false, false, false, false, false, 0, 2}, // native 5F
    {0x0600, true, false, true, false, false, false, false, false, 0, 2}, // native 60
    {0x0610, true, false, true, false, false, false, false, false, 0, 2}, // native 61
    {0x0620, true, true, true, false, false, false, false, false, 0, 2}, // native 62
    {0x0630, true, true, true, false, false, false, false, false, 0, 2}, // native 63
    {0x0640, true, false, true, false, false, false, false, true, 9, 2}, // native 64
    {0x0650, true, false, true, false, false, false, false, true, 8, 2}, // native 65
    {0x0660, true, true, true, false, false, false, false, false, 0, 2}, // native 66
    {0x0670, true, true, true, false, false, false, false, false, 0, 2}, // native 67
    {0x0680, true, false, true, false, false, false, false, false, 0, 2}, // native 68
    {0x0690, true, true, true, false, false, false, false, false, 4, 2}, // native 69
    {0x06a0, true, false, true, false, false, false, false, false, 0, 2}, // native 6A
    {0x06b0, true, true, true, false, false, false, false, false, 4, 2}, // native 6B
    {0x06c0, false, false, true, false, false, false, false, false, 6, 2}, // native 6C
    {0x06d0, true, false, true, false, false, false, false, false, 6, 2}, // native 6D
    {0x06e0, false, false, true, false, false, false, false, false, 6, 2}, // native 6E
    {0x06f0, true, false, true, false, false, false, false, false, 6, 2}, // native 6F
    {0x0700, true, false, true, false, false, false, false, false, 0, 2}, // native 70
    {0x0710, true, false, true, false, false, false, false, false, 0, 2}, // native 71
    {0x0720, true, false, true, false, false, false, false, false, 0, 2}, // native 72
    {0x0730, true, false, true, false, false, false, false, false, 0, 2}, // native 73
    {0x0740, true, false, true, false, false, false, false, false, 0, 2}, // native 74
    {0x0750, true, false, true, false, false, false, false, false, 0, 2}, // native 75
    {0x0760, true, false, true, false, false, false, false, false, 0, 2}, // native 76
    {0x0770, true, false, true, false, false, false, false, false, 0, 2}, // native 77
    {0x0780, true, false, true, false, false, false, false, false, 0, 2}, // native 78
    {0x0790, true, false, true, false, false, false, false, false, 0, 2}, // native 79
    {0x07a0, true, false, true, false, false, false, false, false, 0, 2}, // native 7A
    {0x07b0, true, false, true, false, false, false, false, false, 0, 2}, // native 7B
    {0x07c0, true, false, true, false, false, false, false, false, 0, 2}, // native 7C
    {0x07d0, true, false, true, false, false, false, false, false, 0, 2}, // native 7D
    {0x07e0, true, false, true, false, false, false, false, false, 0, 2}, // native 7E
    {0x07f0, true, false, true, false, false, false, false, false, 0, 2}, // native 7F
    {0x0800, false, true, true, false, false, false, false, false, 4, 0}, // native 80
    {0x0810, true, true, true, false, false, false, false, false, 4, 0}, // native 81
    {0x0820, false, true, true, false, false, false, false, false, 4, 0}, // native 82
    {0x0830, true, true, true, false, false, false, false, false, 4, 0}, // native 83
    {0x0840, false, true, true, false, false, false, false, false, 4, 2}, // native 84
    {0x0850, true, true, true, false, false, false, false, false, 4, 2}, // native 85
    {0x0860, false, true, true, false, false, false, false, false, 4, 2}, // native 86
    {0x0870, true, true, true, false, false, false, false, false, 4, 2}, // native 87
    {0x0880, false, true, false, false, false, false, false, false, 0, 2}, // native 88
    {0x0890, true, true, false, false, false, false, false, false, 0, 2}, // native 89
    {0x08a0, false, true, true, false, true, false, false, false, 0, 2}, // native 8A
    {0x08b0, true, true, true, false, true, false, false, false, 0, 2}, // native 8B
    {0x08c0, true, true, false, true, false, false, true, false, 1, 2}, // native 8C
    {0x08d0, true, true, false, false, false, false, false, false, 0, 2}, // native 8D
    {0x08e0, true, true, true, false, true, false, true, false, 1, 2}, // native 8E
    {0x08f0, true, true, false, false, false, false, false, false, 0, 2}, // native 8F
    {0x0900, true, false, true, false, false, false, false, false, 0, 2}, // native 90
    {0x0910, true, false, true, false, false, false, false, false, 0, 2}, // native 91
    {0x0920, true, false, true, false, false, false, false, false, 0, 2}, // native 92
    {0x0930, true, false, true, false, false, false, false, false, 0, 2}, // native 93
    {0x0940, true, false, true, false, false, false, false, false, 0, 2}, // native 94
    {0x0950, true, false, true, false, false, false, false, false, 0, 2}, // native 95
    {0x0960, true, false, true, false, false, false, false, false, 0, 2}, // native 96
    {0x0970, true, false, true, false, false, false, false, false, 0, 2}, // native 97
    {0x0980, true, false, true, false, false, false, false, false, 0, 2}, // native 98
    {0x0990, true, false, true, false, false, false, false, false, 0, 2}, // native 99
    {0x09a0, true, false, true, false, false, false, false, false, 0, 2}, // native 9A
    {0x09b0, true, false, true, false, false, false, false, false, 0, 2}, // native 9B
    {0x09c0, true, false, true, false, false, false, false, false, 0, 2}, // native 9C
    {0x09d0, true, false, true, false, false, false, false, false, 0, 2}, // native 9D
    {0x09e0, true, false, true, false, false, false, false, false, 0, 2}, // native 9E
    {0x09f0, true, false, true, false, false, false, false, false, 0, 2}, // native 9F
    {0x0a00, false, false, true, false, false, true, false, false, 0, 2}, // native A0
    {0x0a10, true, false, true, false, false, true, false, false, 0, 2}, // native A1
    {0x0a20, false, false, true, false, false, true, false, false, 0, 2}, // native A2
    {0x0a30, true, false, true, false, false, true, false, false, 0, 2}, // native A3
    {0x0a40, false, false, true, false, false, true, false, false, 0, 2}, // native A4
    {0x0a50, true, false, true, false, false, true, false, false, 0, 2}, // native A5
    {0x0a60, false, false, true, false, false, true, false, false, 14, 2}, // native A6
    {0x0a70, true, false, true, false, false, true, false, false, 14, 2}, // native A7
    {0x0a80, false, false, true, false, false, true, false, false, 0, 2}, // native A8
    {0x0a90, true, false, true, false, false, true, false, false, 0, 2}, // native A9
    {0x0aa0, false, false, true, false, false, true, false, false, 0, 2}, // native AA
    {0x0ab0, true, false, true, false, false, true, false, false, 0, 2}, // native AB
    {0x0ac0, false, false, true, false, false, true, false, false, 0, 2}, // native AC
    {0x0ad0, true, false, true, false, false, true, false, false, 0, 2}, // native AD
    {0x0ae0, false, false, true, false, false, true, false, false, 14, 2}, // native AE
    {0x0af0, true, false, true, false, false, true, false, false, 14, 2}, // native AF
    {0x0b00, false, false, true, false, false, false, false, false, 0, 2}, // native B0
    {0x0b10, false, false, true, false, false, false, false, false, 0, 2}, // native B1
    {0x0b20, false, false, true, false, false, false, false, false, 0, 2}, // native B2
    {0x0b30, false, false, true, false, false, false, false, false, 0, 2}, // native B3
    {0x0b40, false, false, true, false, false, false, false, false, 0, 2}, // native B4
    {0x0b50, false, false, true, false, false, false, false, false, 0, 2}, // native B5
    {0x0b60, false, false, true, false, false, false, false, false, 0, 2}, // native B6
    {0x0b70, false, false, true, false, false, false, false, false, 0, 2}, // native B7
    {0x0b80, true, false, true, false, false, false, false, false, 0, 2}, // native B8
    {0x0b90, true, false, true, false, false, false, false, false, 0, 2}, // native B9
    {0x0ba0, true, false, true, false, false, false, false, false, 0, 2}, // native BA
    {0x0bb0, true, false, true, false, false, false, false, false, 0, 2}, // native BB
    {0x0bc0, true, false, true, false, false, false, false, false, 0, 2}, // native BC
    {0x0bd0, true, false, true, false, false, false, false, false, 0, 2}, // native BD
    {0x0be0, true, false, true, false, false, false, false, false, 0, 2}, // native BE
    {0x0bf0, true, false, true, false, false, false, false, false, 0, 2}, // native BF
    {0x0c00, false, true, true, false, false, false, false, false, 14, 3}, // native C0
    {0x0c10, true, true, true, false, false, false, false, false, 14, 3}, // native C1
    {0x0c20, true, false, true, false, false, false, false, false, 0, 2}, // native C2
    {0x0c30, true, false, true, false, false, false, false, false, 0, 2}, // native C3
    {0x0c40, true, true, true, false, false, false, false, false, 0, 2}, // native C4
    {0x0c50, true, true, true, false, false, false, false, false, 0, 2}, // native C5
    {0x0c60, false, true, false, false, false, false, false, false, 0, 2}, // native C6
    {0x0c70, true, true, false, false, false, false, false, false, 0, 2}, // native C7
    {0x0c80, true, false, true, false, false, false, false, false, 0, 2}, // native C8
    {0x0c90, true, false, true, false, false, false, false, false, 0, 2}, // native C9
    {0x0ca0, true, false, true, false, false, false, false, false, 0, 2}, // native CA
    {0x0cb0, true, false, true, false, false, false, false, false, 0, 2}, // native CB
    {0x0cc0, true, false, true, false, false, false, false, false, 0, 2}, // native CC
    {0x0cd0, true, false, true, false, false, false, false, false, 0, 2}, // native CD
    {0x0ce0, true, false, true, false, false, false, false, false, 0, 2}, // native CE
    {0x0cf0, true, false, true, false, false, false, false, false, 0, 2}, // native CF
    {0x0d00, false, true, true, false, false, false, false, false, 0, 3}, // native D0
    {0x0d10, true, true, true, false, false, false, false, false, 0, 3}, // native D1
    {0x0d20, false, true, true, false, false, false, false, false, 0, 3}, // native D2
    {0x0d30, true, true, true, false, false, false, false, false, 0, 3}, // native D3
    {0x0d40, false, false, true, false, false, false, false, false, 0, 2}, // native D4
    {0x0d50, false, false, true, false, false, false, false, false, 0, 2}, // native D5
    {0x0d60, false, false, true, false, false, false, false, false, 0, 2}, // native D6
    {0x0d70, false, false, true, false, false, false, false, false, 0, 2}, // native D7
    {0x0d80, true, true, true, false, false, false, false, false, 0, 2}, // native D8
    {0x0d90, true, true, true, false, false, false, false, false, 0, 2}, // native D9
    {0x0da0, true, true, true, false, false, false, false, false, 0, 2}, // native DA
    {0x0db0, true, true, true, false, false, false, false, false, 0, 2}, // native DB
    {0x0dc0, true, true, true, false, false, false, false, false, 0, 2}, // native DC
    {0x0dd0, true, true, true, false, false, false, false, false, 0, 2}, // native DD
    {0x0de0, true, true, true, false, false, false, false, false, 0, 2}, // native DE
    {0x0df0, true, true, true, false, false, false, false, false, 0, 2}, // native DF
    {0x0e00, false, false, true, false, false, false, false, false, 14, 2}, // native E0
    {0x0e10, true, false, true, false, false, false, false, false, 14, 2}, // native E1
    {0x0e20, true, false, true, false, false, false, false, false, 0, 2}, // native E2
    {0x0e30, true, false, true, false, false, false, false, false, 0, 2}, // native E3
    {0x0e40, false, false, true, false, false, true, false, false, 15, 2}, // native E4
    {0x0e50, true, false, true, false, false, true, false, false, 15, 2}, // native E5
    {0x0e60, false, false, true, false, false, true, false, false, 15, 2}, // native E6
    {0x0e70, true, false, true, false, false, true, false, false, 15, 2}, // native E7
    {0x0e80, true, false, true, false, false, false, false, false, 0, 2}, // native E8
    {0x0e90, true, false, true, false, false, false, false, false, 0, 2}, // native E9
    {0x0ea0, true, false, true, false, false, false, false, false, 0, 2}, // native EA
    {0x0eb0, true, false, true, false, false, false, false, false, 0, 2}, // native EB
    {0x0ec0, false, false, true, false, false, true, false, false, 15, 2}, // native EC
    {0x0ed0, true, false, true, false, false, true, false, false, 15, 2}, // native ED
    {0x0ee0, false, false, true, false, false, true, false, false, 15, 2}, // native EE
    {0x0ef0, true, false, true, false, false, true, false, false, 15, 2}, // native EF
    {0x0f00, true, false, true, false, false, false, false, true, 15, 2}, // native F0
    {0x0f10, true, false, true, false, false, false, false, true, 14, 2}, // native F1
    {0x0f20, true, false, true, false, false, false, false, true, 13, 2}, // native F2
    {0x0f30, true, false, true, false, false, false, false, true, 12, 2}, // native F3
    {0x0f40, true, false, true, false, false, false, false, true, 11, 2}, // native F4
    {0x0f50, true, false, true, false, false, false, false, true, 10, 2}, // native F5
    {0x0f60, false, true, true, false, false, false, false, false, 11, 4}, // native F6
    {0x0f70, true, true, true, false, false, false, false, false, 11, 4}, // native F7
    {0x0f80, true, false, true, false, false, false, false, true, 7, 2}, // native F8
    {0x0f90, true, false, true, false, false, false, false, true, 6, 2}, // native F9
    {0x0fa0, true, false, true, false, false, false, false, true, 5, 2}, // native FA
    {0x0fb0, true, false, true, false, false, false, false, true, 4, 2}, // native FB
    {0x0fc0, true, false, true, false, false, false, false, true, 3, 2}, // native FC
    {0x0fd0, true, false, true, false, false, false, false, true, 2, 2}, // native FD
    {0x0fe0, false, true, true, false, false, false, false, false, 11, 5}, // native FE
    {0x0ff0, true, true, true, false, false, false, false, false, 11, 5}, // native FF
    {0x4000, true, false, true, false, false, false, false, false, 0, 2}, // 0F 00
    {0x4010, true, false, true, false, false, false, false, false, 0, 2}, // 0F 01
    {0x4020, true, false, true, false, false, false, false, false, 0, 2}, // 0F 02
    {0x4030, true, false, true, false, false, false, false, false, 0, 2}, // 0F 03
    {0x4040, true, false, true, false, false, false, false, false, 0, 2}, // 0F 04
    {0x4050, true, false, true, false, false, false, false, false, 0, 2}, // 0F 05
    {0x4060, true, false, true, false, false, false, false, false, 0, 2}, // 0F 06
    {0x4070, true, false, true, false, false, false, false, false, 0, 2}, // 0F 07
    {0x4080, true, false, true, false, false, false, false, false, 0, 2}, // 0F 08
    {0x4090, true, false, true, false, false, false, false, false, 0, 2}, // 0F 09
    {0x40a0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 0A
    {0x40b0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 0B
    {0x40c0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 0C
    {0x40d0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 0D
    {0x40e0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 0E
    {0x40f0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 0F
    {0x4100, false, true, true, false, false, false, false, false, 0, 2}, // 0F 10
    {0x4110, true, true, true, false, false, false, false, false, 0, 2}, // 0F 11
    {0x4120, false, true, true, false, false, false, false, false, 0, 2}, // 0F 12
    {0x4130, true, true, true, false, false, false, false, false, 0, 2}, // 0F 13
    {0x4140, false, true, true, false, false, false, false, false, 0, 2}, // 0F 14
    {0x4150, true, true, true, false, false, false, false, false, 0, 2}, // 0F 15
    {0x4160, false, true, true, false, false, false, false, false, 0, 2}, // 0F 16
    {0x4170, true, true, true, false, false, false, false, false, 0, 2}, // 0F 17
    {0x4180, false, true, true, false, false, false, false, false, 0, 2}, // 0F 18
    {0x4190, true, true, true, false, false, false, false, false, 0, 2}, // 0F 19
    {0x41a0, false, true, true, false, false, false, false, false, 0, 2}, // 0F 1A
    {0x41b0, true, true, true, false, false, false, false, false, 0, 2}, // 0F 1B
    {0x41c0, false, true, true, false, false, false, false, false, 0, 2}, // 0F 1C
    {0x41d0, true, true, true, false, false, false, false, false, 0, 2}, // 0F 1D
    {0x41e0, false, true, true, false, false, false, false, false, 0, 2}, // 0F 1E
    {0x41f0, true, true, true, false, false, false, false, false, 0, 2}, // 0F 1F
    {0x4200, false, false, true, false, false, false, false, false, 10, 2}, // 0F 20
    {0x4210, false, false, true, false, false, false, false, false, 10, 2}, // 0F 21
    {0x4220, false, false, true, false, false, false, false, false, 10, 2}, // 0F 22
    {0x4230, false, false, true, false, false, false, false, false, 10, 2}, // 0F 23
    {0x4240, false, false, true, false, false, false, false, false, 10, 2}, // 0F 24
    {0x4250, false, false, true, false, false, false, false, false, 10, 2}, // 0F 25
    {0x4260, false, false, true, false, false, false, false, false, 10, 2}, // 0F 26
    {0x4270, false, false, true, false, false, false, false, false, 10, 2}, // 0F 27
    {0x4280, false, true, true, false, false, false, false, false, 0, 2}, // 0F 28
    {0x4290, true, true, false, false, false, false, false, false, 0, 2}, // 0F 29
    {0x42a0, false, true, true, false, false, false, false, false, 0, 2}, // 0F 2A
    {0x42b0, true, true, false, false, false, false, false, false, 0, 2}, // 0F 2B
    {0x42c0, false, true, false, false, false, false, false, false, 0, 2}, // 0F 2C
    {0x42d0, true, true, false, false, false, false, false, false, 0, 2}, // 0F 2D
    {0x42e0, false, true, false, false, false, false, false, false, 0, 2}, // 0F 2E
    {0x42f0, true, true, false, false, false, false, false, false, 0, 2}, // 0F 2F
    {0x4300, false, true, false, false, false, true, false, false, 3, 2}, // 0F 30
    {0x4310, true, true, false, false, false, true, false, false, 3, 2}, // 0F 31
    {0x4320, false, true, false, false, false, true, false, false, 3, 2}, // 0F 32
    {0x4330, true, true, false, false, false, true, false, false, 3, 2}, // 0F 33
    {0x4340, false, true, false, false, false, true, false, false, 3, 2}, // 0F 34
    {0x4350, true, true, false, false, false, true, false, false, 3, 2}, // 0F 35
    {0x4360, false, true, false, false, false, true, false, false, 3, 2}, // 0F 36
    {0x4370, true, true, false, false, false, true, false, false, 3, 2}, // 0F 37
    {0x4380, false, true, false, false, false, true, false, false, 3, 2}, // 0F 38
    {0x4390, true, true, false, false, false, true, false, false, 3, 2}, // 0F 39
    {0x43a0, false, true, false, false, false, true, false, false, 3, 2}, // 0F 3A
    {0x43b0, true, true, false, false, false, true, false, false, 3, 2}, // 0F 3B
    {0x43c0, false, true, false, false, false, true, false, false, 3, 2}, // 0F 3C
    {0x43d0, true, true, false, false, false, true, false, false, 3, 2}, // 0F 3D
    {0x43e0, false, true, false, false, false, true, false, false, 3, 2}, // 0F 3E
    {0x43f0, true, true, false, false, false, true, false, false, 3, 2}, // 0F 3F
    {0x4400, true, false, true, false, false, false, false, false, 0, 2}, // 0F 40
    {0x4410, true, false, true, false, false, false, false, false, 0, 2}, // 0F 41
    {0x4420, true, false, true, false, false, false, false, false, 0, 2}, // 0F 42
    {0x4430, true, false, true, false, false, false, false, false, 0, 2}, // 0F 43
    {0x4440, true, false, true, false, false, false, false, false, 0, 2}, // 0F 44
    {0x4450, true, false, true, false, false, false, false, false, 0, 2}, // 0F 45
    {0x4460, true, false, true, false, false, false, false, false, 0, 2}, // 0F 46
    {0x4470, true, false, true, false, false, false, false, false, 0, 2}, // 0F 47
    {0x4480, true, false, true, false, false, false, false, false, 0, 2}, // 0F 48
    {0x4490, true, false, true, false, false, false, false, false, 0, 2}, // 0F 49
    {0x44a0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 4A
    {0x44b0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 4B
    {0x44c0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 4C
    {0x44d0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 4D
    {0x44e0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 4E
    {0x44f0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 4F
    {0x4500, true, false, true, false, false, false, false, false, 0, 2}, // 0F 50
    {0x4510, true, false, true, false, false, false, false, false, 0, 2}, // 0F 51
    {0x4520, true, false, true, false, false, false, false, false, 0, 2}, // 0F 52
    {0x4530, true, false, true, false, false, false, false, false, 0, 2}, // 0F 53
    {0x4540, true, false, true, false, false, false, false, false, 0, 2}, // 0F 54
    {0x4550, true, false, true, false, false, false, false, false, 0, 2}, // 0F 55
    {0x4560, true, false, true, false, false, false, false, false, 0, 2}, // 0F 56
    {0x4570, true, false, true, false, false, false, false, false, 0, 2}, // 0F 57
    {0x4580, true, false, true, false, false, false, false, false, 0, 2}, // 0F 58
    {0x4590, true, false, true, false, false, false, false, false, 0, 2}, // 0F 59
    {0x45a0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 5A
    {0x45b0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 5B
    {0x45c0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 5C
    {0x45d0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 5D
    {0x45e0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 5E
    {0x45f0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 5F
    {0x4600, true, false, true, false, false, false, false, false, 0, 2}, // 0F 60
    {0x4610, true, false, true, false, false, false, false, false, 0, 2}, // 0F 61
    {0x4620, true, false, true, false, false, false, false, false, 0, 2}, // 0F 62
    {0x4630, true, false, true, false, false, false, false, false, 0, 2}, // 0F 63
    {0x4640, true, false, true, false, false, false, false, false, 0, 2}, // 0F 64
    {0x4650, true, false, true, false, false, false, false, false, 0, 2}, // 0F 65
    {0x4660, true, false, true, false, false, false, false, false, 0, 2}, // 0F 66
    {0x4670, true, false, true, false, false, false, false, false, 0, 2}, // 0F 67
    {0x4680, true, false, true, false, false, false, false, false, 0, 2}, // 0F 68
    {0x4690, true, false, true, false, false, false, false, false, 0, 2}, // 0F 69
    {0x46a0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 6A
    {0x46b0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 6B
    {0x46c0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 6C
    {0x46d0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 6D
    {0x46e0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 6E
    {0x46f0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 6F
    {0x4700, true, false, true, false, false, false, false, false, 0, 2}, // 0F 70
    {0x4710, true, false, true, false, false, false, false, false, 0, 2}, // 0F 71
    {0x4720, true, false, true, false, false, false, false, false, 0, 2}, // 0F 72
    {0x4730, true, false, true, false, false, false, false, false, 0, 2}, // 0F 73
    {0x4740, true, false, true, false, false, false, false, false, 0, 2}, // 0F 74
    {0x4750, true, false, true, false, false, false, false, false, 0, 2}, // 0F 75
    {0x4760, true, false, true, false, false, false, false, false, 0, 2}, // 0F 76
    {0x4770, true, false, true, false, false, false, false, false, 0, 2}, // 0F 77
    {0x4780, true, false, true, false, false, false, false, false, 0, 2}, // 0F 78
    {0x4790, true, false, true, false, false, false, false, false, 0, 2}, // 0F 79
    {0x47a0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 7A
    {0x47b0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 7B
    {0x47c0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 7C
    {0x47d0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 7D
    {0x47e0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 7E
    {0x47f0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 7F
    {0x4800, true, false, true, false, false, false, false, false, 0, 2}, // 0F 80
    {0x4810, true, false, true, false, false, false, false, false, 0, 2}, // 0F 81
    {0x4820, true, false, true, false, false, false, false, false, 0, 2}, // 0F 82
    {0x4830, true, false, true, false, false, false, false, false, 0, 2}, // 0F 83
    {0x4840, true, false, true, false, false, false, false, false, 0, 2}, // 0F 84
    {0x4850, true, false, true, false, false, false, false, false, 0, 2}, // 0F 85
    {0x4860, true, false, true, false, false, false, false, false, 0, 2}, // 0F 86
    {0x4870, true, false, true, false, false, false, false, false, 0, 2}, // 0F 87
    {0x4880, true, false, true, false, false, false, false, false, 0, 2}, // 0F 88
    {0x4890, true, false, true, false, false, false, false, false, 0, 2}, // 0F 89
    {0x48a0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 8A
    {0x48b0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 8B
    {0x48c0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 8C
    {0x48d0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 8D
    {0x48e0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 8E
    {0x48f0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 8F
    {0x4900, true, false, true, false, false, false, false, false, 0, 2}, // 0F 90
    {0x4910, true, false, true, false, false, false, false, false, 0, 2}, // 0F 91
    {0x4920, true, false, true, false, false, false, false, false, 0, 2}, // 0F 92
    {0x4930, true, false, true, false, false, false, false, false, 0, 2}, // 0F 93
    {0x4940, true, false, true, false, false, false, false, false, 0, 2}, // 0F 94
    {0x4950, true, false, true, false, false, false, false, false, 0, 2}, // 0F 95
    {0x4960, true, false, true, false, false, false, false, false, 0, 2}, // 0F 96
    {0x4970, true, false, true, false, false, false, false, false, 0, 2}, // 0F 97
    {0x4980, true, false, true, false, false, false, false, false, 0, 2}, // 0F 98
    {0x4990, true, false, true, false, false, false, false, false, 0, 2}, // 0F 99
    {0x49a0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 9A
    {0x49b0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 9B
    {0x49c0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 9C
    {0x49d0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 9D
    {0x49e0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 9E
    {0x49f0, true, false, true, false, false, false, false, false, 0, 2}, // 0F 9F
    {0x4a00, true, false, true, false, false, false, false, false, 0, 2}, // 0F A0
    {0x4a10, true, false, true, false, false, false, false, false, 0, 2}, // 0F A1
    {0x4a20, true, false, true, false, false, false, false, false, 0, 2}, // 0F A2
    {0x4a30, true, false, true, false, false, false, false, false, 0, 2}, // 0F A3
    {0x4a40, true, false, true, false, false, false, false, false, 0, 2}, // 0F A4
    {0x4a50, true, false, true, false, false, false, false, false, 0, 2}, // 0F A5
    {0x4a60, true, false, true, false, false, false, false, false, 0, 2}, // 0F A6
    {0x4a70, true, false, true, false, false, false, false, false, 0, 2}, // 0F A7
    {0x4a80, true, false, true, false, false, false, false, false, 0, 2}, // 0F A8
    {0x4a90, true, false, true, false, false, false, false, false, 0, 2}, // 0F A9
    {0x4aa0, true, false, true, false, false, false, false, false, 0, 2}, // 0F AA
    {0x4ab0, true, false, true, false, false, false, false, false, 0, 2}, // 0F AB
    {0x4ac0, true, false, true, false, false, false, false, false, 0, 2}, // 0F AC
    {0x4ad0, true, false, true, false, false, false, false, false, 0, 2}, // 0F AD
    {0x4ae0, true, false, true, false, false, false, false, false, 0, 2}, // 0F AE
    {0x4af0, true, false, true, false, false, false, false, false, 0, 2}, // 0F AF
    {0x4b00, true, false, true, false, false, false, false, false, 0, 2}, // 0F B0
    {0x4b10, true, false, true, false, false, false, false, false, 0, 2}, // 0F B1
    {0x4b20, true, false, true, false, false, false, false, false, 0, 2}, // 0F B2
    {0x4b30, true, false, true, false, false, false, false, false, 0, 2}, // 0F B3
    {0x4b40, true, false, true, false, false, false, false, false, 0, 2}, // 0F B4
    {0x4b50, true, false, true, false, false, false, false, false, 0, 2}, // 0F B5
    {0x4b60, true, false, true, false, false, false, false, false, 0, 2}, // 0F B6
    {0x4b70, true, false, true, false, false, false, false, false, 0, 2}, // 0F B7
    {0x4b80, true, false, true, false, false, false, false, false, 0, 2}, // 0F B8
    {0x4b90, true, false, true, false, false, false, false, false, 0, 2}, // 0F B9
    {0x4ba0, true, false, true, false, false, false, false, false, 0, 2}, // 0F BA
    {0x4bb0, true, false, true, false, false, false, false, false, 0, 2}, // 0F BB
    {0x4bc0, true, false, true, false, false, false, false, false, 0, 2}, // 0F BC
    {0x4bd0, true, false, true, false, false, false, false, false, 0, 2}, // 0F BD
    {0x4be0, true, false, true, false, false, false, false, false, 0, 2}, // 0F BE
    {0x4bf0, true, false, true, false, false, false, false, false, 0, 2}, // 0F BF
    {0x4c00, true, false, true, false, false, false, false, false, 0, 2}, // 0F C0
    {0x4c10, true, false, true, false, false, false, false, false, 0, 2}, // 0F C1
    {0x4c20, true, false, true, false, false, false, false, false, 0, 2}, // 0F C2
    {0x4c30, true, false, true, false, false, false, false, false, 0, 2}, // 0F C3
    {0x4c40, true, false, true, false, false, false, false, false, 0, 2}, // 0F C4
    {0x4c50, true, false, true, false, false, false, false, false, 0, 2}, // 0F C5
    {0x4c60, true, false, true, false, false, false, false, false, 0, 2}, // 0F C6
    {0x4c70, true, false, true, false, false, false, false, false, 0, 2}, // 0F C7
    {0x4c80, true, false, true, false, false, false, false, false, 0, 2}, // 0F C8
    {0x4c90, true, false, true, false, false, false, false, false, 0, 2}, // 0F C9
    {0x4ca0, true, false, true, false, false, false, false, false, 0, 2}, // 0F CA
    {0x4cb0, true, false, true, false, false, false, false, false, 0, 2}, // 0F CB
    {0x4cc0, true, false, true, false, false, false, false, false, 0, 2}, // 0F CC
    {0x4cd0, true, false, true, false, false, false, false, false, 0, 2}, // 0F CD
    {0x4ce0, true, false, true, false, false, false, false, false, 0, 2}, // 0F CE
    {0x4cf0, true, false, true, false, false, false, false, false, 0, 2}, // 0F CF
    {0x4d00, true, false, true, false, false, false, false, false, 0, 2}, // 0F D0
    {0x4d10, true, false, true, false, false, false, false, false, 0, 2}, // 0F D1
    {0x4d20, true, false, true, false, false, false, false, false, 0, 2}, // 0F D2
    {0x4d30, true, false, true, false, false, false, false, false, 0, 2}, // 0F D3
    {0x4d40, true, false, true, false, false, false, false, false, 0, 2}, // 0F D4
    {0x4d50, true, false, true, false, false, false, false, false, 0, 2}, // 0F D5
    {0x4d60, true, false, true, false, false, false, false, false, 0, 2}, // 0F D6
    {0x4d70, true, false, true, false, false, false, false, false, 0, 2}, // 0F D7
    {0x4d80, true, false, true, false, false, false, false, false, 0, 2}, // 0F D8
    {0x4d90, true, false, true, false, false, false, false, false, 0, 2}, // 0F D9
    {0x4da0, true, false, true, false, false, false, false, false, 0, 2}, // 0F DA
    {0x4db0, true, false, true, false, false, false, false, false, 0, 2}, // 0F DB
    {0x4dc0, true, false, true, false, false, false, false, false, 0, 2}, // 0F DC
    {0x4dd0, true, false, true, false, false, false, false, false, 0, 2}, // 0F DD
    {0x4de0, true, false, true, false, false, false, false, false, 0, 2}, // 0F DE
    {0x4df0, true, false, true, false, false, false, false, false, 0, 2}, // 0F DF
    {0x4e00, true, false, true, false, false, false, false, false, 0, 2}, // 0F E0
    {0x4e10, true, false, true, false, false, false, false, false, 0, 2}, // 0F E1
    {0x4e20, true, false, true, false, false, false, false, false, 0, 2}, // 0F E2
    {0x4e30, true, false, true, false, false, false, false, false, 0, 2}, // 0F E3
    {0x4e40, true, false, true, false, false, false, false, false, 0, 2}, // 0F E4
    {0x4e50, true, false, true, false, false, false, false, false, 0, 2}, // 0F E5
    {0x4e60, true, false, true, false, false, false, false, false, 0, 2}, // 0F E6
    {0x4e70, true, false, true, false, false, false, false, false, 0, 2}, // 0F E7
    {0x4e80, true, false, true, false, false, false, false, false, 0, 2}, // 0F E8
    {0x4e90, true, false, true, false, false, false, false, false, 0, 2}, // 0F E9
    {0x4ea0, true, false, true, false, false, false, false, false, 0, 2}, // 0F EA
    {0x4eb0, true, false, true, false, false, false, false, false, 0, 2}, // 0F EB
    {0x4ec0, true, false, true, false, false, false, false, false, 0, 2}, // 0F EC
    {0x4ed0, true, false, true, false, false, false, false, false, 0, 2}, // 0F ED
    {0x4ee0, true, false, true, false, false, false, false, false, 0, 2}, // 0F EE
    {0x4ef0, true, false, true, false, false, false, false, false, 0, 2}, // 0F EF
    {0x4f00, true, false, true, false, false, false, false, false, 0, 2}, // 0F F0
    {0x4f10, true, false, true, false, false, false, false, false, 0, 2}, // 0F F1
    {0x4f20, true, false, true, false, false, false, false, false, 0, 2}, // 0F F2
    {0x4f30, true, false, true, false, false, false, false, false, 0, 2}, // 0F F3
    {0x4f40, true, false, true, false, false, false, false, false, 0, 2}, // 0F F4
    {0x4f50, true, false, true, false, false, false, false, false, 0, 2}, // 0F F5
    {0x4f60, true, false, true, false, false, false, false, false, 0, 2}, // 0F F6
    {0x4f70, true, false, true, false, false, false, false, false, 0, 2}, // 0F F7
    {0x4f80, true, false, true, false, false, false, false, false, 0, 2}, // 0F F8
    {0x4f90, true, false, true, false, false, false, false, false, 0, 2}, // 0F F9
    {0x4fa0, true, false, true, false, false, false, false, false, 0, 2}, // 0F FA
    {0x4fb0, true, false, true, false, false, false, false, false, 0, 2}, // 0F FB
    {0x4fc0, true, false, true, false, false, false, false, false, 0, 2}, // 0F FC
    {0x4fd0, true, false, true, false, false, false, false, false, 0, 2}, // 0F FD
    {0x4fe0, true, false, true, false, false, false, false, false, 0, 2}, // 0F FE
    {0x4ff0, true, false, true, false, false, false, false, false, 0, 2}, // 0F FF
    {0x6000, true, false, true, false, false, false, false, false, 0, 0}, // 8080 00
    {0x6010, true, false, true, false, false, false, false, false, 0, 0}, // 8080 01
    {0x6020, false, false, true, false, false, false, false, false, 0, 0}, // 8080 02
    {0x6030, true, false, true, false, false, false, false, false, 0, 0}, // 8080 03
    {0x6040, false, false, true, false, false, false, false, false, 12, 0}, // 8080 04
    {0x6050, false, false, true, false, false, false, false, false, 12, 0}, // 8080 05
    {0x6060, false, false, true, false, true, false, false, false, 0, 0}, // 8080 06
    {0x6070, false, false, true, false, false, false, false, false, 0, 0}, // 8080 07
    {0x6080, true, false, true, false, false, false, false, false, 0, 0}, // 8080 08
    {0x6090, true, false, true, false, false, false, false, false, 13, 0}, // 8080 09
    {0x60a0, false, false, true, false, false, false, false, false, 0, 0}, // 8080 0A
    {0x60b0, true, false, true, false, false, false, false, false, 0, 0}, // 8080 0B
    {0x60c0, false, false, true, false, false, false, false, false, 12, 0}, // 8080 0C
    {0x60d0, false, false, true, false, false, false, false, false, 12, 0}, // 8080 0D
    {0x60e0, false, false, true, false, true, false, false, false, 0, 0}, // 8080 0E
    {0x60f0, false, false, true, false, false, false, false, false, 0, 0}, // 8080 0F
    {0x6100, true, false, true, false, false, false, false, false, 0, 0}, // 8080 10
    {0x6110, true, false, true, false, false, false, false, false, 0, 0}, // 8080 11
    {0x6120, false, false, true, false, false, false, false, false, 0, 0}, // 8080 12
    {0x6130, true, false, true, false, false, false, false, false, 0, 0}, // 8080 13
    {0x6140, false, false, true, false, false, false, false, false, 12, 0}, // 8080 14
    {0x6150, false, false, true, false, false, false, false, false, 12, 0}, // 8080 15
    {0x6160, false, false, true, false, true, false, false, false, 0, 0}, // 8080 16
    {0x6170, false, false, true, false, false, false, false, false, 0, 0}, // 8080 17
    {0x6180, true, false, true, false, false, false, false, false, 0, 0}, // 8080 18
    {0x6190, true, false, true, false, false, false, false, false, 13, 0}, // 8080 19
    {0x61a0, false, false, true, false, false, false, false, false, 0, 0}, // 8080 1A
    {0x61b0, true, false, true, false, false, false, false, false, 0, 0}, // 8080 1B
    {0x61c0, false, false, true, false, false, false, false, false, 12, 0}, // 8080 1C
    {0x61d0, false, false, true, false, false, false, false, false, 12, 0}, // 8080 1D
    {0x61e0, false, false, true, false, true, false, false, false, 0, 0}, // 8080 1E
    {0x61f0, false, false, true, false, false, false, false, false, 0, 0}, // 8080 1F
    {0x6200, true, false, true, false, false, false, false, false, 0, 0}, // 8080 20
    {0x6210, true, false, true, false, false, false, false, false, 0, 0}, // 8080 21
    {0x6220, true, false, true, false, false, false, false, false, 0, 0}, // 8080 22
    {0x6230, true, false, true, false, false, false, false, false, 0, 0}, // 8080 23
    {0x6240, false, false, true, false, false, false, false, false, 12, 0}, // 8080 24
    {0x6250, false, false, true, false, false, false, false, false, 12, 0}, // 8080 25
    {0x6260, false, false, true, false, true, false, false, false, 0, 0}, // 8080 26
    {0x6270, false, false, true, false, false, false, false, false, 10, 0}, // 8080 27
    {0x6280, true, false, true, false, false, false, false, false, 0, 0}, // 8080 28
    {0x6290, true, false, true, false, false, false, false, false, 13, 0}, // 8080 29
    {0x62a0, true, false, true, false, false, false, false, false, 0, 0}, // 8080 2A
    {0x62b0, true, false, true, false, false, false, false, false, 0, 0}, // 8080 2B
    {0x62c0, false, false, true, false, false, false, false, false, 12, 0}, // 8080 2C
    {0x62d0, false, false, true, false, false, false, false, false, 12, 0}, // 8080 2D
    {0x62e0, false, false, true, false, true, false, false, false, 0, 0}, // 8080 2E
    {0x62f0, true, false, true, false, false, false, false, false, 0, 0}, // 8080 2F
    {0x6300, true, false, true, false, false, false, false, false, 0, 0}, // 8080 30
    {0x6310, true, false, true, false, false, false, false, false, 0, 0}, // 8080 31
    {0x6320, false, false, true, false, false, false, false, false, 0, 0}, // 8080 32
    {0x6330, true, false, true, false, false, false, false, false, 0, 0}, // 8080 33
    {0x6340, false, false, true, false, false, false, false, false, 12, 0}, // 8080 34
    {0x6350, false, false, true, false, false, false, false, false, 12, 0}, // 8080 35
    {0x6360, false, false, true, false, true, false, false, false, 0, 0}, // 8080 36
    {0x6370, true, false, true, false, false, false, false, true, 6, 0}, // 8080 37
    {0x6380, true, false, true, false, false, false, false, false, 0, 0}, // 8080 38
    {0x6390, true, false, true, false, false, false, false, false, 13, 0}, // 8080 39
    {0x63a0, false, false, true, false, false, false, false, false, 0, 0}, // 8080 3A
    {0x63b0, true, false, true, false, false, false, false, false, 0, 0}, // 8080 3B
    {0x63c0, false, false, true, false, false, false, false, false, 12, 0}, // 8080 3C
    {0x63d0, false, false, true, false, false, false, false, false, 12, 0}, // 8080 3D
    {0x63e0, false, false, true, false, true, false, false, false, 0, 0}, // 8080 3E
    {0x63f0, true, false, true, false, false, false, false, true, 10, 0}, // 8080 3F
    {0x6400, false, false, true, false, false, false, false, false, 0, 1}, // 8080 40
    {0x6410, false, false, true, false, false, false, false, false, 0, 1}, // 8080 41
    {0x6420, false, false, true, false, false, false, false, false, 0, 1}, // 8080 42
    {0x6430, false, false, true, false, false, false, false, false, 0, 1}, // 8080 43
    {0x6440, false, false, true, false, false, false, false, false, 0, 1}, // 8080 44
    {0x6450, false, false, true, false, false, false, false, false, 0, 1}, // 8080 45
    {0x6460, false, false, true, false, false, false, false, false, 0, 1}, // 8080 46
    {0x6470, false, false, true, false, false, false, false, false, 0, 1}, // 8080 47
    {0x6480, false, false, true, false, false, false, false, false, 0, 1}, // 8080 48
    {0x6490, false, false, true, false, false, false, false, false, 0, 1}, // 8080 49
    {0x64a0, false, false, true, false, false, false, false, false, 0, 1}, // 8080 4A
    {0x64b0, false, false, true, false, false, false, false, false, 0, 1}, // 8080 4B
    {0x64c0, false, false, true, false, false, false, false, false, 0, 1}, // 8080 4C
    {0x64d0, false, false, true, false, false, false, false, false, 0, 1}, // 8080 4D
    {0x64e0, false, false, true, false, false, false, false, false, 0, 1}, // 8080 4E
    {0x64f0, false, false, true, false, false, false, false, false, 0, 1}, // 8080 4F
    {0x6500, false, false, true, false, false, false, false, false, 0, 2}, // 8080 50
    {0x6510, false, false, true, false, false, false, false, false, 0, 2}, // 8080 51
    {0x6520, false, false, true, false, false, false, false, false, 0, 2}, // 8080 52
    {0x6530, false, false, true, false, false, false, false, false, 0, 2}, // 8080 53
    {0x6540, false, false, true, false, false, false, false, false, 0, 2}, // 8080 54
    {0x6550, false, false, true, false, false, false, false, false, 0, 2}, // 8080 55
    {0x6560, false, false, true, false, false, false, false, false, 0, 2}, // 8080 56
    {0x6570, false, false, true, false, false, false, false, false, 0, 2}, // 8080 57
    {0x6580, false, false, true, false, false, false, false, false, 0, 2}, // 8080 58
    {0x6590, false, false, true, false, false, false, false, false, 0, 2}, // 8080 59
    {0x65a0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 5A
    {0x65b0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 5B
    {0x65c0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 5C
    {0x65d0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 5D
    {0x65e0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 5E
    {0x65f0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 5F
    {0x6600, false, false, true, false, false, false, false, false, 0, 2}, // 8080 60
    {0x6610, false, false, true, false, false, false, false, false, 0, 2}, // 8080 61
    {0x6620, false, false, true, false, false, false, false, false, 0, 2}, // 8080 62
    {0x6630, false, false, true, false, false, false, false, false, 0, 2}, // 8080 63
    {0x6640, false, false, true, false, false, false, false, false, 0, 2}, // 8080 64
    {0x6650, false, false, true, false, false, false, false, false, 0, 2}, // 8080 65
    {0x6660, false, false, true, false, false, false, false, false, 0, 2}, // 8080 66
    {0x6670, false, false, true, false, false, false, false, false, 0, 2}, // 8080 67
    {0x6680, false, false, true, false, false, false, false, false, 0, 2}, // 8080 68
    {0x6690, false, false, true, false, false, false, false, false, 0, 2}, // 8080 69
    {0x66a0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 6A
    {0x66b0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 6B
    {0x66c0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 6C
    {0x66d0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 6D
    {0x66e0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 6E
    {0x66f0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 6F
    {0x6700, false, false, true, false, false, false, false, false, 0, 2}, // 8080 70
    {0x6710, false, false, true, false, false, false, false, false, 0, 2}, // 8080 71
    {0x6720, false, false, true, false, false, false, false, false, 0, 2}, // 8080 72
    {0x6730, false, false, true, false, false, false, false, false, 0, 2}, // 8080 73
    {0x6740, false, false, true, false, false, false, false, false, 0, 2}, // 8080 74
    {0x6750, false, false, true, false, false, false, false, false, 0, 2}, // 8080 75
    {0x6760, false, false, true, false, false, false, false, true, 11, 2}, // 8080 76
    {0x6770, false, false, true, false, false, false, false, false, 0, 2}, // 8080 77
    {0x6780, false, false, true, false, false, false, false, false, 0, 2}, // 8080 78
    {0x6790, false, false, true, false, false, false, false, false, 0, 2}, // 8080 79
    {0x67a0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 7A
    {0x67b0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 7B
    {0x67c0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 7C
    {0x67d0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 7D
    {0x67e0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 7E
    {0x67f0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 7F
    {0x6800, false, false, true, false, false, false, false, false, 0, 0}, // 8080 80
    {0x6810, false, false, true, false, false, false, false, false, 0, 0}, // 8080 81
    {0x6820, false, false, true, false, false, false, false, false, 0, 0}, // 8080 82
    {0x6830, false, false, true, false, false, false, false, false, 0, 0}, // 8080 83
    {0x6840, false, false, true, false, false, false, false, false, 0, 2}, // 8080 84
    {0x6850, false, false, true, false, false, false, false, false, 0, 2}, // 8080 85
    {0x6860, false, false, true, false, false, false, false, false, 0, 2}, // 8080 86
    {0x6870, false, false, true, false, false, false, false, false, 0, 2}, // 8080 87
    {0x6880, false, false, true, false, false, false, false, false, 0, 2}, // 8080 88
    {0x6890, false, false, true, false, false, false, false, false, 0, 2}, // 8080 89
    {0x68a0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 8A
    {0x68b0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 8B
    {0x68c0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 8C
    {0x68d0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 8D
    {0x68e0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 8E
    {0x68f0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 8F
    {0x6900, false, false, true, false, false, false, false, false, 0, 2}, // 8080 90
    {0x6910, false, false, true, false, false, false, false, false, 0, 2}, // 8080 91
    {0x6920, false, false, true, false, false, false, false, false, 0, 2}, // 8080 92
    {0x6930, false, false, true, false, false, false, false, false, 0, 2}, // 8080 93
    {0x6940, false, false, true, false, false, false, false, false, 0, 2}, // 8080 94
    {0x6950, false, false, true, false, false, false, false, false, 0, 2}, // 8080 95
    {0x6960, false, false, true, false, false, false, false, false, 0, 2}, // 8080 96
    {0x6970, false, false, true, false, false, false, false, false, 0, 2}, // 8080 97
    {0x6980, false, false, true, false, false, false, false, false, 0, 2}, // 8080 98
    {0x6990, false, false, true, false, false, false, false, false, 0, 2}, // 8080 99
    {0x69a0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 9A
    {0x69b0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 9B
    {0x69c0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 9C
    {0x69d0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 9D
    {0x69e0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 9E
    {0x69f0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 9F
    {0x6a00, false, false, true, false, false, false, false, false, 0, 2}, // 8080 A0
    {0x6a10, false, false, true, false, false, false, false, false, 0, 2}, // 8080 A1
    {0x6a20, false, false, true, false, false, false, false, false, 0, 2}, // 8080 A2
    {0x6a30, false, false, true, false, false, false, false, false, 0, 2}, // 8080 A3
    {0x6a40, false, false, true, false, false, false, false, false, 0, 2}, // 8080 A4
    {0x6a50, false, false, true, false, false, false, false, false, 0, 2}, // 8080 A5
    {0x6a60, false, false, true, false, false, false, false, false, 0, 2}, // 8080 A6
    {0x6a70, false, false, true, false, false, false, false, false, 0, 2}, // 8080 A7
    {0x6a80, false, false, true, false, false, false, false, false, 0, 2}, // 8080 A8
    {0x6a90, false, false, true, false, false, false, false, false, 0, 2}, // 8080 A9
    {0x6aa0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 AA
    {0x6ab0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 AB
    {0x6ac0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 AC
    {0x6ad0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 AD
    {0x6ae0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 AE
    {0x6af0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 AF
    {0x6b00, false, false, true, false, false, false, false, false, 0, 2}, // 8080 B0
    {0x6b10, false, false, true, false, false, false, false, false, 0, 2}, // 8080 B1
    {0x6b20, false, false, true, false, false, false, false, false, 0, 2}, // 8080 B2
    {0x6b30, false, false, true, false, false, false, false, false, 0, 2}, // 8080 B3
    {0x6b40, false, false, true, false, false, false, false, false, 0, 2}, // 8080 B4
    {0x6b50, false, false, true, false, false, false, false, false, 0, 2}, // 8080 B5
    {0x6b60, false, false, true, false, false, false, false, false, 0, 2}, // 8080 B6
    {0x6b70, false, false, true, false, false, false, false, false, 0, 2}, // 8080 B7
    {0x6b80, false, false, true, false, false, false, false, false, 0, 2}, // 8080 B8
    {0x6b90, false, false, true, false, false, false, false, false, 0, 2}, // 8080 B9
    {0x6ba0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 BA
    {0x6bb0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 BB
    {0x6bc0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 BC
    {0x6bd0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 BD
    {0x6be0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 BE
    {0x6bf0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 BF
    {0x6c00, true, false, true, false, false, false, false, false, 0, 3}, // 8080 C0
    {0x6c10, true, false, true, false, false, false, false, false, 0, 3}, // 8080 C1
    {0x6c20, true, false, true, false, false, false, false, false, 0, 2}, // 8080 C2
    {0x6c30, true, false, true, false, false, false, false, false, 0, 2}, // 8080 C3
    {0x6c40, true, false, true, false, false, false, false, false, 0, 2}, // 8080 C4
    {0x6c50, true, false, true, false, false, false, false, false, 0, 2}, // 8080 C5
    {0x6c60, false, false, true, false, false, false, false, false, 0, 2}, // 8080 C6
    {0x6c70, true, false, true, false, false, false, false, false, 0, 2}, // 8080 C7
    {0x6c80, true, false, true, false, false, false, false, false, 0, 2}, // 8080 C8
    {0x6c90, true, false, true, false, false, false, false, false, 0, 2}, // 8080 C9
    {0x6ca0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 CA
    {0x6cb0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 CB
    {0x6cc0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 CC
    {0x6cd0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 CD
    {0x6ce0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 CE
    {0x6cf0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 CF
    {0x6d00, true, false, true, false, false, false, false, false, 0, 3}, // 8080 D0
    {0x6d10, true, false, true, false, false, false, false, false, 0, 3}, // 8080 D1
    {0x6d20, true, false, true, false, false, false, false, false, 0, 3}, // 8080 D2
    {0x6d30, false, false, true, false, false, false, false, false, 15, 3}, // 8080 D3
    {0x6d40, true, false, true, false, false, false, false, false, 0, 2}, // 8080 D4
    {0x6d50, true, false, true, false, false, false, false, false, 0, 2}, // 8080 D5
    {0x6d60, false, false, true, false, false, false, false, false, 0, 2}, // 8080 D6
    {0x6d70, true, false, true, false, false, false, false, false, 0, 2}, // 8080 D7
    {0x6d80, true, false, true, false, false, false, false, false, 0, 2}, // 8080 D8
    {0x6d90, true, false, true, false, false, false, false, false, 0, 2}, // 8080 D9
    {0x6da0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 DA
    {0x6db0, false, false, true, false, false, false, false, false, 15, 2}, // 8080 DB
    {0x6dc0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 DC
    {0x6dd0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 DD
    {0x6de0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 DE
    {0x6df0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 DF
    {0x6e00, true, false, true, false, false, false, false, false, 0, 2}, // 8080 E0
    {0x6e10, true, false, true, false, false, false, false, false, 0, 2}, // 8080 E1
    {0x6e20, true, false, true, false, false, false, false, false, 0, 2}, // 8080 E2
    {0x6e30, true, false, true, false, false, false, false, false, 0, 2}, // 8080 E3
    {0x6e40, true, false, true, false, false, false, false, false, 0, 2}, // 8080 E4
    {0x6e50, true, false, true, false, false, false, false, false, 0, 2}, // 8080 E5
    {0x6e60, false, false, true, false, false, false, false, false, 0, 2}, // 8080 E6
    {0x6e70, true, false, true, false, false, false, false, false, 0, 2}, // 8080 E7
    {0x6e80, true, false, true, false, false, false, false, false, 0, 2}, // 8080 E8
    {0x6e90, true, false, true, false, false, false, false, false, 0, 2}, // 8080 E9
    {0x6ea0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 EA
    {0x6eb0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 EB
    {0x6ec0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 EC
    {0x6ed0, true, false, true, false, false, false, false, true, 1, 2}, // 8080 ED
    {0x6ee0, false, false, true, false, false, false, false, false, 0, 2}, // 8080 EE
    {0x6ef0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 EF
    {0x6f00, true, false, true, false, false, false, false, false, 0, 2}, // 8080 F0
    {0x6f10, true, false, true, false, false, false, false, false, 0, 2}, // 8080 F1
    {0x6f20, true, false, true, false, false, false, false, false, 0, 2}, // 8080 F2
    {0x6f30, true, false, true, false, false, false, false, true, 5, 2}, // 8080 F3
    {0x6f40, true, false, true, false, false, false, false, false, 0, 2}, // 8080 F4
    {0x6f50, true, false, true, false, false, false, false, false, 0, 2}, // 8080 F5
    {0x6f60, false, false, true, false, false, false, false, false, 0, 4}, // 8080 F6
    {0x6f70, true, false, true, false, false, false, false, false, 0, 4}, // 8080 F7
    {0x6f80, true, false, true, false, false, false, false, false, 0, 2}, // 8080 F8
    {0x6f90, true, false, true, false, false, false, false, false, 0, 2}, // 8080 F9
    {0x6fa0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 FA
    {0x6fb0, true, false, true, false, false, false, false, true, 4, 2}, // 8080 FB
    {0x6fc0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 FC
    {0x6fd0, true, false, true, false, false, false, false, false, 0, 2}, // 8080 FD
    {0x6fe0, false, false, true, false, false, false, false, false, 0, 5}, // 8080 FE
    {0x6ff0, true, false, true, false, false, false, false, false, 0, 5}, // 8080 FF
    {0x5000, true, false, true, false, false, false, false, false, 0, 2}, // ED 00
    {0x5010, true, false, true, false, false, false, false, false, 0, 2}, // ED 01
    {0x5020, true, false, true, false, false, false, false, false, 0, 2}, // ED 02
    {0x5030, true, false, true, false, false, false, false, false, 0, 2}, // ED 03
    {0x5040, true, false, true, false, false, false, false, false, 0, 2}, // ED 04
    {0x5050, true, false, true, false, false, false, false, false, 0, 2}, // ED 05
    {0x5060, true, false, true, false, false, false, false, false, 0, 2}, // ED 06
    {0x5070, true, false, true, false, false, false, false, false, 0, 2}, // ED 07
    {0x5080, true, false, true, false, false, false, false, false, 0, 2}, // ED 08
    {0x5090, true, false, true, false, false, false, false, false, 0, 2}, // ED 09
    {0x50a0, true, false, true, false, false, false, false, false, 0, 2}, // ED 0A
    {0x50b0, true, false, true, false, false, false, false, false, 0, 2}, // ED 0B
    {0x50c0, true, false, true, false, false, false, false, false, 0, 2}, // ED 0C
    {0x50d0, true, false, true, false, false, false, false, false, 0, 2}, // ED 0D
    {0x50e0, true, false, true, false, false, false, false, false, 0, 2}, // ED 0E
    {0x50f0, true, false, true, false, false, false, false, false, 0, 2}, // ED 0F
    {0x5100, true, false, true, false, false, false, false, false, 0, 2}, // ED 10
    {0x5110, true, false, true, false, false, false, false, false, 0, 2}, // ED 11
    {0x5120, true, false, true, false, false, false, false, false, 0, 2}, // ED 12
    {0x5130, true, false, true, false, false, false, false, false, 0, 2}, // ED 13
    {0x5140, true, false, true, false, false, false, false, false, 0, 2}, // ED 14
    {0x5150, true, false, true, false, false, false, false, false, 0, 2}, // ED 15
    {0x5160, true, false, true, false, false, false, false, false, 0, 2}, // ED 16
    {0x5170, true, false, true, false, false, false, false, false, 0, 2}, // ED 17
    {0x5180, true, false, true, false, false, false, false, false, 0, 2}, // ED 18
    {0x5190, true, false, true, false, false, false, false, false, 0, 2}, // ED 19
    {0x51a0, true, false, true, false, false, false, false, false, 0, 2}, // ED 1A
    {0x51b0, true, false, true, false, false, false, false, false, 0, 2}, // ED 1B
    {0x51c0, true, false, true, false, false, false, false, false, 0, 2}, // ED 1C
    {0x51d0, true, false, true, false, false, false, false, false, 0, 2}, // ED 1D
    {0x51e0, true, false, true, false, false, false, false, false, 0, 2}, // ED 1E
    {0x51f0, true, false, true, false, false, false, false, false, 0, 2}, // ED 1F
    {0x5200, true, false, true, false, false, false, false, false, 10, 2}, // ED 20
    {0x5210, true, false, true, false, false, false, false, false, 10, 2}, // ED 21
    {0x5220, true, false, true, false, false, false, false, false, 10, 2}, // ED 22
    {0x5230, true, false, true, false, false, false, false, false, 10, 2}, // ED 23
    {0x5240, true, false, true, false, false, false, false, false, 10, 2}, // ED 24
    {0x5250, true, false, true, false, false, false, false, false, 10, 2}, // ED 25
    {0x5260, true, false, true, false, false, false, false, false, 10, 2}, // ED 26
    {0x5270, true, false, true, false, false, false, false, false, 10, 2}, // ED 27
    {0x5280, true, false, true, false, false, false, false, false, 0, 2}, // ED 28
    {0x5290, true, false, false, false, false, false, false, false, 0, 2}, // ED 29
    {0x52a0, true, false, true, false, false, false, false, false, 0, 2}, // ED 2A
    {0x52b0, true, false, false, false, false, false, false, false, 0, 2}, // ED 2B
    {0x52c0, true, false, false, false, false, false, false, false, 0, 2}, // ED 2C
    {0x52d0, true, false, false, false, false, false, false, false, 0, 2}, // ED 2D
    {0x52e0, true, false, false, false, false, false, false, false, 0, 2}, // ED 2E
    {0x52f0, true, false, false, false, false, false, false, false, 0, 2}, // ED 2F
    {0x5300, true, false, false, false, false, true, false, false, 3, 2}, // ED 30
    {0x5310, true, false, false, false, false, true, false, false, 3, 2}, // ED 31
    {0x5320, true, false, false, false, false, true, false, false, 3, 2}, // ED 32
    {0x5330, true, false, false, false, false, true, false, false, 3, 2}, // ED 33
    {0x5340, true, false, false, false, false, true, false, false, 3, 2}, // ED 34
    {0x5350, true, false, false, false, false, true, false, false, 3, 2}, // ED 35
    {0x5360, true, false, false, false, false, true, false, false, 3, 2}, // ED 36
    {0x5370, true, false, false, false, false, true, false, false, 3, 2}, // ED 37
    {0x5380, true, false, false, false, false, true, false, false, 3, 2}, // ED 38
    {0x5390, true, false, false, false, false, true, false, false, 3, 2}, // ED 39
    {0x53a0, true, false, false, false, false, true, false, false, 3, 2}, // ED 3A
    {0x53b0, true, false, false, false, false, true, false, false, 3, 2}, // ED 3B
    {0x53c0, true, false, false, false, false, true, false, false, 3, 2}, // ED 3C
    {0x53d0, true, false, false, false, false, true, false, false, 3, 2}, // ED 3D
    {0x53e0, true, false, false, false, false, true, false, false, 3, 2}, // ED 3E
    {0x53f0, true, false, false, false, false, true, false, false, 3, 2}, // ED 3F
    {0x5400, true, false, true, false, false, false, false, false, 0, 2}, // ED 40
    {0x5410, true, false, true, false, false, false, false, false, 0, 2}, // ED 41
    {0x5420, true, false, true, false, false, false, false, false, 0, 2}, // ED 42
    {0x5430, true, false, true, false, false, false, false, false, 0, 2}, // ED 43
    {0x5440, true, false, true, false, false, false, false, false, 0, 2}, // ED 44
    {0x5450, true, false, true, false, false, false, false, false, 0, 2}, // ED 45
    {0x5460, true, false, true, false, false, false, false, false, 0, 2}, // ED 46
    {0x5470, true, false, true, false, false, false, false, false, 0, 2}, // ED 47
    {0x5480, true, false, true, false, false, false, false, false, 0, 2}, // ED 48
    {0x5490, true, false, true, false, false, false, false, false, 0, 2}, // ED 49
    {0x54a0, true, false, true, false, false, false, false, false, 0, 2}, // ED 4A
    {0x54b0, true, false, true, false, false, false, false, false, 0, 2}, // ED 4B
    {0x54c0, true, false, true, false, false, false, false, false, 0, 2}, // ED 4C
    {0x54d0, true, false, true, false, false, false, false, false, 0, 2}, // ED 4D
    {0x54e0, true, false, true, false, false, false, false, false, 0, 2}, // ED 4E
    {0x54f0, true, false, true, false, false, false, false, false, 0, 2}, // ED 4F
    {0x5500, true, false, true, false, false, false, false, false, 0, 2}, // ED 50
    {0x5510, true, false, true, false, false, false, false, false, 0, 2}, // ED 51
    {0x5520, true, false, true, false, false, false, false, false, 0, 2}, // ED 52
    {0x5530, true, false, true, false, false, false, false, false, 0, 2}, // ED 53
    {0x5540, true, false, true, false, false, false, false, false, 0, 2}, // ED 54
    {0x5550, true, false, true, false, false, false, false, false, 0, 2}, // ED 55
    {0x5560, true, false, true, false, false, false, false, false, 0, 2}, // ED 56
    {0x5570, true, false, true, false, false, false, false, false, 0, 2}, // ED 57
    {0x5580, true, false, true, false, false, false, false, false, 0, 2}, // ED 58
    {0x5590, true, false, true, false, false, false, false, false, 0, 2}, // ED 59
    {0x55a0, true, false, true, false, false, false, false, false, 0, 2}, // ED 5A
    {0x55b0, true, false, true, false, false, false, false, false, 0, 2}, // ED 5B
    {0x55c0, true, false, true, false, false, false, false, false, 0, 2}, // ED 5C
    {0x55d0, true, false, true, false, false, false, false, false, 0, 2}, // ED 5D
    {0x55e0, true, false, true, false, false, false, false, false, 0, 2}, // ED 5E
    {0x55f0, true, false, true, false, false, false, false, false, 0, 2}, // ED 5F
    {0x5600, true, false, true, false, false, false, false, false, 0, 2}, // ED 60
    {0x5610, true, false, true, false, false, false, false, false, 0, 2}, // ED 61
    {0x5620, true, false, true, false, false, false, false, false, 0, 2}, // ED 62
    {0x5630, true, false, true, false, false, false, false, false, 0, 2}, // ED 63
    {0x5640, true, false, true, false, false, false, false, false, 0, 2}, // ED 64
    {0x5650, true, false, true, false, false, false, false, false, 0, 2}, // ED 65
    {0x5660, true, false, true, false, false, false, false, false, 0, 2}, // ED 66
    {0x5670, true, false, true, false, false, false, false, false, 0, 2}, // ED 67
    {0x5680, true, false, true, false, false, false, false, false, 0, 2}, // ED 68
    {0x5690, true, false, true, false, false, false, false, false, 0, 2}, // ED 69
    {0x56a0, true, false, true, false, false, false, false, false, 0, 2}, // ED 6A
    {0x56b0, true, false, true, false, false, false, false, false, 0, 2}, // ED 6B
    {0x56c0, true, false, true, false, false, false, false, false, 0, 2}, // ED 6C
    {0x56d0, true, false, true, false, false, false, false, false, 0, 2}, // ED 6D
    {0x56e0, true, false, true, false, false, false, false, false, 0, 2}, // ED 6E
    {0x56f0, true, false, true, false, false, false, false, false, 0, 2}, // ED 6F
    {0x5700, true, false, true, false, false, false, false, false, 0, 2}, // ED 70
    {0x5710, true, false, true, false, false, false, false, false, 0, 2}, // ED 71
    {0x5720, true, false, true, false, false, false, false, false, 0, 2}, // ED 72
    {0x5730, true, false, true, false, false, false, false, false, 0, 2}, // ED 73
    {0x5740, true, false, true, false, false, false, false, false, 0, 2}, // ED 74
    {0x5750, true, false, true, false, false, false, false, false, 0, 2}, // ED 75
    {0x5760, true, false, true, false, false, false, false, false, 0, 2}, // ED 76
    {0x5770, true, false, true, false, false, false, false, false, 0, 2}, // ED 77
    {0x5780, true, false, true, false, false, false, false, false, 0, 2}, // ED 78
    {0x5790, true, false, true, false, false, false, false, false, 0, 2}, // ED 79
    {0x57a0, true, false, true, false, false, false, false, false, 0, 2}, // ED 7A
    {0x57b0, true, false, true, false, false, false, false, false, 0, 2}, // ED 7B
    {0x57c0, true, false, true, false, false, false, false, false, 0, 2}, // ED 7C
    {0x57d0, true, false, true, false, false, false, false, false, 0, 2}, // ED 7D
    {0x57e0, true, false, true, false, false, false, false, false, 0, 2}, // ED 7E
    {0x57f0, true, false, true, false, false, false, false, false, 0, 2}, // ED 7F
    {0x5800, true, false, true, false, false, false, false, false, 0, 2}, // ED 80
    {0x5810, true, false, true, false, false, false, false, false, 0, 2}, // ED 81
    {0x5820, true, false, true, false, false, false, false, false, 0, 2}, // ED 82
    {0x5830, true, false, true, false, false, false, false, false, 0, 2}, // ED 83
    {0x5840, true, false, true, false, false, false, false, false, 0, 2}, // ED 84
    {0x5850, true, false, true, false, false, false, false, false, 0, 2}, // ED 85
    {0x5860, true, false, true, false, false, false, false, false, 0, 2}, // ED 86
    {0x5870, true, false, true, false, false, false, false, false, 0, 2}, // ED 87
    {0x5880, true, false, true, false, false, false, false, false, 0, 2}, // ED 88
    {0x5890, true, false, true, false, false, false, false, false, 0, 2}, // ED 89
    {0x58a0, true, false, true, false, false, false, false, false, 0, 2}, // ED 8A
    {0x58b0, true, false, true, false, false, false, false, false, 0, 2}, // ED 8B
    {0x58c0, true, false, true, false, false, false, false, false, 0, 2}, // ED 8C
    {0x58d0, true, false, true, false, false, false, false, false, 0, 2}, // ED 8D
    {0x58e0, true, false, true, false, false, false, false, false, 0, 2}, // ED 8E
    {0x58f0, true, false, true, false, false, false, false, false, 0, 2}, // ED 8F
    {0x5900, true, false, true, false, false, false, false, false, 0, 2}, // ED 90
    {0x5910, true, false, true, false, false, false, false, false, 0, 2}, // ED 91
    {0x5920, true, false, true, false, false, false, false, false, 0, 2}, // ED 92
    {0x5930, true, false, true, false, false, false, false, false, 0, 2}, // ED 93
    {0x5940, true, false, true, false, false, false, false, false, 0, 2}, // ED 94
    {0x5950, true, false, true, false, false, false, false, false, 0, 2}, // ED 95
    {0x5960, true, false, true, false, false, false, false, false, 0, 2}, // ED 96
    {0x5970, true, false, true, false, false, false, false, false, 0, 2}, // ED 97
    {0x5980, true, false, true, false, false, false, false, false, 0, 2}, // ED 98
    {0x5990, true, false, true, false, false, false, false, false, 0, 2}, // ED 99
    {0x59a0, true, false, true, false, false, false, false, false, 0, 2}, // ED 9A
    {0x59b0, true, false, true, false, false, false, false, false, 0, 2}, // ED 9B
    {0x59c0, true, false, true, false, false, false, false, false, 0, 2}, // ED 9C
    {0x59d0, true, false, true, false, false, false, false, false, 0, 2}, // ED 9D
    {0x59e0, true, false, true, false, false, false, false, false, 0, 2}, // ED 9E
    {0x59f0, true, false, true, false, false, false, false, false, 0, 2}, // ED 9F
    {0x5a00, true, false, true, false, false, false, false, false, 0, 2}, // ED A0
    {0x5a10, true, false, true, false, false, false, false, false, 0, 2}, // ED A1
    {0x5a20, true, false, true, false, false, false, false, false, 0, 2}, // ED A2
    {0x5a30, true, false, true, false, false, false, false, false, 0, 2}, // ED A3
    {0x5a40, true, false, true, false, false, false, false, false, 0, 2}, // ED A4
    {0x5a50, true, false, true, false, false, false, false, false, 0, 2}, // ED A5
    {0x5a60, true, false, true, false, false, false, false, false, 0, 2}, // ED A6
    {0x5a70, true, false, true, false, false, false, false, false, 0, 2}, // ED A7
    {0x5a80, true, false, true, false, false, false, false, false, 0, 2}, // ED A8
    {0x5a90, true, false, true, false, false, false, false, false, 0, 2}, // ED A9
    {0x5aa0, true, false, true, false, false, false, false, false, 0, 2}, // ED AA
    {0x5ab0, true, false, true, false, false, false, false, false, 0, 2}, // ED AB
    {0x5ac0, true, false, true, false, false, false, false, false, 0, 2}, // ED AC
    {0x5ad0, true, false, true, false, false, false, false, false, 0, 2}, // ED AD
    {0x5ae0, true, false, true, false, false, false, false, false, 0, 2}, // ED AE
    {0x5af0, true, false, true, false, false, false, false, false, 0, 2}, // ED AF
    {0x5b00, true, false, true, false, false, false, false, false, 0, 2}, // ED B0
    {0x5b10, true, false, true, false, false, false, false, false, 0, 2}, // ED B1
    {0x5b20, true, false, true, false, false, false, false, false, 0, 2}, // ED B2
    {0x5b30, true, false, true, false, false, false, false, false, 0, 2}, // ED B3
    {0x5b40, true, false, true, false, false, false, false, false, 0, 2}, // ED B4
    {0x5b50, true, false, true, false, false, false, false, false, 0, 2}, // ED B5
    {0x5b60, true, false, true, false, false, false, false, false, 0, 2}, // ED B6
    {0x5b70, true, false, true, false, false, false, false, false, 0, 2}, // ED B7
    {0x5b80, true, false, true, false, false, false, false, false, 0, 2}, // ED B8
    {0x5b90, true, false, true, false, false, false, false, false, 0, 2}, // ED B9
    {0x5ba0, true, false, true, false, false, false, false, false, 0, 2}, // ED BA
    {0x5bb0, true, false, true, false, false, false, false, false, 0, 2}, // ED BB
    {0x5bc0, true, false, true, false, false, false, false, false, 0, 2}, // ED BC
    {0x5bd0, true, false, true, false, false, false, false, false, 0, 2}, // ED BD
    {0x5be0, true, false, true, false, false, false, false, false, 0, 2}, // ED BE
    {0x5bf0, true, false, true, false, false, false, false, false, 0, 2}, // ED BF
    {0x5c00, true, false, true, false, false, false, false, false, 0, 2}, // ED C0
    {0x5c10, true, false, true, false, false, false, false, false, 0, 2}, // ED C1
    {0x5c20, true, false, true, false, false, false, false, false, 0, 2}, // ED C2
    {0x5c30, true, false, true, false, false, false, false, false, 0, 2}, // ED C3
    {0x5c40, true, false, true, false, false, false, false, false, 0, 2}, // ED C4
    {0x5c50, true, false, true, false, false, false, false, false, 0, 2}, // ED C5
    {0x5c60, true, false, true, false, false, false, false, false, 0, 2}, // ED C6
    {0x5c70, true, false, true, false, false, false, false, false, 0, 2}, // ED C7
    {0x5c80, true, false, true, false, false, false, false, false, 0, 2}, // ED C8
    {0x5c90, true, false, true, false, false, false, false, false, 0, 2}, // ED C9
    {0x5ca0, true, false, true, false, false, false, false, false, 0, 2}, // ED CA
    {0x5cb0, true, false, true, false, false, false, false, false, 0, 2}, // ED CB
    {0x5cc0, true, false, true, false, false, false, false, false, 0, 2}, // ED CC
    {0x5cd0, true, false, true, false, false, false, false, false, 0, 2}, // ED CD
    {0x5ce0, true, false, true, false, false, false, false, false, 0, 2}, // ED CE
    {0x5cf0, true, false, true, false, false, false, false, false, 0, 2}, // ED CF
    {0x5d00, true, false, true, false, false, false, false, false, 0, 2}, // ED D0
    {0x5d10, true, false, true, false, false, false, false, false, 0, 2}, // ED D1
    {0x5d20, true, false, true, false, false, false, false, false, 0, 2}, // ED D2
    {0x5d30, true, false, true, false, false, false, false, false, 0, 2}, // ED D3
    {0x5d40, true, false, true, false, false, false, false, false, 0, 2}, // ED D4
    {0x5d50, true, false, true, false, false, false, false, false, 0, 2}, // ED D5
    {0x5d60, true, false, true, false, false, false, false, false, 0, 2}, // ED D6
    {0x5d70, true, false, true, false, false, false, false, false, 0, 2}, // ED D7
    {0x5d80, true, false, true, false, false, false, false, false, 0, 2}, // ED D8
    {0x5d90, true, false, true, false, false, false, false, false, 0, 2}, // ED D9
    {0x5da0, true, false, true, false, false, false, false, false, 0, 2}, // ED DA
    {0x5db0, true, false, true, false, false, false, false, false, 0, 2}, // ED DB
    {0x5dc0, true, false, true, false, false, false, false, false, 0, 2}, // ED DC
    {0x5dd0, true, false, true, false, false, false, false, false, 0, 2}, // ED DD
    {0x5de0, true, false, true, false, false, false, false, false, 0, 2}, // ED DE
    {0x5df0, true, false, true, false, false, false, false, false, 0, 2}, // ED DF
    {0x5e00, true, false, true, false, false, false, false, false, 0, 2}, // ED E0
    {0x5e10, true, false, true, false, false, false, false, false, 0, 2}, // ED E1
    {0x5e20, true, false, true, false, false, false, false, false, 0, 2}, // ED E2
    {0x5e30, true, false, true, false, false, false, false, false, 0, 2}, // ED E3
    {0x5e40, true, false, true, false, false, false, false, false, 0, 2}, // ED E4
    {0x5e50, true, false, true, false, false, false, false, false, 0, 2}, // ED E5
    {0x5e60, true, false, true, false, false, false, false, false, 0, 2}, // ED E6
    {0x5e70, true, false, true, false, false, false, false, false, 0, 2}, // ED E7
    {0x5e80, true, false, true, false, false, false, false, false, 0, 2}, // ED E8
    {0x5e90, true, false, true, false, false, false, false, false, 0, 2}, // ED E9
    {0x5ea0, true, false, true, false, false, false, false, false, 0, 2}, // ED EA
    {0x5eb0, true, false, true, false, false, false, false, false, 0, 2}, // ED EB
    {0x5ec0, true, false, true, false, false, false, false, false, 0, 2}, // ED EC
    {0x5ed0, true, false, true, false, false, false, false, false, 0, 2}, // ED ED
    {0x5ee0, true, false, true, false, false, false, false, false, 0, 2}, // ED EE
    {0x5ef0, true, false, true, false, false, false, false, false, 0, 2}, // ED EF
    {0x5f00, true, false, true, false, false, false, false, false, 0, 2}, // ED F0
    {0x5f10, true, false, true, false, false, false, false, false, 0, 2}, // ED F1
    {0x5f20, true, false, true, false, false, false, false, false, 0, 2}, // ED F2
    {0x5f30, true, false, true, false, false, false, false, false, 0, 2}, // ED F3
    {0x5f40, true, false, true, false, false, false, false, false, 0, 2}, // ED F4
    {0x5f50, true, false, true, false, false, false, false, false, 0, 2}, // ED F5
    {0x5f60, true, false, true, false, false, false, false, false, 0, 2}, // ED F6
    {0x5f70, true, false, true, false, false, false, false, false, 0, 2}, // ED F7
    {0x5f80, true, false, true, false, false, false, false, false, 0, 2}, // ED F8
    {0x5f90, true, false, true, false, false, false, false, false, 0, 2}, // ED F9
    {0x5fa0, true, false, true, false, false, false, false, false, 0, 2}, // ED FA
    {0x5fb0, true, false, true, false, false, false, false, false, 0, 2}, // ED FB
    {0x5fc0, true, false, true, false, false, false, false, false, 0, 2}, // ED FC
    {0x5fd0, true, false, true, false, false, false, false, false, 0, 2}, // ED FD
    {0x5fe0, true, false, true, false, false, false, false, false, 0, 2}, // ED FE
    {0x5ff0, true, false, true, false, false, false, false, false, 0, 2}, // ED FF
};

static const char* const disassembly[1024] = {
    "000: OP1 -> tmpB     OP2 -> tmpA    ---  ALU XI, tmpA",
    "001: SIGMA -> OP1                   -WE  EC=COMMIT",
    "002:                                ---",
    "003:                                ---",
    "004: OP1 -> tmpB     Q -> tmpA      ---  JUMP JNW, 02",
    "005: Q -> tmpAH                     ---  --",
    "006:                                --E  ALU XI, tmpA",
    "007: SIGMA -> OP1                   -W-  --",
    "008: SP -> DP                       ---  EC=MR, SR=SS",
    "009: SP -> tmpB                     ---  ALU INC2, tmpB",
    "00A: SIGMA -> SP                    ---  --",
    "00B: OPR -> OP2                     F-E  --",
    "00C: SP -> tmpB                     ---  ALU DEC2, tmpB",
    "00D: OP2 -> OPR      SIGMA -> IND   ---  EC=MW, SR=SS",
    "00E: SIGMA -> SP                    --E  --",
    "00F:                                ---",
    "010: A -> tmpBL                     ---  ALU ADJD, tmpB",
    "011: K -> tmpA                      --E  ALU ADD, tmpA",
    "012: SIGMA -> AL     SIGMA -> NULL  -W-  --",
    "013:                                ---",
    "014: A -> tmpBL                     ---  ALU ADJD, tmpB",
    "015: K -> tmpA                      --E  ALU SUB, tmpA",
    "016: SIGMA -> AL     SIGMA -> NULL  -W-  --",
    "017:                                ---",
    "018: A -> tmpBL                     ---  ALU ADJA, tmpB",
    "019: K -> tmpA                      ---  ALU ADD, tmpA",
    "01A: SIGMA -> AL     SIGMA -> NULL  -W-  ALU INC, tmpB",
    "01B: AL:AH -> tmpB                  ---  JUMP JNC, 05",
    "01C: SIGMA -> AH                    ---  --",
    "01D:                                --E  --",
    "01E:                                ---",
    "01F:                                ---",
    "020: A -> tmpBL                     ---  ALU ADJA, tmpB",
    "021: K -> tmpA                      ---  ALU SUB, tmpA",
    "022: SIGMA -> AL     SIGMA -> NULL  -W-  ALU DEC, tmpB",
    "023: AL:AH -> tmpB                  ---  JUMP JNC, 05",
    "024: OP1 -> tmpB                    --E  ALU XI, tmpB",
    "025: SIGMA -> OP1                   -W-  --",
    "026:                                ---",
    "027:                                ---",
    "028: SP -> tmpB                     ---  ALU DEC2, tmpB",
    "029: SIGMA -> SP     SIGMA -> IND   --E  EC=MW, SR=SS",
    "02A: OP1 -> OPR                     ---  --",
    "02B:                                ---",
    "02C: SP -> DP                       ---  EC=MR, SR=SS",
    "02D: SP -> tmpB                     ---  ALU INC2, tmpB",
    "02E: SIGMA -> SP                    ---  --",
    "02F: OPR -> OP1                     F-E  --",
    "030:                                --E  --",
    "031:                                ---",
    "032:                                ---",
    "033:                                ---",
    "034: Q -> tmpBL                     ---  ALU ADD, tmpA",
    "035:                                ---  JUMP OPC, 04",
    "036:                                --E  --",
    "037:                                ---",
    "038: PC -> tmpA                     ---  IC=SUSP",
    "039: SIGMA -> PC                    --E  IC=FLUSH",
    "03A:                                ---",
    "03B:                                ---",
    "03C: Q -> tmpBL                     ---  JUMP JNW, 02",
    "03D: Q -> tmpBH                     ---  --",
    "03E: tmpB -> tmpA                   ---  ALU XI, tmpA",
    "03F: OP1 -> tmpB                    ---  --",
    "040: SIGMA -> OP1                   -WE  EC=COMMIT",
    "041:                                ---",
    "042:                                ---",
    "043:                                ---",
    "044: OP1 -> tmpA     OP2 -> tmpB    --E  ALU AND, tmpA",
    "045: SIGMA -> NULL                  -W-  --",
    "046:                                ---",
    "047:                                ---",
    "048: OP1 -> tmpA     OP2 -> tmpB    ---  --",
    "049: tmpA -> OP2                    --E  EC=COMMIT",
    "04A: tmpB -> OP1                    ---  --",
    "04B:                                ---",
    "04C: OP2 -> tmpA                    ---  --",
    "04D: tmpA -> OP1                    --E  EC=COMMIT",
    "04E:                                ---",
    "04F:                                ---",
    "050: OP2 -> OP1                     --E  EC=COMMIT",
    "051:                                ---",
    "052:                                ---",
    "053:                                ---",
    "054:                                --E  --",
    "055: SIGMA -> OP2                   ---  --",
    "056:                                ---",
    "057:                                ---",
    "058: SIGMA -> tmpA                  ---  ALU INC2, tmpB",
    "059: SP -> DP        SP -> tmpB     ---  EC=MR, SR=SS",
    "05A: SIGMA -> SP                    F--  ALU PASS, tmpA",
    "05B: SIGMA -> DP                    --E  EC=COMMIT",
    "05C: OP1 -> tmpB     A -> tmpA      ---  --",
    "05D: tmpA -> OP1                    --E  --",
    "05E: tmpB -> A                      ---  --",
    "05F:                                ---",
    "060: A -> tmpBL                     --E  --",
    "061: tmpB -> A                      ---  --",
    "062:                                ---",
    "063:                                ---",
    "064: ZERO -> D       A -> tmpB      ---  --",
    "065:                                ---  JUMP JNS, 03",
    "066: K -> D                         ---  --",
    "067:                                --E  --",
    "068: Q -> tmpAL                     ---  --",
    "069: Q -> tmpAH                     ---  --",
    "06A: Q -> tmpBL                     ---  --",
    "06B: Q -> tmpBH                     ---  CALL FARCALL (0D) -> 7680 [Line 228]",
    "06C:                                ---  JUMP BUSY, 03",
    "06D:                                --E  IC=WAIT",
    "06E:                                ---",
    "06F:                                ---  JUMP INT, 05",
    "070:                                ---  JUMP UNC, 00",
    "071:                                ---  IC=SUSP",
    "072: PC -> tmpB                     ---  ALU DEC, tmpB",
    "073: SIGMA -> PC                    --E  IC=FLUSH",
    "074: SP -> tmpB                     ---  ALU DEC2, tmpB",
    "075: FLAGS -> OPR    SIGMA -> IND   --E  EC=MW, SR=SS",
    "076: SIGMA -> SP                    ---  --",
    "077:                                ---",
    "078: SP -> DP                       ---  EC=MR, SR=SS",
    "079: SP -> tmpB                     ---  ALU INC2, tmpB",
    "07A: OPR -> FLAGS                   F-E  --",
    "07B: SIGMA -> SP                    ---  --",
    "07C: AL:AH -> tmpAL                 ---  --",
    "07D: FLAGS -> tmpAH                 --E  --",
    "07E: tmpA -> FLAGS                  ---  --",
    "07F:                                ---",
    "080: FLAGS -> AH                    --E  --",
    "081:                                ---",
    "082:                                ---",
    "083:                                ---",
    "084: Q -> tmpBL                     ---  --",
    "085: Q -> tmpBH                     ---  --",
    "086: tmpB -> DP                     ---  EC=MR",
    "087: OPR -> OP1                     F-E  --",
    "088: Q -> tmpBL                     ---  --",
    "089: Q -> tmpBH                     ---  --",
    "08A: tmpB -> DP                     --E  EC=MW",
    "08B: OP1 -> OPR                     ---  --",
    "08C: DIRSZ -> tmpC   SI -> tmpB     ---  ALU ADD, tmpC",
    "08D: SI -> DP                       ---  EC=MR",
    "08E: SIGMA -> SI     DI -> tmpB     ---  ALU ADD, tmpC",
    "08F: DI -> DP                       --E  EC=MW, SR=ES",
    "090: FLAGS -> OPR                   F--  --",
    "091: SIGMA -> tmpB   SIGMA -> IND   ---  IC=MFS, EC=MW, SR=SS",
    "092: CS -> OPR       SIGMA -> IND   F--  JUMP JLCNZ, 0C",
    "093:                                ---  IC=SETEM",
    "094: C -> LC         C -> tmpB      ---  ALU PASS, tmpB",
    "095: SIGMA -> NULL                  ---  ALU ADD, tmpC",
    "096: DIRSZ -> tmpC                  ---  JUMP JZ, 07",
    "097: SI -> DP        DI -> tmpB     ---  EC=MR",
    "098: SIGMA -> DI                    ---  --",
    "099: tmpB -> DP      SI -> tmpB     ---  EC=MW, SR=ES",
    "09A: SIGMA -> SI                    ---  JUMP REP, 03",
    "09B: LC -> C                        ---  CALL REP (08) -> 7400 [Line 21C]",
    "09C: DIRSZ -> tmpC   SI -> tmpB     ---  ALU ADD, tmpC",
    "09D: SI -> DP                       ---  EC=MR",
    "09E: SIGMA -> SI     DI -> tmpB     ---  --",
    "09F: DI -> DP        SIGMA -> tmpA  ---  EC=MR, SR=ES",
    "0A0: OPR -> tmpB                    F--  --",
    "0A1: tmpA -> DI                     ---  ALU SUB, tmpA",
    "0A2: OPR -> tmpA                    F-E  --",
    "0A3: SIGMA -> NULL                  -W-  --",
    "0A4: C -> LC         C -> tmpB      ---  ALU PASS, tmpB",
    "0A5: DIRSZ -> tmpC   SIGMA -> NULL  ---  ALU ADD, tmpC",
    "0A6:                                ---  JUMP JZ, 0B",
    "0A7: DI -> DP        DI -> tmpB     ---  EC=MR, SR=ES",
    "0A8: SIGMA -> DI     SI -> tmpB     ---  --",
    "0A9: SI -> DP        SIGMA -> tmpB  ---  EC=MR",
    "0AA: OPR -> tmpA                    F--  --",
    "0AB: tmpB -> SI                     ---  ALU SUB, tmpA",
    "0AC: OPR -> tmpB                    F--  --",
    "0AD: SIGMA -> NULL                  -W-  ALU ADD, tmpC",
    "0AE:                                ---  JUMP REP, 03",
    "0AF: LC -> C                        ---  CALL REP (08) -> 7400 [Line 21C]",
    "0B0: tmpB -> tmpC                   ---  JUMP JNW, 0F",
    "0B1: tmpB -> D                      ---  --",
    "0B2: tmpA -> A                      ---  CALL MUL (04) -> 7200 [Line 200]",
    "0B3: tmpB -> AH                     ---  --",
    "0B4: A -> tmpB       Q -> tmpA      ---  JUMP JNW, 02",
    "0B5: Q -> tmpAH                     ---  --",
    "0B6:                                --E  ALU AND, tmpA",
    "0B7: SIGMA -> NULL                  -W-  --",
    "0B8: DIRSZ -> tmpC   DI -> tmpB     ---  ALU ADD, tmpC",
    "0B9: DI -> DP                       ---  EC=MW, SR=ES",
    "0BA: OP1 -> OPR                     --E  --",
    "0BB: SIGMA -> DI                    ---  --",
    "0BC: C -> LC         C -> tmpB      ---  ALU PASS, tmpB",
    "0BD: DIRSZ -> tmpC   SIGMA -> NULL  ---  ALU ADD, tmpC",
    "0BE: OP1 -> OPR                     ---  JUMP JZ, 05",
    "0BF: DI -> DP        DI -> tmpB     ---  EC=MW, SR=ES",
    "0C0: SIGMA -> DI                    ---  JUMP REP, 03",
    "0C1: LC -> C                        ---  CALL REP (08) -> 7400 [Line 21C]",
    "0C2:                                ---",
    "0C3:                                ---",
    "0C4: DIRSZ -> tmpC   SI -> tmpB     ---  ALU ADD, tmpC",
    "0C5: SI -> DP                       ---  EC=MR",
    "0C6: SIGMA -> SI                    ---  --",
    "0C7: OPR -> OP1                     F-E  --",
    "0C8: C -> LC         C -> tmpB      ---  ALU PASS, tmpB",
    "0C9: DIRSZ -> tmpC   SIGMA -> NULL  ---  ALU ADD, tmpC",
    "0CA:                                ---  JUMP JZ, 07",
    "0CB: SI -> DP        SI -> tmpB     ---  EC=MR",
    "0CC: SIGMA -> SI                    ---  --",
    "0CD: OPR -> OP1                     F--  --",
    "0CE:                                ---  JUMP REP, 03",
    "0CF: LC -> C                        ---  CALL REP (08) -> 7400 [Line 21C]",
    "0D0: DIRSZ -> tmpC   DI -> tmpB     ---  ALU ADD, tmpC",
    "0D1: DI -> DP                       ---  EC=MR, SR=ES",
    "0D2: SIGMA -> DI                    ---  ALU SUB, tmpA",
    "0D3: OP1 -> tmpB                    ---  --",
    "0D4: OPR -> tmpA                    F--  --",
    "0D5: SIGMA -> NULL                  -WE  --",
    "0D6:                                ---",
    "0D7:                                ---",
    "0D8: SIGMA -> DI                    ---  ALU SUB, tmpA",
    "0D9: OP1 -> tmpB                    ---  --",
    "0DA: OPR -> tmpA                    F--  --",
    "0DB: SIGMA -> NULL                  -W-  ALU ADD, tmpC",
    "0DC:                                ---  JUMP REP, 03",
    "0DD:                                ---",
    "0DE:                                ---",
    "0DF: LC -> C                        ---  CALL REP (08) -> 7400 [Line 21C]",
    "0E0: Q -> tmpBL                     ---  JUMP JNW, 02",
    "0E1: Q -> tmpBH                     ---  --",
    "0E2: tmpB -> OP1                    --E  --",
    "0E3:                                ---",
    "0E4: Q -> tmpBL                     ---  --",
    "0E5: Q -> tmpBH                     ---  ALU INC2, tmpA",
    "0E6: SP -> DP        SP -> tmpA     ---  IC=SUSP, EC=MR, SR=SS",
    "0E7:                                ---",
    "0E8: SIGMA -> tmpA                  ---  ALU ADD, tmpA",
    "0E9: SIGMA -> SP                    ---  --",
    "0EA: OPR -> PC                      F-E  IC=FLUSH",
    "0EB:                                ---",
    "0EC: SIGMA -> DP     SIGMA -> tmpA  ---  EC=MR, SR=SS",
    "0ED: SIGMA -> tmpA                  ---  CALL FARRET (10) -> 7800 [Line 230]",
    "0EE:                                ---",
    "0EF:                                ---",
    "0F0: SP -> DP        SP -> tmpA     ---  IC=SUSP, EC=MR, SR=SS",
    "0F1:                                ---  ALU INC2, tmpA",
    "0F2: SIGMA -> SP                    ---  --",
    "0F3: OPR -> PC                      F-E  IC=FLUSH",
    "0F4: SP -> DP        SP -> tmpA     ---  IC=SUSP, EC=MR, SR=SS",
    "0F5: ZERO -> tmpB                   ---  ALU INC2, tmpA",
    "0F6: SIGMA -> DP     SIGMA -> tmpA  ---  EC=MR, SR=SS",
    "0F7: SIGMA -> tmpA                  ---  CALL FARRET (10) -> 7800 [Line 230]",
    "0F8: OPR -> OP2      SIGMA -> tmpB  F--  ALU INC2, tmpB",
    "0F9: SIGMA -> DP                    ---  EC=MR",
    "0FA: OPR -> ES                      F-E  --",
    "0FB:                                ---",
    "0FC: OPR -> OP2      SIGMA -> tmpB  F--  ALU INC2, tmpB",
    "0FD: SIGMA -> DP                    ---  EC=MR",
    "0FE: OPR -> DS                      F-E  --",
    "0FF:                                ---",
    "100: Q -> tmpBL                     ---  JUMP JNW, 02",
    "101: Q -> tmpBH                     ---  --",
    "102: tmpB -> OP1                    --E  EC=COMMIT",
    "103:                                ---",
    "104: 3 -> tmpBL                     ---  IC=SUSP",
    "105:                                ---  CALL INT (02) -> 7100 [Line 1E8]",
    "106:                                ---",
    "107:                                ---",
    "108: Q -> tmpBL                     ---  CALL INT (02) -> 7100 [Line 1E8]",
    "109:                                ---",
    "10A:                                ---",
    "10B:                                ---",
    "10C: 4 -> tmpBL                     ---  JUMP JO, 03",
    "10D:                                --E  --",
    "10E:                                ---",
    "10F:                                ---  CALL INT (02) -> 7100 [Line 1E8]",
    "110: SP -> DP        SP -> tmpA     ---  IC=SUSP, EC=MR, SR=SS",
    "111:                                ---  CALL IRET (01) -> 7080 [Line 1E0]",
    "112:                                ---",
    "113:                                ---",
    "114: 1 -> LC                        ---  --",
    "115: OP1 -> tmpB                    ---  ALU PASS, tmpB",
    "116: SIGMA -> tmpB                  -W-  ALU XI, tmpB, R",
    "117: SIGMA -> OP1                   --E  EC=COMMIT",
    "118: OP1 -> tmpB                    ---  ALU PASS, tmpA",
    "119: C -> tmpAL                     ---  --",
    "11A: tmpA -> LC      SIGMA -> NULL  ---  ALU PASS, tmpB",
    "11B:                                ---  CALL ROT (09) -> 7480 [Line 224]",
    "11C: Q -> tmpC       A -> tmpA      ---  --",
    "11D: ZERO -> tmpB                   ---  --",
    "11E: 8 -> LC                        ---  ALU SUB, tmpC",
    "11F: SIGMA -> tmpB                  ---  ALU DIV, tmpC, R",
    "120: SIGMA -> NULL   SIGMA -> tmpB  ---  ALU DIV, tmpC",
    "121: tmpA -> AH                     --E  ALU PASS, tmpB",
    "122: SIGMA -> AL                    -W-  --",
    "123:                                ---",
    "124: AL:AH -> tmpA   Q -> tmpB      ---  --",
    "125: AL:AH -> tmpB                  ---  ALU ADD, tmpB",
    "126: SIGMA -> tmpB                  ---  --",
    "127: SIGMA -> tmpB                  ---  ALU ADD, tmpA",
    "128: SIGMA -> tmpB                  ---  ALU ADD, tmpB",
    "129: SIGMA -> tmpB                  ---  --",
    "12A: ZERO -> AH      A -> tmpA      --E  ALU ADD, tmpA",
    "12B: SIGMA -> AL                    -W-  --",
    "12C: A -> tmpAL      B -> tmpB      ---  --",
    "12D: SIGMA -> DP                    ---  EC=MR",
    "12E: OPR -> AL                      F-E  --",
    "12F:                                ---",
    "130:                                --E  --",
    "131:                                ---",
    "132:                                ---",
    "133:                                ---",
    "134: C -> LC                        ---  --",
    "135:                                ---",
    "136: Q -> tmpAL                     ---  JUMP REP, 04",
    "137:                                --E  --",
    "138: LC -> C                        ---  --",
    "139: tmpA -> tmpBL                  ---  IC=SUSP",
    "13A: PC -> tmpA                     ---  ALU ADD, tmpA",
    "13B: SIGMA -> PC                    --E  IC=FLUSH",
    "13C: Q -> tmpAL      C -> tmpB      ---  ALU DEC, tmpB",
    "13D: SIGMA -> C                     ---  --",
    "13E: C -> LC                        ---  JUMP JNZ, 05",
    "13F:                                --E  --",
    "140: Q -> tmpAL      C -> tmpB      ---  ALU PASS, tmpB",
    "141: SIGMA -> NULL                  ---  --",
    "142:                                ---  JUMP JZ, 05",
    "143: C -> LC                        --E  --",
    "144: Q -> tmpAL                     ---  --",
    "145: tmpA -> DP                     ---  EC=MR, SR=None",
    "146: OPR -> OP1                     F-E  --",
    "147:                                ---",
    "148: Q -> tmpAL                     ---  ALU PASS, tmpA",
    "149: OP1 -> OPR      SIGMA -> IND   --E  EC=MW, SR=None",
    "14A:                                ---",
    "14B:                                ---",
    "14C: Q -> tmpAL      SP -> tmpB     ---  ALU DEC2, tmpB",
    "14D: Q -> tmpAH                     ---  --",
    "14E: SIGMA -> SP     SIGMA -> IND   ---  IC=SUSP",
    "14F: PC -> tmpB                     ---  ALU ADD, tmpA",
    "150: SIGMA -> PC                    ---  IC=FLUSH",
    "151: tmpB -> OPR                    --E  EC=MW, SR=SS",
    "152:                                ---",
    "153:                                ---",
    "154: Q -> tmpBL                     ---  ALU ADD, tmpA",
    "155: Q -> tmpBH                     ---  JUMP UNC, 02",
    "156: PC -> tmpA                     ---  IC=SUSP",
    "157: SIGMA -> PC                    --E  IC=FLUSH",
    "158: Q -> tmpBL                     ---  ALU ADD, tmpA",
    "159:                                ---  IC=SUSP",
    "15A: PC -> tmpA                     ---  --",
    "15B: SIGMA -> PC                    --E  IC=FLUSH",
    "15C: Q -> tmpBL                     ---  --",
    "15D: Q -> tmpBH                     ---  --",
    "15E: Q -> tmpAL                     ---  --",
    "15F: Q -> tmpAH                     ---  --",
    "160: tmpA -> CS                     ---  IC=SUSP",
    "161: tmpB -> PC                     --E  IC=FLUSH",
    "162:                                ---",
    "163:                                ---",
    "164: D -> DP                        ---  EC=MR, SR=None",
    "165: OPR -> OP1                     F-E  --",
    "166:                                ---",
    "167:                                ---",
    "168: D -> DP                        --E  EC=MW, SR=None",
    "169: OP1 -> OPR                     ---  --",
    "16A:                                ---",
    "16B:                                ---",
    "16C: Q -> tmpBL                     ---  JUMP JNW, 02",
    "16D: Q -> tmpBH                     ---  --",
    "16E: OP1 -> tmpA                    --E  ALU AND, tmpA",
    "16F: SIGMA -> NULL                  -W-  --",
    "170: OP1 -> tmpB                    ---  ALU XI, tmpB",
    "171: SIGMA -> OP1                   -WE  EC=COMMIT",
    "172:                                ---",
    "173:                                ---",
    "174: OP1 -> tmpB                    ---  ALU XI, tmpB",
    "175: SIGMA -> OP1                   --E  EC=COMMIT",
    "176:                                ---",
    "177:                                ---",
    "178: OP1 -> tmpC     ZERO -> tmpB   ---  ALU PASS, tmpC",
    "179: A -> tmpA                      ---  --",
    "17A: 8 -> LC                        ---  JUMP JNW, 04",
    "17B: 16 -> LC                       ---  --",
    "17C: SIGMA -> tmpB                  ---  ALU MUL, tmpC, R",
    "17D:                                ---  ALU PASS, tmpB",
    "17E: tmpA -> A                      ---  JUMP JNW, 08",
    "17F: tmpB -> D       SIGMA -> NULL  ---  CALL MUL2 (05) -> 7280 [Line 204]",
    "180: tmpB -> AH      SIGMA -> NULL  ---  CALL MUL2 (05) -> 7280 [Line 204]",
    "181:                                ---",
    "182:                                ---",
    "183:                                ---",
    "184: OP1 -> tmpA     A -> tmpB      ---  ALU MULDIV, tmpB",
    "185:                                ---  CALL IMUL (06) -> 7300 [Line 208]",
    "186:                                ---",
    "187:                                ---",
    "188: OP1 -> tmpC     A -> tmpA      ---  ALU SUB, tmpC",
    "189: D -> tmpB                      ---  JUMP JNW, 04",
    "18A: 16 -> LC                       ---  --",
    "18B: SIGMA -> NULL                  -W-  JUMP UNC, 07",
    "18C: AL:AH -> tmpB                  ---  --",
    "18D: 8 -> LC                        ---  --",
    "18E: SIGMA -> NULL                  -W-  --",
    "18F:                                ---  JUMP JNC, 0D",
    "190: SIGMA -> tmpB                  ---  ALU DIV, tmpC, R",
    "191: SIGMA -> NULL   SIGMA -> tmpB  ---  ALU DIV, tmpC",
    "192: tmpA -> A                      ---  JUMP JNW, 0E",
    "193: tmpB -> D                      --E  --",
    "194:                                ---",
    "195: ZERO -> tmpBL                  ---  CALL INT (02) -> 7100 [Line 1E8]",
    "196: tmpB -> AH                     --E  --",
    "197:                                ---",
    "198: OP1 -> tmpB                    ---  ALU MULDIV, tmpB",
    "199: 8 -> LC                        ---  IC=SCOF",
    "19A: SIGMA -> tmpC                  ---  ALU PASS, tmpB",
    "19B: D -> tmpB       SIGMA -> tmpA  ---  JUMP JNW, 05",
    "19C: 16 -> LC                       ---  JUMP UNC, 06",
    "19D: AL:AH -> tmpB                  ---  --",
    "19E:                                ---  IC=SIGN",
    "19F:                                ---  CALL IDIV (0F) -> 7780 [Line 1A0]",
    "1A0: A -> tmpA                      ---  ALU NEG, tmpA",
    "1A1: tmpB -> OPR                    ---  JUMP JNS, 06",
    "1A2: SIGMA -> tmpA                  -W-  ALU NEG, tmpB",
    "1A3:                                ---  JUMP JNC, 05",
    "1A4:                                ---  ALU NOT, tmpB",
    "1A5: SIGMA -> tmpB                  ---  --",
    "1A6:                                ---  ALU SUB, tmpC",
    "1A7: SIGMA -> NULL                  -W-  CALL IDIV2 (12) -> 7900 [Line 1A8]",
    "1A8:                                ---  JUMP JC, 02",
    "1A9: ZERO -> tmpBL                  ---  CALL INT (02) -> 7100 [Line 1E8]",
    "1AA: SIGMA -> tmpB                  ---  ALU DIV, tmpC, R",
    "1AB: SIGMA -> NULL   SIGMA -> tmpB  ---  ALU DIV, tmpC",
    "1AC: tmpB -> tmpC                   ---  ALU PASS, tmpA",
    "1AD: OPR -> tmpB     SIGMA -> NULL  -W-  ALU NEG, tmpA",
    "1AE:                                ---  JUMP JL, 01",
    "1AF:                                ---  JUMP JPOS/NZ4S, 09",
    "1B0: SIGMA -> tmpA                  ---  --",
    "1B1:                                ---  ALU NEG, tmpC",
    "1B2:                                ---  JUMP JNS, 0C",
    "1B3: SIGMA -> tmpC                  ---  --",
    "1B4: tmpA -> A                      ---  JUMP JNW, 0F",
    "1B5: tmpC -> D                      --E  --",
    "1B6:                                ---",
    "1B7: tmpC -> AH                     --E  --",
    "1B8: OP1 -> tmpB                    ---  ALU XI, tmpB",
    "1B9: SIGMA -> OP1                   -WE  EC=COMMIT",
    "1BA:                                ---",
    "1BB:                                ---",
    "1BC: PC -> tmpA      SP -> tmpB     ---  ALU DEC2, tmpB",
    "1BD: OP1 -> PC       SIGMA -> IND   ---  IC=FLUSH",
    "1BE: SIGMA -> SP                    ---  EC=MW, SR=SS",
    "1BF: tmpA -> OPR                    --E  --",
    "1C0: SIGMA -> tmpB                  ---  IC=SUSP",
    "1C1: OPR -> tmpA                    F--  ALU INC2, tmpB",
    "1C2: SIGMA -> DP                    ---  EC=MR",
    "1C3: OPR -> tmpB                    F--  CALL FARCALL (0D) -> 7680 [Line 228]",
    "1C4: OP1 -> PC                      --E  IC=FLUSH",
    "1C5:                                ---",
    "1C6:                                ---",
    "1C7:                                ---",
    "1C8: OPR -> tmpB     SIGMA -> tmpA  F--  ALU INC2, tmpA",
    "1C9: SIGMA -> DP                    ---  IC=SUSP, EC=MR",
    "1CA: OPR -> CS                      F--  --",
    "1CB: tmpB -> PC                     --E  IC=FLUSH",
    "1CC: SP -> tmpB                     ---  ALU DEC2, tmpB",
    "1CD: SIGMA -> SP                    ---  --",
    "1CE: OP1 -> OPR      SIGMA -> IND   --E  EC=MW, SR=SS",
    "1CF:                                ---",
    "1D0: ZERO -> DS      ZERO -> tmpB   ---  ALU PASS, tmpA",
    "1D1: ZERO -> FLAGS                  ---  IC=SUSP",
    "1D2: K -> CS                        ---  --",
    "1D3: ZERO -> PC                     ---  IC=FLUSH",
    "1D4: ZERO -> ES                     --E  IC=MFS",
    "1D5: ZERO -> SS                     ---  --",
    "1D6:                                ---",
    "1D7:                                ---",
    "1D8: 1 -> tmpBL                     ---  IC=SUSP",
    "1D9:                                ---  CALL INT (02) -> 7100 [Line 1E8]",
    "1DA: 2 -> tmpBL                     ---  IC=SUSP",
    "1DB:                                ---  CALL INT (02) -> 7100 [Line 1E8]",
    "1DC: ZERO -> DP                     ---  IC=SUSP, EC=INTA, SR=None",
    "1DD: OPR -> tmpB                    F--  --",
    "1DE: ZERO -> DP                     ---  EC=INTA, SR=None",
    "1DF: OPR -> tmpB                    F--  CALL INT (02) -> 7100 [Line 1E8]",
    "1E0:                                ---  ALU INC2, tmpA",
    "1E1: SIGMA -> DP     SIGMA -> tmpA  ---  IC=SUSP, EC=MR, SR=SS",
    "1E2: OPR -> PC                      F--  --",
    "1E3: SIGMA -> DP     SIGMA -> tmpA  ---  EC=MR, SR=SS",
    "1E4: OPR -> CS                      F--  IC=FLUSH",
    "1E5: SIGMA -> SP                    ---  --",
    "1E6: OPR -> FLAGS                   F-E  --",
    "1E7:                                ---",
    "1E8: ZERO -> tmpBH                  ---  ALU ADD, tmpB",
    "1E9: SIGMA -> tmpB                  ---  IC=SUSP, EC=INTV, SR=None",
    "1EA: SIGMA -> DP                    ---  EC=MR, SR=None",
    "1EB: SIGMA -> tmpB                  ---  ALU INC2, tmpB",
    "1EC: SIGMA -> DP                    ---  EC=MR, SR=None",
    "1ED: OPR -> tmpC                    F--  --",
    "1EE: SP -> tmpB                     ---  ALU DEC2, tmpB",
    "1EF: OPR -> tmpA                    F--  --",
    "1F0: FLAGS -> OPR                   F--  --",
    "1F1: SIGMA -> tmpB   SIGMA -> IND   ---  IC=CLR_IF_TF?, EC=MW, SR=SS",
    "1F2: CS -> OPR       SIGMA -> IND   F--  IC=MFS",
    "1F3:                                ---",
    "1F4:                                ---",
    "1F5: tmpA -> CS      SIGMA -> tmpB  ---  EC=MW, SR=SS",
    "1F6: PC -> OPR       SIGMA -> IND   F--  --",
    "1F7: tmpC -> PC                     ---  EC=MW, SR=SS",
    "1F8: SIGMA -> SP                    --E  IC=FLUSH",
    "1F9:                                ---",
    "1FA:                                ---",
    "1FB:                                ---",
    "1FC: tmpA -> A                      --E  --",
    "1FD:                                ---",
    "1FE:                                ---",
    "1FF:                                ---",
    "200: tmpA -> tmpB                   ---  ALU ADD, tmpB",
    "201: SIGMA -> NULL   ZERO -> tmpB   -W-  ALU ADC, tmpC",
    "202: SIGMA -> NULL                  ---  CALL MUL2 (05) -> 7280 [Line 204]",
    "203:                                ---",
    "204:                                ---  IC=CCOF",
    "205:                                ---  JUMP JZ, 03",
    "206:                                ---  IC=SCOF",
    "207:                                --E  --",
    "208: tmpA -> tmpB    SIGMA -> tmpA  ---  IC=SIGN",
    "209:                                ---",
    "20A: SIGMA -> tmpC   ZERO -> tmpB   ---  ALU PASS, tmpC",
    "20B: 8 -> LC                        ---  JUMP JNWO, 05",
    "20C: 16 -> LC                       ---  --",
    "20D: SIGMA -> tmpB                  ---  ALU MUL, tmpC, R",
    "20E: tmpB -> tmpC                   ---  JUMP JPOS/NZ4S, 0C",
    "20F:                                ---  ALU NEG, tmpA",
    "210: SIGMA -> tmpA                  -W-  ALU NEG, tmpB",
    "211:                                ---  JUMP JNC, 0B",
    "212:                                ---  ALU NOT, tmpB",
    "213: SIGMA -> tmpC   SIGMA -> tmpB  ---  --",
    "214: tmpA -> AL                     ---  CALL MUL (04) -> 7200 [Line 200]",
    "215:                                ---",
    "216:                                ---",
    "217:                                ---",
    "218: tmpA -> OP2                    ---  CALL MUL (04) -> 7200 [Line 200]",
    "219:                                ---",
    "21A:                                ---",
    "21B:                                ---",
    "21C: C -> tmpB                      ---  ALU PASS, tmpB",
    "21D: PC -> tmpB      SIGMA -> NULL  ---  ALU SUB, tmpA",
    "21E:                                ---  JUMP JZ, 04",
    "21F:                                ---  JUMP INT, 05",
    "220:                                --E  --",
    "221: PFXCNT -> tmpA                 ---  --",
    "222: SIGMA -> tmpB                  ---  ALU DEC, tmpB",
    "223: SIGMA -> PC                    --E  IC=FLUSH",
    "224:                                ---  JUMP JZ, 03",
    "225: SIGMA -> tmpB                  -W-  ALU XI, tmpB, R",
    "226: SIGMA -> OP1                   ---  EC=COMMIT",
    "227:                                --E  --",
    "228: tmpB -> tmpC    SP -> tmpB     ---  IC=SUSP",
    "229: CS -> OPR                      F--  ALU DEC2, tmpB",
    "22A: SIGMA -> DP                    ---  EC=MW, SR=SS",
    "22B: PC -> OPR       SIGMA -> tmpB  F--  --",
    "22C: tmpC -> CS      SIGMA -> IND   ---  EC=MW, SR=SS",
    "22D: tmpA -> PC                     --E  IC=FLUSH",
    "22E: SIGMA -> SP                    ---  --",
    "22F:                                ---",
    "230: OPR -> tmpC                    F--  ALU ADD, tmpA",
    "231: SIGMA -> SP                    ---  --",
    "232: OPR -> CS                      F--  --",
    "233: tmpC -> PC                     --E  IC=FLUSH",
    "234: SP -> tmpB                     ---  ALU DEC2, tmpB",
    "235: A -> OPR        SIGMA -> IND   F--  --",
    "236: SIGMA -> tmpB                  ---  EC=MW, SR=SS",
    "237: C -> OPR                       F--  CALL PUSHA (0B) -> 7580 [Line 238]",
    "238: SIGMA -> tmpB   SIGMA -> IND   ---  EC=MW, SR=SS",
    "239: D -> OPR                       F--  --",
    "23A: SIGMA -> tmpB   SIGMA -> IND   ---  EC=MW, SR=SS",
    "23B: B -> OPR                       F--  --",
    "23C: SIGMA -> tmpB   SIGMA -> IND   ---  EC=MW, SR=SS",
    "23D: SP -> OPR                      F--  --",
    "23E: SIGMA -> tmpB   SIGMA -> IND   ---  EC=MW, SR=SS",
    "23F: BP -> OPR                      F--  --",
    "240: SIGMA -> tmpB   SIGMA -> IND   ---  EC=MW, SR=SS",
    "241: SI -> OPR                      F--  --",
    "242: SIGMA -> tmpB   SIGMA -> IND   ---  EC=MW, SR=SS",
    "243: DI -> OPR                      F--  --",
    "244: SIGMA -> SP     SIGMA -> IND   --E  EC=MW, SR=SS",
    "245:                                ---",
    "246:                                ---",
    "247:                                ---",
    "248: SP -> DP        SP -> tmpB     ---  EC=MR, SR=SS",
    "249:                                ---  ALU INC2, tmpB",
    "24A: SIGMA -> tmpB   SIGMA -> IND   ---  EC=MR, SR=SS",
    "24B: OPR -> DI                      F--  CALL POPA (0C) -> 7600 [Line 24C]",
    "24C: SIGMA -> tmpB   SIGMA -> IND   ---  EC=MR, SR=SS",
    "24D: SIGMA -> tmpB                  ---  --",
    "24E: OPR -> SI                      F--  --",
    "24F: SIGMA -> tmpB   SIGMA -> IND   ---  EC=MR, SR=SS",
    "250: OPR -> BP                      F--  --",
    "251: SIGMA -> tmpB   SIGMA -> IND   ---  EC=MR, SR=SS",
    "252: OPR -> B                       F--  --",
    "253: SIGMA -> tmpB   SIGMA -> IND   ---  EC=MR, SR=SS",
    "254: OPR -> D                       F--  --",
    "255: SIGMA -> tmpB   SIGMA -> IND   ---  EC=MR, SR=SS",
    "256: OPR -> C                       F--  --",
    "257: SIGMA -> SP                    ---  --",
    "258: OPR -> A                       F-E  --",
    "259:                                ---",
    "25A:                                ---",
    "25B:                                ---",
    "25C: Q -> tmpAL      SP -> tmpB     ---  ALU DEC2, tmpB",
    "25D: Q -> tmpAH      SIGMA -> IND   ---  --",
    "25E:                                ---  EC=MW, SR=SS",
    "25F: BP -> OPR                      F--  CALL ENTER (0A) -> 7500 [Line 260]",
    "260: SIGMA -> SP     Q -> tmpB      ---  --",
    "261: ZERO -> tmpBH                  ---  ALU PASS, tmpB",
    "262: SIGMA -> NULL                  ---  ALU DEC, tmpB",
    "263: SP -> tmpC                     ---  JUMP JZ, 0E",
    "264: SIGMA -> NULL                  ---  ALU DEC, tmpB",
    "265: SIGMA -> LC                    ---  JUMP JZ, 0B",
    "266: BP -> tmpB                     ---  ALU DEC2, tmpB",
    "267: SIGMA -> BP     SIGMA -> IND   ---  EC=MR, SR=SS",
    "268: SP -> tmpB                     ---  --",
    "269: SIGMA -> SP     SIGMA -> IND   ---  EC=MW, SR=SS",
    "26A:                                ---  JUMP JLCNZ, 06",
    "26B: SP -> tmpB                     ---  ALU DEC2, tmpB",
    "26C: SIGMA -> SP     SIGMA -> IND   ---  EC=MW, SR=SS",
    "26D: tmpC -> OPR                    F--  --",
    "26E: tmpC -> BP      SP -> tmpB     --E  ALU SUB, tmpA",
    "26F: SIGMA -> SP                    ---  --",
    "270: BP -> DP        BP -> tmpB     ---  EC=MR, SR=SS",
    "271: 2 -> tmpA                      ---  ALU ADD, tmpA",
    "272: SIGMA -> SP                    ---  --",
    "273: OPR -> BP                      F-E  --",
    "274: OPR -> tmpC     SIGMA -> tmpA  F--  ALU INC2, tmpA",
    "275: FLAGS -> LC     SIGMA -> IND   ---  EC=MR",
    "276: OP2 -> tmpB                    ---  ALU SUB, tmpC",
    "277: SIGMA -> NULL                  -W-  --",
    "278: LC -> FLAGS     OP2 -> tmpA    ---  JUMP JL, 0A",
    "279: OPR -> tmpB                    F--  ALU SUB, tmpA",
    "27A: SIGMA -> NULL                  -W-  --",
    "27B: LC -> FLAGS                    ---  JUMP JL, 0B",
    "27C:                                --E  --",
    "27D:                                ---",
    "27E: OPR -> tmpA                    F--  --",
    "27F: 5 -> tmpBL                     ---  CALL INT (02) -> 7100 [Line 1E8]",
    "280: Q -> tmpA       SP -> tmpB     ---  ALU DEC2, tmpB",
    "281: SIGMA -> SP     SIGMA -> IND   ---  EC=MW, SR=SS",
    "282: tmpA -> tmpBL                  --E  --",
    "283: tmpB -> OPR                    ---  --",
    "284: Q -> tmpAL      SP -> tmpB     ---  ALU DEC2, tmpB",
    "285: Q -> tmpAH                     ---  --",
    "286: tmpA -> OPR     SIGMA -> IND   ---  EC=MW, SR=SS",
    "287: SIGMA -> SP                    --E  --",
    "288: Q -> tmpAL                     ---  ALU PASS, tmpA",
    "289: OP1 -> tmpB                    ---  --",
    "28A: tmpA -> LC      SIGMA -> NULL  ---  ALU PASS, tmpB",
    "28B:                                ---  CALL ROT (09) -> 7480 [Line 224]",
    "28C: Q -> tmpBL                     ---  JUMP JNW, 02",
    "28D: Q -> tmpBH                     ---  --",
    "28E: OP1 -> tmpA                    ---  ALU MULDIV, tmpB",
    "28F:                                ---  CALL IMUL2 (07) -> 7380 [Line 208]",
    "290: D -> DP                        ---  EC=MR, SR=None",
    "291: DIRSZ -> tmpA   DI -> tmpB     ---  --",
    "292: DI -> DP                       --E  EC=MW, SR=ES",
    "293: SIGMA -> DI                    ---  --",
    "294: C -> LC         C -> tmpB      ---  ALU PASS, tmpB",
    "295: SIGMA -> NULL                  ---  ALU ADD, tmpC",
    "296: DIRSZ -> tmpC                  ---  JUMP JZ, 07",
    "297: D -> DP                        ---  EC=MR, SR=None",
    "298:                                ---",
    "299: DI -> DP        DI -> tmpB     ---  EC=MW, SR=ES",
    "29A: SIGMA -> DI                    ---  JUMP REP, 03",
    "29B: LC -> C                        ---  CALL REP (08) -> 7400 [Line 21C]",
    "29C: SI -> DP                       ---  EC=MR",
    "29D: DIRSZ -> tmpA   SI -> tmpB     ---  --",
    "29E: D -> DP                        --E  EC=MW, SR=None",
    "29F: SIGMA -> SI                    ---  --",
    "2A0: C -> LC         C -> tmpB      ---  ALU PASS, tmpB",
    "2A1: SIGMA -> NULL                  ---  ALU ADD, tmpC",
    "2A2: DIRSZ -> tmpC                  ---  JUMP JZ, 07",
    "2A3: SI -> DP        SI -> tmpB     ---  EC=MR",
    "2A4: SIGMA -> SI                    ---  --",
    "2A5: D -> DP                        ---  EC=MW, SR=None",
    "2A6:                                ---  JUMP REP, 03",
    "2A7: LC -> C                        ---  CALL REP (08) -> 7400 [Line 21C]",
    "2A8: OP1 -> tmpB     C -> tmpA      ---  ALU BITM, tmpA",
    "2A9: K -> tmpA                      ---  ALU AND, tmpA",
    "2AA: SIGMA -> NULL                  -WE  --",
    "2AB:                                ---",
    "2AC: OP1 -> tmpB     Q -> tmpA      ---  ALU BITM, tmpA",
    "2AD: K -> tmpA                      ---  ALU AND, tmpA",
    "2AE: SIGMA -> NULL                  -WE  --",
    "2AF:                                ---",
    "2B0: OP1 -> tmpB     C -> tmpA      ---  ALU BITM, tmpA",
    "2B1: K -> tmpA                      ---  ALU OR, tmpA",
    "2B2: SIGMA -> OP1                   --E  EC=COMMIT",
    "2B3:                                ---",
    "2B4: OP1 -> tmpB     Q -> tmpA      ---  ALU BITM, tmpA",
    "2B5: K -> tmpA                      ---  ALU OR, tmpA",
    "2B6: SIGMA -> OP1                   --E  EC=COMMIT",
    "2B7:                                ---",
    "2B8: OP1 -> tmpB     C -> tmpA      ---  ALU BITM, tmpA",
    "2B9: K -> tmpA                      ---  ALU NOT, tmpA",
    "2BA: SIGMA -> tmpA                  ---  ALU AND, tmpA",
    "2BB: SIGMA -> OP1                   --E  EC=COMMIT",
    "2BC: OP1 -> tmpB     Q -> tmpA      ---  ALU BITM, tmpA",
    "2BD: K -> tmpA                      ---  ALU NOT, tmpA",
    "2BE: SIGMA -> tmpA                  ---  ALU AND, tmpA",
    "2BF: SIGMA -> OP1                   --E  EC=COMMIT",
    "2C0: OP1 -> tmpB     C -> tmpA      ---  ALU BITM, tmpA",
    "2C1: K -> tmpA                      ---  ALU XOR, tmpA",
    "2C2: SIGMA -> OP1                   --E  EC=COMMIT",
    "2C3:                                ---",
    "2C4: OP1 -> tmpB     Q -> tmpA      ---  ALU BITM, tmpA",
    "2C5: K -> tmpA                      ---  ALU XOR, tmpA",
    "2C6: SIGMA -> OP1                   --E  EC=COMMIT",
    "2C7:                                ---",
    "2C8: C -> tmpAL                     ---  ALU INC, tmpA",
    "2C9: SIGMA -> tmpB                  ---  ALU SHR, tmpB",
    "2CA: SIGMA -> LC                    ---  IC=BCD_INIT",
    "2CB: SI -> DP        SI -> tmpA     ---  EC=MR",
    "2CC:                                ---  ALU INC, tmpA",
    "2CD: SIGMA -> SI                    ---  --",
    "2CE: OPR -> tmpC                    F--  --",
    "2CF: DI -> DP                       ---  EC=MR, SR=ES",
    "2D0: OPR -> tmpB                    F--  ALU ADC, tmpC",
    "2D1: SIGMA -> tmpB                  -W-  ALU ADJD, tmpB",
    "2D2: K -> tmpA                      ---  ALU ADD, tmpA",
    "2D3: DI -> DP        SIGMA -> NULL  -W-  EC=MW, SR=ES",
    "2D4:                                ---  IC=BCD_ZERO",
    "2D5: SIGMA -> OPR    DI -> tmpA     ---  ALU INC, tmpA",
    "2D6: SIGMA -> DI     ONES -> tmpB   ---  JUMP JLCNZ, 03",
    "2D7: C -> tmpAL                     ---  ALU ADD, tmpB",
    "2D8:                                ---  JUMP JC, 03",
    "2D9: 1 -> tmpB                      ---  JUMP JPOS/NZ4S, 03",
    "2DA: ZERO -> tmpB                   ---  --",
    "2DB: SIGMA -> NULL                  -W-  ALU INC, tmpA",
    "2DC: SIGMA -> tmpB                  ---  ALU SHR, tmpB",
    "2DD: DI -> tmpB      SIGMA -> tmpA  ---  ALU SUB, tmpA",
    "2DE: SIGMA -> DI     SI -> tmpB     --E  --",
    "2DF: SIGMA -> SI                    ---  --",
    "2E0: OPR -> tmpB                    F--  ALU SBB, tmpC",
    "2E1: SIGMA -> tmpB                  -W-  ALU ADJD, tmpB",
    "2E2: K -> tmpA                      ---  ALU SUB, tmpA",
    "2E3: DI -> DP        SIGMA -> NULL  -W-  EC=MW, SR=ES",
    "2E4: OPR -> tmpB                    F--  ALU SBB, tmpC",
    "2E5: SIGMA -> tmpB                  -W-  ALU ADJD, tmpB",
    "2E6: K -> tmpA                      ---  ALU SUB, tmpA",
    "2E7: DI -> DP        SIGMA -> NULL  -W-  --",
    "2E8: 4 -> LC                        ---  --",
    "2E9: OP1 -> tmpBL                   ---  --",
    "2EA: AL:AH -> tmpBH                 ---  ALU PASS, tmpB",
    "2EB: SIGMA -> tmpB                  ---  ALU ROL12, tmpB, R",
    "2EC: tmpB -> OP1                    ---  ALU PASS, tmpB",
    "2ED: A -> tmpA                      ---  EC=COMMIT",
    "2EE: tmpB -> A                      ---  --",
    "2EF: AL:AH -> tmpB                  ---  --",
    "2F0: tmpA -> tmpBH                  --E  --",
    "2F1: tmpB -> A                      ---  --",
    "2F2:                                ---",
    "2F3:                                ---",
    "2F4: 8 -> LC                        ---  --",
    "2F5: OP1 -> tmpBL                   ---  --",
    "2F6: AL:AH -> tmpBH                 ---  ALU PASS, tmpB",
    "2F7: SIGMA -> tmpB                  ---  ALU ROL12, tmpB, R",
    "2F8: 15 -> tmpC                     ---  ALU PASS, tmpC",
    "2F9: OP2 -> tmpAL    SIGMA -> tmpB  ---  ALU SUB, tmpA",
    "2FA: SIGMA -> A                     ---  ALU PASS, tmpA",
    "2FB:                                ---",
    "2FC: SI -> DP        SIGMA -> tmpB  ---  EC=MR",
    "2FD: OP1 -> tmpAL                   ---  ALU ADD, tmpA",
    "2FE: tmpC -> tmpB    SIGMA -> tmpA  ---  ALU AND, tmpA",
    "2FF: SIGMA -> LC                    ---  ALU SUB, tmpA",
    "300: SI -> tmpB      SIGMA -> NULL  -W-  ALU INC2, tmpB",
    "301: OPR -> tmpC                    F--  JUMP JZ, 0B",
    "302:                                ---  JUMP JNC, 0E",
    "303: SIGMA -> SI     SIGMA -> IND   ---  JUMP JZ, 0E",
    "304: tmpC -> tmpA                   ---  EC=MR",
    "305: OPR -> tmpC                    F--  --",
    "306: LC -> tmpB                     ---  ALU INC, tmpB",
    "307: SIGMA -> LC     SIGMA -> tmpB  ---  ALU ADJA, tmpB",
    "308: SIGMA -> NULL                  ---  ALU PASS, tmpC",
    "309: tmpB -> OP1     SIGMA -> tmpB  ---  --",
    "30A: ZERO -> tmpC                   ---  ALU PASS, tmpB",
    "30B: SIGMA -> tmpB                  ---  ALU MUL, tmpC, R",
    "30C: A -> tmpB                      ---  ALU PASS, tmpB",
    "30D: SIGMA -> LC                    ---  --",
    "30E: ZERO -> tmpB                   ---  JUMP JZ, 08",
    "30F: SIGMA -> tmpB                  ---  ALU MUL, tmpC, R",
    "310: 15 -> tmpC                     ---  ALU PASS, tmpC",
    "311: Q -> tmpAL      SIGMA -> tmpB  ---  --",
    "312:                                ---  ALU SUB, tmpA",
    "313: SIGMA -> A                     ---  ALU PASS, tmpA",
    "314: OP1 -> tmpAL                   ---  ALU PASS, tmpA",
    "315: tmpA -> LC      SIGMA -> NULL  ---  --",
    "316: ZERO -> tmpC                   ---  JUMP JZ, 06",
    "317: DI -> DP                       ---  EC=MR, SR=ES",
    "318: OPR -> tmpB                    F--  ALU PASS, tmpB",
    "319: SIGMA -> tmpB                  ---  ALU MUL, tmpC, R",
    "31A: tmpA -> OPR                    ---  --",
    "31B: OP2 -> tmpAL                   ---  ALU INC, tmpA",
    "31C: OP1 -> tmpAL    SIGMA -> tmpB  ---  ALU ADD, tmpA",
    "31D: SIGMA -> tmpC                  ---  --",
    "31E: tmpB -> LC                     ---  --",
    "31F: 15 -> tmpB                     ---  ALU AND, tmpC",
    "320: OP1 -> tmpAL                   ---  --",
    "321: SIGMA -> OP1                   ---  ALU SUB, tmpC",
    "322: A -> tmpB       SIGMA -> NULL  -W-  CALL EXT (0E) -> 7700 [Line 324]",
    "323:                                ---",
    "324: DI -> DP                       ---  JUMP JNC, 0E",
    "325: 16 -> tmpB                     ---  ALU SUB, tmpA",
    "326: SIGMA -> LC                    ---  --",
    "327: OPR -> tmpA                    ---  --",
    "328: ZERO -> tmpC    A -> tmpB      ---  ALU PASS, tmpB",
    "329: SIGMA -> tmpB                  ---  ALU MUL, tmpC, R",
    "32A: DI -> tmpC                     ---  ALU PASS, tmpC",
    "32B: DI -> DP                       ---  EC=MW, SR=ES",
    "32C: tmpA -> OPR                    ---  --",
    "32D: OP1 -> tmpAL                   ---  ALU INC2, tmpC",
    "32E: SIGMA -> DI                    ---  ALU PASS, tmpA",
    "32F: tmpA -> LC      SIGMA -> NULL  ---  --",
    "330: ZERO -> tmpC                   ---  JUMP JNZ, 0E",
    "331: SIGMA -> OP1                   --E  --",
    "332:                                ---",
    "333: DI -> DP                       ---  EC=MR, SR=ES",
    "334: OPR -> tmpA                    ---  ALU PASS, tmpB",
    "335: SIGMA -> tmpB                  ---  ALU MUL, tmpC, R",
    "336: tmpA -> tmpC                   ---  --",
    "337: OP1 -> tmpAL                   ---  --",
    "338: tmpA -> LC                     ---  --",
    "339: OPR -> tmpB                    F--  ALU PASS, tmpB",
    "33A: SIGMA -> tmpB                  ---  ALU SHR, tmpB, R",
    "33B: tmpA -> LC                     ---  ALU PASS, tmpC",
    "33C: DI -> DP        SIGMA -> tmpA  ---  --",
    "33D: ZERO -> tmpC                   ---  --",
    "33E: SIGMA -> tmpB                  ---  ALU DIV, tmpC, R",
    "33F: tmpB -> OPR                    --E  EC=MW, SR=ES",
    "340: OPR -> tmpB                    F--  ALU PASS, tmpB",
    "341: SIGMA -> tmpB                  ---  ALU MUL, tmpC, R",
    "342: tmpA -> OPR                    ---  --",
    "343: Q -> tmpAL                     ---  ALU INC, tmpA",
    "344: Q -> tmpBL                     ---  --",
    "345: 1 -> LC                        ---  CALL EM_INT (03) -> 7180 [Line 1E8]",
    "346:                                ---",
    "347:                                ---",
    "348:                                --E  --",
    "349:                                ---",
    "34A:                                ---",
    "34B:                                ---",
    "34C: OP1 -> tmpA                    ---  --",
    "34D: B -> DP                        ---  --",
    "34E: tmpA -> OP2                    --E  EC=COMMIT",
    "34F: PC -> NULL                     ---  --",
    "350: Q -> tmpAL                     ---  --",
    "351: B -> DP                        ---  --",
    "352: tmpA -> OP2                    --E  EC=COMMIT",
    "353: PC -> NULL                     ---  --",
    "354: Q -> tmpAL                     ---  --",
    "355: Q -> tmpAH                     ---  --",
    "356: tmpA -> OP2                    --E  --",
    "357:                                ---",
    "358: Q -> tmpAL                     ---  --",
    "359: Q -> tmpAH                     ---  --",
    "35A: tmpA -> DP                     ---  EC=MR",
    "35B: OPR -> AL                      F-E  --",
    "35C: Q -> tmpAL                     ---  ALU PASS, tmpA",
    "35D: Q -> tmpAH                     ---  --",
    "35E: A -> OPR        SIGMA -> IND   --E  EC=MW",
    "35F: PC -> NULL                     ---  --",
    "360: Q -> tmpAL                     ---  --",
    "361: Q -> tmpAH                     ---  --",
    "362: tmpA -> DP                     ---  EC=MR",
    "363: OPR -> B                       F-E  --",
    "364: Q -> tmpAL                     ---  ALU PASS, tmpA",
    "365: Q -> tmpAH                     ---  --",
    "366: B -> OPR        SIGMA -> IND   --E  EC=MW",
    "367: PC -> NULL                     ---  --",
    "368: OP2 -> DP                      ---  EC=MR",
    "369: OPR -> AL                      F-E  --",
    "36A:                                ---",
    "36B:                                ---",
    "36C: OP2 -> DP                      ---  --",
    "36D: A -> OPR                       --E  EC=MW",
    "36E: PC -> NULL                     ---  --",
    "36F:                                ---",
    "370: BP -> DP        B -> tmpA      ---  EC=MR",
    "371: OPR -> B        BP -> tmpB     F--  ALU PASS, tmpB",
    "372: tmpA -> OPR     SIGMA -> IND   --E  EC=MW",
    "373: PC -> NULL                     ---  --",
    "374: B -> tmpA                      ---  --",
    "375: D -> B                         --E  --",
    "376: tmpA -> D                      ---  --",
    "377:                                ---",
    "378: B -> PC                        --E  IC=FLUSH",
    "379:                                ---",
    "37A:                                ---",
    "37B:                                ---",
    "37C: B -> BP                        --E  --",
    "37D:                                ---",
    "37E:                                ---",
    "37F:                                ---",
    "380: OP2 -> tmpB                    ---  ALU INC, tmpB",
    "381: B -> DP                        ---  --",
    "382: SIGMA -> OP2                   -WE  EC=COMMIT",
    "383: PC -> NULL                     ---  --",
    "384: OP2 -> tmpB                    ---  ALU DEC, tmpB",
    "385: B -> DP                        ---  --",
    "386: SIGMA -> OP2                   -WE  EC=COMMIT",
    "387: PC -> NULL                     ---  --",
    "388: OP2 -> tmpB                    --E  ALU INC, tmpB",
    "389: SIGMA -> OP2                   ---  --",
    "38A:                                ---",
    "38B:                                ---",
    "38C: OP2 -> tmpB                    --E  ALU DEC, tmpB",
    "38D: SIGMA -> OP2                   ---  --",
    "38E:                                ---",
    "38F:                                ---",
    "390: OP1 -> tmpA     A -> tmpB      ---  ALU XI, tmpA",
    "391: B -> DP                        --E  --",
    "392: SIGMA -> AL                    -W-  --",
    "393:                                ---",
    "394: Q -> tmpAL      A -> tmpB      ---  ALU XI, tmpA",
    "395: SIGMA -> AL                    -WE  --",
    "396:                                ---",
    "397:                                ---",
    "398: OP2 -> tmpA     B -> tmpB      ---  ALU ADD, tmpA",
    "399: SIGMA -> B                     --E  --",
    "39A:                                ---",
    "39B:                                ---",
    "39C: A -> tmpA                      ---  ALU ADJD, tmpA",
    "39D: K -> tmpB                      --E  ALU ADD, tmpA",
    "39E: SIGMA -> AL     SIGMA -> NULL  -W-  --",
    "39F:                                ---",
    "3A0: A -> tmpA                      --E  ALU NOT, tmpA",
    "3A1: SIGMA -> AL                    ---  --",
    "3A2:                                ---",
    "3A3:                                ---",
    "3A4: 1 -> LC                        ---  --",
    "3A5: A -> tmpB                      ---  ALU PASS, tmpB",
    "3A6: SIGMA -> tmpB                  -W-  ALU XI, tmpB, R",
    "3A7: SIGMA -> AL                    --E  --",
    "3A8: Q -> tmpAL                     ---  --",
    "3A9: Q -> tmpAH                     ---  --",
    "3AA:                                ---",
    "3AB: tmpA -> PC                     --E  IC=FLUSH",
    "3AC: Q -> tmpAL                     ---  --",
    "3AD: Q -> tmpAH                     ---  --",
    "3AE:                                ---  JUMP OPC, 05",
    "3AF:                                --E  --",
    "3B0:                                ---",
    "3B1: tmpA -> PC                     --E  IC=FLUSH",
    "3B2:                                ---",
    "3B3:                                ---",
    "3B4: BP -> tmpB                     ---  ALU DEC2, tmpB",
    "3B5: SIGMA -> BP     SIGMA -> IND   ---  IC=SUSP",
    "3B6: PC -> OPR                      ---  EC=MW",
    "3B7: OPC38 -> PC                    --E  IC=FLUSH",
    "3B8: Q -> tmpAL      BP -> tmpB     ---  ALU DEC2, tmpB",
    "3B9: Q -> tmpAH                     ---  --",
    "3BA: SIGMA -> BP     SIGMA -> IND   ---  IC=SUSP",
    "3BB: PC -> OPR                      ---  EC=MW",
    "3BC: tmpA -> PC                     --E  IC=FLUSH",
    "3BD:                                ---",
    "3BE:                                ---",
    "3BF:                                ---",
    "3C0: Q -> tmpAL      BP -> tmpB     ---  ALU DEC2, tmpB",
    "3C1: Q -> tmpAH                     ---  --",
    "3C2:                                ---  JUMP OPC, 05",
    "3C3:                                --E  --",
    "3C4:                                ---",
    "3C5: SIGMA -> BP     SIGMA -> IND   ---  IC=SUSP",
    "3C6: PC -> OPR                      ---  EC=MW",
    "3C7: tmpA -> PC                     --E  IC=FLUSH",
    "3C8: BP -> DP                       ---  IC=SUSP, EC=MR",
    "3C9: BP -> tmpA                     ---  ALU INC2, tmpA",
    "3CA: SIGMA -> BP                    ---  --",
    "3CB: OPR -> PC                      F-E  IC=FLUSH",
    "3CC:                                ---",
    "3CD:                                ---  JUMP OPC, 04",
    "3CE:                                --E  --",
    "3CF:                                ---",
    "3D0: BP -> DP                       ---  IC=SUSP, EC=MR",
    "3D1: BP -> tmpA                     ---  ALU INC2, tmpA",
    "3D2: SIGMA -> BP                    ---  --",
    "3D3: OPR -> PC                      F-E  IC=FLUSH",
    "3D4: BP -> tmpB                     ---  ALU DEC2, tmpB",
    "3D5: SIGMA -> BP     SIGMA -> IND   ---  --",
    "3D6: OP2 -> OPR                     --E  EC=MW",
    "3D7: PC -> NULL                     ---  --",
    "3D8: BP -> tmpB                     ---  ALU DEC2, tmpB",
    "3D9: SIGMA -> BP     SIGMA -> IND   ---  --",
    "3DA: OP2 -> OPR                     --E  EC=MW",
    "3DB: PC -> NULL                     ---  --",
    "3DC: FLAGS -> tmpAL  BP -> tmpB     ---  ALU DEC2, tmpB",
    "3DD: AL:AH -> tmpAH  SIGMA -> IND   ---  --",
    "3DE: tmpA -> OPR                    --E  EC=MW",
    "3DF: SIGMA -> BP                    ---  --",
    "3E0: BP -> DP        BP -> tmpA     ---  EC=MR",
    "3E1:                                ---  ALU INC2, tmpA",
    "3E2: SIGMA -> BP                    ---  --",
    "3E3: OPR -> OP2                     F-E  --",
    "3E4: BP -> DP        BP -> tmpA     ---  EC=MR",
    "3E5:                                ---  ALU INC2, tmpA",
    "3E6: SIGMA -> BP                    ---  --",
    "3E7: OPR -> OP2                     F-E  --",
    "3E8: BP -> DP        A -> tmpB      ---  EC=MR",
    "3E9: OPR -> A                       F--  --",
    "3EA: AL:AH -> tmpA                  ---  --",
    "3EB: tmpB -> tmpAH   A -> tmpB      ---  ALU PASS, tmpB",
    "3EC: tmpA -> A       SIGMA -> tmpA  ---  --",
    "3ED: FLAGS -> tmpAH  BP -> tmpB     ---  ALU INC2, tmpB",
    "3EE: tmpA -> FLAGS                  --E  --",
    "3EF: SIGMA -> BP                    ---  --",
    "3F0: Q -> tmpAL                     ---  ALU PASS, tmpA",
    "3F1: A -> OPR        SIGMA -> IND   --E  EC=MW, SR=None",
    "3F2: PC -> NULL                     ---  --",
    "3F3: PC -> NULL                     ---  --",
    "3F4: Q -> tmpAL                     ---  --",
    "3F5: tmpA -> DP                     ---  EC=MR, SR=None",
    "3F6: OPR -> AL                      F-E  --",
    "3F7:                                ---",
    "3F8: SP -> DP        SP -> tmpA     ---  IC=SUSP, EC=MR, SR=SS",
    "3F9:                                ---  IC={0}",
    "3FA:                                ---  CALL IRET (01) -> 7080 [Line 1E0]",
    "3FB:                                ---",
    "3FC: Q -> tmpBL                     ---  --",
    "3FD: ZERO -> LC                     ---  CALL EM_INT (03) -> 7180 [Line 1E8]",
    "3FE:                                ---",
    "3FF:                                ---",
};

static uint16_t debugWordIndex(uint16_t address) {
    if (address >= 0x8000) { return 0xffff; }
    const auto base = columns[directory[address >> 4]][(address >> 2) & 3];
    return base == 0xffff ? 0xffff : uint16_t(base + (address & 3));
}

const char* GeneratedCpu::microcodeDisassembly(uint16_t address) const {
    const auto index = debugWordIndex(address & 0x7fff);
    if (index == 0xffff) { return ""; }
    if (model_ == Model::V20) {
        switch (index) {
        case 0x1dc: return "1DC: A -> tmpC                      ---  IC=SUSP, EC=INTA, SR=None";
        case 0x1dd: return "1DD: OPR -> A                       F--  --";
        case 0x1de: return "1DE: AL:AH -> tmpBL                 ---  --";
        case 0x1df: return "1DF: tmpC -> A                      ---  CALL INT (02) -> 7100 [Line 1E8]";
        default: break;
        }
    }
    return disassembly[index];
}

uint16_t GeneratedCpu::microcodeListingLine(uint16_t address) const {
    const auto index = debugWordIndex(address);
    if (index == 0xffff) { return 0xffff; }
    const unsigned gap = model_ == Model::V20 ? 0x1e0 : 0x1dc;
    return uint16_t(index + (index >= gap ? 4 : 0));
}

} // namespace marty::nec
