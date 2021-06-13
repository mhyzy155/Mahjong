#include "Game.h"

Game::Game() : gameRunning(true), tilesets(3), gameOriginal(true), mouse(nullptr), board(nullptr), gfx(nullptr) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        timer = new Timer();

        window = NULL;
        renderer = NULL;
        //windowWidth = 1280;
        //windowHeight = 720;
        windowWidth = 1600;
        windowHeight = 900;

        gameScene = 1;

        mouse = new Mouse();

        buttonNewgame = new Button(new Text("New game", 50, Colors::green), Colors::beige, 20);
        buttonExit = new Button(new Text("Exit", 50, Colors::red), Colors::beige, 20);
        buttonOriginal = new Button(new Text("Original", 50, Colors::green), Colors::beige, 20);
        buttonSimple = new Button(new Text("Simplified", 50, Colors::green), Colors::beige, 20);
        buttonEasy = new Button(new Text("Easy", 50, Colors::green), Colors::beige, 20);
        buttonMedium = new Button(new Text("Medium", 50, Colors::yellow), Colors::beige, 20);
        buttonHard = new Button(new Text("Hard", 50, Colors::red), Colors::beige, 20);
        buttonAgain = new Button(new Text("Play again", 50, Colors::green), Colors::beige, 20);

        for (int i = 1; i <= tilesets; i++) {
            std::string buttonString = "tileset " + std::to_string(i);
            buttonTileset.push_back(new Button(new Text(buttonString, 50, Colors::green), Colors::beige, 20));
        }

        text_tileset = new Text("Choose a tileset:", 70, Colors::green);
        text_mode = new Text("Choose a mode:", 70, Colors::green);
        text_difficulty = new Text("Choose a difficulty:", 70, Colors::green);
        text_win = new Text("You won!", 100, Colors::white);

        printf("Creating a window... ");
        if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &window, &renderer) == 0) {
            printf("- OK\n");
            gfx = new Graphics(renderer, window, windowWidth, windowHeight);
        } else {
            printf("- error!\n");
        }
    } else {
        printf("SDL_Init error\n");
        gameRunning = false;
    }
}

Game::~Game() {
    gameRunning = false;

    pickedTiles.clear();

    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }

    printf("Closing a window... ");

    if (gfx != nullptr) {
        delete gfx;
        gfx = nullptr;
    }
    delete board;
    board = nullptr;
    delete mouse;
    mouse = nullptr;
    delete timer;
    timer = nullptr;

    delete buttonNewgame;
    buttonNewgame = nullptr;
    delete buttonExit;
    buttonExit = nullptr;
    delete buttonOriginal;
    buttonOriginal = nullptr;
    delete buttonSimple;
    buttonSimple = nullptr;
    delete buttonEasy;
    buttonEasy = nullptr;
    delete buttonMedium;
    buttonMedium = nullptr;
    delete buttonHard;
    buttonHard = nullptr;
    delete buttonAgain;
    buttonAgain = nullptr;

    std::vector<Button*>::iterator it;
    for (it = buttonTileset.begin(); it != buttonTileset.end();) {
        delete *it;
        it = buttonTileset.erase(it);
    }

    delete text_tileset;
    text_tileset = nullptr;
    delete text_mode;
    text_mode = nullptr;
    delete text_difficulty;
    text_difficulty = nullptr;
    delete text_win;
    text_win = nullptr;

    SDL_Quit();

    printf("- OK\n");
}

void Game::Update() {
    SDL_Event event;
    int dtime = timer->GetDelta();
    while (gameRunning) {
        gfx->StartDraw();
        switch (gameScene) {
            case 1:
                buttonNewgame->draw(windowWidth / 2, windowHeight / 2 - 60, renderer);
                buttonExit->draw(windowWidth / 2, windowHeight / 2 + 60, renderer);
                break;
            case 2:
                text_tileset->draw(windowWidth / 2 - text_tileset->getRect().w / 2, 100, renderer);
                for (int i = 0; i < tilesets; i++) {
                    buttonTileset[i]->draw(windowWidth / 2, 300 + i * 150, renderer);
                }
                break;
            case 3:
                text_mode->draw(windowWidth / 2 - text_mode->getRect().w / 2, 100, renderer);
                buttonOriginal->draw(windowWidth / 2, windowHeight / 2 - 60, renderer);
                buttonSimple->draw(windowWidth / 2, windowHeight / 2 + 60, renderer);
                break;
            case 4:
                text_difficulty->draw(windowWidth / 2 - text_difficulty->getRect().w / 2, 100, renderer);
                buttonEasy->draw(windowWidth / 2, windowHeight / 2 - 100, renderer);
                buttonMedium->draw(windowWidth / 2, windowHeight / 2, renderer);
                buttonHard->draw(windowWidth / 2, windowHeight / 2 + 100, renderer);
                break;
            case 5:
                gfx->DrawBoardSprites(board);
                break;
            case 6:
                gfx->DrawBG();
                text_win->draw((windowWidth - text_win->getRect().w) / 2, (windowHeight - text_win->getRect().h) / 2, renderer);
                buttonAgain->draw(windowWidth / 2, windowHeight / 2 + 150, renderer);
                buttonExit->draw(windowWidth / 2, windowHeight / 2 + 250, renderer);
                break;
        }
        gfx->EndDraw();

        /*
        ///FPS counter
        if (dtime > 0) {
            printf("FPS: %d\n", 1000 / dtime);
        } else {
            printf("Inf.\n");
        }
        */

        if (SDL_WaitEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    gameRunning = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (gameScene) {
                        case 1:
                            if (mouse->isPressed(buttonNewgame->getRect())) gameScene = 2;
                            if (mouse->isPressed(buttonExit->getRect())) gameRunning = false;
                            break;
                        case 2:
                            for (int i = 0; i < tilesets; i++) {
                                if (mouse->isPressed(buttonTileset[i]->getRect())) {
                                    gameTileset = i + 1;
                                    gameScene = 3;
                                }
                            }
                            break;
                        case 3:
                            if (mouse->isPressed(buttonOriginal->getRect())) {
                                gameOriginal = true;
                                gameScene = 4;
                            }
                            if (mouse->isPressed(buttonSimple->getRect())) {
                                gameOriginal = false;
                                gameScene = 4;
                            }
                            break;
                        case 4:
                            if (mouse->isPressed(buttonEasy->getRect())) {
                                board = new Board(gameTileset, 9);
                                gameBoardTiles = board->getBoardTilesNumber();
                                gameScene = 5;
                            }
                            break;
                        case 5:
                            mouse->buttonDown(gfx, board, tileXindex, tileYindex);
                            buttonDown();
                            break;
                        case 6:
                            if (mouse->isPressed(buttonAgain->getRect())) gameScene = 2;
                            if (mouse->isPressed(buttonExit->getRect())) gameRunning = false;
                            break;
                    }

                    break;
            }
        }
    }
}

bool Game::getStatus() {
    return gameRunning;
}

void Game::buttonDown() {
    int** boardTiles = board->getBoard();
    int empty = board->getBoardEmpty();

    //one tile selected
    if (tileXindex >= 0 && tileYindex >= 0 && pickedTiles.size() == 1) {
        int i = board->getBoardFloors() - 1;
        while (i >= 0) {
            if (boardTiles[i][pickedTiles[0]] == empty) {
                i--;
            } else
                break;
        }
        int index1 = i;

        i = board->getBoardFloors() - 1;
        while (i >= 0) {
            if (boardTiles[i][tileYindex * board->getBoardWidth() + tileXindex] == empty) {
                i--;
            } else
                break;
        }
        int index2 = i;

        if (pickedTiles[0] != (tileYindex * board->getBoardWidth() + tileXindex) && boardTiles[index1][pickedTiles[0]] == boardTiles[index2][tileYindex * board->getBoardWidth() + tileXindex]) {
            if (gameOriginal) {
                if ((tileXindex == 0 || tileXindex == board->getBoardWidth() - 1) || (boardTiles[i][tileYindex * board->getBoardWidth() + tileXindex - 1] == empty || boardTiles[i][tileYindex * board->getBoardWidth() + tileXindex + 1] == empty)) {
                    boardTiles[index1][pickedTiles[0]] = board->getBoardEmpty();
                    boardTiles[index2][tileYindex * board->getBoardWidth() + tileXindex] = board->getBoardEmpty();
                    pickedTiles.clear();
                    gameBoardTiles -= 2;
                    if (gameBoardTiles <= 0) gameScene = 6;
                }
            } else {
                boardTiles[index1][pickedTiles[0]] = board->getBoardEmpty();
                boardTiles[index2][tileYindex * board->getBoardWidth() + tileXindex] = board->getBoardEmpty();
                pickedTiles.clear();
                gameBoardTiles -= 2;
                if (gameBoardTiles <= 0) gameScene = 6;
            }
        } else if (pickedTiles[0] != (tileYindex * board->getBoardWidth() + tileXindex)) {
            if (gameOriginal) {
                if ((tileXindex == 0 || tileXindex == board->getBoardWidth() - 1) || (boardTiles[i][tileYindex * board->getBoardWidth() + tileXindex - 1] == empty || boardTiles[i][tileYindex * board->getBoardWidth() + tileXindex + 1] == empty)) {
                    pickedTiles.clear();
                    pickedTiles.push_back(tileYindex * board->getBoardWidth() + tileXindex);
                }
            } else {
                pickedTiles.clear();
                pickedTiles.push_back(tileYindex * board->getBoardWidth() + tileXindex);
            }
        }
    } else if (tileXindex >= 0 && tileYindex >= 0) {
        if (gameOriginal) {
            int i = board->getBoardFloors() - 1;
            while (i >= 0) {
                if (boardTiles[i][tileYindex * board->getBoardWidth() + tileXindex] == empty) {
                    i--;
                } else
                    break;
            }
            if ((tileXindex == 0 || tileXindex == board->getBoardWidth() - 1) || (boardTiles[i][tileYindex * board->getBoardWidth() + tileXindex - 1] == empty || boardTiles[i][tileYindex * board->getBoardWidth() + tileXindex + 1] == empty)) {
                pickedTiles.clear();
                pickedTiles.push_back(tileYindex * board->getBoardWidth() + tileXindex);
            }
        } else {
            pickedTiles.clear();
            pickedTiles.push_back(tileYindex * board->getBoardWidth() + tileXindex);
        }
    }

    gfx->grabPickedTiles(pickedTiles);
}

void Game::setStatus(bool status) {
    gameRunning = status;
}
