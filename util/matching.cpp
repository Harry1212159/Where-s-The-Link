
string Ipath(int** map, int iStart, int jStart, int iEnd, int jEnd) {
    string Iline = "";

    if (iStart == iEnd) {
        if (jStart < jEnd) {
            Iline += "d";
            for (int j=jStart+1; j<jEnd; j++) {
                Iline += "d";
                if (map[iStart][j] != 0) {
                    return "";
                }
            }
        } else {
            Iline += "a";
            for (int j=jStart-1; j>jEnd; j--) {
                Iline += "a";
                if (map[iStart][j] != 0) {
                    return "";
                }
            }
        }
        return Iline;
    } else if (jStart == jEnd) {
        if (iStart < iEnd) {
            Iline += "s";
            for (int i=iStart+1; i<iEnd; i++) {
                Iline += "s";
                if (map[i][jStart] != 0) {
                    return "";
                }
            }
        } else {
            Iline += "w";
            for (int i=iStart-1; i>iEnd; i--) {
                Iline += "w";
                if (map[i][jStart] != 0) {
                    return "";
                }
            }
        }
        return Iline;
    } else {
        return "";
    }
}

string Lpath(int** map, int iStart, int jStart, int iEnd, int jEnd) {
    string IlineHor, IlineVer;

    IlineHor = Ipath(map, iStart, jStart, iStart, jEnd);
    IlineVer = Ipath(map, iStart, jEnd, iEnd, jEnd);
    if (IlineHor != "" && IlineVer != "" && map[iStart][jEnd] == 0) {
        return IlineHor + IlineVer;
    }

    IlineVer = Ipath(map, iStart, jStart, iEnd, jStart);
    IlineHor = Ipath(map, iEnd, jStart, iEnd, jEnd);
    if (IlineVer != "" && IlineHor != "" && map[iEnd][jStart] == 0) {
        return IlineVer + IlineHor;
    }

    return "";
}

string Zpath(int** map, int iStart, int jStart, int iEnd, int jEnd) {
    string Iline, Lline;

    Iline = "";
    if (jStart > jEnd) {
        for (int j=jStart-1; j>jEnd; j--) {
            Iline += "a";
            if (map[iStart][j] != 0) {
                break;
            }
            Lline = Lpath(map, iStart, j, iEnd, jEnd);
            if (Lline != "") {
                return Iline + Lline;
            }
        }
    } else {
        for (int j=jStart+1; j<jEnd; j++) {
            Iline += "d";
            if (map[iStart][j] != 0) {
                break;
            }
            Lline = Lpath(map, iStart, j, iEnd, jEnd);
            if (Lline != "") {
                return Iline + Lline;
            }
        }
    }

    Iline = "";
    if (iStart > iEnd) {
        for (int i=iStart-1; i>iEnd; i--) {
            Iline += "w";
            if (map[i][jStart] != 0) {
                break;
            }
            Lline = Lpath(map, i, jStart, iEnd, jEnd);
            if (Lline != "") {
                return Iline + Lline;
            }
        }
    } else {
        for (int i=iStart+1; i<iEnd; i++) {
            Iline += "s";
            if (map[i][jStart] != 0) {
                break;
            }
            Lline = Lpath(map, i, jStart, iEnd, jEnd);
            if (Lline != "") {
                return Iline + Lline;
            }
        }
    }
    return "";
}

string Upath(int** map, int mapWidth, int mapHeight, int iStart, int jStart, int iEnd, int jEnd) {
    string Iline, Lline;

    Iline = "";
    for (int j=jStart-1; j>=0; j--) {
        Iline += "a";
        if (map[iStart][j] != 0) {
            break;
        }
        Lline = Lpath(map, iStart, j, iEnd, jEnd);
        if (Lline != "") {
            return Iline + Lline;
        }
    }

    Iline = "";
    for (int j=jStart+1; j<mapWidth; j++) {
        Iline += "d";
        if (map[iStart][j] != 0) {
            break;
        }
        Lline = Lpath(map, iStart, j, iEnd, jEnd);
        if (Lline != "") {
            return Iline + Lline;
        }
    }

    Iline = "";
    for (int i=iStart-1; i>=0; i--) {
        Iline += "w";
        if (map[i][jStart] != 0) {
            break;
        }
        Lline = Lpath(map, i, jStart, iEnd, jEnd);
        if (Lline != "") {
            return Iline + Lline;
        }
    }

    Iline = "";
    for (int i=iStart+1; i<mapHeight; i++) {
        Iline += "s";
        if (map[i][jStart] != 0) {
            break;
        }
        Lline = Lpath(map, i, jStart, iEnd, jEnd);
        if (Lline != "") {
            return Iline + Lline;
        }
    }
    return "";
}

string findPath(int** map, int mapWidth, int mapHeight, int iStart, int jStart, int iEnd, int jEnd) {
    if ( map[iStart][jStart] == map[iEnd][jEnd] && (iStart != iEnd || jStart != jEnd) ) {
        if (Ipath(map, iStart, jStart, iEnd, jEnd) != "") {
            return Ipath(map, iStart, jStart, iEnd, jEnd);
        }
        if (Lpath(map, iStart, jStart, iEnd, jEnd) != "") {
            return Lpath(map, iStart, jStart, iEnd, jEnd);
        }
        if (Zpath(map, iStart, jStart, iEnd, jEnd) != "") {
            return Zpath(map, iStart, jStart, iEnd, jEnd);
        }
        if (Upath(map, mapWidth, mapHeight, iStart, jStart, iEnd, jEnd) != "") {
            return Upath(map, mapWidth, mapHeight, iStart, jStart, iEnd, jEnd);
        }
    }
    return "";
}

void Suggest(int** map, int mapWidth, int mapHeight) {
    int cellWidth = 5, cellHeight = 3;
    for (int i=1; i<mapHeight-1; i++) {
        for (int j=1; j<mapWidth-1; j++) {
            if (map[i][j] != 0) {
                for (int k=1; k<mapHeight-1; k++) {
                    for (int l=1; l<mapWidth-1; l++) {
                        if (map[k][l] != 0 && findPath(map, mapWidth, mapHeight, i, j, k, l) != "") {
                            SetColor(0, 15);
                            GoTo(cellWidth*j, cellHeight*i);
                            cout << char(201) << char(205) << char(205) << char(205) << char(187);
                            GoTo(cellWidth*j, cellHeight*i+1);
                            cout << char(186) << char(32) << char(64+map[i][j]) << char(32) << char(186);
                            GoTo(cellWidth*j, cellHeight*i+2);
                            cout << char(200) << char(205) << char(205) << char(205) << char(188);
                            GoTo(cellWidth*l, cellHeight*k);
                            cout << char(201) << char(205) << char(205) << char(205) << char(187);
                            GoTo(cellWidth*l, cellHeight*k+1);
                            cout << char(186) << char(32) << char(64+map[k][l]) << char(32) << char(186);
                            GoTo(cellWidth*l, cellHeight*k+2);
                            cout << char(200) << char(205) << char(205) << char(205) << char(188);
                            return;
                        }
                    }
                }
            }
        }
    }
}

bool isImpossible(int** map, int mapWidth, int mapHeight) {
    for (int i=1; i<mapHeight-1; i++) {
        for (int j=1; j<mapWidth-1; j++) {
            if (map[i][j] != 0) {
                for (int k=1; k<mapHeight-1; k++) {
                    for (int l=1; l<mapWidth-1; l++) {
                        if (map[k][l] != 0) {
                            if (findPath(map, mapWidth, mapHeight, i, j, k, l)  != "") {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

void Shuffle(int** map, int mapWidth, int mapHeight) {
    int temp[128];
    int index = 0;
    for (int i=1; i<mapHeight-1; i++) {
        for (int j=1; j<mapWidth-1; j++) {
            if (map[i][j] != 0) {
                temp[index] = map[i][j];
                index++;
                map[i][j] = 0;
            }
        }
    }
    int iRan, jRan;
    for (int i=0; i<index; i++) {
        do {
            iRan = rand()%(mapHeight-2) + 1;
            jRan = rand()%(mapWidth-2) + 1;
        } while (map[iRan][jRan] != 0);
        map[iRan][jRan] = temp[i];
    }
}

bool isOver(int **map, int mapWidth, int mapHeight) {
    for (int i=0; i<mapHeight; i++) {
        for (int j=0; j<mapWidth; j++) {
            if (*( *(map+i) +j) != 0) {
                return false;
            }
        }
    }
    return true;
}

void Move(int **map, int mapWidth, int mapHeight, int &xCur, int &yCur, int &iStart, int &jStart, int &iEnd, int &jEnd, bool &swch, int levelChoice, bool &saveGame) {
    char ch = getch();
    if (ch == 72 || ch == 'w') {
        if (yCur == 1) {
            yCur = mapHeight - 2;
        } else {
            yCur--;
        }
    } else if (ch == 80 || ch == 's') {
        if (yCur == mapHeight - 2) {
            yCur = 1;
        } else {
            yCur++;
        }
    } else if (ch == 77 || ch == 'd') {
        if (xCur == mapWidth - 2) {
            xCur = 1;
        } else {
            xCur++;
        }
    } else if (ch == 75 || ch == 'a') {
        if (xCur == 1) {
            xCur = mapWidth - 2;
        } else {
            xCur--;
        }
    } else if (ch == 104) {
        Suggest(map, mapWidth, mapHeight);
        Move(map, mapWidth, mapHeight, xCur, yCur, iStart, jStart, iEnd, jEnd, swch, levelChoice, saveGame);
    } else if (ch == ' ' || ch == 13) {
        if (swch) {
            if (map[yCur][xCur] != 0) {
            	jStart = xCur;
            	iStart = yCur;     
    	        swch = !swch;       
            }
        } else {
            if (map[yCur][xCur] != 0) {
            	jEnd = xCur;
            	iEnd = yCur;
    	        swch = !swch;
            }
        }
    } else if (ch == 27) {
        loginPlayer.state[levelChoice].p = mapWidth;
        loginPlayer.state[levelChoice].q = mapHeight;
        loginPlayer.state[levelChoice].p_ = xCur;
        loginPlayer.state[levelChoice].q_ = yCur;

        int index = 0;
        for (int i=0; i<mapHeight; i++) {
            for (int j=0; j<mapWidth; j++) {
                loginPlayer.state[levelChoice].board[index] = map[i][j];
                index++;
            }
        }

        saveGame = true;

    } else {
        Move(map, mapWidth, mapHeight, xCur, yCur, iStart, jStart, iEnd, jEnd, swch, levelChoice, saveGame);
    }
}