#pragma once

#include <GL/gl3w.h>

#include <GLFW/glfw3.h>

#include <stdexcept>

class Core {
  private:
	GLFWwindow *window;
	int scrWidth;
	int	scrHeight;


  public:
	Core(int scrWidth = 800, int scrHeight = 600);
	~Core();
	Core(const Core &other) = delete;
	Core &operator=(const Core &other) = delete;

	[[nodiscard]] bool shouldStayOpen() const noexcept;
	[[nodiscard]] GLFWwindow *getWindow() const noexcept;
	void swapBuffersAndPollEvents() const noexcept;
	void setCallbacks() const noexcept;
	void bindDefaultFrameBuffer() const noexcept;
	void setWindowSize(int width, int height) const noexcept;

};

