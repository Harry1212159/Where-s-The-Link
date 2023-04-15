#include "matching.cpp"

struct Level {
    int mapWidth;
    int mapHeight;
    int charNum;

    int** Map;
    string* Background;

    void (*MapHandle)(Level level, int xCur, int yCur, int &iStart, int &jStart, int &iEnd, int &jEnd, int &score, bool &swch);
};

int** GenerateMap(int mapWidth, int mapHeight, int charNum) {
    int **map = new int* [mapHeight];
    for (int i=0; i<mapHeight; i++) {
        *(map+i) = new int [mapWidth];
    }

    // Set all to 0
    for (int i=0; i<mapHeight; i++) {
        for (int j=0; j<mapWidth; j++) {
            *( *(map+i) + j) = 0;
        }
    }

    int occurrence = ( (mapWidth-2) * (mapHeight-2)) / charNum;
    if (occurrence % 2 == 1) {
        occurrence--;
    }
    int blank = ( (mapWidth-2) * (mapHeight-2)) - charNum * occurrence;

    // Fill map randomly
    int iRan, jRan;
    srand(time(0));
    for (int ch=1; ch<=charNum; ch++) {
        for (int oc=1; oc<=occurrence; oc++) {
            do {
                iRan = rand()%(mapHeight-2) + 1;
                jRan = rand()%(mapWidth-2) + 1;
            } while (*( *(map+iRan) + jRan) != 0);
            *( *(map+iRan) + jRan) = ch;
        }
    }
    for (int bl=1; bl<=blank/2; bl++) {
        int fill = rand()%charNum + 1;
        do {
            iRan = rand()%(mapHeight-2) + 1;
            jRan = rand()%(mapWidth-2) + 1;
        } while (*( *(map+iRan) + jRan) != 0);
        *( *(map+iRan) + jRan) = fill;
        do {
            iRan = rand()%(mapHeight-2) + 1;
            jRan = rand()%(mapWidth-2) + 1;
        } while (*( *(map+iRan) + jRan) != 0);
        *( *(map+iRan) + jRan) = fill;
    }

    return map;
}

string* GetBackground(int index) {
    string* background = new string [99];
    ifstream bgFile;
    bgFile.open("resources/background" + to_string(index) + ".txt");
    if (bgFile.is_open()) {
        int i = 0;
        while (!bgFile.eof()) {
            getline(bgFile, *(background+i), '\n');
            i++;
        }
        bgFile.close();
    } else {
        GoTo(Padding("!!! BACKGROUND NOT FOUND !!!"), 3);
        cout << "!!! BACKGROUND NOT FOUND !!!";
    }
    return background;
}

// Draw the map
void DrawCell(int** map, string* bg, int x, int y, int xCur, int yCur, int iStart, int jStart) {
    int cellWidth = 5, cellHeight = 3;
    if (map[y][x] != 0) {
        if (x == xCur && y == yCur) {
            SetColor(0, 15);
            GoTo(cellWidth*x, cellHeight*y);
            cout << char(201) << char(205) << char(205) << char(205) << char(187);
            GoTo(cellWidth*x, cellHeight*y+1);
            cout << char(186) << char(32) << char(64+map[y][x]) << char(32) << char(186);
            GoTo(cellWidth*x, cellHeight*y+2);
            cout << char(200) << char(205) << char(205) << char(205) << char(188);
        } else if (x == jStart && y == iStart) {
            SetColor(0, 7);
            GoTo(cellWidth*x, cellHeight*y);
            cout << char(201) << char(205) << char(205) << char(205) << char(187);
            GoTo(cellWidth*x, cellHeight*y+1);
            cout << char(186) << char(32) << char(64+map[y][x]) << char(32) << char(186);
            GoTo(cellWidth*x, cellHeight*y+2);
            cout << char(200) << char(205) << char(205) << char(205) << char(188);
        } else {
            if (map[y][x] == 7) { // White
                SetColor(0, 13);
            } else if (map[y][x] == 8) { // Gray
                SetColor(0, 14);
            } else {
                SetColor(0, map[y][x]);
            }
            GoTo(cellWidth*x, cellHeight*y);
            cout << char(218) << char(196) << char(196) << char(196) << char(191);
            GoTo(cellWidth*x, cellHeight*y+1);
            cout << char(179) << char(32) << char(64+map[y][x]) << char(32) << char(179);
            GoTo(cellWidth*x, cellHeight*y+2);
            cout << char(192) << char(196) << char(196) << char(196) << char(217);
        }
    } else {
        if (x == xCur && y == yCur) {
            SetColor(0, 15);
            GoTo(cellWidth*x, cellHeight*y);
            cout << char(201) << char(205) << char(205) << char(205) << char(187);
            GoTo(cellWidth*x, cellHeight*y+1);
            cout << char(186) << char(32) << char(32) << char(32) << char(186);
            GoTo(cellWidth*x, cellHeight*y+2);
            cout << char(200) << char(205) << char(205) << char(205) << char(188);
        } else {
            SetColor(0, 7);
            GoTo(cellWidth*x, cellHeight*y);
            cout << bg[cellHeight*y][cellWidth*x] << bg[cellHeight*y][cellWidth*x+1] << bg[cellHeight*y][cellWidth*x+2] << bg[cellHeight*y][cellWidth*x+3] << bg[cellHeight*y][cellWidth*x+4];
            GoTo(cellWidth*x, cellHeight*y+1);
            cout << bg[cellHeight*y][cellWidth*x] << bg[cellHeight*y+1][cellWidth*x+1] << bg[cellHeight*y+1][cellWidth*x+2] << bg[cellHeight*y+1][cellWidth*x+3] << bg[cellHeight*y+2][cellWidth*x+4];
            GoTo(cellWidth*x, cellHeight*y+2);
            cout << bg[cellHeight*y+2][cellWidth*x] << bg[cellHeight*y+2][cellWidth*x+1] << bg[cellHeight*y+2][cellWidth*x+2] << bg[cellHeight*y+2][cellWidth*x+3] << bg[cellHeight*y+2][cellWidth*x+4];
        } 
    }
}

void DrawLink(string path, int iStart, int jStart) {
    int cellWidth = 5, cellHeight = 3;
    int x = jStart*cellWidth + 2, y = iStart*cellHeight + 1;
    if (path[0] == 'a') {
        x--;
    } else if (path[0] == 'd') {
        x++;
    } else if (path[0] == 'w') {
        y--;
    } else if (path[0] == 's') {
        y++;
    }
    for (int p=0; p<path.size(); p++) {
        if (path[p] == 'a') {
            for (int l=0; l<cellWidth-1; l++) {
                GoTo(x, y);
                cout << char(196);
                x--;
            }
            GoTo(x, y);
            if (path[p+1] == 'a') {
                cout << char(196);
                x--;
            } else if (path[p+1] == 'w') {
                cout << char(192);
                y--;
            } else if (path[p+1] == 's') {
                cout << char(218);
                y++;
            }

        } else if (path[p] == 'd') {
            for (int l=0; l<cellWidth-1; l++) {
                GoTo(x, y);
                cout << char(196);
                x++;
            }
            GoTo(x, y);
            if (path[p+1] == 'd') {
                cout << char(196);
                x++;
            } else if (path[p+1] == 'w') {
                cout << char(217);
                y--;
            } else if (path[p+1] == 's') {
                cout << char(191);
                y++;
            }

        } else if (path[p] == 'w') {
            for (int l=0; l<cellHeight-1; l++) {
                GoTo(x, y);
                cout << char(179);
                y--;
            }
            GoTo(x, y);
            if (path[p+1] == 'w') {
                cout << char(179);
                y--;
            } else if (path[p+1] == 'a') {
                cout << char(191);
                x--;
            } else if (path[p+1] == 'd') {
                cout << char(218);
                x++;
            }
        } else if (path[p] == 's') {
            for (int l=0; l<cellHeight-1; l++) {
                GoTo(x, y);
                cout << char(179);
                y++;
            }
            GoTo(x, y);
            if (path[p+1] == 's') {
                cout << char(179);
                y++;
            } else if (path[p+1] == 'a') {
                cout << char(217);
                x--;
            } else if (path[p+1] == 'd') {
                cout << char(192);
                x++;
            }
        }
    }
}

// Level's Feature

void Normal(Level level, int xCur, int yCur, int &iStart, int &jStart, int &iEnd, int &jEnd, int &score, bool &swch) {
    string path = findPath(level.Map, level.mapWidth, level.mapHeight, iStart, jStart, iEnd, jEnd);

    if (path != "") {
        level.Map[iStart][jStart] = level.Map[iEnd][jEnd] = 0;
        DrawLink(path, iStart, jStart);
        Sleep(600);
        score += 100;
    }
    if (swch) {
        iStart = jStart = iEnd = jEnd = 0;
    }

    for (int y=0; y<level.mapHeight; y++) {
        for (int x=0; x<level.mapWidth; x++) {
            DrawCell(level.Map, level.Background, x, y, xCur, yCur, iStart, jStart);
        }
    }
}

void Falldown(Level level, int xCur, int yCur, int &iStart, int &jStart, int &iEnd, int &jEnd, int &score, bool &swch) {
    string path = findPath(level.Map, level.mapWidth, level.mapHeight, iStart, jStart, iEnd, jEnd);
    if (path != "") {
        level.Map[iStart][jStart] = level.Map[iEnd][jEnd] = 0;
        DrawLink(path, iStart, jStart);
        score += 100;
        Sleep(600);

        if (jStart == jEnd) {
            if (iStart > iEnd ) {
                swap(iStart, iEnd);
            }
        }
        for (int i=iStart; i>1; i--) {
            swap(level.Map[i][jStart], level.Map[i-1][jStart]);
        }
        for (int i=iEnd; i>1; i--) {
            swap(level.Map[i][jEnd], level.Map[i-1][jEnd]);
        }
    }
    if (swch) {
        iStart = jStart = iEnd = jEnd = 0;
    }

    for (int y=0; y<level.mapHeight; y++) {
        for (int x=0; x<level.mapWidth; x++) {
            DrawCell(level.Map, level.Background, x, y, xCur, yCur, iStart, jStart);
        }
    }
}

void Messup(Level level, int xCur, int yCur, int &iStart, int &jStart, int &iEnd, int &jEnd, int &score, bool &swch) {
    string path = findPath(level.Map, level.mapWidth, level.mapHeight, iStart, jStart, iEnd, jEnd);
    if (path != "") {
        level.Map[iStart][jStart] = level.Map[iEnd][jEnd] = 0;
        DrawLink(path, iStart, jStart);
        score += 100;
        Sleep(600);
        
        Shuffle(level.Map, level.mapWidth, level.mapHeight);
    }
    if (swch) {
        iStart = jStart = iEnd = jEnd = 0;
    }

    for (int y=0; y<level.mapHeight; y++) {
        for (int x=0; x<level.mapWidth; x++) {
            DrawCell(level.Map, level.Background, x, y, xCur, yCur, iStart, jStart);
        }
    }
}

void Dark(Level level, int xCur, int yCur, int &iStart, int &jStart, int &iEnd, int &jEnd, int &score, bool &swch) {
    string path = findPath(level.Map, level.mapWidth, level.mapHeight, iStart, jStart, iEnd, jEnd);
    if (path != "") {
        level.Map[iStart][jStart] = level.Map[iEnd][jEnd] = 0;
        DrawLink(path, iStart, jStart);
        score += 100;
        Sleep(600);
    }
    if (swch) {
        iStart = jStart = iEnd = jEnd = 0;
    }

    int cellWidth = 5, cellHeight = 3;
    for (int y=0; y<level.mapHeight; y++) {
        for (int x=0; x<level.mapWidth; x++) {
            if ((xCur-1<=x && x<=xCur+1) && (yCur-1<=y && y<=yCur+1)) {
                DrawCell(level.Map, level.Background, x, y, xCur, yCur, iStart, jStart);
            } else {
                SetColor(0, 7);
                GoTo(cellWidth*x, cellHeight*y);
                cout << "     ";
                GoTo(cellWidth*x, cellHeight*y+1);
                cout << "     ";
                GoTo(cellWidth*x, cellHeight*y+2);
                cout << "     ";
            } 
        }
    }
}

Level GenerateLevel(int index) {
    Level level;

    switch (index) {
        case 0:
            // Level 1
            level.mapWidth = 12;
            level.mapHeight = 10;
            level.charNum = 6;
            level.Map = GenerateMap(level.mapWidth, level.mapHeight, level.charNum);
            level.Background = GetBackground(0);
            level.MapHandle = &Normal;
            break;
        case 1:
            // Level 2
            level.mapWidth = 14;
            level.mapHeight = 10;
            level.charNum = 8;
            level.Map = GenerateMap(level.mapWidth, level.mapHeight, level.charNum);
            level.Background = GetBackground(1);
            level.MapHandle = &Falldown;
            break;

        case 2:
            // Level 3
            level.mapWidth = 16;
            level.mapHeight = 10;
            level.charNum = 10;
            level.Map = GenerateMap(level.mapWidth, level.mapHeight, level.charNum);
            level.Background = GetBackground(2);
            level.MapHandle = &Messup;
            break;

        case 3:
            // Level 4
            level.mapWidth = 18;
            level.mapHeight = 10;
            level.charNum = 12;
            level.Map = GenerateMap(level.mapWidth, level.mapHeight, level.charNum);
            level.Background = GetBackground(3);
            level.MapHandle = &Dark;
            break;
    }
    return level;
}
