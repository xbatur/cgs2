#include "shape_manager.h"

Shape* ShapeManager::CreateShape(Shape* shapePtr) {
	shapePtr->Draw();
	shapes.push_back(shapePtr);
	return shapePtr;
}

Line2D* ShapeManager::CreateLine(const Point2D& P0, const Point2D& P1, const Color& colorValue) {
	Line2D* newLine = new Line2D(P0.GetX(), P0.GetY(), P1.GetX(), P1.GetY(), colorValue);
	newLine->Draw();
	shapes.push_back(newLine);
	return newLine;
}

Circle2D* ShapeManager::CreateCircle(const Point2D& P0, int radius, const Color& colorValue) {
	Circle2D *newCircle = new Circle2D(P0.GetX(), P0.GetY(), radius, colorValue);
	newCircle->Draw();
	shapes.push_back(newCircle);
	return newCircle;
}

int ShapeManager::AddShape(Shape* shapePtr) {
	shapes.push_back(shapePtr);
	return 1;
}

int ShapeManager::AddTemporaryShape(Shape* shapePtr) {
	tempShapes.push_back(shapePtr);
	return 1;
}

int ShapeManager::FreeTempShapes() {
	tempShapes.clear();
	return 1;
}

int ShapeManager::GetTempShapesSize() const{
	return tempShapes.size();
}

int ShapeManager::DeleteItem(Shape* shapePtr) {
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i] == shapePtr) {
			shapes.erase(shapes.begin() + i);
			return 1;
		}
	}
	return -1;
}
int ShapeManager::DeleteLastItem() {
	if (shapes.size() > 0) {
		shapes.pop_back();
		return 1;
	}
	else {
		return -1;
	}
	return 1;
}

int ShapeManager::DeleteShapes() {
	shapes.clear();
	return 1;
}

Shape* ShapeManager::GetItem(Shape* shapePtr) {
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i] == shapePtr) {
			return shapes[i];
		}
	}
	return nullptr;
}

int ShapeManager::DeleteAxes2D() {
	mainAxes2D.clear();
	return 1;
}

int ShapeManager::DrawAxes2D(int screenWidth, int screenHeight) {
	//Get greatest common divisor.
	int gcd = std::gcd(screenWidth, screenHeight);
	for (int i = 0; i < screenHeight; i += gcd) {
		Line2D* DuplicateX = new Line2D(0, screenHeight - i, screenWidth, screenHeight - i, Color(50, 0, 0, 50));
		DuplicateX->Draw();
		mainAxes2D.push_back(DuplicateX);
	}

	for (int i = 0; i < screenWidth; i += gcd) {
		Line2D* DuplicateY = new Line2D(i, 0, i, screenHeight, Color(0, 50, 0, 50));
		DuplicateY->Draw();
		mainAxes2D.push_back(DuplicateY);
	}
	//For Main X Axis
	Line2D* MainX = new Line2D(0, screenHeight/2,screenWidth, screenHeight/2, Color::red);
	MainX->Draw();
	mainAxes2D.push_back(MainX);

	//For Main Y Axis
	Line2D* MainY = new Line2D(screenWidth/2, 0, screenWidth/2, screenHeight, Color::green);
	MainY->Draw();
	mainAxes2D.push_back(MainY);
	return 1;
}

int ShapeManager::GetTotalSize() const {
	return mainAxes2D.size() + shapes.size();
}
Shape* ShapeManager::GetShape(int index) {
	return shapes.at(index);
}

Shape* ShapeManager::GetTempShape(int index) {
	return tempShapes.at(index);
}

Line2D* ShapeManager::GetMainAxes2D(int index){
	return mainAxes2D.at(index);
}

int ShapeManager::GetShapesSize() const{
	return shapes.size();
}
int ShapeManager::GetAxes2DSize() const{
	return mainAxes2D.size();
}