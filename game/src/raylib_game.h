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
// Structures gameplay
//----------------------------------------------------------------------------------
// GameTransform, données positionnelles 
typedef struct GameTransform
{
    Vector2 position;
    Vector2 size;
} GameTransform;

// Cockpit, données sur l'habitacle de la voiture
typedef struct Cockpit
{
    Vector2 size;
    Color color;
} Cockpit;

// Headlights, données sur les phares avant de la voiture
typedef struct Headlights
{
    float radius;
    Color color;
} Headlights;

// Backlights, données sur les phares arrières de la voiture
typedef struct Backlights
{
    Vector2 size;
    Color color;
} Backlights;

// Wheels, données sur les roues de la voiture
typedef struct Wheels
{
    Vector2 size;
    Vector2 offset;
    Color color;
} Wheels;

// Nitro, données sur le nitro
typedef struct Nitro
{
    float reserve;
    bool active;
} Nitro;


// Car, données sur la voiture
typedef struct Car
{
    GameTransform transform;
    Color color;

    Vector2 speed;
    Vector2 acceleration;
    Vector2 motorForce;

    float frictionCoefficient;
    float horsePower;

    Cockpit cockpit;
    Headlights headlights;
    Backlights backlights;
    Wheels wheels;
    Nitro nitro;
} Car;

typedef struct Obstacle
{
    GameTransform transform;
    Color color;
} Obstacle;

//----------------------------------------------------------------------------------
// Fonctions gameplay
//----------------------------------------------------------------------------------
// Création de la voiture à l'aide des données positionnelles
Car create_car(GameTransform carTransform);

// Création de l'obstacle
Obstacle create_obstacle(GameTransform obstacleTransform);

// Gestion des collisions de la voiture avec l'obstacle
bool isCarCollidingObstacle(Car car, Obstacle obstacle);
bool lineColliding(Vector2 pointA, Vector2 pointB, Vector2 pointC, Vector2 pointD);