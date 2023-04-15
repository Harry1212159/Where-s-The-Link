// 2D map
// #include "level.cpp"
// Link list map
#include "linklist/level-linklist.cpp"

int levelChoice;
void LevelMenu() {
    levelChoice = 0;
    char ch;
    while ((ch != 75 && ch != 'a'  && ch != 27) && (ch != 77 && ch != 'd' && ch != ' ' && ch != 13)) {
        // Display Main Menu
        ClearScreen();
        DrawLogo();

        int yStart = 11;
        GoTo(Padding("LEVEL"), yStart);
        cout << "LEVEL";
        
        yStart++;
        for (int i=0; i<4; i++) {
            yStart += 2;
            GoTo(Padding(" >> LEVEL " + to_string(i+1) + " << "), yStart);
            if (i == levelChoice) {
                cout << " >> LEVEL " << to_string(i+1) << " << ";
            } else {
                if (i <= loginPlayer.level) {
                    cout << "    LEVEL " << to_string(i+1) << "    ";
                } else {
                    cout << "LEVEL " << to_string(i+1) << "  LOCKED";
                }
            }
        }

        // Move
        ch = getch();
        if (ch == 72 || ch == 'w') {
            if (levelChoice == 0) {
                if (loginPlayer.level > 3) {
                    levelChoice = 3;
                } else {
                    levelChoice = loginPlayer.level;
                }
            } else {
                levelChoice--;
            }
        } else if (ch == 80 || ch == 's') {
            if (levelChoice == loginPlayer.level || levelChoice > 3) {
                levelChoice = 0;
            } else {
                levelChoice++;
            }
        }
    }

    // Next
    system("cls");
    if (ch == 75 || ch == 'a' || ch == 27) {
        MainMenu();
        return;
    } else {
        Play();
        return;
    }
}

void DrawInfoBox(int levelScore) {
    int t = time(0);

    GoTo(91, 4);
    cout << "Level: " << levelChoice+1;

    GoTo(91, 6);
    cout << "Player: " << loginPlayer.name;

    GoTo(91, 8);
    cout << "            ";
    GoTo(91, 8);
    cout << "Score: " << levelScore;

    GoTo(91, 14);
    cout << "Press (H) for suggestion";
    GoTo(91, 16);
    cout << "Press (Esc) for saving";
}

void Play() {
    // Set up
    int score = 0, levelScore = 0;
    int startTime = time(0);

    int xCur = 1, yCur = 1;
    int iStart = 0, iEnd = 0, jStart = 0, jEnd = 0;
    bool swch = true, saveGame = false;

    Level level;
    level = GenerateLevel(levelChoice);

    if (loginPlayer.state[levelChoice].p != 0) {
        level.mapWidth = loginPlayer.state[levelChoice].p;
        level.mapHeight = loginPlayer.state[levelChoice].q;
        xCur = loginPlayer.state[levelChoice].p_;
        yCur = loginPlayer.state[levelChoice].q_;        
        int index = 0;
        for (int i=0; i<loginPlayer.state[levelChoice].p; i++) {
            for (int j=0; j<loginPlayer.state[levelChoice].q; j++) {
                // level.Map[i][j] = loginPlayer.state[levelChoice].board[index]; // 2D
                ChangeMap(level.Map, j, i, loginPlayer.state[levelChoice].board[index]); // Linklist
                index++;
            }
        }
    }
    
    // Game loop
    while (true) {
        ClearScreen();

        levelScore = score - (time(0) - startTime) * 10;
        
        SetColor(0, 7);
        DrawInfoBox(levelScore);


        (level.MapHandle)(level, xCur, yCur, iStart, jStart, iEnd, jEnd, score, swch);

        if (isOver(level.Map, level.mapWidth, level.mapHeight)) {
            break;
        }

        while (isImpossible(level.Map, level.mapWidth, level.mapHeight)) {
            Shuffle(level.Map, level.mapWidth, level.mapHeight);
        }

        Move(level.Map, level.mapWidth, level.mapHeight, xCur, yCur, iStart, jStart, iEnd, jEnd, swch, levelChoice, saveGame);
        if (saveGame) {
            if (loginPlayerIndex >= 0) {
                UpdateInfo(loginPlayer, levelChoice);
            }
            system("cls");
            LevelMenu();
            return;
        }

    }

    // Delete map

    // 2D
    // for (int i=0; i<level.mapHeight; i++) {
    //     delete [] *(level.Map+i);
    // }
    // delete [] level.Map;

    // Linklist
    DeleteMap(level.Map);

    // Update player record
    if (levelChoice == loginPlayer.level) {
        loginPlayer.level++;
    }
    if (levelScore > loginPlayer.state[levelChoice].bestScore) {
        loginPlayer.state[levelChoice].bestScore = levelScore;
    }

    if (loginPlayerIndex >= 0) {
        UpdateInfo(loginPlayer, levelChoice);
    }

    loginPlayer.state[levelChoice].p = 0;

    // After game menu
    system("cls");
    GoTo(Padding("You win !!!"), 12);
    cout << "You win !!!" << endl;
    GoTo(Padding("Your score in this level: " + to_string(levelScore)), 14);
    cout << "Your score in this level: " << levelScore;
    GoTo(Padding("Your best score in this level: " + to_string(loginPlayer.state[levelChoice].bestScore)), 16);
    cout << "Your best score in this level: " << loginPlayer.state[levelChoice].bestScore;
    GoTo(Padding("Your total score: " + to_string(loginPlayer.record[0].points)), 18);
    cout << "Your total score: " << loginPlayer.record[0].points;

    GoTo(Padding("Back to Level Menu (W) - Play again (Space) - Next level (D)"), 20);
    cout << "Back to Level Menu (A) - Play again (Space) - Next level (D)";
    char ch;
    while ((ch != 75 && ch != 'a') && (ch != 32 && ch != 13) && (ch != 77 && ch != 'd')) {
        ch = getch();
    }
    system("cls");
    if (ch == 75 || ch == 'a' || ch == 27) {
        LevelMenu();
    } else if (ch == 77 || ch == 'd') {
        levelChoice++;
        if (levelChoice < 4) {
            Play();
        } else {
            LevelMenu();
        }
    } else {
        Play();
    }
}
