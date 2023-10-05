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

	GameTransform carTransform = {{400, 800}, {30, 60}};
	Car car = create_car(carTransform);

	float nitroBarWidth = 100;
	float nitroBarHeight = 30;
	Vector2 nitroBar = { WINDOW_WIDTH - 10 - nitroBarWidth, WINDOW_HEIGHT - 10 - nitroBarHeight };

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
		car.acceleration.x = -car.frictionCoefficient * car.speed.x + car.motorForce.x;
		car.acceleration.y = -car.frictionCoefficient * car.speed.y + car.motorForce.y;

		car.speed.x = car.speed.x + car.acceleration.x*GetFrameTime();
		car.speed.y = car.speed.y + car.acceleration.y*GetFrameTime();

		if (IsKeyDown(KEY_LEFT))
			car.motorForce.x = -car.frictionCoefficient * car.horsePower;

		if (IsKeyDown(KEY_RIGHT))
			car.motorForce.x = car.frictionCoefficient * car.horsePower;

		if (IsKeyDown(KEY_UP))
			car.motorForce.y = -car.frictionCoefficient * car.horsePower;

		if (IsKeyDown(KEY_DOWN))
		{
			car.motorForce.y = car.frictionCoefficient * car.horsePower;
			car.backlights.color = YELLOW;
		}
		else
			car.backlights.color = RED;

		if (IsKeyDown(KEY_LEFT_SHIFT) && car.nitro.reserve > 0)
		{
			car.horsePower = 600;
			car.nitro.active = true;
			car.nitro.reserve--;
		}
		else
		{
			car.horsePower = 200;
			car.nitro.active = false;
			car.nitro.reserve += car.nitro.reserve < 100 ? .5F : .0F;
		}

		if (!(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN))) {
			car.motorForce.x = 0;
			car.motorForce.y = 0;
		}

		car.transform.position.x = car.transform.position.x + car.speed.x*GetFrameTime();
		car.transform.position.y = car.transform.position.y + car.speed.y*GetFrameTime();

		/*
		Bords
		*/
		if ((car.transform.position.x - car.wheels.size.x / 2) < 0)
		{
			car.transform.position.x = car.wheels.size.x / 2;
			car.speed.x = 0;
			car.speed.y = 0;
		}
		if ((car.transform.position.x + car.transform.size.x + car.wheels.size.x / 2) > WINDOW_WIDTH)
		{
			car.transform.position.x = WINDOW_WIDTH - car.transform.size.x -car.wheels.size.x / 2;
			car.speed.x = 0;
			car.speed.y = 0;
		}
		if ((car.transform.position.y - (car.transform.size.x / 6)) < 0)
		{
			car.transform.position.y = car.transform.size.x / 6;
			car.speed.x = 0;
			car.speed.y = 0;
		}
		if ((car.transform.position.y + car.transform.size.y) > WINDOW_HEIGHT)
		{
			car.transform.position.y = WINDOW_HEIGHT - car.transform.size.y;
			car.speed.x = 0;
			car.speed.y = 0;
		}

		/*
		Obstacle logic
		if (car.transform.position.x > 400)
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
				car.transform.size.y++;

			if (IsKeyDown(KEY_K))
				car.transform.size.x++;

			if (IsKeyDown(KEY_L))
				car.transform.size.y--;

			if (IsKeyDown(KEY_M) || IsKeyDown(KEY_SEMICOLON))
				car.transform.size.x--;
		}
		*/

		 /* Gestion de l'affichage ici
		 */
		BeginDrawing();
		{
			ClearBackground(RAYWHITE);

			// Phares
			DrawCircle(car.transform.position.x + car.headlights.radius, car.transform.position.y, car.headlights.radius, car.headlights.color);
			DrawCircle(car.transform.position.x + car.transform.size.x - car.headlights.radius, car.transform.position.y, car.headlights.radius, car.headlights.color);

			// Habitacle
			DrawRectangle(car.transform.position.x, car.transform.position.y, car.transform.size.x, car.transform.size.y, car.color);
			DrawEllipse(car.transform.position.x + car.transform.size.x / 2, car.transform.position.y + car.transform.size.y / 2, car.cockpit.size.x, car.cockpit.size.y, car.cockpit.color);

			// Roues
			DrawRectangle(car.transform.position.x - car.wheels.offset.x, car.transform.position.y + car.wheels.offset.y, car.wheels.size.x, car.wheels.size.y, car.wheels.color);
			DrawRectangle(car.transform.position.x - car.wheels.offset.x, car.transform.position.y + car.transform.size.y - 3 * car.wheels.offset.y, car.wheels.size.x, car.wheels.size.y, car.wheels.color);

			DrawRectangle(car.transform.position.x + car.transform.size.x - car.wheels.offset.x, car.transform.position.y + car.wheels.offset.y, car.wheels.size.x, car.wheels.size.y, car.wheels.color);
			DrawRectangle(car.transform.position.x + car.transform.size.x - car.wheels.offset.x, car.transform.position.y + car.transform.size.y - 3 * car.wheels.offset.y, car.wheels.size.x, car.wheels.size.y, car.wheels.color);

			// Feux de recul
			DrawRectangle(car.transform.position.x, car.transform.position.y + car.transform.size.y - car.backlights.size.y, car.backlights.size.x, car.backlights.size.y, car.backlights.color);
			DrawRectangle(car.transform.position.x + car.transform.size.x - car.backlights.size.x, car.transform.position.y + car.transform.size.y - car.backlights.size.y, car.backlights.size.x, car.backlights.size.y, car.backlights.color);

			if (car.nitro.active)
				DrawRectangle(car.transform.position.x, car.transform.position.y + car.transform.size.y, car.transform.size.x, car.transform.size.y / 15, BLUE);

			// nitro counter
			DrawRectangle(nitroBar.x, nitroBar.y, nitroBarWidth + 4, nitroBarHeight + 4, DARKBLUE);
			DrawRectangle(nitroBar.x + 2, nitroBar.y + 2, nitroBarWidth, nitroBarHeight, WHITE);
			DrawRectangle(nitroBar.x + 2, nitroBar.y + 2, car.nitro.reserve, nitroBarHeight, DARKBLUE);

			// Debug
			DrawFPS(10, 10);
			DrawText(TextFormat("coords : %.2fx%.0f", car.transform.position.x, car.transform.position.y), debugX, debugY + debugSpacing * debugLine++, 10, car.wheels.color);
			DrawText(TextFormat("speed : %.2fx%.0f", car.speed.x, car.speed.y), debugX, debugY + debugSpacing * debugLine++, 10, car.wheels.color);
			DrawText(TextFormat("velocity : %.2fx%.0f", car.acceleration.x, car.acceleration.y), debugX, debugY + debugSpacing * debugLine++, 10, car.wheels.color);
			DrawText(TextFormat("nitro reserve : %.2f", car.nitro.reserve), debugX, debugY + debugSpacing * debugLine++, 10, car.wheels.color);

			DrawText(TextFormat("BOUCHAUD Lucas - SEZNEC Romain", 42), debugX, WINDOW_HEIGHT - 20, 10, BLACK);

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
