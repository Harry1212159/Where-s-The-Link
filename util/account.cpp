#define PADDING 500
#define NAMESIZE 20
#define PASSSIZE 20
#define EMAILSIZE 20
#define BOARDSIZE 999
#define URLSIZE 100

struct State{
    int p, q;
    int p_, q_;
    int board[BOARDSIZE];
    int file_background[URLSIZE];
    int bestScore;
};

struct Date{
    int dd, mm, yy;
};

struct Record{
    Date date;
    int points;
};

struct Player{
    char mask;
    char name[NAMESIZE];
    char pass[PASSSIZE];
    char email[EMAILSIZE];

    int level;

    Record record[5];
    State state[4];
};

int playerNum;
int loginPlayerIndex = -1;
Player loginPlayer;

void xorData(char* str, char mask) {
    for(int i = 0; str[i] != '\0'; i++) {
        str[i] ^= mask;
    }
}
void Masking(Player &player) {
    xorData(player.name, player.mask);
    xorData(player.pass, player.mask);
    xorData(player.email, player.mask);
}

int totalScore(Player player) {
    int totalScore = 0;
    for (int i=0; i<4; i++) {
        totalScore += player.state[i].bestScore;
    }
    return totalScore;
}

void GetDate(Date &date) {
    time_t now = time(0);
    tm tstruct;
    tstruct = *localtime(&now);
    date.yy = 1900 + tstruct.tm_year;
    date.mm = tstruct.tm_mon;
    date.dd = tstruct.tm_mday;
}

void SortPlayer(Player* players) {
    int max, maxIndex;
    for (int i=0; i<playerNum; i++) {
        max = totalScore(players[i]);
        maxIndex = i;
        for (int j=i+1; j<playerNum; j++) {
            if (totalScore(players[j]) > max) {
                max = totalScore(players[j]);
                maxIndex = j;
            }
        }
        swap(players[i], players[maxIndex]);
    }
}

void SortRecord(Record record[5]) {
    int max, maxIndex;
    for (int i=0; i<5; i++) {
        max = record[i].points;
        maxIndex = i;
        for (int j=i+1; j<5; j++) {
            if (record[j].points > max) {
                max = record[j].points;
                maxIndex = j;
            }
        }
        swap(record[i], record[maxIndex]);
    }
}

Player* GetPlayer() {
    ifstream f("resources/player.dat", ios::binary);

    // Get file size
    f.seekg(0, ios::end);
    playerNum = f.tellg() / sizeof(Player);
    f.seekg(0, ios::beg);


    // Read file
    Player* players = new Player[playerNum];
    for (int p=0; p<playerNum; p++) {
        f.read( (char*) &players[p], sizeof(Player));
        // Masking(players[p]);
    }

    f.close();

    return players;

}

void Signup(string name, string email, string pass) {
    // Create new player
    Player player;
    // Must change after
    player.mask = 'a';
    strcpy(player.name, name.c_str());
    strcpy(player.email, email.c_str());
    strcpy(player.pass, pass.c_str());
    player.level = 0;
    for (int i=0; i<5; i++) {
        player.record[i].points = 0;
        player.record[i].date.dd = player.record[i].date.mm = player.record[i].date.yy = 0;
    }
    for (int i=0; i<4; i++) {
        player.state[i].p = 0;
        player.state[i].bestScore = 0;
    }

    // Get player list
    Player* players = GetPlayer();

    // Check if player is available
    for (int i=0; i<playerNum; i++) {
        if (strcmp(players[i].name, player.name) == 0) {
            GoTo(Padding("This player already exists !!!"), 22);
            cout << "This player already exists !!!";
            return;
        }
    }
    
    // Add player
    ofstream f("resources/player.dat", ios::app | ios::binary);

    // Masking(player);

    f.write( (char*) &player, sizeof(Player));

    loginPlayerIndex = playerNum;
    loginPlayer = player;

    f.close();

    delete [] players;
}

void Login(string name, string pass) {
    // Get player list
    Player* players = GetPlayer();

    // Check if player exists
    for (int i=0; i<playerNum; i++) {
        if (strcmp(players[i].name, name.c_str()) == 0) {
            if (strcmp(players[i].pass, pass.c_str()) == 0) {
                loginPlayerIndex = i;
                loginPlayer = players[i];
            } else {
                GoTo(Padding("Wrong password !!!"), 20);
                cout << "Wrong password !!!";
            }
            delete [] players;
            return;
        }
    }

    // If not exists
    GoTo(Padding("Player name does not exist !!!"), 20);
    cout << "Player name does not exist !!!";

    delete [] players;
}

bool isHackable(Player player) {
    string afterAt =  "";
    for (int i=0; i<strlen(player.email); i++) {
        if (player.email[i] == '@') {
            for (int j=i+1; j<strlen(player.email); j++) {
                afterAt += player.email[j];
            }
            break;
        }
    }
    return (strcmp(afterAt.c_str(), "student.hcmus.edu.vn") == 0 || strcmp(afterAt.c_str(), "clc.fitus.edu.vn") == 0);
}

void Hack(int score, int level) {
    // Get player list
    Player* players = GetPlayer();

    // Update
    ofstream f("resources/player.dat", ios::out | ios::binary);

    players[loginPlayerIndex].state[level].bestScore = score;
    players[loginPlayerIndex].record[4].points = totalScore(players[loginPlayerIndex]);
    GetDate(players[loginPlayerIndex].record[4].date);
    SortRecord(players[loginPlayerIndex].record);

    loginPlayer = players[loginPlayerIndex];

    SortPlayer(players);

    for (int i=0; i<playerNum; i++) {
        // Masking(players[i]);
        f.write( (char *) &players[i], sizeof(Player));
    }

    f.close();

    delete [] players;
}

void UpdateInfo(Player player, int levelCur) {
    // Get player list
    Player* players = GetPlayer();

    // Update
    ofstream f("resources/player.dat", ios::out | ios::binary);

    // Level 
    if (player.level > players[loginPlayerIndex].level) {
        players[loginPlayerIndex].level = player.level;
    }

    // Best score of level & Record
    if (player.state[levelCur].bestScore > players[loginPlayerIndex].state[levelCur].bestScore) {
        players[loginPlayerIndex].state[levelCur].bestScore = player.state[levelCur].bestScore;

        players[loginPlayerIndex].record[4].points = totalScore(players[loginPlayerIndex]);
        GetDate(players[loginPlayerIndex].record[4].date);
        SortRecord(players[loginPlayerIndex].record);
    }

    // Save game
    players[loginPlayerIndex].state[levelCur] = player.state[levelCur];

    SortPlayer(players);

    for (int i=0; i<playerNum; i++) {
        // Masking(players[i]);
        f.write( (char *) &players[i], sizeof(Player));
    }

    f.close();

    delete [] players;
}