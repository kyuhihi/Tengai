// Tengai.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Tengai.h"
#include "Obj.h"
#include "MainGame.h"
#include "InitPage.h"
#include "ClearPage.h"
#include "GameOver.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND	g_hWnd;
DWORD		dwOldTime = GetTickCount();


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TENGAI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
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
					{            // 누른좌표가 맞을시 실행되는 코드.
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
						Safe_Delete<CMainGame*>(pMainGame);//메인창을 지우고
						pGameOver = new CGameOver;//게임오버창만들고
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
			else if (pGameOver)//게임오버창.
			{
				if (dwOldTime + 10 < GetTickCount())
				{
					pGameOver;
					int iResult = pGameOver->Update();
					if (iResult == GAMERESTART)
					{//게임 재시작은 
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
            // 메뉴 선택을 구문 분석합니다.
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

// 정보 대화 상자의 메시지 처리기입니다.
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
