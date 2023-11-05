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
// RectangleEdges, structure obligatoire qui contient les 4 cotes de la voiture sous forme de flottants
typedef struct RectangleEdges
{
    float left;   // left x-coordinate
    float right;  // right x-coordinate
    float top;    // top y-coordinate
    float bottom; // bottom y-coordinate
} RectangleEdges;

// RectangleCentered, structure obligatoire qui contient deux Vector2 correspondant au centre du rectange et dimensions
typedef struct RectangleCentered
{
    Vector2 center;
    Vector2 size;
} RectangleCentered;

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
// Structures UI
//----------------------------------------------------------------------------------
typedef struct NitroUI
{
	GameTransform transform;
} NitroUI;

typedef struct DebugUI
{
	Vector2 position;
	float spacing;
	int line;
} DebugUI;

//----------------------------------------------------------------------------------
// Fonctions obligatoires
//----------------------------------------------------------------------------------
// Fonction obligatoire, transforme un Rectangle en RectangleEdges
RectangleEdges RecToRecEdges(Rectangle rectangle);

// Fonction obligatoire, transforme un RectangleEdges en RectangeCentered
RectangleCentered RecEdgesToRecCentered(RectangleEdges rectangleEdges);

// Fonction obligatoire, transforme un RectangleCentered en Rectangle
Rectangle RecCenteredToRec(RectangleCentered rectangleCentered);

// Fonction obligatoire, transforme un Rectangle en RectangleCentered
RectangleCentered RecToRecCentered(Rectangle rectangle);

// Fonction obligatoire, transforme un RectangleCentered en RectangleEdges
RectangleEdges RecCenteredToRecEdges(RectangleCentered rectangleCentered);

// Fonction obligatoire, transforme un RectangleEdges en Rectangle
Rectangle RecEdgesToRec(RectangleEdges rectangleEdges);


//----------------------------------------------------------------------------------
// Fonctions gameplay
//----------------------------------------------------------------------------------
// Création de la voiture à l'aide des données positionnelles
Car create_car(GameTransform carTransform);

// Gestion des entrees utilisateurs
void inputManagement(Car *car, bool carCollidingObstacle, char* arduinoMessage);

// Gestion des collisions de la voiture avec les bords de la fenetre
void windowEdgeManagement(Car *car);

// Création de l'obstacle
Obstacle create_obstacle(GameTransform obstacleTransform);

// Gestion des collisions de la voiture avec l'obstacle
void obstacleCollisionManagement(Car *car, Obstacle *obstacle, Vector2 previousCarPosition);
bool isCarCollidingObstacle(Car *car, Obstacle *obstacle);
bool lineColliding(Vector2 pointA, Vector2 pointB, Vector2 pointC, Vector2 pointD);

//----------------------------------------------------------------------------------
// Fonctions UI
//----------------------------------------------------------------------------------
// Creation de l'UI du nitro
NitroUI create_nitro_ui(GameTransform nitroUiTransform);

// Creation de l'UI de debug
DebugUI create_debug_ui(Vector2 position, float spacing);

//----------------------------------------------------------------------------------
// Fonctions dessin
//----------------------------------------------------------------------------------
void drawCar(Car car);
void drawObstacle(Obstacle obstacle);

void drawNitroUi(NitroUI nitroUi, Car car);
void drawDebugUi(DebugUI debugUi, Car car, char* arduinoMessage);