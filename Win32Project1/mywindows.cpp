#include "mywindows.h"

Window::Window(HINSTANCE hInstance)
{
	// clear out the window class for use
	ZeroMemory(&m_wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	m_wc.cbSize = sizeof(WNDCLASSEX);
	m_wc.style = CS_HREDRAW | CS_VREDRAW;
	m_wc.lpfnWndProc = DummyWindowProc;
	m_wc.hInstance = hInstance;
	m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	m_wc.lpszClassName = L"WindowClass1";

	// register the window class
	RegisterClassEx(&m_wc);

	m_hInstance = hInstance;
}

int Window::MainLoop()
{
	// this struct holds Windows event messages
	MSG msg;

	// wait for the next message in the queue, store the result in 'msg'
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// translate keystroke messages into the right format
		TranslateMessage(&msg);

		// send the message to the WindowProc function
		DispatchMessage(&msg);
	}

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

// this is the main message handler for the program
LRESULT Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	wstring output = L"Window::WindowProc  ->  message: ";
	output += to_wstring(message);
	output += L"\n";

	OutputDebugString(output.c_str());

	// sort through and find what code to run for the message given
	switch (message)
	{
	// this message is read when the window is closed
	case WM_DESTROY:
	{
		return OnClose();
	} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT Window::DummyWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window *wnd = nullptr;

	wstring output = L"Window::DummyWindowProc  ->  message: ";
	output += to_wstring(message);
	output += L"\n";

	OutputDebugString(output.c_str());

	if (message == WM_NCCREATE)
	{
		// get the pointer to the window from
		// lpCreateParams which was set in CreateWindow
		SetWindowLong(hWnd, GWL_USERDATA,
			(long)((LPCREATESTRUCT(lParam))->lpCreateParams));
	}

	// get the pointer to the window
	wnd = GetObjectFromWindow(hWnd);

	// if we have the pointer, go to the message handler of the window
	// else, use DefWindowProc
	if (wnd)
		return wnd->WindowProc(hWnd, message, wParam, lParam);
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}

Window::~Window()
{
}

bool Window::Create(wstring title, int x, int y, int width, int height, DWORD style, HWND parent)
{
	m_parent = parent;

	// create the window and use the result as the handle
	m_hWnd = CreateWindow(
		L"WindowClass1",    // name of the window class
		title.c_str(),   // title of the window
		style,    // window style
		x,    // x-position of the window
		y,    // y-position of the window
		width,    // width of the window
		height,    // height of the window
		m_parent,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		m_hInstance,    // application handle
		(void *)this);    // used with multiple windows, NULL
	
	//OutputDebugString(wstring(L"m_hWnd: " + to_wstring(reinterpret_cast<unsigned long>(m_hWnd)) + L"\n").c_str());

	return (m_hWnd != nullptr);
}

int Window::OnClose()
{
	MessageBox(m_hWnd, L"chiudo...", L"Ciao", MB_ICONINFORMATION | MB_OK);
	
	// close the application entirely
	PostQuitMessage(0);
	return 0;
}

void Window::Show(int nCmdShow)
{
	// display the window on the screen
	ShowWindow(m_hWnd, nCmdShow);

	MainLoop();
}
