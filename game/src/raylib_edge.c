#include "raylib.h"
#include "raylib_game.h"

void windowEdgeManagement(Car *car)
{
	if (car->transform.position.x - car->wheels.size.x / 2 < 0)
	{
		car->transform.position.x = car->wheels.size.x / 2;
		car->speed.x = 0;
		car->speed.y = 0;
	}
	if (car->transform.position.x + car->transform.size.x + car->wheels.size.x / 2 > WINDOW_WIDTH)
	{
		car->transform.position.x = WINDOW_WIDTH - car->transform.size.x - car->wheels.size.x / 2;
		car->speed.x = 0;
		car->speed.y = 0;
	}
	if (car->transform.position.y - (car->transform.size.x / 6) < 0)
	{
		car->transform.position.y = car->transform.size.x / 6;
		car->speed.x = 0;
		car->speed.y = 0;
	}
	if (car->transform.position.y + car->transform.size.y > WINDOW_HEIGHT)
	{
		car->transform.position.y = WINDOW_HEIGHT - car->transform.size.y;
		car->speed.x = 0;
		car->speed.y = 0;
	}
}