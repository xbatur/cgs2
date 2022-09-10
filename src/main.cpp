#include "screen.h"
#include "vec.h"

int main() {
	ShapeManager* shapeManager = new ShapeManager;
	Screen *screen = new Screen(shapeManager);
	Circle2D* circ = shapeManager->CreateCircle(Point2D(0, 0), 128, Color::yellow);
	while (screen->ScreenLoop() != 1) {

	}
	delete screen;
	return 0;
}

