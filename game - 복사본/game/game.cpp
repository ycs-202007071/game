// game.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "game.h"
#include "resource.h"
/*#include "stdio.h"
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif*/

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
WCHAR pass_1[MAX_LOADSTRING];
BOOL light_f = false;
BOOL frame_f = false;
int safe_f = 1;
BOOL door_f = false;
BOOL pot_f = false;
BOOL drawer1_f = false;
BOOL drawer2_f = false;
int drawer3_f = 1;
int x, y;
BOOL item1_f = false;
BOOL item2_f = false;
BOOL item3_f = false;
BOOL item4_f = false;
BOOL item5_f = false;
BOOL item6_f = false;
int g_ps;
int password = 1215;
BOOL end_f;
BOOL door2_f = false;

//사각형
RECT light_r;//조명
RECT frame_r;//액자
RECT safe_r;//금고
RECT door_r;//문
RECT pot_r;//화분
RECT drawer1_r;//서랍
RECT drawer2_r;//서랍
RECT drawer3_r;//서랍
RECT item1_r;//아이템창
RECT item2_r;//아이템창
RECT item3_r;//아이템창
RECT item4_r;//아이템창
RECT item5_r;//아이템창
RECT item6_r;//아이템창
RECT end1_r;//엔딩창
RECT end2_r;//엔딩창
RECT end3_r;//엔딩창
 
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc, hMemDC, hMemDC_door;
    PAINTSTRUCT ps;
    HBITMAP hImage, hOldBitmap;
    HBITMAP hImage_door, hOldBitmap_door;
    BITMAP bit;
    BITMAP bit_door;
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
        light_r.left = 400; light_r.right = 480; light_r.top = 0; light_r.bottom = 120;
        light_r.left = 400;	light_r.right = 480;	light_r.top = 80;	light_r.bottom = 120;
        frame_r.left = 80;	frame_r.right = 160;	frame_r.top = 160;	frame_r.bottom = 240;
        safe_r.left = 45;	safe_r.right = 200;	safe_r.top = 400;	safe_r.bottom = 560;
        door_r.left = 320;	door_r.right = 545;	door_r.top = 200;	door_r.bottom = 570;
        pot_r.left = 720;	pot_r.right = 800;	pot_r.top = 240;	pot_r.bottom = 320;
        drawer1_r.left = 690;	drawer1_r.right = 815;	drawer1_r.top = 330;	drawer1_r.bottom = 400;
        drawer2_r.left = 690;	drawer2_r.right = 815;	drawer2_r.top = 400;	drawer2_r.bottom = 480;
        drawer3_r.left = 690;	drawer3_r.right = 815;	drawer3_r.top = 480;	drawer3_r.bottom = 560;
        item1_r.left = 50;	item1_r.right = 170;	item1_r.top = 580;	item1_r.bottom = 660;
        item2_r.left = 180;	item2_r.right = 300;	item2_r.top = 580;	item2_r.bottom = 660;
        item3_r.left = 310;	item3_r.right = 430;	item3_r.top = 580;	item3_r.bottom = 660;
        item4_r.left = 440;	item4_r.right = 560;	item4_r.top = 580;	item4_r.bottom = 660;
        item5_r.left = 570;	item5_r.right = 690;	item5_r.top = 580;	item5_r.bottom = 660;
        item6_r.left = 700;	item6_r.right = 820;	item6_r.top = 580;	item6_r.bottom = 660;
        end1_r.left = 620;	end1_r.right = 800;	end1_r.top = 0;	end1_r.bottom = 90;
        end2_r.left = 630;	end2_r.right = 700;	end2_r.top = 10;	end2_r.bottom = 80;
        end3_r.left = 720;	end3_r.right = 810;	end3_r.top = 10;	end3_r.bottom = 80;



        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        hMemDC = CreateCompatibleDC(hdc);
        hMemDC_door = CreateCompatibleDC(hdc);
        MessageBox(hWnd, L"나는 내가 누군지 기억이 나지 않고 어딘지 모르는 이곳에 갇혀있다.\n 여기는 어딜까.\n※비밀번호가 틀릴경우 재시작 바랍니다", L"게임 시작", MB_OK); //살려야한다
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

        Rectangle(hdc, 45, 575, 825, 665);//아이템목록
        Rectangle(hdc, 680, 320, 825, 570);//서랍
        Rectangle(hdc, 45, 400, 80, 570);//금고다리
        Rectangle(hdc, 165, 400, 200, 570);//금고다리
        
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
        Ellipse(hdc, 330, 370, 350, 390);
        Ellipse(hdc, 748, 340, 763, 355);
        Ellipse(hdc, 748, 410, 763, 425);
        Ellipse(hdc, 748, 490, 763, 505);
        Rectangle(hdc, 55, 410, 190, 550);
        Ellipse(hdc, 70, 460, 110, 500);

        
        
       
        hImage = (HBITMAP)LoadImage(NULL, TEXT("lamp.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);
        GetObject(hImage, sizeof(BITMAP), &bit);
        BitBlt(hdc, 0, 0, 900, 750, hMemDC, 0, 0, SRCCOPY);
        SelectObject(hMemDC, hOldBitmap);
        DeleteObject(hImage);
        DeleteDC(hMemDC);
        EndPaint(hWnd, &ps);
        return 0;

        



        EndPaint(hWnd, &ps);

    }
    break;
    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        if (x >= 400 && x <= 480 && y >= 0 && y <= 120)//조명
        {
            if (light_f == false) {
                MessageBox(hWnd, L"찢어진 종이를 찾았어.", L"아이템1 활성화", MB_OK);
                light_f = true;
                item1_f = true;
            }
            else {
                MessageBox(hWnd, L"더이상 아무것도 없어.", L"조명", MB_OK);
            }
        }

        if (x >= 80 && x <= 160 && y >= 160 && y <= 240)//액자
        {
            if (frame_f == false) {
                MessageBox(hWnd, L"찢어진 종이를 찾았어. ", L"아이템2 활성화", MB_OK);
                frame_f = true;
                item2_f = true;

            }
            else {
                MessageBox(hWnd, L"더이상 아무것도 없어.", L"액자", MB_OK);
            }
        }

        if (x >= 45 && x <= 200 && y >= 400 && y <= 560)//금고
        {
            if (safe_f == 1) {
                MessageBox(hWnd, L"잠겨있어, 비밀번호를 입력해야해.", L"금고", MB_OK);
            }
            if (safe_f == 2) {
                MessageBox(hWnd, L"내가 제일 행복했던 날은 언제였을까?", L"금고", MB_OK);
            }

            if (safe_f == 3) {
                 MessageBox(hWnd, L"마지막 열쇠야.", L"아이템6 활성화", MB_OK);
                 item6_f = true;
                 safe_f = 4;
            }
            if (safe_f == 4) {
                MessageBox(hWnd, L"더이상 아무것도 없어.", L"금고", MB_OK);
            }
        }

        if (x >= 320 && x <= 545 && y >= 200 && y <= 570)//문
        {
            if (door_f == false) {
                MessageBox(hWnd, L"문이 잠겨있어. ", L"문", MB_OK);
            }
            else {
                MessageBox(hWnd, L"너도 다이어리와 쪽지로 알고 있잖아. ", L"문", MB_OK);
                MessageBox(hWnd, L"여기가 꿈이라는 걸. ", L"???", MB_OK);
                MessageBox(hWnd, L"진짜 나갈꺼야?", L"???", MB_OK);
                MessageBox(hWnd, L"여기를 나가게 되면 다시는 돌아오지 못하게 될꺼야...", L"???", MB_OK);
                MessageBox(hWnd, L"여기서 우리 평생 쉬는게 좋을지도 몰라.", L"나", MB_OK);
                MessageBox(hWnd, L"잘 생각해줘.", L"나", MB_OK);
                MessageBox(hWnd, L"난 못보낼거같아. 그래서 이문은 절대 열리지 않아. ", L"나", MB_OK);
                door2_f = true;
            }
        }

        if (x >= 820 && x <= 900 && y >= 0 && y <= 80)//문2
        {
            if (door2_f == false) {
            }
            else {
                MessageBox(hWnd, L"End - 현실로의 복귀\n 주인공은 현실로 돌아갔습니다. \n아무것도 없는 영원한 꿈보단 괴로워도 행복할 수도 있는 현실이 나을 지도 모르니까요\n\n 너무 행복하려고 애쓰지 않아도 괜찮아.\n 하지만 네가 어떤 것들에게서\n 진정한 행복을 느끼는지 스스로 발견하는 일에는 애써야 해\n 세상의 행복이 아닌 나의 행복을 아는 일\n 그런 일들을 사치라 생각하지 않아야 해\n - 달의 조각 중 행복, 하현", L"엔딩1", MB_OK);
                EndDialog(hWnd, LOWORD(wParam));
            }
        }
        if (x >= 0 && x <= 80 && y >= 0 && y <= 80)//문2
        {
            if (door2_f == false) {
            }
            else {
                MessageBox(hWnd, L"End - 영원한 안식\n 주인공은 영원한 꿈속에 남기로 했답니다.\n 죽은 것은 아니에요. 그냥\n 그냥 현실들이 너무 버거워 도망가 있을 뿐이에요\n\n 우리 저 깜깜한 바닷속으로 가자, 내가 말하면\n 사실 나 그말을 기다리고 있었어\n 그렇게 함께 사라질 사람을 찾고 있어\n 벗어 둔 신발 곱게 포개어 놓고 \n내 마음에 네 마음 더해\n 딱 그 무게만큼만 저 아래로 가라앉자\n - 달의 조각 중 잠수, 하현 ", L"엔딩2", MB_OK);
                EndDialog(hWnd, LOWORD(wParam));
            }
        }

        if (x >= 720 && x <= 800 && y >= 240 && y <= 320)//화분
        {
            if (pot_f == false) {
                MessageBox(hWnd, L"열쇠를 주었어. ", L"아이템4 활성화", MB_OK);
                item4_f = true;
                pot_f = true;
            }
            else {
                MessageBox(hWnd, L"이젠 식물밖에 없어.", L"화분", MB_OK);
            }
        }

        if (x >= 690 && x <= 815 && y >= 330 && y <= 400)//서랍1
        {
            if (drawer1_f == false) {
                MessageBox(hWnd, L"찢어진 종이를 찾았어 ", L"아이템3 활성화", MB_OK);
                item3_f = true;
                drawer1_f = true;
               
            }
            else {
                MessageBox(hWnd, L"더이상 아무것도 없어.", L"서랍1", MB_OK);
               
            }
        }

        if (x >= 690 && x <= 815 && y >= 400 && y <= 480)//서랍2
        {
            MessageBox(hWnd, L"비어있어. ", L"서랍2", MB_OK);
        }

        if (x >= 690 && x <= 815 && y >= 480 && y <= 560)//서랍3
        {
            if (drawer3_f == 1) {
                MessageBox(hWnd, L"잠겨있어, 열쇠를 사용해야해. ", L"서랍3", MB_OK);
            }
            if (drawer3_f == 2) {
                MessageBox(hWnd, L"다이어리를 찾았어. ", L"아이템5 활성화", MB_OK);
                item5_f = true;
                drawer3_f = 3;
            }
            if (drawer3_f == 3) {
                MessageBox(hWnd, L"더이상 아무것도 없어.", L"서랍3", MB_OK);
            }
        }

        if (x >= 50 && x <= 170 && y >= 580 && y <= 660)//아이템
        {
            if (item1_f == false) {
            }
            else {
                MessageBox(hWnd, L"여기가 더 좋을지도 몰라\n저밖엔 많은 나쁜 사람들이 있어.", L"메모1", MB_OK);
            }
        }
        if (x >= 180 && x <= 300 && y >= 580 && y <= 660)//아이템2
        {
            if (item2_f == false) {
            }
            else {
                MessageBox(hWnd, L"꿈 or 현실", L"메모2", MB_OK);
            }
        }
        if (x >= 310 && x <= 430 && y >= 580 && y <= 660)//아이템3
        {
            if (item3_f == false) {
            }
            else {
                MessageBox(hWnd, L"Exit = right top, leave = left top", L"메모3", MB_OK);
            }
        }
        if (x >= 440 && x <= 570 && y >= 580 && y <= 660)//아이템4
        {
            if (item4_f == false) {
            }
            else {
                drawer3_f = 2;
                MessageBox(hWnd, L"3번째 서랍이 열렸어, 열쇠는 이제 쓸모 없어.", L"ITEM4", MB_OK);
            }
        }

        if (x >= 570 && x <= 690 && y >= 580 && y <= 660)//아이템5
        {
            if (item5_f == false) {
            }
            else {
                MessageBox(hWnd, L"12.15 오늘은 내 생일이다. 너무 즐겁다. \n02.23 취업을 했다. \n09.02 지친다. 다이어리를 쓸 기력도 없다. \n이게 내가 바라던 생활인가? 그냥 다 잊고 잠들고 싶다. \n10.02 평생 잘 수 있는 방법을 찾아냈다. 이 방법이 성공하기를", L"다이어리", MB_OK);
                safe_f = 2;

            }
        }
   

        if (x >= 700 && x <= 820 && y >= 580 && y <= 660)//아이템6
        {
            if (item6_f == false) {
            }
            else {
                MessageBox(hWnd, L"문이 열렸어. ", L"마지막 열쇠", MB_OK);
                door_f = true;

            }
        }
        break;

        //if()

     case WM_KEYDOWN:
    {
        wchar_t value;
        int v;
        if ('0' > wParam)
            break;
        if ('9' < wParam)
            break;
        value = wParam;
        pass_1[g_ps++] = wParam;
        v = _wtoi(pass_1);
        //printf("%d", v);
        MessageBox(hWnd, pass_1, L"패스워드", MB_OK);
        //password = lstrcmpW(pass_1, ps);
        if (password == v)
        {
            MessageBox(hWnd, L"금고가 열렸어.", L"금고가 열렸어.", MB_OK);
            safe_f = 3;
            //drawer3_f == 3;
        }
       
    
        //lstrcatW(pass_1, (LPCSTR)value);
        //MessageBox(hWnd, L"3번째 서랍이 열렸어.", L"서랍3", MB_OK);
        
        //drawer3_f == 2;
    break;
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