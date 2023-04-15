#include "header.hpp"

int main() {
    PlaySound(TEXT("resources\\BGM.wav"), NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
    SetUpWindow();
  
    MainMenu();

    return 0;
}

