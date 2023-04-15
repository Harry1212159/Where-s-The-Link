void SetWindowSize(SHORT width, SHORT height) {
    // HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    // SMALL_RECT WindowSize;
    // WindowSize.Top = 0;
    // WindowSize.Left = 0;
    // WindowSize.Right = width;
    // WindowSize.Bottom = height;

    // SetConsoleWindowInfo(hStdout, 1, &WindowSize);

    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, 50, 50, width, height, TRUE);
}

void SetScreenBufferSize(SHORT width, SHORT height) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleScreenBufferSize(hStdout, NewSize);
}

void DisableResizeWindow() {
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) &~WS_SIZEBOX);
}

void DisableCtrButton(bool Close, bool Min, bool Max) {
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);
    if (Close) {
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    if (Min) {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max) {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}

void DisableScrollbar() {
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, false);
}

void ShowCur(bool CursorVisibility) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;
    
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;
    
    SetConsoleCursorInfo(handle, &ConCurInf);
}

void SetColor(int background_color, int text_color) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = background_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

void GoTo(SHORT posX, SHORT posY) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

    SetConsoleCursorPosition(hStdout, Position);
}

void ClearScreen() {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
