#ifndef GEO_ELEMENTS_H
#define GEO_ELEMENTS_H
#include "vec.h"
#include <math.h>
#include <numeric>
//#include "log_handler.h"

class Color {
public:
	//Constructor of a color class, r for red, g for green, b for blue, a for alpha.
	Color(int r = 0, int g = 0, int b = 0, int a = 0);
	//Copy constructor
	Color(const Color& col) {
		r = col.r;
		g = col.g;
		b = col.b;
		a = col.a;
	}
	//Assignment copy constructor
	Color& operator=(const Color& col) {
		r = col.r;
		g = col.g;
		b = col.b;
		a = col.a;
		return *this;
	}
	int GetRed() const;
	int GetGreen() const;
	int GetBlue() const;
	int GetAlpha() const;
	int SetColor(char red, char green, char blue, char alpha);

	static const Color white;
	static const Color red;
	static const Color green;
	static const Color blue;
	static const Color pink;
	static const Color orange;
	static const Color yellow;
	static const Color purple;
	static const Color magenta;
private:
	char r, g, b, a;
};

//Abstract Shape class.
//Gives scheme for derived classes.
class Shape {
public:
	virtual int Draw() = 0;
	virtual int Rotate(float angle) = 0;
	virtual int Scale(const Vec3f &scaleVector) = 0;
	virtual int Translate(const Vec3f &translateVector) = 0;
	virtual int SetColor(const Color& colorValue) = 0;
	virtual const Color* GetColor() const= 0;
	virtual int GetElementCount() const = 0;
	virtual const Vec3<int>* GetPoints() const= 0;
	virtual const Vec3<int>& GetPoint(int index) const= 0;
	Vec3<float> *points = nullptr;
};

class Point2D {
public:
	//Gives 0 values for members.
	Point2D();
	Point2D(int x, int y);
	void Set(int x, int y);
	int GetX() const;
	int GetY() const;
	void SetX(int xVal);
	void SetY(int yVal);
private:
	int x, y;
};

class Line2D : public Shape{
public:
	//Constructors.
	Line2D();
	Line2D(int x0, int y0, int x1, int y1, const Color& colorValue);
	//Destructor.
	~Line2D();
	//Copy constructor.
	Line2D(const Line2D& line) {
		x0 = line.x0;
		y0 = line.y0;
		x1 = line.x1;
		y1 = line.y1;
		absdx = line.absdx;
		absdy = line.absdy;
		if (points != nullptr && line.points != nullptr) {
			if (elementCount > 0) {
				delete[] points;
				points = nullptr;
			}
		}
		points = new Vec3<int>[line.GetElementCount()];
		for (int i = 0; i < line.GetElementCount(); i++) {
			points[i] = line.GetPoint(i);
		}
	}
	//Copy assignment.
	Line2D& operator=(const Line2D& line) {
		x0 = line.x0;
		y0 = line.y0;
		x1 = line.x1;
		y1 = line.y1;
		absdx = line.absdx;
		absdy = line.absdy;
		if (points != nullptr && line.points != nullptr) {
			if (elementCount > 0) {
				delete[] points;
				points = nullptr;
			}
		}
		points = new Vec3<int>[line.GetElementCount()];
		for (int i = 0; i < line.GetElementCount(); i++) {
			points[i] = line.GetPoint(i);
		}
		return *this;
	}
	//Calculates line points and adds points variable.
	int Draw();
	//Calculates line points and adds points variable.
	int ReDraw(int x0, int y0, int x1, int y1, const Color& colorValue);
	//Takes degree angle and rotates line. Angle should be degree, not radian.
	int Rotate(float angle);
	//Rotates and returns new line. Angle should be degree, not radian.
	Line2D* RotateNew(float angle);
	//Scale line by vector values, z value is useless.
	int Scale(const Vec3f& scaleVector);
	//Translate line by vector values, z value is useless.
	int Translate(const Vec3f& translateVector);
	//Change color value.
	int SetColor(const Color& colorValue);
	//Get size of line points.
	int GetElementCount() const;
	//Returns const Color*.
	const Color* GetColor() const;
	//Returns points (Vec3<int>*).
	const Vec3<int>* GetPoints() const;
	const Vec3<int>& GetLastPoint() const;
	const Vec3<int>& GetFirstPoint() const;
	//Get const point by index.
	const Vec3<int>& GetPoint(int index) const;
private:
	//Draw line with Bresenham Line Algorithm.
	int BresenhamLine();
	//Draw line with DDA line algorithm, for slope > 1.
	int DDALine();
	//Start point x0,y0 and end point x1,y1.
	int x0, y0, x1, y1;
	//Start and end point x-y values differences.
	int absdy, absdx;
	Color color;
	Vec3<int>* points = nullptr;
	Vec3<int> firstPoint;
	Vec3<int> lastPoint;
	int elementCount = 0;
};

class Circle2D : public Shape{
public:
	Circle2D(int xCenter, int yCenter, int radius,const Color& colorValue) {
		xC = xCenter;
		yC = yCenter;
		this->radius = radius;
		color = colorValue;
		elementCount = 8 * radius;
		points = new Vec3<int>[elementCount];
	}
	~Circle2D();
	int Draw();
	int Rotate(float angle);
	int Scale(const Vec3f& scaleVector);
	int Translate(const Vec3f& translateVector);
	int SetColor(const Color& colorValue);
	const Color* GetColor() const;
	int GetElementCount() const;
	const Vec3<int>* GetPoints() const;
	const Vec3<int>& GetPoint(int index) const;
private:
	//Circle draw algorithm
	int MidPoint();
	int PlotPoints(int x, int y, int index);
	int DeAllocatePoints();
	Vec3<int>* points = nullptr;
	Color color;
	int radius = 0;
	int xC = 0;
	int yC = 0;
	int elementCount = 0;
};

#endif
