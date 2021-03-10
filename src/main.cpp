#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "Snake.hpp"
#include "NeuralNetwork.hpp"
#include "Vector.hpp"
#include "Population.hpp"

#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

int main(int argc, char** argv) {

	Vector boardSize(20, 20);
	Vector cellSize(30, 30);
	Vector windowSize(boardSize.x * cellSize.x, boardSize.y * cellSize.y);
	Vector glPivot(windowSize.x / 2, windowSize.y / 2);
	SDL_Color gridBackground = { 22, 22, 22, 255};
	SDL_Color gridLineColor = { 44, 44, 44, 255};

	/*
	std::vector<int> sizing{ 24, 16, 16, 3};
	NeuralNetwork nn(sizing);
	Snake snake(Vector(20, 20), nn);
	*/

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[ERROR] Init video: %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_WindowFlags flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.x, windowSize.y, flags);
	SDL_Renderer* renderer;

	SDL_SetWindowMinimumSize(window, 500, 300);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, glContext);

	SDL_GL_SetSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
		std::cerr << "[ERROR] Couldn't initialize glad" << std::endl;
	} else {
		std::cout << "[INFO] glad initialized" << std::endl;
	}

	std::cout << "[INFO] OpenGL renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "[INFO] OpenGL from glad: " << GLVersion.major << "." << GLVersion.minor << std::endl;

	glViewport(0, 0, windowSize.x, windowSize.y);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	(void) io;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(window, glContext);
	ImGui_ImplOpenGL3_Init("#version 150");

	ImVec4 background = ImVec4(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1.00f);

	glClearColor(background.x, background.y, background.z, background.w);

	bool loop = true;

	while(loop) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		SDL_Event event;

		while(SDL_PollEvent(&event)) {

			ImGui_ImplSDL2_ProcessEvent(&event);

			switch (event.type)
			{
				case SDL_QUIT:
					loop = false;
					break;
				case SDL_WINDOWEVENT:
					switch (event.window.event)
					{
						case SDL_WINDOWEVENT_RESIZED:
							windowSize.x = event.window.data1;
							windowSize.y = event.window.data2;
							glViewport(0, 0, windowSize.x, windowSize.y);
							break;
						default:
							break;
					}
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							loop = false;
							break;
						
						default:
							break;
					}
					break;
				default:
					break;
			}
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		bool showdemowindow = true;
		ImGui::ShowDemoWindow(&showdemowindow);

		SDL_SetRenderDrawColor(renderer, gridBackground.r, gridBackground.g, gridBackground.b, gridBackground.a);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, gridLineColor.r, gridLineColor.g, gridLineColor.b, gridLineColor.a);

		glBegin(GL_LINES);
		for (size_t x = 0; x < 1 + boardSize.x * cellSize.x; x += cellSize.x) {
			if (x < glPivot.x) {
				glVertex2i(x / glPivot.x - 1, -1);
			} else {
				glVertex2i(x / glPivot.x, 1);
			}
			// glVertex2i(x, windowSize.y);
			// SDL_RenderDrawLine(renderer, x, 0, x, windowSize.y);
		}
		glEnd();
		glLineWidth(1.0f);

		for (size_t y = 0; y < 1 + boardSize.y * cellSize.y; y += cellSize.y) {
			SDL_RenderDrawLine(renderer, 0, y, windowSize.x, y);
		}

		{
			static int counter = 0;
			int sdlWidth = 0;
			int sdlHeight = 0;
			int controlsWidth = 0;

			SDL_GetWindowSize(window, &sdlWidth, &sdlHeight);
			controlsWidth = sdlWidth;

			if ((controlsWidth /= 3) < 300) {
				controlsWidth = 300;
			}

			ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
			ImGui::SetNextWindowSize(
				ImVec2(static_cast<float>(controlsWidth), static_cast<float>(sdlHeight - 20)),
				ImGuiCond_Always
			);

			ImGui::Begin("Controls", NULL, ImGuiWindowFlags_NoResize);

			ImGui::Dummy(ImVec2(0.0f, 1.0f));
			ImVec4 v(1.0f, 0.0f, 1.0f, 1.0f);
			ImGui::TextColored(v, "Platform");
			ImGui::Text("%s", SDL_GetPlatform());
			// ImGui::Text("CPU cores: %s", SDL_GetCPUCount());
			ImGui::Text("RAM: %.2f GB", SDL_GetSystemRAM() / 1024.0f);

			if (ImGui::Button("Counter button")) {
				std::cout << "counter button clicked" << std::endl;
				counter++;
			}

			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::End();
		}

		ImGui::Render();

		glFlush();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// SDL_GL_SwapBuffers();
		SDL_GL_SwapWindow(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

/*
	Vector boardSize(20, 20);
	std::vector<int> sizing{ 28, 16, 3 };

	Population population(boardSize, 0.05, 2000, sizing);

	while(true) {
		if (population.isGenerationFinish()) {
			population.nextGeneration();
		}

		population.nextCycle();
	}
*/
	return EXIT_SUCCESS;
}
