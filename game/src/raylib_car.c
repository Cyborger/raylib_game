#include "raylib.h"
#include "raylib_game.h"

Car create_car(GameTransform carTransform)
{
    Car car = {
        .transform = carTransform,
        .color = RED,
        
        .speed = {0, 0},
        .acceleration = {0, 0},
        .motorForce = {0, 0},

        .frictionCoefficient = 5,
        .horsePower = 200,

        .cockpit = {
            .size = {carTransform.size.x / 3, carTransform.size.y / 3},
            .color = DARKGRAY
        },
        .headlights = {
            .radius = carTransform.size.x / 6,
            .color = YELLOW
        },
        .backlights = {
            .size = {carTransform.size.x / 3, carTransform.size.y / 15},
            .color = RED
        },
        .wheels = {
            .size = {carTransform.size.x / 6, carTransform.size.y / 6},
            .offset = {carTransform.size.x / 15, carTransform.size.y / 12},
            .color = BLACK
        },
        .nitro = {
            .reserve = 100,
            .active = false
        }
    };

    return car;
}