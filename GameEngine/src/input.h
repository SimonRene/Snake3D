#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GE {

	// TODO: boolean -> is there active Input?

	class Input {

		class Button
		{
		public:
			bool justPressed();
			bool justReleased();

			bool down();
			bool up();

			void update(bool _down);

		private:
			bool isDown = false;
			bool wasLastFrameDown = false;
		};

		class Mouse
		{
		public:
			bool moving();
			bool movingX();
			bool movingY();

			double positionX();
			double positionY();

			double movementX();
			double movementY();

			bool leftDown();
			bool middleDown();
			bool rightDown();

			bool leftUp();
			bool middleUp();
			bool rightUp();

			bool leftJustPressed();
			bool middleJustPressed();
			bool rightJustPressed();

			bool leftJustReleased();
			bool middleJustReleased();
			bool rightJustReleased();

			bool down(size_t button_id);
			bool up(size_t button_id);

			bool justPressed(size_t button_id);
			bool justReleased(size_t button_id);

			bool scrolling();

			double scrollX();
			double scrollY();


			Mouse();
			~Mouse();

			friend class Input;

		private:

			void update(size_t button_id, bool _down);
			void updateMovement(float _xPos, float _yPos);

			double xPosition = 0.0, yPosition = 0.0;
			double lastFrame_xPosition = 0.0, lastFrame_yPosition = 0.0;
			
			bool* isDown;
			bool* wasLastFrameDown;

			double currentFrameScrollX = 0.0f;
			double currentFrameScrollY = 0.0f;

			double lastFrameScrollX = 0.0;
			double lastFrameScrollY = 0.0;

			size_t number_of_mouse_buttons = 8;

			// first frame done? -> no mouse movement on first frame
			bool initialized = false;
		};

		

	public:
		static void initializeInput(GLFWwindow* _window);
		static void updateInput();

		static Button ESCAPE;
		static Button A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
		static Button SPACE;
		static Button n0, n1, n2, n3, n4, n5, n6, n7, n8, n9;
		static Button f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12;
		static Button ENTER;
		static Button UP, DOWN, RIGHT, LEFT;
		static Button SHIFT_L, SHIFT_R;
		static Button CTRL_L, CTRL_R;


		static Mouse MOUSE;


	private:

		static GLFWwindow* window;


		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		
	};
}