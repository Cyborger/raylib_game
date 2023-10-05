#pragma once
#include "raylib.h"

//----------------------------------------------------------------------------------
// Constantes
//----------------------------------------------------------------------------------
enum
{
    WINDOW_WIDTH = 800,
    WINDOW_HEIGHT = 1000,
    TARGET_FPS = 60
};

//----------------------------------------------------------------------------------
// Structures
//----------------------------------------------------------------------------------
// Vector2Transform, données positionnelles 
typedef struct Vector2Transform
{
    Vector2 position;
    Vector2 size;
} Vector2Transform;

