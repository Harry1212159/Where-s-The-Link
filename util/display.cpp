#include "console.cpp"

void SetUpWindow() {
    SetConsoleTitle(TEXT("Where's The Link"));
    SetWindowSize(150, 30);
    DisableResizeWindow();
    DisableCtrButton(0, 0, 1);
    DisableScrollbar();
    ShowCur(0);
}

int Padding(string str) {
    return ( 122 / 2 - str.size() / 2);
}

void DrawLogo() {
    string temp;
    ifstream logoFile;
    logoFile.open("resources/logo.txt");
    if (logoFile.is_open()) {
        int line = 3;
        while (!logoFile.eof()) {
            getline(logoFile, temp, '\n');
            GoTo(Padding(temp), line);
            cout << temp << endl;
            line++;
        }
        logoFile.close();
    } else {
        GoTo(Padding("!!! LOGO NOT FOUND !!!"), 3);
        cout << "!!! LOGO NOT FOUND !!!";
    }
}