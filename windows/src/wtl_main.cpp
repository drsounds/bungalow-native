#include <atlbase.h>
#include <atlapp.h>
#include <atlframe.h>
#include <atltypes.h>
#include <atlcrack.h>
#include <dwmapi.h>
#include <windowsx.h>

namespace WTL
{
    using ::CPoint;
    using ::CSize;
}

#include "NativeApplication.h"

using namespace ATL;
CAppModule _Module;

namespace
{
    constexpr int headerHeight = 36;
    constexpr int captionButtonWidth = 46;
    constexpr int menuWidth = 80;

    class MainFrame : public CFrameWindowImpl<MainFrame>
    {
    public:
        DECLARE_FRAME_WND_CLASS_EX(_T("BungalowNativeWtlWindow"), CS_DROPSHADOW, COLOR_WINDOW)

        space::NativeApplication app;

        BEGIN_MSG_MAP(MainFrame)
            MSG_WM_CREATE(OnCreate)
            MSG_WM_SIZE(OnSize)
            MSG_WM_PAINT(OnPaint)
            MESSAGE_HANDLER(WM_NCCALCSIZE, OnNcCalcSize)
            MESSAGE_HANDLER(WM_NCPAINT, OnNcPaint)
            MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest)
            MSG_WM_LBUTTONDOWN(OnLeftButtonDown)
            MSG_WM_LBUTTONUP(OnLeftButtonUp)
            MSG_WM_MOUSEMOVE(OnMouseMove)
            MSG_WM_TIMER(OnTimer)
            MESSAGE_HANDLER(WM_COMMAND, OnCommand)
            CHAIN_MSG_MAP(CFrameWindowImpl<MainFrame>)
        END_MSG_MAP()

        LRESULT OnCreate(LPCREATESTRUCT)
        {
            return app.initialize(m_hWnd) ? 0 : -1;
        }

        LRESULT OnNcCalcSize(UINT message, WPARAM wParam, LPARAM lParam, BOOL&)
        {
            const LRESULT result = DefWindowProc(message, wParam, lParam);
            if (wParam)
                reinterpret_cast<NCCALCSIZE_PARAMS *>(lParam)->rgrc[0].top += headerHeight;
            else
                reinterpret_cast<RECT *>(lParam)->top += headerHeight;
            return result;
        }

        LRESULT OnNcPaint(UINT message, WPARAM wParam, LPARAM lParam, BOOL&)
        {
            const LRESULT result = DefWindowProc(message, wParam, lParam);
            RECT windowRect{};
            POINT clientOrigin{};
            GetWindowRect(&windowRect);
            ClientToScreen(&clientOrigin);

            HDC dc = ::GetWindowDC(m_hWnd);
            if (!dc)
                return result;

            const int width = windowRect.right - windowRect.left;
            const int top = clientOrigin.y - windowRect.top - headerHeight;
            RECT header{0, top, width, top + headerHeight};
            HBRUSH background = CreateSolidBrush(RGB(32, 32, 32));
            FillRect(dc, &header, background);
            DeleteObject(background);

            SetBkMode(dc, TRANSPARENT);
            SetTextColor(dc, RGB(255, 255, 255));

            RECT menu{0, top, menuWidth, top + headerHeight};
            DrawTextW(dc, L"Menu", 4, &menu, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            RECT title{menuWidth, top, width - captionButtonWidth * 3, top + headerHeight};
            wchar_t windowTitle[256]{};
            GetWindowTextW(m_hWnd, windowTitle, static_cast<int>(sizeof(windowTitle) / sizeof(*windowTitle)));
            DrawTextW(dc, windowTitle, -1, &title, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

            const UINT buttonFlags[] = {DFCS_CAPTIONMIN, IsZoomed() ? DFCS_CAPTIONRESTORE : DFCS_CAPTIONMAX, DFCS_CAPTIONCLOSE};
            for (int i = 0; i < 3; ++i)
            {
                RECT button{width - captionButtonWidth * (3 - i), top,
                    width - captionButtonWidth * (2 - i), top + headerHeight};
                DrawFrameControl(dc, &button, DFC_CAPTION, buttonFlags[i]);
            }

            ::ReleaseDC(m_hWnd, dc);
            return result;
        }

        LRESULT OnNcHitTest(UINT message, WPARAM wParam, LPARAM lParam, BOOL&)
        {
            const LRESULT hit = DefWindowProc(message, wParam, lParam);
            if (hit >= HTLEFT && hit <= HTBOTTOMRIGHT)
                return hit;

            RECT windowRect{};
            POINT clientOrigin{};
            GetWindowRect(&windowRect);
            ClientToScreen(&clientOrigin);
            const int x = GET_X_LPARAM(lParam);
            const int y = GET_Y_LPARAM(lParam);
            const int headerTop = clientOrigin.y - headerHeight;
            if (x < windowRect.left || x >= windowRect.right || y < headerTop || y >= clientOrigin.y)
                return hit;

            if (x >= windowRect.right - captionButtonWidth)
                return HTCLOSE;
            if (x >= windowRect.right - captionButtonWidth * 2)
                return HTMAXBUTTON;
            if (x >= windowRect.right - captionButtonWidth * 3)
                return HTMINBUTTON;
            if (x < windowRect.left + menuWidth)
                return HTSYSMENU;
            return HTCAPTION;
        }

        void OnSize(UINT, CSize)
        {
            app.resize();
            Invalidate(FALSE);
        }

        void OnPaint(HDC dc)
        {
            app.paint(dc);
        }

        void OnLeftButtonDown(UINT, CPoint point)
        {
            SetCapture();
            app.mouseEvent("mousedown", point.x, point.y);
        }

        void OnLeftButtonUp(UINT, CPoint point)
        {
            ReleaseCapture();
            app.mouseEvent("mouseup", point.x, point.y);
        }

        void OnMouseMove(UINT, CPoint point)
        {
            app.mouseEvent("mousemove", point.x, point.y);
        }

        void OnTimer(UINT_PTR)
        {
            app.timer();
        }

        LRESULT OnCommand(UINT, WPARAM wParam, LPARAM lParam, BOOL&)
        {
            app.command(wParam, lParam);
            return 0;
        }
    };
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int showCommand)
{
    if (FAILED(_Module.Init(nullptr, instance)))
        return 1;

    MainFrame frame;
    if (frame.CreateEx() == nullptr)
    {
        _Module.Term();
        return 1;
    }
    frame.ModifyStyle(WS_CAPTION, 0, SWP_FRAMECHANGED);
    const DWORD roundedCorners = 2;
    DwmSetWindowAttribute(frame, 33, &roundedCorners, sizeof(roundedCorners));
    frame.ShowWindow(showCommand);
    frame.UpdateWindow();

    CMessageLoop loop;
    _Module.AddMessageLoop(&loop);
    const int result = loop.Run();
    _Module.RemoveMessageLoop();
    _Module.Term();
    return result;
}
