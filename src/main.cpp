#include "screen.h"
#include "vec.h"

int main() {
	ShapeManager* shapeManager = new ShapeManager;
	Screen *screen = new Screen(shapeManager);
	Line2D* lineA = shapeManager->CreateLine(Point2D(0, 0), Point2D(100, 100), Color::red);
	Line2D* lineB = shapeManager->CreateLine(Point2D(0, 0), Point2D(50, 200), Color::green);
	shapeManager->DeleteItem(lineA);
	Vec3<int> projVec = lineA->GetLastPoint().Project(lineB->GetLastPoint());
	Line2D* lineP = shapeManager->CreateLine(Point2D(lineA->GetLastPoint().x, lineA->GetLastPoint().y), Point2D(projVec.x, projVec.y), Color::blue);
	float angle = 0;
	while (screen->ScreenLoop() != 1) {
		Line2D* lineRotated = lineA->RotateNew(angle++);
		projVec = lineRotated->GetLastPoint().Project(lineB->GetLastPoint());
		shapeManager->AddTemporaryShape(lineRotated);
		lineP->ReDraw(projVec.x, projVec.y, lineRotated->GetLastPoint().x, lineRotated->GetLastPoint().y, *lineP->GetColor());
		if (angle > 360)
			angle = 0;
	}
	delete screen;
	return 0;
}