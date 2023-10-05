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
*     Nom prénom : Bouchaud Lucas
*     Nom prénom : SEZNEC Romain
*     Numéro binôme : L
*/

#include "raylib.h"
#include "raylib_game.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include "ArduinoComP1DEFI.h"

bool lineColliding(Vector2 pointA, Vector2 pointB, Vector2 pointC, Vector2 pointD)
{
	return (pointA.x <= pointD.x && pointC.x <= pointB.x) && (pointA.y <= pointD.y && pointC.y <= pointB.y);
}


int main(void)
{
	//--------------------------------------------------------------------------------------
	// Initialization
	//--------------------------------------------------------------------------------------

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Projet 1 DEFI - BOUCHAUD Lucas - SEZNEC Romain");
	InitAudioDevice(); 
	SetTargetFPS(TARGET_FPS);
	
	Vector2 carSpeed = { 0, 0 };
	Vector2 carVelocity = { 0, 0 };
	Vector2 carPos = { 400, 800 };

	float coefFrottement = 5;
	float puissanceMoteur = 200;
	Vector2 forceMoteur = { 0, 0 };

	float nitroReserve = 100;
	bool nitroActivated = false;
	bool nitroRecharge = false;

	float carWidth = 30, carHeight = 60;
	Color carColor = RED;

	float habitacleWidth = carWidth / 3, habitacleHeight = carHeight / 3;
	Color habitacleColor = DARKGRAY;

	float headlightRadius = carWidth / 6;
	Color headlightColor = BLUE;

	float wheelWidth = carWidth / 6, wheelHeight = carHeight / 6;
	float wheelOffsetY = carHeight / 12, wheelOffsetX = carWidth / 15;
	Color wheelColor = BLACK;

	float backlightWidth = carWidth / 3;
	float backlightHeight = carHeight / 15;
	Color backlightColor = RED;

	float nitroBarWidth = 100;
	float nitroBarHeight = 30;
	Vector2 nitroBar = { SCREENSIZE.x - 10 - nitroBarWidth, SCREENSIZE.y - 10 - nitroBarHeight };

	Vector2 obstaclePos = { 200, 150 };
	Vector2 obstacleSize = { 100, 50 };
	Color obstacleColor = BLACK;

	float debugX = 10, debugY = 40;
	float debugSpacing = 10, debugLine = 0;

	//--------------------------------------------------------------------------------------
	// Game loop principale (code exécuté à chaque frame (60 fois par secondes))
	//--------------------------------------------------------------------------------------
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		/*
		 * Gestion de tout ce qui n'est pas l'affichage ici
		 */

		debugLine = 0;

		/*
		* Gestion de l'input
		*/
		carVelocity.x = -coefFrottement * carSpeed.x + forceMoteur.x;
		carVelocity.y = -coefFrottement * carSpeed.y + forceMoteur.y;

		carSpeed.x = carSpeed.x + carVelocity.x*GetFrameTime();
		carSpeed.y = carSpeed.y + carVelocity.y*GetFrameTime();

		if (IsKeyDown(KEY_LEFT))
			forceMoteur.x = -coefFrottement * puissanceMoteur;

		if (IsKeyDown(KEY_RIGHT))
			forceMoteur.x = coefFrottement * puissanceMoteur;

		if (IsKeyDown(KEY_UP))
			forceMoteur.y = -coefFrottement * puissanceMoteur;

		if (IsKeyDown(KEY_DOWN))
		{
			forceMoteur.y = coefFrottement * puissanceMoteur;
			backlightColor = YELLOW;
		}
		else
			backlightColor = RED;

		if (nitroRecharge || nitroReserve <= 0)
		{
			nitroActivated = false;
			nitroReserve += .5;
			nitroRecharge = nitroReserve < 100;
		}
		else if (IsKeyDown(KEY_LEFT_SHIFT) && !nitroRecharge) // nitro
		{
			nitroActivated = true;
			nitroReserve --;
			puissanceMoteur = 600;
		}
		else
		{
			nitroActivated = false;
			puissanceMoteur = 200;
		}

		if (!(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN))) {
			forceMoteur.x = 0;
			forceMoteur.y = 0;
		}

		carPos.x = carPos.x + carSpeed.x*GetFrameTime();
		carPos.y = carPos.y + carSpeed.y*GetFrameTime();

		/*
		Bords
		*/
		if ((carPos.x - wheelWidth / 2) < 0)
		{
			carPos.x = wheelWidth / 2;
			carSpeed.x = 0;
			carSpeed.y = 0;
		}
		if ((carPos.x + carWidth + wheelWidth / 2) > SCREENSIZE.x)
		{
			carPos.x = SCREENSIZE.x - carWidth -wheelWidth / 2;
			carSpeed.x = 0;
			carSpeed.y = 0;
		}
		if ((carPos.y - (carWidth / 6)) < 0)
		{
			carPos.y = carWidth / 6;
			carSpeed.x = 0;
			carSpeed.y = 0;
		}
		if ((carPos.y + carHeight) > SCREENSIZE.y)
		{
			carPos.y = SCREENSIZE.y - carHeight;
			carSpeed.x = 0;
			carSpeed.y = 0;
		}

		/*
		Obstacle logic
		if (carPos.x > 400)
		{
			obstacleColor = SKYBLUE;
		}
		else
		{
			obstacleColor = BLACK;
		}
		*/

		/*
		{
			if (IsKeyDown(KEY_O))
				carHeight++;

			if (IsKeyDown(KEY_K))
				carWidth++;

			if (IsKeyDown(KEY_L))
				carHeight--;

			if (IsKeyDown(KEY_M) || IsKeyDown(KEY_SEMICOLON))
				carWidth--;
		}
		*/

		 /* Gestion de l'affichage ici
		 */
		BeginDrawing();
		{
			ClearBackground(RAYWHITE);

			// Phares
			DrawCircle(carPos.x + headlightRadius, carPos.y, headlightRadius, headlightColor);
			DrawCircle(carPos.x + carWidth - headlightRadius, carPos.y, headlightRadius, headlightColor);

			// Habitacle
			DrawRectangle(carPos.x, carPos.y, carWidth, carHeight, carColor);
			DrawEllipse(carPos.x + carWidth / 2, carPos.y + carHeight / 2, habitacleWidth, habitacleHeight, habitacleColor);

			// Roues
			DrawRectangle(carPos.x - wheelOffsetX, carPos.y + wheelOffsetY, wheelWidth, wheelHeight, wheelColor);
			DrawRectangle(carPos.x - wheelOffsetX, carPos.y + carHeight - 3 * wheelOffsetY, wheelWidth, wheelHeight, wheelColor);

			DrawRectangle(carPos.x + carWidth - wheelOffsetX, carPos.y + wheelOffsetY, wheelWidth, wheelHeight, wheelColor);
			DrawRectangle(carPos.x + carWidth - wheelOffsetX, carPos.y + carHeight - 3 * wheelOffsetY, wheelWidth, wheelHeight, wheelColor);

			// Feux de recul
			DrawRectangle(carPos.x, carPos.y + carHeight - backlightHeight, backlightWidth, backlightHeight, backlightColor);
			DrawRectangle(carPos.x + carWidth - backlightWidth, carPos.y + carHeight - backlightHeight, backlightWidth, backlightHeight, backlightColor);

			if (nitroActivated)
				DrawRectangle(carPos.x, carPos.y + carHeight, carWidth, carHeight / 15, BLUE);

			// nitro counter
			DrawRectangle(nitroBar.x, nitroBar.y, nitroBarWidth + 4, nitroBarHeight + 4, DARKBLUE);
			DrawRectangle(nitroBar.x + 2, nitroBar.y + 2, nitroBarWidth, nitroBarHeight, WHITE);
			DrawRectangle(nitroBar.x + 2, nitroBar.y + 2, nitroReserve, nitroBarHeight, DARKBLUE);

			// Debug
			DrawFPS(10, 10);
			DrawText(TextFormat("coords : %.2fx%.0f", carPos.x, carPos.y), debugX, debugY + debugSpacing * debugLine++, 10, wheelColor);
			DrawText(TextFormat("speed : %.2fx%.0f", carSpeed.x, carSpeed.y), debugX, debugY + debugSpacing * debugLine++, 10, wheelColor);
			DrawText(TextFormat("velocity : %.2fx%.0f", carVelocity.x, carVelocity.y), debugX, debugY + debugSpacing * debugLine++, 10, wheelColor);
			DrawText(TextFormat("nitro reserve : %.2f", nitroReserve), debugX, debugY + debugSpacing * debugLine++, 10, wheelColor);

			DrawText(TextFormat("BOUCHAUD Lucas - SEZNEC Romain", 42), debugX, SCREENSIZE.y - 20, 10, BLACK);

			// Obstacle
			DrawRectangle(obstaclePos.x, obstaclePos.y, obstacleSize.x, obstacleSize.y, obstacleColor);
		}
		EndDrawing();
	}

	//--------------------------------------------------------------------------------------
	// De-Initialization (code exécuté une fois à la fin du programme)
	//--------------------------------------------------------------------------------------

	CloseAudioDevice();     // Close audio context
	CloseWindow();          // Close window and OpenGL context

	return 0;
}
