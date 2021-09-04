#pragma once

#include <GL/gl3w.h>

#include <GLFW/glfw3.h>

#include <exception>

class Engine {
  private:
	GLFWwindow *window;

  public:
	Engine(unsigned ScrWidth, unsigned ScrHeight);
	~Engine();
	Engine(const Engine &other) = delete;
	Engine &operator=(const Engine &other) = delete;

	[[nodiscard]] bool shouldStayOpen() const noexcept;
	[[nodiscard]] GLFWwindow *getWindow() const noexcept;
	void swapBuffersAndPollEvents() const noexcept;
	void setCallbacks() const noexcept;
	void bindDefaultFrameBuffer() const noexcept;

};

