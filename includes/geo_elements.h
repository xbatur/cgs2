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
	virtual Vec3<int>* GetPoints()= 0;
	virtual Vec3<int>* GetPoint(int index)= 0;
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
	}
	//Copy assignment.
	Line2D& operator=(const Line2D& line) {
		x0 = line.x0;
		y0 = line.y0;
		x1 = line.x1;
		y1 = line.y1;
		absdx = line.absdx;
		absdy = line.absdy;
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
	Vec3<int>* GetPoints();
	const Vec3<int>& GetLastPoint();
	const Vec3<int>& GetFirstPoint();
	//Get point by index.
	Vec3<int>* GetPoint(int index);
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
#endif
