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

void drawCar(Car car)
{
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

	// Rectangle nitro
	if (car.nitro.active)
		DrawRectangle(car.transform.position.x, car.transform.position.y + car.transform.size.y, car.transform.size.x, car.transform.size.y / 15, BLUE);

}