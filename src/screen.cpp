#include "screen.h"

//Turn local coordinates to screen coordinates.
Point2D Screen::LocalToScreen2D(Point2D* point) {
	return Point2D(half_width + point->GetX(), half_height - point->GetY());
}
//Turn screen cordinates to local coordinates.
Point2D Screen::ScreenToLocal2D(int x, int y) {
	return Point2D(x - half_width, half_height - y);
}

Screen::Screen(ShapeManager* shapeManagerPtr) {
	printInfo("Screen starting up.");
	//SDL Initialization.
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printError("SDL_Init failed: " + std::string(SDL_GetError()));
		exit(-1);
	}
	if (SDL_GetCurrentDisplayMode(0, &dm) != 0) {
		printError("SDL_GetDesktopDisplayMode failed: " + std::string(SDL_GetError()));
		exit(-1);
	}
	//Calculate screen dimensions.
	width = dm.w;
	height = dm.h;
	half_width = (int)(width / 2);
	half_height = (int)(height / 2);
	printInfo("Screen height: " + std::to_string(height));
	printInfo("Screen width: " + std::to_string(width));
	SDL_CreateWindowAndRenderer(half_width, half_height, SDL_WINDOW_RESIZABLE, &window, &renderer);
	SDL_SetWindowResizable(window, SDL_bool(1));
	keystate = SDL_GetKeyboardState(NULL);
	//Assign Shape Manager.
	shapeManager = shapeManagerPtr;
	//Optionally, draw 2D axes.
	shapeManager->DrawAxes2D(width, height);
}

//From SDL2:
//flags may be SDL_WINDOW_FULLSCREEN, for "real" fullscreen with a videomode change; 
//SDL_WINDOW_FULLSCREEN_DESKTOP for "fake" fullscreen that takes the size of the desktop; and 0 for windowed mode.
int  Screen::SetFullScreenMode(int mode) {
	if (SDL_SetWindowFullscreen(window, mode) == 0){
		return 1;
	}
	else {
		printError("on SetFullScreenMode: " + std::string(SDL_GetError()));
		return -1;
	}
}

void Screen::HandleInputs() {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			quit = true;
		}
		//Handle mouse input.
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			switch (event.button.clicks) {
			case 1:
				SDL_GetMouseState(&mouseX, &mouseY);
				if (drawMode) {
					mouseLeftRecords[clickCount].SetX(mouseX);
					mouseLeftRecords[clickCount++].SetY(mouseY);
					//Check if it's still in same frame, if it's then don't increment clickCount.
					if (mouseLeftRecords[0].GetX() == mouseLeftRecords[1].GetX() && mouseLeftRecords[0].GetY() == mouseLeftRecords[1].GetY())
						clickCount = 1;
					if (clickCount > 1) {
						Line2D* line = shapeManager->CreateLine(ScreenToLocal2D(mouseLeftRecords[0].GetX(), mouseLeftRecords[0].GetY()), ScreenToLocal2D(mouseLeftRecords[1].GetX(), mouseLeftRecords[1].GetY()),Color::red);
						clickCount = 0;
					}
				}
				break;
			case 2:

				break;
			}
		}
	}

	//Handle keyboard input.
	//ESC key for quit program.
	if (keystate[SDL_SCANCODE_ESCAPE]) {
		quit = true;
	}
	//LCTRL+D for draw mode.
	if (keystate[SDL_SCANCODE_LCTRL] && keystate[SDL_SCANCODE_D]) {
		drawMode = true;
		editMode = false;
		printInfo("Draw mode online.");
	}
	//LCTRL+E for edit mode.
	if (keystate[SDL_SCANCODE_LCTRL] && keystate[SDL_SCANCODE_E]) {
		drawMode = false;
		editMode = true;
		printInfo("Edit mode online.");
	}
	//When draw mode 1, L-> Line
	if (keystate[SDL_SCANCODE_L]) {
		if (drawMode) {
			selectedToolDraw = 1;
			printInfo("Selected tool: Line");
		}
	}
	//When edit mode 1, delete last item in shapes vector from shapeManager.
	if (keystate[SDL_SCANCODE_R]) {
		if (editMode && selectedToolDraw == 1) {
			shapeManager->DeleteLastItem();
			editMode = false;
		}
	}
	//LCTRL+LALT+R for Clear screen
	if (keystate[SDL_SCANCODE_LCTRL] && keystate[SDL_SCANCODE_LALT] && keystate[SDL_SCANCODE_R]) {
		shapeManager->DeleteShapes();
	}

}

int Screen::ScreenLoop() {
	//Clear screen.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	//Calculate delta time.
	if (!startTime) {
			startTime = SDL_GetTicks();
	}
	else {
			delta = endTime - startTime;
	}
	if (delta < timePerFrame) {
			SDL_Delay(timePerFrame - delta);
	}
	//Handle inputs.
	HandleInputs();
	//Clear screen.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	//Draw 2D axes.
	for (int i = 0; i < shapeManager->GetAxes2DSize(); i++) {
		Draw(shapeManager->GetMainAxes2D(i));
	}
	//Draw shapes.
	for (int i = 0; i < shapeManager->GetShapesSize(); i++) {
		DrawShapeFromLocalSpace(shapeManager->GetShape(i));
	}
	//Draw temporary shapes.
	for (int i = 0; i < shapeManager->GetTempShapesSize(); i++) {
		DrawShapeFromLocalSpace(shapeManager->GetTempShape(i));
	}
	//Present
	SDL_RenderPresent(renderer);

	//Recalculate delta time.
	startTime = endTime;
	endTime = SDL_GetTicks();
	//Clear temporary shapes.
	shapeManager->FreeTempShapes();
	if (quit) {
		return 1;
	}
	else {
		return -1;
	}
}

void Screen::Draw(Shape* shape) {
	const Color* colorPtr = shape->GetColor();
	SDL_SetRenderDrawColor(renderer, colorPtr->GetRed(), colorPtr->GetGreen(), colorPtr->GetBlue(), colorPtr->GetAlpha());
	for (int i = 0; i < shape->GetElementCount(); i++) {
		SDL_RenderDrawPoint(renderer, shape->GetPoint(i)->x, shape->GetPoint(i)->y);
	}
}

void Screen::DrawShapeFromLocalSpace(Shape* shape) {
	const Color* colorPtr = shape->GetColor();
	SDL_SetRenderDrawColor(renderer, colorPtr->GetRed(), colorPtr->GetGreen(), colorPtr->GetBlue(), colorPtr->GetAlpha());
	for (int i = 0; i < shape->GetElementCount(); i++) {
		Point2D newPoints = LocalToScreen2D(&Point2D(shape->GetPoint(i)->x, shape->GetPoint(i)->y));
		SDL_RenderDrawPoint(renderer, newPoints.GetX(), newPoints.GetY());
	}
}

void Screen::CloseScreen() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_VideoQuit();
	SDL_Quit();
}

Screen::~Screen() {
	CloseScreen();
	delete shapeManager;
	shapeManager = nullptr;
}
