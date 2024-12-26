#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <Windows.h>


// Global Members

// Main Window Class Name
static TCHAR szWindowClass[] = _T("SimpleWebClient");

// Application Title
static TCHAR szTitle[] = _T("SimpleWebClient");

// Instance Handle
static HINSTANCE hInst;

// Window-Procedure callback function
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// HTML file content
std::string	fileContent;

// Function to read local html file
bool ReadHTMLFile(const std::string&);

// Entry Point
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, _T("Call to RegisterClassEX failed!"), _T("SimpleWebClient says"), NULL);
		return 1;
	}

	hInst = hInstance;

	HWND hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
		500, 100, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		MessageBox(NULL, _T("Call to CreateWindowEx failed!"), _T("SimpleWebClient says"), NULL);
		return 1;
	}

	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, SimpleWebClient!");

	switch (message)
	{
	case WM_CREATE:

		if (!ReadHTMLFile("C:\\Users\\PRAATLE\\selfLearning\\SWC\\index.html"))
		{
			MessageBox(NULL, _T("Failed to open file"), _T("SimpleWebClient says"), NULL);
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 5, 5, std::wstring(fileContent.begin(), fileContent.end()).c_str(), _tcslen(std::wstring(fileContent.begin(), fileContent.end()).c_str()));
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

bool ReadHTMLFile(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		return false;
	}

	file >> fileContent;

	std::string line;

	while (file >> line)
	{
		fileContent += line;
		fileContent.push_back('\n');
	}

	return true;
}
