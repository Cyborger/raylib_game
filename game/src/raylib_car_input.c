#include "raylib.h"
#include "raylib_game.h"
#include "ArduinoComP1DEFI.h"
#include <stdio.h>

bool inputManagement(Car *car, bool carCollidingObstacle, char* arduinoMessage)
{
    bool activateLed = false;
    Vector2 joystick = {525, 525};
    if (arduinoMessage != "(null)")
    {
        sscanf(arduinoMessage, "<%f,%f>", &joystick.x, &joystick.y);
    }
	car->acceleration.x = -car->frictionCoefficient * car->speed.x + car->motorForce.x;
	car->acceleration.y = -car->frictionCoefficient * car->speed.y + car->motorForce.y;

	car->speed.x = car->speed.x + car->acceleration.x*GetFrameTime();
	car->speed.y = car->speed.y + car->acceleration.y*GetFrameTime();

	if ((IsKeyDown(KEY_LEFT) || joystick.x <= 480) && !carCollidingObstacle)
		car->motorForce.x = -car->frictionCoefficient * car->horsePower;

	if ((IsKeyDown(KEY_RIGHT) || joystick.x >= 570) && !carCollidingObstacle)
		car->motorForce.x = car->frictionCoefficient * car->horsePower;

	if ((IsKeyDown(KEY_UP) || joystick.y <= 480) && !carCollidingObstacle)
		car->motorForce.y = -car->frictionCoefficient * car->horsePower;

	if ((IsKeyDown(KEY_DOWN) || joystick.y >= 570) && !carCollidingObstacle)
	{
		car->motorForce.y = car->frictionCoefficient * car->horsePower;
		car->backlights.color = YELLOW;
        activateLed = true;
	}
	else
		car->backlights.color = RED;

	if (IsKeyDown(KEY_LEFT_SHIFT) && car->nitro.reserve > 0)
	{
		car->horsePower = 600;
		car->nitro.active = true;
		car->nitro.reserve--;
	}
	else
	{
		car->horsePower = 200;
		car->nitro.active = false;
		car->nitro.reserve += car->nitro.reserve < 100 ? .5F : .0F;
	}

	if (!(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) || !(joystick.x > 480 && joystick.x < 570) || !(joystick.y > 480 && joystick.y < 570))) {
		car->motorForce.x = 0;
		car->motorForce.y = 0;
	}

	car->transform.position.x = car->transform.position.x + car->speed.x*GetFrameTime();
	car->transform.position.y = car->transform.position.y + car->speed.y*GetFrameTime();

    return activateLed;
}