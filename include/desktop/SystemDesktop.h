#ifndef SYSTEM_DESKTOP_H
#define SYSTEM_DESKTOP_H

#include "SystemBase.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace System
{
	void OnWindowResized(GLFWwindow* window, int width, int height);
	void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);

	class SystemDesktop : public SystemBase
	{
	public:
		bool InitSystem() override;
		void Update() override;
		bool IsRunning() override;
		// TODO getsystemtype

		bool LoadBinaryDataFromAssets(const std::string fileName, unsigned char*& data, off_t& length) const override;
		bool LoadStringDataFromAssets(const std::string fileName, std::string& data) const override;

	private:
		GLFWwindow* InitWindow();
		bool InitGlad();

	private:
		GLFWwindow* m_gameWindow = nullptr;
	};
}

#endif // SYSTEM_H
