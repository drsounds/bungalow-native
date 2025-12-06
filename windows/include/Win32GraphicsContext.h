#pragma once

#ifndef H_WIN32SPIDER
#define H_WIN32SPIDER

#include <Windows.h>
#include <wingdi.h>
#include <map>
#include "libspider.h"
#include "SPColor.h"
#include "Element.h"
#include "GraphicsContext.h"
#include "InputEventArgs.h"
#include <map>
using namespace std;
using namespace spider;
LRESULT CALLBACK subEditProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace spider {
	class SPImage;
	class SPElement;
    class WindowElement;
	COLORREF toWin32Color(spider::SPColor color);
	class Win32GraphicsContext : public GraphicsContext {
	private:
		HDC hDC;
		HWND hWnd;
	public:
	    LPPOINT currentOffset;
	    void restoreOrigo();
	    HRGN currentRgn;
		static map<SPElement *, HWND> *controls;
		static map<HWND, SPElement *> *hwnds;
		Win32GraphicsContext(HWND hWnd, HDC hDC, WindowElement *window);
		~Win32GraphicsContext();
        SPImage *loadImage(const string& bitmap);

        virtual void drawImagePart(SPImage *image, int x, int y, int width, int height, int x1, int y1, int x2, int y2);
        virtual void drawSkinImage(string resourceId, int x, int y, int w, int h);
		void setClip(sp_rectangle rect);
		void drawLine(int x1, int y1, int w, int h, spider::SPColor *color);
		void drawImage(SPImage *image, int x1, int y1, int w, int h);
		void drawRectangle(int x1, int y1, int w, int h, spider::SPColor *color);
		void fillRectangle(int x1, int y1, int w, int h, spider::SPColor *color);
        void drawControl(string control, SPElement *elm, int x, int y, int w, int h);
		void invalidateRegion(rectangle region);
		void drawString(string text, spider::SPFontStyle *fontStyle, spider::SPColor *color,int x, int y, int w, int h);
		void drawInputElement(Element *elm, int x, int y, int w, int h);
		void setFontStyle(spider::FontStyle *fs);
		void setOrigo(const int& x, const int& y);
		void drawHTMLText(string html, SPFontStyle *fs, SPColor *color, int x, int y, int w, int h);
		sp_rectangle measureString(string text, spider::SPFontStyle *font);
		virtual void declipRect();
	};
};
#endif
