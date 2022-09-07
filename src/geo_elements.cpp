#include "geo_elements.h"
Color::Color(int r, int g, int b, int a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}
int Color::SetColor(char red, char green, char blue, char alpha) {
	r = red;
	g = green;
	b = blue;
	a = alpha;
	return 1;
}

int Color::GetRed() const {
	return (int)r;
}

int Color::GetGreen() const {
	return (int)g;
}

int Color::GetBlue() const {
	return (int)b;
}

int Color::GetAlpha () const {
	return (int)a;
}

//Some basic pre-defined colors.
const Color Color::white{ 0,0,0,255 };
const Color Color::red{ 255,0,0,255 };
const Color Color::green{ 0,255,0,255 };
const Color Color::blue{ 0,0,255,255 };
const Color Color::pink{ 255,0,255,255 };
const Color Color::orange{ 255,128,0,255 };
const Color Color::yellow{ 255,255,0,255 };
const Color Color::purple{ 127,0,255,255 };
const Color Color::magenta{ 255,0,127,255 };

Point2D::Point2D() {
	x = 0;
	y = 0;
}
Point2D::Point2D(int x, int y) {
	this->x = x;
	this->y = y;
}
void Point2D::Set(int x, int y) {
	this->x = x;
	this->y = y;
}

int Point2D::GetX() const{
	return x;
}

int Point2D::GetY() const {
	return y;
}

void Point2D::SetX(int xVal){
	x = xVal;
}

void Point2D::SetY(int yVal){
	y = yVal;
}

Line2D::Line2D() {
	//Give random values for empty line.
	x0 = 10;
	y0 = 10;
	x1 = 1;
	y1 = 1;
	firstPoint = Vec3(x0, y0, 0);
	lastPoint = Vec3(x1, y1, 0);
	color = Color::white;
	absdx = 0;
	absdy = 0;
}

Line2D::Line2D(int x0, int y0, int x1, int y1, const Color& colorValue) {
	this->x0 = x0;
	this->y0 = y0;
	this->x1 = x1;
	this->y1 = y1;
	firstPoint = Vec3(x0, y0, 0);
	lastPoint = Vec3(x1, y1, 0);
	color = colorValue;
	absdx = x1 - x0;
	if (absdx < 0) absdx = -absdx;
	absdy = y1 - y0;
	if (absdy < 0) absdy = -absdy;
}

Line2D::~Line2D() {
	if (elementCount > 1)
		delete[] points;
	else if (elementCount != 0)
		delete points;
}

int Line2D::Draw() {
	BresenhamLine();
	return 1;
}

int Line2D::ReDraw(int x0, int y0, int x1, int y1, const Color& colorValue) {
	this->x0 = x0;
	this->y0 = y0;
	this->x1 = x1;
	this->y1 = y1;
	firstPoint = Vec3(x0, y0, 0);
	lastPoint = Vec3(x1, y1, 0);
	color = colorValue;
	absdx = x1 - x0;
	if (absdx < 0) absdx = -absdx;
	absdy = y1 - y0;
	if (absdy < 0) absdy = -absdy;
	if (points != nullptr && elementCount > 1) {
		delete[] points;
		points = nullptr;
		elementCount = 0;
	}
	if (points != nullptr && elementCount > 0) {
		delete points;
		points = nullptr;
		elementCount = 0;
	}
	BresenhamLine();
	return 1;
}

Line2D* Line2D::RotateNew(float angle) {
	//Get last point, rotate it, and draw new line from that point.
	Vec3<int> lastPoint(x1, y1, 0);
	//Before rotate, turn degree to radian.
	lastPoint.Rotate2DSelf(angle * (3.14159265358979323846264338327950288 / 180.0));
	Line2D* newLine = new Line2D(x0, y0, lastPoint.x, lastPoint.y, color);
	newLine->Draw();
	return newLine;
}

int Line2D::Rotate(float angle) {
	//Get last point, rotate it, and draw same line from that point.
	Vec3<int> lastPoint(x1, y1, 0);
	//Before rotate, turn degree to radian.
	lastPoint.Rotate2DSelf(angle * (3.14159265358979323846264338327950288 / 180.0));
	x1 = lastPoint.x;
	y1 = lastPoint.y;
	Draw();
	return 1;
}

int Line2D::Scale(const Vec3f& scaleVector) {
	ReDraw(x0, y0, points[elementCount-1].x * scaleVector.x, points[elementCount - 1].y * scaleVector.y, color);
	return 1;
}

int Line2D::Translate(const Vec3f& translateVector) {
	for (int i = 0; i < elementCount; i++) {
		points[i].x += translateVector.x;
		points[i].y += translateVector.y;
	}
	return 1;
}

int Line2D::SetColor(const Color& colorValue) {
	color = colorValue;
	return 1;
}

int Line2D::DDALine() {
	double xInc, yInc;
	double x, y;
	if (x0 > x1) {
		x = x1;
		y = y1;
	}
	else {
		x = x0;
		y = y0;
	}
	xInc = ((double)absdx / (double)absdy);
	yInc = 1;
	points = new Vec3<int>[absdy];
	elementCount = absdy;
	for (int i = 0; i < absdy; i++) {
		x += xInc;
		if (x0 > x1)
			y0 > y1 ? y++ : y--;
		else
			y0 > y1 ? y-- : y++;
		points[i].Set((int)x, (int)y);
	}
	return 1;
}

int Line2D::BresenhamLine() {
	if (absdy > absdx) {
		DDALine();
		return 1;
	}
	int pk = 2 * absdy - absdx;
	int twoDy = 2 * absdy;
	int twoDyDx = 2 * (absdy - absdx);
	points = new Vec3<int>[absdx];
	elementCount = absdx;
	int x, y, xEnd;
	int iterator = 0;
	if (x0 > x1) {
		x = x1;
		y = y1;
		xEnd = x0;
	}
	else {
		x = x0;
		y = y0;
		xEnd = x1;
	}
	while (x < xEnd) {
		x++;
		if (pk < 0) {
			pk += twoDy;
		}
		else {
			if (x0 > x1)
				y0 > y1 ? y++ : y--;
			else
				y0 > y1 ? y-- : y++;
			pk += twoDyDx;
		}
		points[iterator].Set(x, y);
		iterator++;
	}
	return 1;
}

int Line2D::GetElementCount() const{
	return elementCount;
}

const Color* Line2D::GetColor() const{
	return &color;
}

Vec3<int>* Line2D::GetPoints(){
	return points;
}
Vec3<int>* Line2D::GetPoint(int index) {
	return &points[index];
}

const Vec3<int>& Line2D::GetLastPoint(){
	return lastPoint;
}

const Vec3<int>& Line2D::GetFirstPoint() {
	return firstPoint;
}