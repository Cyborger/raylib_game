#include "raylib.h"
#include "raylib_game.h"

bool isCarCollidingObstacle(Car car, Obstacle obstacle)
{
	float carLeft = car.transform.position.x;
	float carRight = car.transform.position.x + car.transform.size.x;
	float carTop = car.transform.position.y;
	float carBottom = car.transform.position.y + car.transform.size.y;

	float obsLeft = obstacle.transform.position.x;
	float obsRight = obstacle.transform.position.x + obstacle.transform.size.x;
	float obsTop = obstacle.transform.position.y;
	float obsBottom = obstacle.transform.position.y + obstacle.transform.size.y;

	return (carLeft < obsRight && carRight > obsLeft) && (carTop < obsBottom && carBottom > obsTop);	
}

Obstacle create_obstacle(GameTransform obstacleTransform)
{
	Obstacle obstacle = {
		.transform = obstacleTransform,
		.color = BLACK
	};

	return obstacle;
}

bool lineColliding(Vector2 pointA, Vector2 pointB, Vector2 pointC, Vector2 pointD)
{
	return (pointA.x <= pointD.x && pointC.x <= pointB.x) && (pointA.y <= pointD.y && pointC.y <= pointB.y);
}
