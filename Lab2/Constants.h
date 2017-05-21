#pragma once
const int positionsIndex = 0;
const int colorsIndex = 1;



#pragma region Matrix
const static char* M_MODEL = "model";
const static char* M_VIEW = "view";
const static char* M_PROJ = "projection";
static const char* NORM_MATRIX = "normalMatrix";
const static char* LSPACE_MATRIX = "lightSpaceMatrix";
#pragma endregion

const static std::string TEX_DIR = "Textures//";

const static char* CAM_POS = "cameraPosition";
const static char* SHADOW_MAP = "shadowMap";
const static char* DIFFUSE_TEX = "materialTex";

#pragma region Light
static char* L_POS = "position";
static char* L_DIR = "direction";
static char* L_INTENS = "intensities";
static char* L_AMBIENTCOEFF = "ambientCoefficient";
const static char* L_ATTEN = "attenuation";
const int POINT_LIGHT = 0;//точечный источник
const int DIR_LIGHT = 1;//направленный источник
const static char* NUM_LIGHTS = "numLights";//количество источников света
const static char* L_ARR = "allLights";//имя массива источников света
#pragma endregion
#pragma region Material
static const char* MAT_SHINE = "materialShininess";//интенсивность отражения
static const char* MAT_SPCOLOR = "materialSpecularColor";//цвет блика
static const char* MAT_ALPHA = "materialAlpha";//непрозрачность
const static char* MAT_TEX = "materialTex";//текстура
#pragma endregion
