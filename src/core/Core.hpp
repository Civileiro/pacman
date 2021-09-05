#pragma once

#include <GL/gl3w.h>

#include <GLFW/glfw3.h>

#include <exception>

class Core {
  private:
	GLFWwindow *window;
	int scrWidth, scrHeight;


  public:
	Core(int scrWidth, int scrHeight);
	~Core();
	Core(const Core &other) = delete;
	Core &operator=(const Core &other) = delete;

	[[nodiscard]] bool shouldStayOpen() const noexcept;
	[[nodiscard]] GLFWwindow *getWindow() const noexcept;
	void swapBuffersAndPollEvents() const noexcept;
	void setCallbacks() const noexcept;
	void bindDefaultFrameBuffer() const noexcept;

};

