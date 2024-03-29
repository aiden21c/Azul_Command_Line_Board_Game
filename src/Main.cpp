#include "../include/Main.h"

void displayMenu();

void displayCredits();

int getSeed(int argc, char **argv);

bool getSaveFiles(std::vector<string> &saveFiles);

int main(int argc, char **argv) {
    unique_ptr<GameManager> manager;
    int seed = getSeed(argc, argv);
    cout << endl << "Welcome to Azul!" << endl;

    bool gameExit = false;
    while (!gameExit) {
        cout << "-------------------";
        displayMenu();
        std::cout << INPUT_TAB;

        int input = 0;
        cin >> input;
        cout << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (input == NEW_GAME) {
            string player1 = "";
            string player2 = "";

            cout << "Enter player 1's name: " << endl;
            cout << INPUT_TAB;
            getline(cin, player1);
            transform(player1.begin(), player1.end(), player1.begin(), ::toupper);

            cout << "Enter player 2's name: " << endl;
            cout << INPUT_TAB;
            getline(cin, player2);
            transform(player2.begin(), player2.end(), player2.begin(), ::toupper);

            if (!cin.eof()) {
                if (player1 == player2) {
                    cout << endl << "Players cannot have the same name" << endl;
                } else {
                    cout << endl << "Starting a new game..." << endl;
                    manager = make_unique<GameManager>(player1, player2, seed);
                    manager->playGame();
                }
            }
        } else if (input == LOAD_GAME) {
            string saveSelection;
            bool selection = false;
            std::vector<string> saveFiles;
            bool files = getSaveFiles(saveFiles);

            if (files) {
                std::sort(saveFiles.begin(), saveFiles.end());
                for (auto &saveFile : saveFiles) {
                    cout << saveFile << endl;
                }
                cout << endl << "Please enter the name of the save file you wish to load: " << endl
                     << INPUT_TAB;
                cin >> saveSelection;
                // Check if file exists
                for (auto &saveFile : saveFiles) {
                    if (saveFile == saveSelection) {
                        selection = true;
                    }
                }
                if (!selection) {
                    cout << endl << "There are no current files under that name." << endl << endl;
                } else {
                    string filename = SAVE_PATH + saveSelection;
                    cout << "Loading game from selection..." << endl;
                    try {
                        manager = make_unique<GameManager>(filename);
                        manager->playGame();
                    } catch (const std::exception &e) {
                        std::cout << endl << "Incorrect game file format. Try again." << endl;
                    }
                }
            } else {
                cout << "There are no save files available to choose from. Please start a new game"
                     << endl;
            }
        } else if (input == CREDITS) {
            displayCredits();
        } else if (input == QUIT || cin.eof()) {
            cout << endl << "Quitting Game...\nGoodbye" << endl;
            gameExit = true;
        } else {
            cout << "Selection is invalid. Please try again." << endl;
        }
    }
    return EXIT_SUCCESS;
}

int getSeed(int argc, char **argv) {
    // Generate random seed
    std::random_device engine;
    int min = std::numeric_limits<int>::min();
    int max = std::numeric_limits<int>::max();

    std::uniform_int_distribution<int> uniform_dist(min, max);
    int seed = uniform_dist(engine);

    //Override seed with command line argument
    for (int i = 0; i != argc; ++i) {
        if (argv[i] == std::string(SEED_FLAG)) {
            seed = std::stoi(argv[i + 1]);
        }
    }
    return seed;
}

void displayMenu() {
    cout << endl << "Menu" << endl;
    cout << "----" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Credits (Show Student Information)" << endl;
    cout << "4. Quit" << endl << endl;
}

void displayCredits() {
    string filename = CREDITS_PATH;
    ifstream file;
    file.open(filename);
    cout << "-------------------------------------" << endl;
    if (!file.fail()) {
        if (file.is_open()) {
            while (!file.eof()) {
                string line;
                getline(file, line);
                cout << line << endl;
            }
            file.close();
        }
    } else {
        cout << "Credits data could not be found" << endl;
    }
    cout << "-------------------------------------" << endl;
}

bool getSaveFiles(std::vector<string> &saveFiles) {
    bool files = false;
    struct dirent *ent;
    DIR *directory = opendir(SAVE_PATH);

    if (directory != nullptr) {
        char str1[] = ".", str2[] = "..";
        while ((ent = readdir(directory)) != nullptr) {
            if ((strcmp(ent->d_name, "save_tests") != 0) && (strcmp(ent->d_name, str1) != 0) &&
                (strcmp(ent->d_name, str2) != 0)) {
                files = true;
                saveFiles.emplace_back(ent->d_name);
            }
        }
        closedir(directory);
    }
    return files;
}
