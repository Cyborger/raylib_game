#pragma once
#include <dinput.h>

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
// Structures gameplay
//----------------------------------------------------------------------------------
// Vector2Transform, données positionnelles 
typedef struct Vector2Transform
{
    Vector2 position;
    Vector2 size;
} Vector2Transform;

// Cockpit, données sur l'habitacle de la voiture
typedef struct Cockpit
{
    Vector2 size;
    Color color = DARKGRAY;
} Cockpit;

// Headlights, données sur les phares avant de la voiture
typedef struct Headlights
{
    float radius;
    Color color = YELLOW;
} Headlights;

// Backlights, données sur les phares arrières de la voiture
typedef struct Backlights
{
    Vector2 size;
    Color color = RED;
} Backlights;

// Wheels, données sur les roues de la voiture
typedef struct Wheels
{
    Vector2 size;
    Vector2 offset;
    Color color = BLACK;
} Wheels;

// Nitro, données sur le nitro
typedef struct Nitro
{
    float reserve = 100;
    bool active = false;
} Nitro;


// Car, données sur la voiture
typedef struct Car
{
    Vector2Transform transform = {{400, 800}, {30, 60}};
    Color color = RED;

    Vector2 speed = {0, 0};
    Vector2 acceleration = {0, 0};
    Vector2 motorForce = {0, 0};

    float frictionCoefficient = 5;
    float horsePower = 200;

    Cockpit cockpit = {{transform.size.x / 3, transform.size.y / 3}};
    Headlights headlights = {transform.size.x / 6};
    Backlights backlights = {{transform.size.x / 3, transform.size.y / 15}};
    Wheels wheels = {
        {transform.size.x / 6, transform.size.y / 6},
        {transform.size.x / 15, transform.size.y / 12}
    };
    Nitro nitro;
} Car;
