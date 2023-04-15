
int authChoice = 0;
void AuthMenu() {
    char ch;
    while ((ch != 75 && ch != 'a'  && ch != 27) && (ch != 77 && ch != 'd' && ch != ' ' && ch != 13)) {
        // Display Auth Menu
        ClearScreen();
        DrawLogo();

        int yStart = 11;
        GoTo(Padding("SIGN IN TO SAVE YOUR PROGRESS"), yStart);
        cout << "SIGN IN TO SAVE YOUR PROGRESS";

        yStart++;
        string options[3] = {"SIGN IN", "SIGN UP", "GUEST"};
        for (int i=0; i<3; i++) {
            yStart += 2;
            GoTo(Padding(">> " + options[i] + " <<"), yStart);
            if (i == authChoice) {
                cout << ">> " + options[i] + " <<";
            } else {
                cout << "   " + options[i] + "   ";
            }
        }

        // Move
        ch = getch();
        if (ch == 72 || ch == 'w') {
            if (authChoice == 0) {
                authChoice = 2;
            } else {
                authChoice--;
            }
        } else if (ch == 80 || ch == 's') {
            if (authChoice == 2) {
                authChoice = 0;
            } else {
                authChoice++;
            }
        }
    }

    // Next
    system("cls");
    if (ch == 75 || ch == 'a' || ch == 27) {
        MainMenu();
    } else {
        system("cls");
        switch (authChoice) {
            case 0:
                LoginForm();
                break;
            case 1:
                SignupForm();
                break;
            case 2:
                loginPlayerIndex = -1;
                
                Player guest;
                strcpy(guest.name,"Guest");
                guest.level = 0;
                loginPlayer = guest;
                
                break;
        }
        LevelMenu();
    }
}

void LoginForm() {
    int choice = 0;
    string loginForm[2];

    char ch;
    while (ch != 75 && ch != 'a'  && ch != 27) {
        // Display Auth Menu
        ClearScreen();
        DrawLogo();

        int xStart = 40, yStart = 11;
        GoTo(Padding("SIGN IN"), yStart);
        cout << "SIGN IN";

        yStart++;
        string options[3] = {"ENTER NAME", "ENTER PASSWORD", "LOG IN"};
        for (int i=0; i<3; i++) {
            yStart += 2;
            GoTo(xStart, yStart);
            if (i == choice) {
                cout << ">> " + options[i];
            } else {
                cout << "   " + options[i];
            }
            if (i < 2) {
                GoTo(xStart + 20, yStart);
                cout << "                       ";
                GoTo(xStart + 20, yStart);
                cout << "   " << loginForm[i];
            }
        }

        // Move
        ch = getch();
        if (ch == 72 || ch == 'w') {
            if (choice == 0) {
                choice = 2;
            } else {
                choice--;
            }
        } else if (ch == 80 || ch == 's') {
            if (choice == 2) {
                choice = 0;
            } else {
                choice++;
            }
        } else if (ch == 77 || ch == 'd' || ch == ' ' || ch == 13) {
            if (choice == 2) {
                Login(loginForm[0], loginForm[1]);
                if (loginPlayerIndex >= 0) {
                    system("cls");
                    return;
                } else {
                    getch();
                    system("cls");
                }
            } else {
                for (int i=0; i<2; i++) {
                    if (i == choice) {
                        GoTo(xStart + 20, 15 + 2*i);
                        cout << ">> ";
                        getline(cin,loginForm[i]);
                        GoTo(xStart + 20, 15 + 2*i);
                        for (int sp=0;sp<3+loginForm[i].size(); sp++) {
                            cout << " ";
                        }
                        if (loginForm[i].size() > 50) {
                            loginForm[i].resize(50);
                        }
                    }
                }
            }
        }
    }

    // Next
    system("cls");
    AuthMenu();
}

void SignupForm() {
    int choice = 0;
    string signupForm[4];
    char ch;
    while (ch != 75 && ch != 'a'  && ch != 27) {
        // Display Auth Menu
        ClearScreen();
        DrawLogo();

        int xStart = 40, yStart = 11;
        GoTo(Padding("SIGN UP"), yStart);
        cout << "SIGN UP";

        yStart++;
        string options[4] = {"ENTER NAME", "ENTER EMAIL", "ENTER PASSWORD", "SIGN UP"};
        for (int i=0; i<4; i++) {
            yStart += 2;
            GoTo(xStart, yStart);
            if (i == choice) {
                cout << ">> " + options[i];
            } else {
                cout << "   " + options[i];
            }
            if (i < 3) {
                GoTo(xStart + 20, yStart);
                cout << "                       ";
                GoTo(xStart + 20, yStart);
                cout << "   " << signupForm[i];
            }
        }

        // Move
        ch = getch();
        if (ch == 72 || ch == 'w') {
            if (choice == 0) {
                choice = 3;
            } else {
                choice--;
            }
        } else if (ch == 80 || ch == 's') {
            if (choice == 3) {
                choice = 0;
            } else {
                choice++;
            }
        } else if (ch == 77 || ch == 'd' || ch == ' ' || ch == 13) {
            if (choice == 3) {
                Signup(signupForm[0], signupForm[1], signupForm[2]);
                if (loginPlayerIndex >= 0) {
                    system("cls");
                    return;
                } else {
                    getch();
                    system("cls");
                }
            } else {
                for (int i=0; i<3; i++) {
                    if (i == choice) {
                        GoTo(xStart + 20, 15 + 2*i);
                        cout << ">> ";
                        getline(cin,signupForm[i]);
                        GoTo(xStart + 20, 15 + 2*i);
                        for (int sp=0;sp<3+signupForm[i].size(); sp++) {
                            cout << " ";
                        }
                        if (signupForm[i].size() > 50) {
                            signupForm[i].resize(50);
                        }
                    }
                }
            }
        }
    }
    // Next
    system("cls");
    AuthMenu(); 
}

void AfterLoginMenu() {
    int choice = 0;
    char ch;
    while ((ch != 75 && ch != 'a'  && ch != 27) && (ch != 77 && ch != 'd' && ch != ' ' && ch != 13) && (ch != 104)) {
        // Display Auth Menu
        ClearScreen();
        DrawLogo();

        int xStart = 40, yStart = 11;
        string space = "";
        space.resize(strlen(loginPlayer.name), ' ');
        GoTo(Padding("WELCOME" + space), yStart);
        cout << "WELCOME ";
        cout << loginPlayer.name;

        yStart++;
        string options[2] = {"PLAY", "LOG OUT"};
        for (int i=0; i<2; i++) {
            yStart += 2;
            GoTo(xStart, yStart);
            if (i == choice) {
                cout << ">> " + options[i];
            } else {
                cout << "   " + options[i];
            }
        }
        if (isHackable(loginPlayer)) {
            yStart += 3;
            GoTo(Padding("PRESS (H) TO HACK !!!"), yStart);
            cout << "PRESS (H) TO HACK !!!";
        }

        // Move
        ch = getch();
        if (ch == 72 || ch == 'w') {
            if (choice == 0) {
                choice = 1;
            } else {
                choice--;
            }
        } else if (ch == 80 || ch == 's') {
            if (choice == 1) {
                choice = 0;
            } else {
                choice++;
            }
        }
    }
    // Next
    system("cls");

    if (ch == 104) {
        HackMenu();
    } else if (ch == 75 || ch == 'a' || ch == 27) {
        MainMenu();
    } else {
        switch (choice) {
            case 0:
                LevelMenu();
                break;
            case 1:
                loginPlayerIndex = -1;
                Player empty;
                loginPlayer = empty;
                MainMenu();
                break;
        }
    }
}

void HackMenu() {
    int choice = 0;
    int score[4];
    for (int i=0; i<4; i++) {
        score[i] = loginPlayer.state[i].bestScore;
    }

    char ch;
    while (ch != 75 && ch != 'a'  && ch != 27) {
        // Display Menu
        ClearScreen();
        DrawLogo();

        int xStart = 40, yStart = 11;
        GoTo(Padding("HACKING"), yStart);
        cout << "HACKING";

        yStart++;
        string options[4] = {"LEVEL 1 BEST SCORE", "LEVEL 2 BEST SCORE", "LEVEL 3 BEST SCORE", "LEVEL 4 BEST SCORE"};
        for (int i=0; i<4; i++) {
            yStart += 2;
            GoTo(xStart, yStart);
            if (i == choice) {
                cout << ">> " + options[i];
            } else {
                cout << "   " + options[i];
            }
            GoTo(xStart + 25, yStart);
            cout << "         ";
            GoTo(xStart + 25, yStart);
            cout << "   " << score[i];
        }

        // Move
        ch = getch();
        if (ch == 72 || ch == 'w') {
            if (choice == 0) {
                choice = 3;
            } else {
                choice--;
            }
        } else if (ch == 80 || ch == 's') {
            if (choice == 3) {
                choice = 0;
            } else {
                choice++;
            }
        } else if (ch == 77 || ch == 'd' || ch == ' ' || ch == 13) {
            for (int i=0; i<4; i++) {
                if (i == choice) {
                    GoTo(xStart + 25, 15 + 2*i);
                    cout << ">> ";
                    cin >> score[i];

                    Hack(score[i], i);

                    system("cls");
                }
            }
        }
    }
    // Next
    system("cls");
    AfterLoginMenu();
}