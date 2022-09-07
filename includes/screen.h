#ifndef SCREEN_H
#define SCREEN_H
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "geo_elements.h"
#include "shape_manager.h"
#include "log_handler.h"
class Screen {
public:
	Screen(ShapeManager* shapeManagerPtr);
	~Screen();
	//Use in main source file, returns -1 when quit state, 1 for normal state.
	int ScreenLoop();
	int SetFullScreenMode(int mode);
	void Draw(Shape* shapePtr);
	//Before drawing accomplish, translate shape to the center of screen.
	void DrawShapeFromLocalSpace(Shape* shape);
private:
	void HandleInputs();
	void CloseScreen();
	Point2D LocalToScreen2D(Point2D* point);
	Point2D ScreenToLocal2D(int x, int y);

	//SDL variables section.
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event event;
	SDL_DisplayMode dm;
	Uint32 buttons;
	
	//Screen variables section.
	Point2D mouseLeftRecords[2];
	Point2D mouseLocalCoord;
	int clickCount;
	int mouseX, mouseY;
	int width, height, half_width, half_height;
	bool quit = false;
	bool drawMode = false;
	bool editMode = false;
	int selectedToolDraw = 0;
	const Uint8* keystate;

	//Delta time variables section.
	Uint32 startTime;
	Uint32 endTime;
	Uint32 delta;
	short fps = 60;
	short timePerFrame = 16; //ms
	Uint32 clickTimer = 0;
	Uint32 oldclickTimer = 0;

	//Vector list of shapes.
	ShapeManager *shapeManager = nullptr;
};
#endif
