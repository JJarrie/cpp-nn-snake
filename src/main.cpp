#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "imgui.h"
#include "backends/imgui_impl_allegro5.h"

ALLEGRO_COLOR ImVec4ToAlColor(ImVec4 v);

int main(int argc, char** argv) {

	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
	al_set_window_title(display, "Dear ImGui Allegro 5 example");
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void) io;

	ImGui::StyleColorsDark();

	ImGui_ImplAllegro5_Init(display);

	bool show_demo_window = true;
	bool show_another_window = false;

	ImVec4 bg_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
	ImVec4 food_color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

	bool running = true;
	while (running) {
		ALLEGRO_EVENT ev;

		while (al_get_next_event(queue, &ev)) {
			ImGui_ImplAllegro5_ProcessEvent(&ev);

			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				running = false;
			}

			if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
				ImGui_ImplAllegro5_InvalidateDeviceObjects();
				al_acknowledge_resize(display);
				ImGui_ImplAllegro5_CreateDeviceObjects();
			}
		}

		ImGui_ImplAllegro5_NewFrame();
		ImGui::NewFrame();

		if (show_demo_window) {
			ImGui::ShowDemoWindow(&show_demo_window);
		}

		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello world!");

			ImGui::Text("This is some useful text.");
			ImGui::Checkbox("Demo Window", &show_demo_window);
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::ColorEdit3("Background color", (float*) &bg_color);
			ImGui::ColorEdit3("Food color", (float*) &food_color);

			if (ImGui::Button("Button")) {
				counter++;
			}

			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		if (show_another_window) {
			ImGui::Begin("Another window", &show_another_window);
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close me")) {
				show_another_window = false;
			}
			ImGui::End();
		}


		ImGui::Render();

		{
			al_clear_to_color(ImVec4ToAlColor(bg_color));
			al_draw_filled_rectangle(100.0f, 100.0f, 200.0f, 200.0f, ImVec4ToAlColor(food_color));
		}

		ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
		al_flip_display();
	}

	ImGui_ImplAllegro5_Shutdown();
	ImGui::DestroyContext();
	al_destroy_event_queue(queue);
	al_destroy_display(display);

	return EXIT_SUCCESS;
}

ALLEGRO_COLOR ImVec4ToAlColor(ImVec4 v) {
	return al_map_rgba_f(v.x * v.w, v.y * v.w, v.z * v.w, v.w);
}
