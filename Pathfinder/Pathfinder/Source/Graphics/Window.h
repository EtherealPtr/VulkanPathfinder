#pragma once

struct GLFWwindow;

class Window
{
public:
	Window(const unsigned short _width, const unsigned short _height, const char* _title);
	~Window();

	bool ShouldWindowClose() const;
	void Update();
	GLFWwindow* GetWindow() const { return m_Window; }
	unsigned short GetWidth() const;
	unsigned short GetHeight() const;

private:
	GLFWwindow* m_Window;
};