// game.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "game.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
BOOL light_f = false;
BOOL frame_f = false;
BOOL safe_f = 1;
BOOL door_f = false;
BOOL pot_f = false;
BOOL drawer1_f = false;
BOOL drawer2_f = false;
int drawer3_f = 1;

//사각형
RECT light_r;
RECT frame_r;
RECT safe_r;
RECT door_r;
RECT pot_r;
RECT drawer1_r;
RECT drawer2_r;
RECT drawer3_r;
RECT item1_r;
RECT item2_r;
RECT item3_r;
RECT item4_r;
RECT item5_r;
RECT item6_r;
 
/*
void light()
{
    if (light_f = false) {
        MessageBox(hWnd, L"찢어진 종이를 찾았어.", L"조명", MB_OK);
        light_f = true;
    }
    else {
        MessageBox(hWnd, L"더이상 아무것도 없어.", L"조명", MB_OK);
    }
}

void frame()
{
    if (frame_f = false) {
        MessageBox(hWnd, L"찢어진 종이를 찾았어. ", L"액자", MB_OK);
        frame_f = true;
    }
    else {
        MessageBox(hWnd, L"더이상 아무것도 없어.", L"액자", MB_OK);
    }
}

void safe()
{
    if (safe_f = false) {
        MessageBox(hWnd, L"잠겨있어, 비밀번호를 입력해야해.", L"금고", MB_OK);
        safe_f = true;
    }
    else {
        MessageBox(hWnd, L"이미 열려있어.", L"금고", MB_OK);
    }
}

void door()
{
    if (door_f = false) {
        MessageBox(hWnd, L"문이 잠겨있어. ", L"문", MB_OK);
        door_f = true;
    }
    else {
        MessageBox(hWnd, L"문이 열렸어.", L"문", MB_OK);
    }
}

void pot()
{
    if (pot_f = false) {
        MessageBox(hWnd, L"열쇠를 주었어. ", L"화분", MB_OK);
        pot_f = true;
    }
    else {
        MessageBox(hWnd, L"꽃밖에 없어.", L"화분", MB_OK);
    }
}

void drawer1()
{
    if (drawer1_f = false) {
        MessageBox(hWnd, L"찢어진 종이를 찾았어. ", L"서랍1", MB_OK);
        drawer1_f = true;
    }
    else {
        MessageBox(hWnd, L"더이상 아무것도 없어.", L"서랍1", MB_OK);
    }
}

void drawer2()
{
    MessageBox(hWnd, L"비어있어. ", L"서랍2", MB_OK);
}

void drawer3()
{
    if (drawer3_f = 1) {
        MessageBox(hWnd, L"잠겨있어, 비밀번호를 입력해야해. ", L"서랍3", MB_OK);
    }
    if(drawer3_f = 2) {
        MessageBox(hWnd, L"다이어리를 찾았어. ", L"서랍3", MB_OK);
    }
    else {
        MessageBox(hWnd, L"더이상 아무것도 없어.", L"서랍3", MB_OK);
    }
}
*/





// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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
    LoadStringW(hInstance, IDC_GAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAME));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAME));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GAME);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

RECT map[6][9] =
{ 0, };
int x = 80, y = 80;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
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
    case WM_CREATE:
        MoveWindow(hWnd, 0, 0, 900, 750, true);
        HDC hdc;
        light_r.left = 400; light_r.right = 480; light_r.top = 80; light_r.bottom = 120;
        light_r.left = 400;	light_r.right = 480;	light_r.top = 80;	light_r.bottom = 120;
        frame_r.left = 80;	frame_r.right = 160;	frame_r.top = 160;	frame_r.bottom = 240;
        safe_r.left = 80;	safe_r.right = 160;	safe_r.top = 400;	safe_r.bottom = 480;
        door_r.left = 320;	door_r.right = 400;	door_r.top = 320;	door_r.bottom = 400;
        pot_r.left = 720;	pot_r.right = 800;	pot_r.top = 240;	pot_r.bottom = 320;
        drawer1_r.left = 720;	drawer1_r.right = 800;	drawer1_r.top = 320;	drawer1_r.bottom = 400;
        drawer2_r.left = 720;	drawer2_r.right = 800;	drawer2_r.top = 400;	drawer2_r.bottom = 480;
        drawer3_r.left = 720;	drawer3_r.right = 800;	drawer3_r.top = 480;	drawer3_r.bottom = 560;
        item1_r.left = 50;	item1_r.right = 170;	item1_r.top = 580;	item1_r.bottom = 660;
        item2_r.left = 180;	item2_r.right = 300;	item2_r.top = 580;	item2_r.bottom = 660;
        item3_r.left = 310;	item3_r.right = 430;	item3_r.top = 580;	item3_r.bottom = 660;
        item4_r.left = 440;	item4_r.right = 560;	item4_r.top = 580;	item4_r.bottom = 660;
        item5_r.left = 570;	item5_r.right = 690;	item5_r.top = 580;	item5_r.bottom = 660;
        item6_r.left = 700;	item6_r.right = 820;	item6_r.top = 580;	item6_r.bottom = 660;




        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        MessageBox(hWnd, L"나는 내가 누군지 기억이 나지 않고 어딘지 모르는 이곳에 갇혀있다. 일단 여기를 나가자", L"게임 시작", MB_OK);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        
        Rectangle(hdc, 45, 575, 825, 665);//아이템목록
        Rectangle(hdc, light_r.left, light_r.top, light_r.right, light_r.bottom);
        Rectangle(hdc, frame_r.left, frame_r.top, frame_r.right, frame_r.bottom);
        Rectangle(hdc, safe_r.left, safe_r.top, safe_r.right, safe_r.bottom);
        Rectangle(hdc, door_r.left, door_r.top, door_r.right, door_r.bottom);
        Rectangle(hdc, pot_r.left, pot_r.top, pot_r.right, pot_r.bottom);
        Rectangle(hdc, drawer1_r.left, drawer1_r.top, drawer1_r.right, drawer1_r.bottom);
        Rectangle(hdc, drawer2_r.left, drawer2_r.top, drawer2_r.right, drawer2_r.bottom);
        Rectangle(hdc, drawer3_r.left, drawer3_r.top, drawer3_r.right, drawer3_r.bottom);
        Rectangle(hdc, item1_r.left, item1_r.top, item1_r.right, item1_r.bottom);
        Rectangle(hdc, item2_r.left, item2_r.top, item2_r.right, item2_r.bottom);
        Rectangle(hdc, item3_r.left, item3_r.top, item3_r.right, item3_r.bottom);
        Rectangle(hdc, item4_r.left, item4_r.top, item4_r.right, item4_r.bottom);
        Rectangle(hdc, item5_r.left, item5_r.top, item5_r.right, item5_r.bottom);
        Rectangle(hdc, item6_r.left, item6_r.top, item6_r.right, item6_r.bottom);


        EndPaint(hWnd, &ps);
        
    }

    break;
    case WM_LBUTTONDOWN:

        break;
        {
            if (TRUE == IntersectRect(&) && frame_f = false) {
                MessageBox(hWnd, L"찢어진 종이를 찾았어. ", L"액자", MB_OK);
                frame_f = true;
            }
            else {
                MessageBox(hWnd, L"더이상 아무것도 없어.", L"액자", MB_OK);
            }}

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