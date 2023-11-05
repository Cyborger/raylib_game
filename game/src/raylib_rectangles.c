#include "raylib.h"
#include "raylib_game.h"

RectangleEdges RecToRecEdges(Rectangle rectangle)
{
    RectangleEdges rectangleEdges = {
            rectangle.x,
            rectangle.x + rectangle.width,
            rectangle.y,
            rectangle.y + rectangle.height
    };

    return rectangleEdges;
}

RectangleCentered RecEdgesToRecCentered(RectangleEdges rectangleEdges)
{
    Vector2 center = {
         rectangleEdges.left + rectangleEdges.right / 2,
         rectangleEdges.top + rectangleEdges.bottom / 2
    };

    Vector2 size = {
            rectangleEdges.right - rectangleEdges.left,
            rectangleEdges.bottom - rectangleEdges.top
    };

    RectangleCentered rectangleCentered = {
            center,
            size
    };

    return rectangleCentered;
}

Rectangle RecCenteredToRec(RectangleCentered rectangleCentered)
{
    Rectangle rectangle = {
            rectangleCentered.center.x - rectangleCentered.size.x / 2,
            rectangleCentered.center.y - rectangleCentered.size.y / 2,
            rectangleCentered.size.x,
            rectangleCentered.size.y
    };

    return rectangle;
}

RectangleCentered RecToRecCentered(Rectangle rectangle)
{
    return RecEdgesToRecCentered(RecToRecEdges(rectangle));
}

RectangleEdges RecCenteredToRecEdges(RectangleCentered rectangleCentered)
{
    return RecToRecEdges(RecCenteredToRec(rectangleCentered));
}

Rectangle RecEdgesToRec(RectangleEdges rectangleEdges)
{
    return RecCenteredToRec(RecEdgesToRecCentered(rectangleEdges));
}
