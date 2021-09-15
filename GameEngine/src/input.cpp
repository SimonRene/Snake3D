#include "input.h"


#include <iostream>
#include <cmath>
#include <limits>

namespace GE {


Input::Button Input::ESCAPE = Input::Button();

Input::Button Input::A = Input::Button();
Input::Button Input::B = Input::Button();
Input::Button Input::C = Input::Button();
Input::Button Input::D = Input::Button();
Input::Button Input::E = Input::Button();
Input::Button Input::F = Input::Button();
Input::Button Input::G = Input::Button();
Input::Button Input::H = Input::Button();
Input::Button Input::I = Input::Button();
Input::Button Input::J = Input::Button();
Input::Button Input::K = Input::Button();
Input::Button Input::L = Input::Button();
Input::Button Input::M = Input::Button();
Input::Button Input::N = Input::Button();
Input::Button Input::O = Input::Button();
Input::Button Input::P = Input::Button();
Input::Button Input::Q = Input::Button();
Input::Button Input::R = Input::Button();
Input::Button Input::S = Input::Button();
Input::Button Input::T = Input::Button();
Input::Button Input::U = Input::Button();
Input::Button Input::V = Input::Button();
Input::Button Input::W = Input::Button();
Input::Button Input::X = Input::Button();
Input::Button Input::Y = Input::Button();
Input::Button Input::Z = Input::Button();

Input::Button Input::n0 = Input::Button();
Input::Button Input::n1 = Input::Button();
Input::Button Input::f1 = Input::Button();
Input::Button Input::n2 = Input::Button();
Input::Button Input::f2 = Input::Button();
Input::Button Input::n3 = Input::Button();
Input::Button Input::f3 = Input::Button();
Input::Button Input::n4 = Input::Button();
Input::Button Input::f4 = Input::Button();
Input::Button Input::n5 = Input::Button();
Input::Button Input::f5 = Input::Button();
Input::Button Input::n6 = Input::Button();
Input::Button Input::f6 = Input::Button();
Input::Button Input::n7 = Input::Button();
Input::Button Input::f7 = Input::Button();
Input::Button Input::n8 = Input::Button();
Input::Button Input::f8 = Input::Button();
Input::Button Input::n9 = Input::Button();
Input::Button Input::f9 = Input::Button();
Input::Button Input::f10 = Input::Button();
Input::Button Input::f11 = Input::Button();
Input::Button Input::f12 = Input::Button();

Input::Button Input::SPACE = Input::Button();
Input::Button Input::ENTER = Input::Button();

Input::Button Input::UP = Input::Button();
Input::Button Input::DOWN = Input::Button();
Input::Button Input::RIGHT = Input::Button();
Input::Button Input::LEFT = Input::Button();

Input::Button Input::SHIFT_L = Input::Button();
Input::Button Input::SHIFT_R = Input::Button();

Input::Button Input::CTRL_L = Input::Button();
Input::Button Input::CTRL_R = Input::Button();

Input::Mouse Input::MOUSE = Input::Mouse();

GLFWwindow* Input::window = nullptr;


bool Input::Button::justPressed() {
	return (isDown && !wasLastFrameDown);
}

bool Input::Button::justReleased() {
	return (!isDown && wasLastFrameDown);
}


bool Input::Button::down() {
	return isDown;
}


bool Input::Button::up() {
	return !isDown;
}


void Input::Button::update(bool _down) {
	wasLastFrameDown = isDown;
	isDown = _down;
}

void Input::initializeInput(GLFWwindow* _window) {
	window = _window;

	glfwSetScrollCallback(window, scroll_callback);

}


void Input::updateInput() {

	// Mouse
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	MOUSE.updateMovement(xPos, yPos);

	MOUSE.update(1, (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS));
	MOUSE.update(2, (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS));
	MOUSE.update(3, (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_3) == GLFW_PRESS));
	MOUSE.update(4, (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_4) == GLFW_PRESS));
	MOUSE.update(5, (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_5) == GLFW_PRESS));
	MOUSE.update(6, (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_6) == GLFW_PRESS));
	MOUSE.update(7, (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_7) == GLFW_PRESS));
	MOUSE.update(8, (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_8) == GLFW_PRESS));

	MOUSE.lastFrameScrollX = MOUSE.currentFrameScrollX;
	MOUSE.lastFrameScrollY = MOUSE.currentFrameScrollY;

	MOUSE.currentFrameScrollX = 0.0;
	MOUSE.currentFrameScrollY = 0.0;

	// Keyboard

	ESCAPE.update(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS);

	A.update(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
	B.update(glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS);
	C.update(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS);
	D.update(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);
	E.update(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS);
	F.update(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS);
	G.update(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS);
	H.update(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS);
	I.update(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS);
	J.update(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS);
	K.update(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS);
	L.update(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS);
	M.update(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS);
	N.update(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS);
	O.update(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS);
	P.update(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS);
	Q.update(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS);
	R.update(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS);
	S.update(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
	T.update(glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS);
	U.update(glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS);
	V.update(glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS);
	W.update(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
	X.update(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS); 
	Y.update(glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS);
	Z.update(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS);

	n0.update(glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS);
	n1.update(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS);
	n2.update(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS);
	n3.update(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS);
	n4.update(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS);
	n5.update(glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS);
	n6.update(glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS);
	n7.update(glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS);
	n8.update(glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS);
	n9.update(glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS);

	f1.update(glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS);
	f2.update(glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS);
	f3.update(glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS);
	f4.update(glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS);
	f5.update(glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS);
	f6.update(glfwGetKey(window, GLFW_KEY_F6) == GLFW_PRESS);
	f7.update(glfwGetKey(window, GLFW_KEY_F7) == GLFW_PRESS);
	f8.update(glfwGetKey(window, GLFW_KEY_F8) == GLFW_PRESS);
	f9.update(glfwGetKey(window, GLFW_KEY_F9) == GLFW_PRESS);
	f10.update(glfwGetKey(window, GLFW_KEY_F10) == GLFW_PRESS);
	f11.update(glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS);
	f12.update(glfwGetKey(window, GLFW_KEY_F12) == GLFW_PRESS);
	// TODO: add F13 - F25 ?

	SPACE.update(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);

	ENTER.update(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS);

	UP.update(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS);
	DOWN.update(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS);
	RIGHT.update(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS);
	LEFT.update(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS);

	SHIFT_L.update(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);
	SHIFT_R.update(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);

	CTRL_L.update(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS);
	CTRL_R.update(glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS);

}


// MOUSE

Input::Mouse::Mouse() {
	isDown = new bool[number_of_mouse_buttons];
	wasLastFrameDown = new bool[number_of_mouse_buttons];
}

Input::Mouse::~Mouse() {
	delete[] isDown;
	delete[] wasLastFrameDown;
}


bool Input::Mouse::moving() {
	return (movingX() || movingY());
}

bool Input::Mouse::movingX() {
	return (std::fabs(xPosition - lastFrame_xPosition) > std::numeric_limits<double>::epsilon());
}

bool Input::Mouse::movingY() {
	return (std::fabs(yPosition - lastFrame_yPosition) > std::numeric_limits<double>::epsilon());
}

double Input::Mouse::positionX() {
	return xPosition;
}

double Input::Mouse::positionY() {
	return yPosition;
}


double Input::Mouse::movementX() {
	return (xPosition - lastFrame_xPosition);
}

double Input::Mouse::movementY() {
	return (yPosition - lastFrame_yPosition);
}


bool Input::Mouse::down(size_t button_id) {
	return isDown[(button_id - 1) % number_of_mouse_buttons];
}

bool Input::Mouse::up(size_t button_id) {
	return !isDown[(button_id - 1) % number_of_mouse_buttons];
}


bool Input::Mouse::justPressed(size_t button_id) {
	size_t index = (button_id - 1) % number_of_mouse_buttons;
	return (isDown[index] && !wasLastFrameDown[index]);
}

bool Input::Mouse::justReleased(size_t button_id) {
	return (!isDown[(button_id - 1) % number_of_mouse_buttons] && wasLastFrameDown[(button_id - 1) % number_of_mouse_buttons]);
}


// ===

bool Input::Mouse::leftDown() {
	return (down(1));
}

bool Input::Mouse::middleDown() {
	return (down(2));
}

bool Input::Mouse::rightDown() {
	return (down(3));
}

bool Input::Mouse::leftUp() {
	return (up(1));
}

bool Input::Mouse::middleUp() {
	return (up(2));
}

bool Input::Mouse::rightUp() {
	return (up(3));
}

bool Input::Mouse::leftJustPressed() {
	return (justPressed(1));
}

bool Input::Mouse::middleJustPressed() {
	return (justPressed(2));
}

bool Input::Mouse::rightJustPressed() {
	return (justPressed(3));
}


bool Input::Mouse::leftJustReleased() {
	return (justReleased(1));
}

bool Input::Mouse::middleJustReleased() {
	return (justReleased(2));
}

bool Input::Mouse::rightJustReleased() {
	return (justReleased(3));
}

bool Input::Mouse::scrolling() {
	return (std::fabs(lastFrameScrollX) >= std::numeric_limits<double>::epsilon() || std::fabs(lastFrameScrollY) >= std::numeric_limits<double>::epsilon());
}

double Input::Mouse::scrollX() {
	return lastFrameScrollX;
}

double Input::Mouse::scrollY() {
	return lastFrameScrollY;
}



// ===


void Input::Mouse::update(size_t button_id, bool _down) {
	size_t index = (button_id - 1) % number_of_mouse_buttons;

	wasLastFrameDown[index] = isDown[index];
	isDown[index] = _down;
}

void Input::Mouse::updateMovement(float _xPos, float _yPos) {
	if (initialized) {
		lastFrame_xPosition = xPosition;
		lastFrame_yPosition = yPosition;
	}
	else { // no mouse movement on first Frame
		initialized = true;
		lastFrame_xPosition = _xPos;
		lastFrame_yPosition = _yPos;
	}

	xPosition = _xPos;
	yPosition = _yPos;
}


void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	(void)window;
	MOUSE.currentFrameScrollX += xoffset;
	MOUSE.currentFrameScrollY += yoffset;
}

}