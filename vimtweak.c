/*
 cl /LD vimtweak.c user32.lib
 gcc -shared -o vimtweak.dll vimtweak.c
 ------------------------------
 :call libcallnr("vimtweak.dll", "SetAlpha", 200)
 :call libcallnr("vimtweak.dll", "EnableMaximize", 1)
 :call libcallnr("vimtweak.dll", "EnableTopMost", 1)
*/
#include <windows.h>

#ifndef LWA_ALPHA
#define LWA_ALPHA 2
#endif

#ifndef WS_EX_LAYERED
#define WS_EX_LAYERED 0x00080000
#endif

#ifdef _MSC_VER
#define EXPORT _declspec(dllexport)
#else
#define EXPORT
#endif

static HWND hTopWindow = NULL;

BOOL CALLBACK
FindWindowProc(HWND hwnd, LPARAM lParam) {
  HWND* pphWnd = (HWND*)lParam;

  if (GetParent(hwnd)) {
    *pphWnd = NULL;
    return TRUE;
  }
  *pphWnd = hwnd;
  return FALSE;
}

static HWND
GetVimWindow() {
  if (hTopWindow) {
    return hTopWindow;
  }

  HMODULE hDllKernel32 = LoadLibrary("kernel32");
  if (hDllKernel32) {
    HWND (WINAPI *pfnGetConsoleWindow)();
    pfnGetConsoleWindow
      = (HWND (WINAPI *)())
          GetProcAddress(hDllKernel32, "GetConsoleWindow");
    if (pfnGetConsoleWindow && (hTopWindow = (HWND) pfnGetConsoleWindow())) {
      ShowWindow(hTopWindow, SW_SHOW);
      return hTopWindow;
    }
  }
  DWORD dwThreadID = GetCurrentThreadId();
  EnumThreadWindows(dwThreadID, FindWindowProc, (LPARAM)&hTopWindow);
  return hTopWindow;
}

EXPORT LONG
SetAlpha(LONG nTrans) {
  HMODULE hDllUser32 = LoadLibrary("user32");
  if (hDllUser32) {
    BOOL (WINAPI *pfnSetLayeredWindowAttributes)(HWND,DWORD,BYTE,DWORD);

    pfnSetLayeredWindowAttributes
      = (BOOL (WINAPI *)(HWND,DWORD,BYTE,DWORD))
          GetProcAddress(hDllUser32, "SetLayeredWindowAttributes");

    if (pfnSetLayeredWindowAttributes) {
      HWND hTop = GetVimWindow();
      if (hTop) {
        if (nTrans == 255) {
          SetWindowLong(hTop, GWL_EXSTYLE,
          GetWindowLong(hTop, GWL_EXSTYLE) & ~WS_EX_LAYERED); 
        } else {
          SetWindowLong(hTop, GWL_EXSTYLE,
          GetWindowLong(hTop, GWL_EXSTYLE) | WS_EX_LAYERED); 
          pfnSetLayeredWindowAttributes(hTop, 0, (BYTE)nTrans, LWA_ALPHA);
        }
      }
    }
    FreeLibrary(hDllUser32);
  }
  return GetLastError();
}

EXPORT LONG
EnableCaption(LONG bCaption) {
  HWND hTop;
  if (hTop = GetVimWindow()) {
    if (bCaption == 0)
      SetWindowLong(hTop, GWL_STYLE,
        GetWindowLong(hTop, GWL_STYLE) & ~WS_CAPTION); 
    else
      SetWindowLong(hTop, GWL_STYLE,
        GetWindowLong(hTop, GWL_STYLE) | WS_CAPTION); 
  }
  return GetLastError();
}

EXPORT LONG
EnableMaximize(LONG bEnable) {
  HWND hTop;
  if (hTop = GetVimWindow()) {
    if (bEnable == 0)
      SendMessage(hTop, WM_SYSCOMMAND, SC_RESTORE, 0);
    else
      SendMessage(hTop, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
  }
  return GetLastError();
}

EXPORT LONG
EnableTopMost(LONG bEnable) {
  HWND hTop;
  if (hTop = GetVimWindow()) {
    if (bEnable == 0)
      SetWindowPos(hTop, HWND_NOTOPMOST, 0, 0, 0, 0,
        SWP_NOSIZE | SWP_NOMOVE);
    else
      SetWindowPos(hTop, HWND_TOPMOST, 0, 0, 0, 0,
        SWP_NOSIZE | SWP_NOMOVE);
  }
  return GetLastError();
}
// vi:set ts=8 sts=2 sw=2 tw=0 et:
