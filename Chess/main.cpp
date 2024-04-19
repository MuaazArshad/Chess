//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <fstream>
//#include<cstring>
//
//using namespace std;
//using namespace sf;
//
//const int gridSize = 70;
//const int windowWidth = 1500;
//const int windowHeight = 1000;
//const int boardSize = 8;
//const int squareSize = min((1400 ) / boardSize, (900) / boardSize);
//
//const int boardWidth = squareSize * boardSize;
//const int boardHeight = squareSize * boardSize;
//const int xOffset = (windowWidth - boardWidth) / 2;
//const int yOffset = (windowHeight - boardHeight) / 2;
//
//class Piece {
//public:
//    char player;
//    char type;
//    string img;
//    Texture pieceTexture;
//    Sprite pieceSprite;
//    Piece(char p, char t) {
//        player = p;
//        type = t;
//        img = string(1,player) + string(1,type) + ".png";
//        if (!pieceTexture.loadFromFile(img)) {
//            cerr << "Error loading pawn image" << std::endl;
//            return;
//        }
//       pieceSprite.setScale(112.f / pieceTexture.getSize().x, 112.f/ pieceTexture.getSize().y);
//        pieceSprite.setTexture(pieceTexture);
//    }
//    virtual bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) = 0;
//};
//
//class Pawn :public Piece {
//public:
//    Pawn(char p, char t) :Piece(p, t) {}
//    int moves = 0;
//    bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) {
//        int direction = (this->player == 'w') ? 1 : -1; // Direction depends on player color
//        
//        if (j1 == j2 && (*arr[i1 - direction][j1]).player == 'n') {
//            if ((this->moves == 0 && (i1 == i2 + 2 * direction || i1 == i2 + 1 * direction)) || (i1 == i2 + 1 * direction)) {
//                moves++;
//                return true;
//            }
//        }
//        else if ((j1 != j2) && (i1 == i2 + 1 * direction) && ((*arr[i1 - direction][j1 - 1]).player != 'n' || (*arr[i1 - direction][j1 + 1]).player != 'n')) {
//            return true;
//        }
//
//        return false;
//    }
//    
//};
//class Knight :public Piece {
//public:
//    Knight(char p, char t) :Piece(p, t) {}
//    bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) {
//        return false;
//    }
//   
//};
//class Bishop :public Piece {
//public:
//    Bishop(char p, char t) :Piece(p, t) {}
//    bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) {
//        return false;
//    }
//    
//};
//class Rook :public Piece {
//public:
//    Rook(char p, char t) :Piece(p, t) {}
//    bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) {
//        int direction = (i1 > i2 || j1 > j2) ? 1 : -1;
//        if (j1 == j2 && (*arr[i1-direction][j1]).player == 'n') {
//                return true;
//        }
//        else if (i1 == i2 && (*arr[i1][j1-direction]).player == 'n'){
//            return true;
//        }
//
//
//        return false;
//    }
//    
//};
//class King :public Piece {
//public:
//    King(char p, char t) :Piece(p, t) {}
//    bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) {
//        return false;
//    }
//    
//};
//class Queen :public Piece {
//public:
//    Queen(char p, char t) :Piece(p, t) {}
//    bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) {
//        return false;
//    }
//    
//};
//
//void moveOverlayBox(RectangleShape& overlayBox, float moveAmount, float boardWidth, float boardHeight) {
//    float currentX = overlayBox.getPosition().x;
//    float currentY = overlayBox.getPosition().y;
//
//     Calculate boundaries for overlay box
//    float minX = 400;
//    float minY = 100;
//    float maxX = boardWidth + 100 /*- overlayBox.getSize().x*/;
//    float maxY = boardHeight - overlayBox.getSize().y;
//
//    if (Keyboard::isKeyPressed(Keyboard::Left) && currentX > minX) {
//        overlayBox.move(-moveAmount, 0);
//    }
//    else if (Keyboard::isKeyPressed(Keyboard::Right) && currentX < maxX) {
//        overlayBox.move(moveAmount, 0);
//    }
//    else if (Keyboard::isKeyPressed(Keyboard::Up) && currentY > minY) {
//        overlayBox.move(0, -moveAmount);
//    }
//    else if (Keyboard::isKeyPressed(Keyboard::Down) && currentY < maxY) {
//        overlayBox.move(0, moveAmount);
//    }
//}
//
//void getCoords(RectangleShape overlayBox,int &i, int &j) {
//    i = (overlayBox.getPosition().y - yOffset) / squareSize;
//    j = (overlayBox.getPosition().x - xOffset) / squareSize;
//}
//
//void newWindow() {
//    RenderWindow newWindow;
//    newWindow.create(VideoMode(windowWidth, windowHeight), "Chess");
//
//     Load background image
//    Texture backgroundTexture;
//    if (!backgroundTexture.loadFromFile("bg2.jpeg")) {
//        std::cerr << "Error loading background image" << std::endl;
//        return;
//    }
//    Sprite backgroundSprite;
//    backgroundSprite.setScale(1500.f / backgroundTexture.getSize().x, 1000.f / backgroundTexture.getSize().y);
//    backgroundSprite.setTexture(backgroundTexture);
//
//    Font font;
//
//    if (!font.loadFromFile("campus personal use.ttf")) {
//         handle error if the font fails to load
//        std::cerr << "Error loading font" << std::endl;
//    }
//
//    Text escText;
//
//    escText.setFont(font);
//    escText.setString("Press Esc to go back to menu");
//    escText.setCharacterSize(16);
//    escText.setPosition(10, 970);
//    escText.setFillColor(Color::White);
//
//
//     Create a chessboard pattern
//    RectangleShape square(Vector2f(squareSize, squareSize));
//
//    Piece* arr[8][8]{};
//    for (int i = 0; i < 8; i++) {
//        if (i == 0) {
//            arr[i][7] = arr[i][0] = new Rook('b', 'r');
//            arr[i][6] = arr[i][1] = new Knight('b', 'n');
//            arr[i][5] = arr[i][2] = new Bishop('b', 'b');
//            arr[i][4] = new King('b', 'k');
//            arr[i][3] = new Queen('b', 'q');
//        }
//        else if (i == 1) {
//            for (int j = 0; j < 8; j++) {
//                arr[i][j] = new Pawn('b', 'p');
//            }
//        }
//        else if (i == 6) {
//            for (int j = 0; j < 8; j++) {
//                arr[i][j] = new Pawn('w', 'p');
//            }
//        }
//        else if (i == 7) {
//            arr[i][7] = arr[i][0] = new Rook('w', 'r');
//            arr[i][6] = arr[i][1] = new Knight('w', 'n');
//            arr[i][5] = arr[i][2] = new Bishop('w', 'b');
//            arr[i][4] = new King('w', 'k');
//            arr[i][3] = new Queen('w', 'q');
//        }
//        else {
//            for (int j = 0; j < 8; j++) {
//                arr[i][j] = new Pawn('n', 's');
//            }
//        }
//    }
//
//
//     Overlay box
//    RectangleShape overlayBox(Vector2f(squareSize, squareSize));
//    overlayBox.setFillColor(Color::Transparent);
//    overlayBox.setOutlineColor(Color::Black);
//    overlayBox.setOutlineThickness(4.0f);
//    overlayBox.setPosition(xOffset, yOffset); // Position overlay box at the top-left corner of the board
//
//    int i1, i2 , j1 , j2;
//    int clicks = 0, turn = 0;
//    while (newWindow.isOpen()) {
//        Event event;
//        while (newWindow.pollEvent(event)) {
//            if (event.type == Event::Closed) {
//                newWindow.close();
//            }
//            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
//                newWindow.close();
//            }
//            moveOverlayBox(overlayBox, float(squareSize), float(boardWidth), float(boardHeight));
//            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && clicks % 2 == 0) {
//                getCoords(overlayBox, i1, j1);
//                if (arr[i1][j1]->player == 'n') {
//                    break;
//             }
//                clicks++;
//            } else 
//            if (clicks % 2 != 0 && event.type == Event::KeyPressed && event.key.code == Keyboard::Enter ) {
//                getCoords(overlayBox, i2, j2);
//
//                clicks++;
//                
//                if ((turn == 0 && arr[i1][j1]->player == 'w' && arr[i2][j2]->player != 'w') ||
//                    (turn == 1 && arr[i1][j1]->player == 'b' && arr[i2][j2]->player != 'b')) {
//                    if (arr[i1][j1]->validMove(arr, i1, j1, i2, j2)) {
//                        swap(arr[i1][j1], arr[i2][j2]);
//                        arr[i1][j1] = new Pawn('n', 's');
//                        turn = (turn == 0) ? 1 : 0;
//                    }
//                }
//            }
//        }
//
//        newWindow.clear();
//        newWindow.draw(backgroundSprite);
//         Draw the chessboard
//        for (int i = 0; i < boardSize; ++i) {
//            for (int j = 0; j < boardSize; ++j) {
//                square.setPosition(xOffset + j * squareSize, yOffset + i * squareSize);
//                if ((i + j) % 2 == 0) {
//                    square.setFillColor(Color(139, 69, 19)); // Dark brown for black squares
//                }
//                else {
//                    square.setFillColor(Color::White); // White for white squares
//                }
//                newWindow.draw(square);
//            }
//        }
//
//       for (int i = 0; i < boardSize; ++i) {
//            for (int j = 0; j < boardSize; ++j) {
//                arr[i][j]->pieceSprite.setPosition(xOffset + j * squareSize, yOffset + i * squareSize);
//                newWindow.draw(arr[i][j]->pieceSprite);
//            }
//        }
//        newWindow.draw(overlayBox);
//        newWindow.draw(escText);
//
//        newWindow.display();
//    }
//}
//
//
//int main() {
//    RenderWindow window;
//    window.create(VideoMode(windowWidth, windowHeight), "Chess");
//     loading background image
//    Texture backgroundTexture;
//    if (!backgroundTexture.loadFromFile("bg3.jpg")) {
//         handle error if the image fails to load
//        std::cerr << "Error loading background image" << std::endl;
//        return -1;
//    }
//
//     create sprite for the background
//    Sprite backgroundSprite;
//    backgroundSprite.setScale(1500.f/backgroundTexture.getSize().x, 1000.f / backgroundTexture.getSize().y);
//    backgroundSprite.setTexture(backgroundTexture);
//
//     create font for text
//    Font font;
//    Font fontButton;
//
//    if (!font.loadFromFile("campus personal use.ttf")) {
//         handle error if the font fails to load
//        std::cerr << "Error loading font" << std::endl;
//        return -1;
//    }
//
//    if (!fontButton.loadFromFile("campus personal use.ttf")) {
//         handle error if the font fails to load
//        std::cerr << "Error loading font" << std::endl;
//        return -1;
//    }
//
//     create text object
//    Text text("CHESS", font, 100);
//    text.setFillColor(Color::Yellow);
//    text.setPosition(250, 10);
//
//     create first block
//    RectangleShape block1(Vector2f(300, 100));
//    block1.setFillColor(Color::Red);
//    block1.setPosition(250, 780);
//
//     create text for the first block
//    Text textBlock1(" Exit", fontButton, 90);
//    textBlock1.setFillColor(Color::Black);
//    textBlock1.setPosition(250, 780);
//
//     create second block
//    RectangleShape block2(Vector2f(300, 100));
//    block2.setFillColor(Color(139, 69, 19));
//    block2.setPosition(250, 670);
//
//     create text for the second block
//    Text textBlock2(" Play", fontButton, 90);
//    textBlock2.setFillColor(Color::Black);
//    textBlock2.setPosition(250, 670);
//
//     create arrow
//
//    Texture arrowTexture;
//
//    if (!arrowTexture.loadFromFile("arrow.png")) {
//         handle error if the image fails to load
//        std::cerr << "Error loading arrow image" << std::endl;
//        return -1;
//    }
//    Sprite arrowSprite(arrowTexture);
//    arrowSprite.setScale(0.01f, 0.01f);
//    arrowSprite.setPosition(180, 790);
//
//
//    while (window.isOpen()) {
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed) {
//                window.close();
//            }
//            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
//                window.close();
//            }
//
//             handle arrow movement
//            if (event.type == Event::KeyPressed) {
//                 move the arrow up
//                if (event.key.code == Keyboard::Up && arrowSprite.getPosition().y > block2.getPosition().y+100) {
//                    arrowSprite.move(0, -110);
//                }
//                 move the arrow down
//                else if (event.key.code == Keyboard::Down && arrowSprite.getPosition().y < block1.getPosition().y) {
//                    arrowSprite.move(0, 110);
//                }
//                 check if enter key is pressed and the arrow is at the first block
//                else if (event.key.code == Keyboard::Return &&
//                    arrowSprite.getPosition().y >= block1.getPosition().y &&
//                    arrowSprite.getPosition().y <= (block1.getPosition().y + block1.getSize().y)) {
//                    window.close();
//                }
//                 check if enter key is pressed and the arrow is at the second block
//                else if (event.key.code == Keyboard::Return &&
//                    arrowSprite.getPosition().y >= block2.getPosition().y &&
//                    arrowSprite.getPosition().y <= (block2.getPosition().y + block2.getSize().y)) {
//                    newWindow();
//                }
//            }
//        }
//
//         clear the window
//        window.clear();
//
//         draw the background
//        window.draw(backgroundSprite);
//
//         draw the text
//        window.draw(text);
//        window.draw(block1);
//        window.draw(textBlock1);
//        window.draw(block2);
//        window.draw(textBlock2);
//        window.draw(arrowSprite);
//
//
//         display what was drawn
//        window.display();
//    }
//
//
//    return 0;
//}


/*
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

const int BOARD_SIZE = 8;
const int SQUARE_SIZE = 80;
const int WINDOW_WIDTH = BOARD_SIZE * SQUARE_SIZE;
const int WINDOW_HEIGHT = BOARD_SIZE * SQUARE_SIZE;

enum class PieceColor {
    None,
    White,
    Black
};

class Piece {
public:
    Piece(char player, char type) : player(player), type(type) {
        string filename = "";
        filename += player;
        filename += type;
        filename += ".png";

        if (!texture.loadFromFile(filename)) {
            std::cerr << "Failed to load texture for piece: " << filename << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale((float)SQUARE_SIZE / texture.getSize().x, (float)SQUARE_SIZE / texture.getSize().y);
    }

    char getPlayer() const { return player; }
    char getType() const { return type; }
    sf::Sprite getSprite() const { return sprite; }

private:
    char player; // 'W' for white, 'B' for black
    char type; // 'P' for pawn, 'R' for rook, 'N' for knight, 'B' for bishop, 'Q' for queen, 'K' for king
    sf::Texture texture;
    sf::Sprite sprite;
};

Piece* board[BOARD_SIZE][BOARD_SIZE];

void initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (i == 1) {
                board[i][j] = new Piece('w', 'p');
            }
            else if (i == 6) {
                board[i][j] = new Piece('b', 'p');
            }
            else if ((i == 0 || i == 7) && (j == 0 || j == 7)) {
                board[i][j] = new Piece((i == 0) ? 'w' : 'b', 'r');
            }
            else {
                board[i][j] = nullptr;
            }
        }
    }
}

void drawBoard(sf::RenderWindow& window) {
    sf::Color lightColor(209, 206, 196);
    sf::Color darkColor(139, 69, 19);

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            square.setPosition(j * SQUARE_SIZE, i * SQUARE_SIZE);
            square.setFillColor((i + j) % 2 == 0 ? lightColor : darkColor);
            window.draw(square);

            Piece* piece = board[i][j];
            if (piece != nullptr) {
                sf::Sprite sprite = piece->getSprite();
                sprite.setPosition(j * SQUARE_SIZE, i * SQUARE_SIZE);
                window.draw(sprite);
            }
        }
    }
}

class ChessGame {
public:
    ChessGame() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simple Chess Game");
        font.loadFromFile("CAMPUS PERSONAL USE.ttf"); // Load font
        initializeBoard();
    }
    void run() {
        while (window.isOpen()) {
            handleEvents();
            draw();
        }
    }
private:
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
    void draw() {
        window.clear();
        drawBoard(window);
        window.display();
    }

    sf::RenderWindow window;
    sf::Font font;
};

int main() {
    ChessGame game;
    game.run();
    return 0;
}
*/
