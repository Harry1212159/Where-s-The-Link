#include "account.cpp"

int menuChoice = 0;
void MainMenu() {
    char ch;
    while (ch != 77 && ch != 'd' && ch != ' ' && ch != 13) {
        // Display Main Menu
        ClearScreen();
        DrawLogo();

        int yStart = 11;
        GoTo(Padding("MAIN MENU"), yStart);
        cout << "MAIN MENU";
        
        yStart++;
        string options[4] = {"START", "LEADERBOARD", "HOW TO PLAY", "QUIT GAME"};
        for (int i=0; i<4; i++) {
            yStart += 2;
            GoTo(Padding(">> " + options[i] + " <<"), yStart);
            if (i == menuChoice) {
                cout << ">> " + options[i] + " <<";
            } else {
                cout << "   " + options[i] + "   ";
            }
        }

        // Move
        ch = getch();
        if (ch == 72 || ch == 'w') {
            if (menuChoice == 0) {
                menuChoice = 3;
            } else {
                menuChoice--;
            }
        } else if (ch == 80 || ch == 's') {
            if (menuChoice == 3) {
                menuChoice = 0;
            } else {
                menuChoice++;
            }
        }
    }

    // Next
    system("cls");
    switch (menuChoice) {
        case 0:
            if (loginPlayerIndex >= 0) {
                AfterLoginMenu();
            } else {
                AuthMenu();
            }
            break;
        case 1:
            DisplayLeaderBoard();
            break;
        case 2:
            DisplayHelp();
            break;
    }
}

void DisplayLeaderBoard() {
    ClearScreen();
    DrawLogo();

    int yStart = 11;
    GoTo(Padding("LEADER BOARD"), yStart);
    cout << "LEADER BOARD";

    // Just data for testing
    Player* players = GetPlayer();
    int n = 6;
    if (playerNum < 6) {
        n = playerNum;
    }

    yStart++;
    for (int i=0; i<n; i++) {
        if (players[i].record[0].points != 0) {
            yStart += 2;
            GoTo(40, yStart);
            cout << players[i].name;
            GoTo(65, yStart);
            cout << players[i].record[0].points;
            GoTo(80, yStart);
            cout << players[i].record[0].date.dd << "-" << players[i].record[0].date.mm << "-" << players[i].record[0].date.yy; 
        }
    }

    delete [] players;

    char ch;
    while (ch != 75 && ch != 'a'  && ch != 27) {
        ch = getch();
    }
    system("cls");
    MainMenu();
}

void DisplayHelp() {
    ClearScreen();
    DrawLogo();

    int yStart = 11;
    GoTo(Padding("HOW TO PLAY"), yStart);
    cout << "HOW TO PLAY";

    GoTo(45, yStart+3);
    cout << "Movement: WASD or ARROW KEYS";
    GoTo(45, yStart+5);
    cout << "Choosing: SPACE or ENTER";

    char ch;
    while (ch != 75 && ch != 'a'  && ch != 27) {
        ch = getch();
    }
    system("cls");
    MainMenu();
}