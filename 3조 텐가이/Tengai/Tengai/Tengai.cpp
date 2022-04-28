// Tengai.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Tengai.h"
#include "Obj.h"
#include "MainGame.h"
#include "InitPage.h"
#include "ClearPage.h"
#include "GameOver.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
HWND	g_hWnd;
DWORD		dwOldTime = GetTickCount();


// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TENGAI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TENGAI));

    MSG msg;
	msg.message = WM_NULL;

	CMainGame*	pMainGame = new CMainGame;

	CInitPage* StartPage = new CInitPage;
	CClearPage* Clear = nullptr;
	CGameOver* pGameOver = nullptr;


	//if (nullptr == pMainGame)
	//	return FALSE;

	pMainGame->Initialize();

	

	while (true)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			PostQuitMessage(0);
			break;
		}
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		else
		{
			
			if (StartPage)
			{
				if (dwOldTime + 10 < GetTickCount())
				{
					StartPage->Update();
					int iResult = StartPage->GetStart();
					StartPage->Render();

					dwOldTime = GetTickCount();

					if (iResult == 1)
					{            // ������ǥ�� ������ ����Ǵ� �ڵ�.
						Safe_Delete<CInitPage*>(StartPage);
						if (!pMainGame) {
							pMainGame = new CMainGame;
							pMainGame->Initialize();
							hit = 0;
						}
					}
				}
			}

			else if(pMainGame)
			{
				if (dwOldTime + 10 < GetTickCount())
				{
					int iResult = pMainGame->Update();
					if (iResult == GAMECLEAR)
					{			
							Safe_Delete<CMainGame*>(pMainGame);	
							Clear = new CClearPage;
					}
					else if (iResult == GAMEOVER)
					{
						Safe_Delete<CMainGame*>(pMainGame);//����â�� �����
						pGameOver = new CGameOver;//���ӿ���â�����
					}
					else
					{
						pMainGame->Late_Update();
						pMainGame->Render();
					}
					/*if (iResult == GAMEOVER)
						Safe_Delete<CMainGame*>(pMainGame);
					pMainGame->Late_Update();
					pMainGame->Render();*/

					
					dwOldTime = GetTickCount();					
				}
			}
			else if (pGameOver)//���ӿ���â.
			{
				if (dwOldTime + 10 < GetTickCount())
				{
					pGameOver;
					int iResult = pGameOver->Update();
					if (iResult == GAMERESTART)
					{//���� ������� 
						StartPage = new CInitPage;
						/*StartPage->Initialize();*/
					}
					else{
						pGameOver->Render();
					}
					

					dwOldTime = GetTickCount();
				}
			}
			else if (Clear)
			{
				if (dwOldTime + 10 < GetTickCount())
				{
				Clear->Update();
				Clear->Render();
				dwOldTime = GetTickCount();
				}
			}
			
		}
	}
	Safe_Delete<CMainGame*>(pMainGame);
	return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TENGAI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 
   RECT rc{ 0, 0, WINCX, WINCY };
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   300, 100, 
	   rc.right - rc.left,
	   rc.bottom - rc.top, 
	   nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
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
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);        
            EndPaint(hWnd, &ps);
        }
        break;



    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
