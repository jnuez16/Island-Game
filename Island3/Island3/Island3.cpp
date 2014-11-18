// Island3.cpp : Defines the entry point for the application.


#include "stdafx.h"
#include "Island3.h"
#include "islandMgr.h"
#include "Tile.h"
#include "Player.h"
#include "Prey.h"
#include "Animals.h"
#include "Predator.h"
#include <ctime>
#include <vector>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HBITMAP bitmap;									// variable for the image

//objects for classes i made
islandMgr imgr;
Player pl(100, 10);
Prey hunt(5, 25, 20);
Prey fish(10, 50, 15);
Predator prd(15, 20, 2);


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	DLG_ACTION(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	DLG_ATTACK(HWND, UINT, WPARAM, LPARAM);

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
	LoadString(hInstance, IDC_ISLAND3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ISLAND3));

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
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ISLAND3));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ISLAND3);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, windowWidthMin, windowHeightMin, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	Reset(imgr);
	InvalidateRect(hWnd, NULL, true);
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	int xPos, yPos, c;
	HDC hMemDC;
	srand(time(NULL));

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

		//initializes the image
	case WM_CREATE:
		{
			bitmap = (HBITMAP)LoadImage(NULL, _T("Q:\\jnuez16\\CS172\\FINAL_PROJECT_Joshua_Nuez\\graphic.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		break;
	case WM_LBUTTONUP:
		c = (rand()%100)+1;
		//Get the coordinates to the array
		xPos = (LOWORD(lParam) - 100)/ 100;
		yPos = (HIWORD(lParam) - 100)/ 100;

		//Tell the game manager to add a move
		SetMove(imgr, xPos, yPos);
		//outputs the dialog box based on the chance of meeting a predator
		if(c >= imgr.isletile[imgr.board[xPos][yPos]].getRate())
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ATTACK), hWnd, DLG_ATTACK);
		}
		//outputs actions you can take
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ACTION), hWnd, DLG_ACTION);
		InvalidateRect(hWnd, NULL, true);
		//checks if the game is over
		CheckWinner(pl, imgr, hWnd);
		break;
	case WM_SIZE:
		RECT r; //make a rectangle object
		//Makes sure the window does not go below the minimum
		GetWindowRect(hWnd, &r);
		if (r.right - r.left < windowWidthMin) {
			SetWindowPos(hWnd, HWND_TOP, r.left, r.top, windowWidthMin, r.bottom-r.top, SWP_NOZORDER | SWP_NOSENDCHANGING);
		}
		if (r.bottom - r.top < windowHeightMin) {
			SetWindowPos(hWnd, HWND_TOP, r.left, r.top, r.right - r.left, windowHeightMin, SWP_NOZORDER | SWP_NOSENDCHANGING);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		//draws the background image
		hMemDC=CreateCompatibleDC(hdc);
		::SelectObject(hMemDC, bitmap);
		BitBlt(hdc, 100, 100, 300, 300, hMemDC, 0, 0, SRCCOPY);
		::DeleteDC(hMemDC);
		//draws the grid over the image
		DrawGrid(pl, imgr, hWnd, hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

//dialog box for actions you can take
INT_PTR CALLBACK DLG_ACTION(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	srand(time(NULL));
	UNREFERENCED_PARAMETER(lParam);
	switch(message)
	{
	case WM_INITDIALOG:
		return(INT_PTR)TRUE;
	case WM_COMMAND:
		if(LOWORD(wParam) == IDFISH)
		{
			int r = (rand()%100)+1;
			if(r <= fish.getChance())
			{
				HPup(fish, pl);
			}
			else
			{
				HPdown(fish, pl);
			}
		}

		else if(LOWORD(wParam) == IDHUNT)
		{
			int r = (rand()%100)+1;
			if(r <= hunt.getChance())
			{
				HPup(hunt, pl);
			}
			else
			{
				HPdown(hunt, pl);
			}
			
		}

		else if(LOWORD(wParam) == IDTRAIN)
		{
			train(pl);
		}

		else if(LOWORD(wParam) == IDREST)
		{
			rest(pl);
		}

		if(LOWORD(wParam) == IDFISH || LOWORD(wParam) == IDHUNT || LOWORD(wParam) == IDTRAIN || LOWORD(wParam) == IDREST)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return(INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

//dialog box if you meet a predator
INT_PTR CALLBACK DLG_ATTACK(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch(message)
	{
	case WM_INITDIALOG:
		return(INT_PTR)TRUE;
	case WM_COMMAND:
		if(LOWORD(wParam) == IDFIGHT)
		{
			fight(pl, prd);
		}
		else if(LOWORD(wParam) == IDRUN)
		{
			run(pl);
		}

		if(LOWORD(wParam) == IDFIGHT || LOWORD(wParam) == IDRUN)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return(INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

