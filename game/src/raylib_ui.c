#include "raylib.h"
#include "raylib_game.h"

NitroUI create_nitro_ui(GameTransform transform)
{
	NitroUI nitroUi = {
		.transform = transform
	};

	return nitroUi;
}

DebugUI create_debug_ui(Vector2 position, float spacing)
{
	DebugUI debugUi = {
		.position = position,
		.spacing = spacing,
		.line = 0
	};

	return debugUi;
}

void drawNitroUi(NitroUI nitroUi, Car car)
{
	DrawRectangle(nitroUi.transform.position.x, nitroUi.transform.position.y, nitroUi.transform.size.x + 4, nitroUi.transform.size.y + 4, DARKBLUE);
	DrawRectangle(nitroUi.transform.position.x + 2, nitroUi.transform.position.y + 2, nitroUi.transform.size.x, nitroUi.transform.size.y, WHITE);
	DrawRectangle(nitroUi.transform.position.x + 2, nitroUi.transform.position.y + 2, car.nitro.reserve, nitroUi.transform.size.y, DARKBLUE);
}

void drawDebugUi(DebugUI debugUi, Car car)
{
	DrawFPS(10, 10);
	DrawText(TextFormat("coords : %.2fx%.0f", car.transform.position.x, car.transform.position.y), debugUi.position.x, debugUi.position.y + debugUi.spacing * debugUi.line++, 10, car.wheels.color);
	DrawText(TextFormat("speed : %.2fx%.0f", car.speed.x, car.speed.y), debugUi.position.x, debugUi.position.y + debugUi.spacing * debugUi.line++, 10, car.wheels.color);
	DrawText(TextFormat("velocity : %.2fx%.0f", car.acceleration.x, car.acceleration.y), debugUi.position.x, debugUi.position.y + debugUi.spacing * debugUi.line++, 10, car.wheels.color);
	DrawText(TextFormat("nitro reserve : %.2f", car.nitro.reserve), debugUi.position.x, debugUi.position.y + debugUi.spacing * debugUi.line++, 10, car.wheels.color);

	DrawText(TextFormat("BOUCHAUD Lucas - SEZNEC Romain", 42), debugUi.position.x, WINDOW_HEIGHT - 20, 10, BLACK);
}