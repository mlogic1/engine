#ifndef SYSTEM_DESKTOP_H
#define SYSTEM_DESKTOP_H

#include "SystemBase.h"
#include "Vector2.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace System
{
	void OnWindowResized(GLFWwindow* window, int width, int height);
	void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);
	void OnKeyMouse(GLFWwindow* window, int key, int action, int mods);

	class SystemDesktop : public SystemBase
	{
	public:
		bool InitSystem() override;
		void Update() override;
		bool IsRunning() override;
		virtual Vector2i GetWindowDimensions() const override;
		// TODO getsystemtype

		bool LoadBinaryDataFromAssets(const std::string fileName, unsigned char*& data, off_t& length) const override;
		bool LoadStringDataFromAssets(const std::string fileName, std::string& data) const override;
		virtual KeyState GetKeyState(const Key& key) override;

	private:
		GLFWwindow* InitWindow();
		bool InitGlad();
		void UpdateCursorPosition();

	private:
		GLFWwindow* m_gameWindow = nullptr;

		// delta
		float lastFrame = -1.0f;
		float deltaTimeAccumulated = 0.f;
		int frameCounter = 0;
	};
}

#endif // SYSTEM_H
