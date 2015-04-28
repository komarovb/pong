// lab1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "lab1.h"
#include "Windows.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

int xball = 50;
int yball = 50;
int BallDirection = 0;
int BallSpeed = 4;
int OldSpeed = 0;

int xpal = 200;
int ypal = 365;

int xAI = 8;

bool pause=false;

HWND mainWnd, ballWnd, AIWnd, GamerWnd;
// Forward declarations of functions included in this code module:
//Creating 4 classes for 4 windows of our program----------
ATOM				MainWindowClass(HINSTANCE hInstance);
ATOM				BallWindowClass(HINSTANCE hInstance);
ATOM				AIWindowClass(HINSTANCE hInstance);
ATOM				GamerWindowClass(HINSTANCE hInstance);
//---------------------------------------------------------

BOOL				InitInstance(HINSTANCE, int);

//Separate CALLBACKS for all windows
LRESULT CALLBACK	MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	BallWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	AIWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	GamerWndProc(HWND, UINT, WPARAM, LPARAM);
//----------------------------------------------------------

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LAB1, szWindowClass, MAX_LOADSTRING);

	MainWindowClass(hInstance);
	BallWindowClass(hInstance);
	AIWindowClass(hInstance);
	GamerWindowClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//Main window class
ATOM MainWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MainWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LAB1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}
//Ball window class
ATOM BallWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BallWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_LAB1);
	wcex.lpszClassName = (LPCWSTR)"ballWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}
//AI window class
ATOM AIWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = AIWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_LAB1);
	wcex.lpszClassName = (LPCWSTR)"aiWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}
//Gamer window class
ATOM GamerWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GamerWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_LAB1);
	wcex.lpszClassName = (LPCWSTR)"gamerWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

   hInst = hInstance; // Store instance handle in our global variable

   mainWnd = CreateWindow(szWindowClass, 0, WS_CLIPCHILDREN | WS_POPUP,
	   500, 250, 400, 400, NULL, NULL, hInstance, NULL);
   ballWnd = CreateWindow((LPCWSTR)"ballWindowClass", szTitle, WS_CHILD,
	   50, 50, 16, 16, mainWnd, NULL, hInstance, NULL);
   AIWnd = CreateWindow((LPCWSTR)"aiWindowClass", szTitle, WS_CHILD,
	   8, 10, 100, 20, mainWnd, NULL, hInstance, NULL);
   GamerWnd = CreateWindow((LPCWSTR)"gamerWindowClass", szTitle, WS_CHILD,
	   200, 365, 100, 20, mainWnd, NULL, hInstance, NULL);


   if (!mainWnd || !ballWnd || !AIWnd || !GamerWnd)
   {
      return FALSE;
   }

   ShowWindow(mainWnd, nCmdShow);
   UpdateWindow(mainWnd);

   SetWindowRgn(ballWnd, CreateEllipticRgn(0, 0, 16, 16), FALSE);
   ShowWindow(ballWnd, nCmdShow);
   UpdateWindow(ballWnd);

   ShowWindow(AIWnd, nCmdShow);
   UpdateWindow(AIWnd);

   SetFocus(GamerWnd);
   ShowWindow(GamerWnd, nCmdShow);
   UpdateWindow(GamerWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK MainWndProc(HWND mainWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_NCHITTEST:
		return HTCAPTION;
	break;
	case WM_NCRBUTTONDOWN:
	{
		POINT p;
		GetCursorPos(&p);
		HMENU menu = CreatePopupMenu();
		InsertMenu(menu, 0, 0, MF_ENABLED, L"Settings");
		TrackPopupMenu(menu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, p.x, p.y, 0, mainWnd, NULL);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(mainWnd, message, wParam, lParam);
	}
	return 0;
}
// BallWndProc - ball CALLBACK function
LRESULT CALLBACK BallWndProc(HWND currentWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		SetTimer(currentWnd, 1, 100, NULL);
	case WM_TIMER:{
					  //first check if the ball currently touches any sides of our field
					  if (xball <= 0)
					  {
						  if (BallDirection == 2)
							  BallDirection = 1;
						  if (BallDirection == 3)
							  BallDirection = 0;
					  }
					  if (xball >= 400 - 16)
					  {
						  if (BallDirection == 0)
							  BallDirection = 3;
						  if (BallDirection == 1)
							  BallDirection = 2;
					  }
					  if (yball >= 400 - 16)
					  {
						  BallSpeed = 0;
						  KillTimer(currentWnd, 1);
						  MessageBox(currentWnd, L"You Lost, try again later", L"^(", NULL);
						  PostQuitMessage(0);
					  }
					  if (yball <= 0)
					  {
						  if (BallDirection == 1)
							  BallDirection = 0;
						  if (BallDirection == 2)
							  BallDirection = 3;
					  }
					  if (yball + 16 >= 365 && xball >= xpal&&xball <= xpal + 100)
					  {
						  if (BallDirection == 0)
							  BallDirection = 1;
						  if (BallDirection == 3)
							  BallDirection = 2;
					  }
					  if (yball<=30 && xball+16 >= xAI&&xball+16 <= xAI + 100)
					  {
						  if (BallDirection == 2)
							  BallDirection = 3;
						  if (BallDirection == 1)
							  BallDirection = 0;
					  }

					  switch (BallDirection)
					  {
					  case 0:
					  {
								xball = xball + BallSpeed;
								yball = yball + BallSpeed;
					  }
						  break;
					  case 1:
					  {
								xball = xball + BallSpeed;
								yball = yball - BallSpeed;
					  }
						  break;
					  case 2:
					  {
								xball = xball - BallSpeed;
								yball = yball - BallSpeed;
					  }
						  break;
					  case 3:
					  {
								xball = xball - BallSpeed;
								yball = yball + BallSpeed;
					  }
						  break;
					  }
					  MoveWindow(currentWnd, xball, yball, 16, 16, TRUE);
						  
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(currentWnd, message, wParam, lParam);
	}
	return 0;
}
// AIWndProc - AI CALLBACK function
LRESULT CALLBACK AIWndProc(HWND currentWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		SetTimer(currentWnd, 2, 100, NULL);
	case WM_TIMER:{
			if ((BallDirection == 1 || BallDirection == 0)&&xAI<=300)
			{
			xAI += BallSpeed;
			MoveWindow(currentWnd, xAI, 10, 100, 20, TRUE);
			}
		if ((BallDirection == 2 || BallDirection == 3)&&xAI>=0)
		{
			xAI -= BallSpeed;
			MoveWindow(currentWnd, xAI, 10, 100, 20, TRUE);
		}
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(currentWnd, message, wParam, lParam);
	}
	return 0;
}
// GamerWndProc - gamer CALLBACK function
LRESULT CALLBACK GamerWndProc(HWND currentWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	int defy = 365; //default y cordinate

	switch (message)
	{
	case WM_NCHITTEST:
		return HTCAPTION;
		break;
	case WM_MOVE:
		{
			int xPos = (int)(short)LOWORD(lParam);   // horizontal position 
			int yPos = (int)(short)HIWORD(lParam);   // vertical position

			xpal = xPos;
			SetFocus(currentWnd);

			if (yPos > defy || yPos < defy)
			{
				SetWindowPos(currentWnd, NULL, xPos, defy, 0, 0, SWP_NOSIZE);
				//MoveWindow(currentWnd, xPos, defy, 100, 20, TRUE);
			}
			if (xPos>300){
				SetWindowPos(currentWnd, NULL, 300, defy, 0, 0, SWP_NOSIZE);
				xpal = 300;
			}
			if (xPos < 0){
				SetWindowPos(currentWnd, NULL, 0, defy, 0, 0, SWP_NOSIZE);
				xpal = 0;
			}
		}
		break;
	case WM_KEYDOWN:
		{
			RECT rectmem;
			GetWindowRect(currentWnd, &rectmem);
			switch (wParam)
			{
			case VK_LEFT:
				SetWindowPos(currentWnd, NULL, xpal-10, defy, 0, 0, SWP_NOSIZE);
				break;
			case VK_RIGHT:
				SetWindowPos(currentWnd, NULL, xpal+10, defy, 0, 0, SWP_NOSIZE);
				break;
			case VK_SPACE:
			{
				if (pause)
					{
					BallSpeed = OldSpeed;
					pause = false;
					}
				else{
					OldSpeed = BallSpeed;
					BallSpeed = 0;
					pause = true;
				}
			}
				break;
			case VK_UP:
				BallSpeed += 2;
				break;
			case VK_DOWN:
				if (BallSpeed>2)
				BallSpeed -= 2;
				break;
			}

		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(currentWnd, message, wParam, lParam);
	}
	return 0;
}