#pragma once
// include the basic windows header file
#include <windows.h>
#include <windowsx.h>
#include <string>

using namespace std;

// the WindowProc function prototype
//LRESULT CALLBACK WindowProc(HWND m_hWnd,
//	UINT message,
//	WPARAM wParam,
//	LPARAM lParam);

class Window
{
public:
	Window(HINSTANCE hInstance);
	virtual ~Window();

	// static message handler to put in WNDCLASSEX structure
	static LRESULT CALLBACK DummyWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool Create(wstring title, int x, int y, int width, int height, DWORD style, HWND parent = 0);
	HWND GetHWND() { return m_hWnd; }

	virtual int OnClose();

	virtual void Show(int nCmdShow = 0);
protected:
	int MainLoop();

	// the real message handler
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// returns a pointer the window (stored as the WindowLong)
	inline static Window *GetObjectFromWindow(HWND hWnd) { return (Window *)GetWindowLong(hWnd, GWL_USERDATA); }
private:
	// the handle for the window, filled by a function
	HWND m_hWnd;
	HWND m_parent;
	HINSTANCE m_hInstance;

	// this struct holds information for the window class
	WNDCLASSEX m_wc;
};