#ifndef SHAPE_MANAGER_H
#define SHAPE_MANAGER_H
#include "geo_elements.h"
#include <vector>

class ShapeManager {
public:
	Shape* CreateShape(Shape* shapePtr);
	Shape* GetShape(int index);
	Shape* GetTempShape(int index);
	Line2D* CreateLine(const Point2D& P0, const Point2D& P1, const Color& colorValue);
	int AddShape(Shape* shapePtr);
	int AddTemporaryShape(Shape* shapePtr);
	int FreeTempShapes();
	Shape* GetItem(Shape* shapePtr);
	int DeleteItem(Shape* shapePtr);
	int DeleteLastItem();
	int DeleteShapes();
	int GetTotalSize() const;
	int GetShapesSize() const;
	int GetTempShapesSize() const;
	int DrawAxes2D(int screenWidth, int screenHeight);
	int GetAxes2DSize() const;
	int DeleteAxes2D();
	Line2D* GetMainAxes2D(int index);
private:
	std::vector<Shape*> shapes;
	std::vector<Shape*> tempShapes;
	std::vector<Line2D*> mainAxes2D;
};
#endif
