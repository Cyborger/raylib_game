/*******************************************************************************************
*
*   raylib game template
*
*   <Game title>
*   <Game description>
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

/**
*  Projet 1 DEFI
*     Nom prenom : Bouchaud Lucas
*     Nom prenom : SEZNEC Romain
*     Numero binome : L
*/

#include "raylib.h"
#include "raylib_game.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include "ArduinoComP1DEFI.h"

int main(void)
{
	//--------------------------------------------------------------------------------------
	// Initialization
	//--------------------------------------------------------------------------------------

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Projet 1 DEFI - BOUCHAUD Lucas - SEZNEC Romain");
	InitAudioDevice(); 
	SetTargetFPS(TARGET_FPS);

	GameTransform carTransform = {{400, 800}, {30, 60}};
	Car car = create_car(carTransform);

	GameTransform obstacleTransform = {{200, 150}, {100, 50}};
	Obstacle obstacle = create_obstacle(obstacleTransform);

	GameTransform nitroUiTransform = {{WINDOW_WIDTH - 110, WINDOW_HEIGHT - 40}, {100, 30}};
	NitroUI nitroUi = create_nitro_ui(nitroUiTransform);

	Vector2 debugUiPosition = { 10, 40 };
	DebugUI debugUi = create_debug_ui(debugUiPosition, 10);

	Vector2 previousCarPosition = car.transform.position;

    // Arduino
    char* portName = "/dev/ttyACM0"; // prof = /dev/ttyACM0
    SerialCom sCom = startArduinoConnection(portName, 9600);
    char* arduinoMessage = "(null)";

	//--------------------------------------------------------------------------------------
	// Game loop principale (code execute a chaque frame (60 fois par secondes))
	//--------------------------------------------------------------------------------------
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
        char* arduinoMessageHard = arduinoReceiveLatestMsg(sCom, '<', '>');
        if (arduinoMessageHard)
            arduinoMessage = arduinoMessageHard;

		bool carCollidingObstacle = isCarCollidingObstacle(&car, &obstacle);
		debugUi.line = 0;

		// Gestion de l'input
		inputManagement(&car, carCollidingObstacle, arduinoMessage);
		
		// Gestion des collisions avec l'obstacle
		obstacleCollisionManagement(&car, &obstacle, previousCarPosition);

		// Gestion des bords de la fenetre
		windowEdgeManagement(&car);

		previousCarPosition = car.transform.position;

		// Gestion de l'affichage
		BeginDrawing();
		{
			ClearBackground(RAYWHITE);

			// Gameplay
			drawCar(car);
			drawObstacle(obstacle);

			// UI
			drawNitroUi(nitroUi, car);
			drawDebugUi(debugUi, car, arduinoMessage);
		}
		EndDrawing();
	}

	//--------------------------------------------------------------------------------------
	// De-Initialization
	//--------------------------------------------------------------------------------------

    closeArduinoConnection(sCom); // Close arduino connection
	CloseAudioDevice();     // Close audio context
	CloseWindow();          // Close window and OpenGL context

	return 0;
}
