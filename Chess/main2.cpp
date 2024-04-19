////////////////////////////////////////////////////
//// Including Libraries
//
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <fstream>
//#include<cstring>
//
//using namespace std;
//using namespace sf;
//
////////////////////////////////////////////////////
//// Declaring Global Variables
//
//const int gridSize = 70;
//const int windowWidth = 1500;
//const int windowHeight = 1000;
//const int boardSize = 8;
//const int squareSize = min((1400) / boardSize, (900) / boardSize);
//
//const int boardWidth = squareSize * boardSize;
//const int boardHeight = squareSize * boardSize;
//const int xOffset = (windowWidth - boardWidth) / 2;
//const int yOffset = (windowHeight - boardHeight) / 2;
//
////////////////////////////////////////////////////
//// Introducing Classes
//
//class Piece {
//public:
//    char player;
//    char type;
//    int moves = 0;
//    string img;
//    Texture pieceTexture;
//    Sprite pieceSprite;
//    Piece(char p, char t) {
//        player = p;
//        type = t;
//        img = string(1, player) + string(1, type) + ".png";
//        if (!pieceTexture.loadFromFile(img)) {
//            cerr << "Error loading pawn image" << endl;
//            return;
//        }
//        pieceSprite.setScale(112.f / pieceTexture.getSize().x, 112.f / pieceTexture.getSize().y);
//        pieceSprite.setTexture(pieceTexture);
//    }
//    virtual bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) = 0;
//    static bool KingChecked(Piece* arr[8][8], char player, RectangleShape& square) {
//        int kingRow = -1;
//        int kingCol = -1;
//
//        // Find the coordinates of the king
//        for (int i = 0; i < 8; i++) {
//            for (int j = 0; j < 8; j++) {
//                if (arr[i][j]->player == player && arr[i][j]->type == 'k') {
//                    kingRow = i;
//                    kingCol = j;
//                    break;
//                }
//            }
//            if (kingRow != -1) break;
//        }
//
//        char opponentPlayer = (player == 'w') ? 'b' : 'w';
//        int turn = (player == 'w') ? 0 : 1;
//
//        // Check if the king is under attack
//        for (int i = 0; i < 8; i++) {
//            for (int j = 0; j < 8; j++) {
//                if ((turn == 0 || turn == 1) && arr[kingRow][kingCol]->player == player &&
//                    arr[i][j]->player == opponentPlayer &&
//                    arr[i][j]->validMove(arr, i, j, kingRow, kingCol)) {
//                    square.setPosition(xOffset + kingCol * squareSize, yOffset + kingRow * squareSize);
//                    square.setFillColor(Color::Red);
//                    return true;
//                }
//            }
//        }
//        if (turn == 0)
//            square.setFillColor(Color::Transparent);
//        return false;
//    }
//    virtual void enPassant(Piece* arr[8][8], int i1, int j1, int i2, int j2, int& turn) = 0;
//};
//
//class Pawn :public Piece {
//public:
//    Pawn(char p, char t) :Piece(p, t) {}
//    bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) {
//        int direction = (this->player == 'w') ? 1 : -1; // Direction depends on player color
//        int side = (j1 < j2) ? 1 : -1;
//
//        if (j1 == j2 && (*arr[i1 - direction][j1]).player == 'n') {
//            if ((this->moves == 0 && (*arr[i1 - 2 * direction][j1]).player == 'n' && (i1 == i2 + 2 * direction || i1 == i2 + 1 * direction))
//                || (i1 == i2 + 1 * direction)) {
//                moves++;
//                return true;
//            }
//        }
//        else if ((j1 != j2) && (i1 == i2 + 1 * direction) && (j1 == j2 - side)) {
//            // Check if the piece can capture diagonally
//            if ((direction == 1 && j1 == 0 && ((*arr[i1 - direction][j1 + 1]).player != 'n')) ||
//                (direction == -1 && j1 == 7 && ((*arr[i1 - direction][j1 - 1]).player != 'n')) ||
//                ((*arr[i1 - direction][j2]).player != 'n')) {
//                return true;
//            }
//        }
//
//        return false;
//    }
//    void enPassant(Piece* arr[8][8], int i1, int j1, int i2, int j2, int& turn) {
//        int side = (j1 < j2) ? 1 : -1;
//        char currentPlayer = arr[i1][j1]->player;
//        char opponentPlayer = (currentPlayer == 'w') ? 'b' : 'w';
//        if (((currentPlayer == 'w' && i1 == 3 && i2 == 2) || (currentPlayer == 'b' && i1 == 4 && i2 == 5)) && (j2 == j1 + side) && arr[i2][j2]->player == 'n' && arr[i1][j1 + side]->player == opponentPlayer && arr[i1][j1 + side]->moves == 1) {
//            swap(arr[i1][j1], arr[i2][j2]);
//            arr[i1][j1 + side] = new Pawn('n', 's');
//            turn = (turn == 0) ? 1 : 0;
//        }
//    }
//};
//
//class Knight :public Piece {
//public:
//    Knight(char p, char t) :Piece(p, t) {}
//    bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) {
//        int direction = (i1 < i2) ? 1 : -1;
//        int side = (j1 < j2) ? 1 : -1;
//        if (j1 == 0 && ((i2 == i1 + 2 * direction && j2 == j1 + 1) || (i2 == i1 + direction && j2 == j1 + 2))) {
//            return true;
//        }
//        else if ((j1 == 1 || j1 == 6) && ((i2 == i1 + 2 * direction && (j2 == j1 + side || j2 == j1 - side)) || (i2 == i1 + direction && j2 == j1 + 2 * side))) {
//            return true;
//        }
//        else if ((j1 > 1 && j1 < 6) && ((i2 == i1 + 2 * direction && (j2 == j1 + side || j2 == j1 - side)) || (i2 == i1 + direction && (j2 == j1 + 2 * side || j2 == j1 - 2 * side)))) {
//            return true;
//        }
//        else if (j1 == 7 && ((i2 == i1 + 2 * direction && j2 == j1 - 1) || (i2 == i1 + direction && j2 == j1 - 2))) {
//            return true;
//        }
//        return false;
//    }
//    void enPassant(Piece* arr[8][8], int i1, int j1, int i2, int j2, int& turn) {}
//};
//
//class Bishop :public Piece {
//public:
//    Bishop(char p, char t) :Piece(p, t) {}
//    bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) {
//        int direction = (i1 < i2) ? 1 : -1;
//        int side = (j1 < j2) ? 1 : -1;
//        if ((i1 - i2 == j1 - j2) || (i2 - i1 == j1 - j2)) {
//            for (int k = i1 + direction, l = j1 + side; k != i2, l != j2; k += direction, l += side) {
//                if ((*arr[k][l]).player != 'n') {
//                    return false;
//                }
//            }
//            return true;
//        }
//
//
//        return false;
//    }
//    void enPassant(Piece* arr[8][8], int i1, int j1, int i2, int j2, int& turn) {}
//};
//
//class Rook :public Piece {
//public:
//    Rook(char p, char t) :Piece(p, t) {}
//    bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) {
//        int direction = (i1 < i2) ? 1 : -1;
//        int side = (j1 < j2) ? 1 : -1;
//        if (i1 != i2 && j1 != j2) {
//            return false;
//        }
//        else
//            if (j1 == j2) {
//                for (int k = i1 + direction; k != i2; k += direction) {
//                    if ((*arr[k][j1]).player != 'n') {
//                        return false;
//                    }
//                }
//            }
//            else if (i1 == i2) {
//                for (int k = j1 + side; k != j2; k += side) {
//                    if ((*arr[i1][k]).player != 'n') {
//                        return false;
//                    }
//                }
//            }
//
//
//        return true;
//    }
//    void enPassant(Piece* arr[8][8], int i1, int j1, int i2, int j2, int& turn) {}
//};
//
//class Queen :public Piece {
//public:
//    Queen(char p, char t) :Piece(p, t) {}
//    bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) {
//        int direction = (i1 < i2) ? 1 : -1;
//        int side = (j1 < j2) ? 1 : -1;
//
//        if (j1 == j2) {
//            for (int k = i1 + direction; k != i2; k += direction) {
//                if ((*arr[k][j1]).player != 'n') {
//                    return false;
//                }
//            }
//            return true;
//        }
//        else if (i1 == i2) {
//            for (int k = j1 + side; k != j2; k += side) {
//                if ((*arr[i1][k]).player != 'n') {
//                    return false;
//                }
//            }
//            return true;
//        }
//        else if ((i1 - i2 == j1 - j2) || (i2 - i1 == j1 - j2)) {
//            for (int k = i1 + direction, l = j1 + side; k != i2, l != j2; k += direction, l += side) {
//                if ((*arr[k][l]).player != 'n') {
//                    return false;
//                }
//            }
//            return true;
//        }
//        return false;
//    }
//    void enPassant(Piece* arr[8][8], int i1, int j1, int i2, int j2, int& turn) {}
//};
//
//class King :public Piece {
//public:
//    King(char p, char t) :Piece(p, t) {}
//    bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) {
//        int direction = (i1 < i2) ? 1 : -1;
//        int side = (j1 < j2) ? 1 : -1;
//        if (((i2 == i1 + direction) && (j2 == j1 + side)) || ((i2 == i1 + direction) && (j2 == j1)) || ((i2 == i1) && (j2 == j1 + side))) {
//            return true;
//        }
//        return false;
//    }
//    void enPassant(Piece* arr[8][8], int i1, int j1, int i2, int j2, int& turn) {}
//
//};
//
////////////////////////////////////////////////////
//// Making Functions
//
//
//// Click within button
//bool isWithinButton(const Vector2i& position, int xMin, int yMin, int xMax, int yMax) {
//    return (position.x > xMin && position.y > yMin && position.x < xMax && position.y < yMax);
//}
//
//// coordinates of table
//void getCoords(Vector2i localPosition, int& i, int& j) {
//    i = (localPosition.y - yOffset) / squareSize;
//    j = (localPosition.x - xOffset) / squareSize;
//}
//
//// click within table
//bool isValidPosition(const Vector2i& position, int xOffset, int yOffset) {
//    return (position.x > xOffset && position.y > yOffset && position.x < 1198 && position.y < 948);
//}
//
//// selectiong piece
//bool handleFirstClick(const Vector2i& localPosition, int& i1, int& j1, Piece* arr[8][8], int turn, RectangleShape& overlayBox) {
//    getCoords(localPosition, i1, j1);
//
//    overlayBox.setOutlineColor(Color::Black);
//    overlayBox.setPosition(xOffset + j1 * squareSize, yOffset + i1 * squareSize);
//    if (arr[i1][j1]->player == 'n' ||
//        (turn == 0 && arr[i1][j1]->player == 'b') ||
//        (turn == 1 && arr[i1][j1]->player == 'w')) {
//        return true; // Break the loop if the clicked piece is invalid for the current turn
//    }
//
//    return false;
//}
//
//bool movePiece(int i1, int j1, int& i2, int& j2, Piece* arr[8][8], int& turn, RectangleShape& square) {
//    Piece* captured;
//    if (arr[i1][j1]->validMove(arr, i1, j1, i2, j2)) {
//        captured = arr[i2][j2];
//
//        swap(arr[i1][j1], arr[i2][j2]);
//        //delete arr[i1][j1];
//        //arr[i1][j1] = nullptr;
//        arr[i1][j1] = new Pawn('n', 's');
//        if ((turn == 0 && Piece::KingChecked(arr, 'w', square)) || turn == 1 && Piece::KingChecked(arr, 'b', square)) {
//            swap(arr[i1][j1], arr[i2][j2]);
//            arr[i2][j2] = captured;
//            return false;
//        }
//        return true; // Move is valid, end turn
//    }
//}
//
//bool possibleMoves(Piece* arr[8][8], int& turn, RectangleShape& square) {
//    Piece* captured;
//    bool possible = false;
//
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            for (int k = 0; k < 8; k++) {
//                for (int l = 0; l < 8; l++) {
//                    if (((turn == 0 && arr[i][j]->player == 'w' && arr[k][l]->player != 'w') || (turn == 1 && arr[i][j]->player == 'b' && arr[k][l]->player != 'b')) && arr[i][j]->validMove(arr, i, j, k, l)) {
//                        if ((turn == 0 && Piece::KingChecked(arr, 'w', square)) || (turn == 1 && Piece::KingChecked(arr, 'b', square))) {
//                            captured = arr[k][l];
//                            swap(arr[i][j], arr[k][l]);
//                            //delete arr[i][j];
//                            //arr[i][j] = nullptr;
//                            arr[i][j] = new Pawn('n', 's');
//                            if ((Piece::KingChecked(arr, 'w', square)) || (Piece::KingChecked(arr, 'b', square))) {
//                                swap(arr[i][j], arr[k][l]);
//                                arr[k][l] = captured;
//                                possible = false;
//                            }
//                            else {
//                                swap(arr[i][j], arr[k][l]);
//                                arr[k][l] = captured;
//                                return true;
//                            }
//                        }
//                        else {
//                            captured = arr[k][l];
//                            swap(arr[i][j], arr[k][l]);
//                            //delete arr[i][j];
//                            //arr[i][j] = nullptr;
//                            arr[i][j] = new Pawn('n', 's');
//                            if ((Piece::KingChecked(arr, 'w', square)) || (Piece::KingChecked(arr, 'b', square))) {
//                                swap(arr[i][j], arr[k][l]);
//                                arr[k][l] = captured;
//                                possible = false;
//                            }
//                            else {
//                                swap(arr[i][j], arr[k][l]);
//                                arr[k][l] = captured;
//                                return true;
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//    return false;
//}
//
//// getting position and moving piece
//bool handleSecondClick(const Vector2i& localPosition, int i1, int j1, int& i2, int& j2, Piece* arr[8][8], int& turn, RectangleShape& overlayBox, RectangleShape& square) {
//    getCoords(localPosition, i2, j2);
//    overlayBox.setOutlineColor(Color::Transparent);
//    if ((turn == 0 && arr[i1][j1]->player == 'w' && arr[i2][j2]->player != 'w') ||
//        (turn == 1 && arr[i1][j1]->player == 'b' && arr[i2][j2]->player != 'b')) {
//
//        if (movePiece(i1, j1, i2, j2, arr, turn, square)) {
//            return true;
//        }
//        if (arr[i1][j1]->type == 'p') {
//            arr[i1][j1]->enPassant(arr, i1, j1, i2, j2, turn);
//        }
//    }
//    return false; // Move is invalid, continue with current turn
//}
//
//char promotionWindow(char player) {
//    RenderWindow promotionWindow;
//    promotionWindow.create(VideoMode(112, 448), "Promote To");
//
//    // Load background image
//    Texture backgroundTexture;
//    if (!backgroundTexture.loadFromFile("bg3.jpg")) {
//        std::cerr << "Error loading background image" << std::endl;
//        return ' ';
//    }
//    Sprite backgroundSprite;
//    backgroundSprite.setScale(1,1);
//    backgroundSprite.setTexture(backgroundTexture);
//
//    Texture Queen;
//    if (!Queen.loadFromFile(string(1, player) + "q.png")) {
//        std::cerr << "Error loading background image" << std::endl;
//        //return;
//    }
//    Sprite QueenSprite;
//    QueenSprite.setScale(112.f / Queen.getSize().x, 112.f / Queen.getSize().y);
//    QueenSprite.setTexture(Queen);
//
//    Texture Bishop;
//    if (!Bishop.loadFromFile(string(1, player) + "b.png")) {
//        std::cerr << "Error loading background image" << std::endl;
//        //return;
//    }
//    Sprite BishopSprite;
//    BishopSprite.setScale(112.f / Bishop.getSize().x, 112.f / Bishop.getSize().y);
//    BishopSprite.setPosition(0, 112);
//    BishopSprite.setTexture(Bishop);
//
//    Texture Rook;
//    if (!Rook.loadFromFile(string(1, player) + "r.png")) {
//        std::cerr << "Error loading background image" << std::endl;
//        //return;
//    }
//    Sprite RookSprite;
//    RookSprite.setScale(112.f / Rook.getSize().x, 112.f / Rook.getSize().y);
//    RookSprite.setPosition(0, 224);
//    RookSprite.setTexture(Rook);
//
//    Texture Knight;
//    if (!Knight.loadFromFile(string(1, player) + "n.png")) {
//        std::cerr << "Error loading background image" << std::endl;
//        //return;
//    }
//    Sprite KnightSprite;
//    KnightSprite.setScale(112.f / Knight.getSize().x, 112.f / Knight.getSize().y);
//    KnightSprite.setPosition(0, 336);
//    KnightSprite.setTexture(Knight);
//
//    promotionWindow.clear();
//
//    while (promotionWindow.isOpen()) {
//        Vector2i Position;
//        Event event;
//        while (promotionWindow.pollEvent(event)) {
//            if (event.type == Event::Closed) {
//                promotionWindow.close();
//            }
//
//
//            if (Mouse::isButtonPressed(Mouse::Left)) {
//                Position = sf::Mouse::getPosition(promotionWindow);
//                cout << Position.x <<" " << Position.y << endl;
//            }
//            if (Position.y < 224 && Position.y > 112 && Position.x < 112 && Position.x > 0) {
//                promotionWindow.close();
//                return 'b';
//            } 
//            else if (Position.y < 336 && Position.y > 224 && Position.x < 112 && Position.x > 0) {
//                promotionWindow.close();
//                return 'r';
//            }
//            else if (Position.y < 448 && Position.y > 336 && Position.x < 112 && Position.x > 0) {
//                promotionWindow.close();
//                return 'n';
//            }else if (Position.y < 112 && Position.x < 112 && Position.x > 0 && Position.y > 0) {
//                promotionWindow.close();
//                return 'q';
//            }
//        }
//        promotionWindow.draw(backgroundSprite);
//        promotionWindow.draw(QueenSprite);
//        promotionWindow.draw(BishopSprite);
//        promotionWindow.draw(RookSprite);
//        promotionWindow.draw(KnightSprite);
//        promotionWindow.display();
//
//
//    }
//}
//
//
////////////////////////////////////////////////////
//// Rendering game window
//
//void newWindow() {
//    RenderWindow newWindow;
//    newWindow.create(VideoMode(windowWidth, windowHeight), "Chess");
//
//    // Load background image
//    Texture backgroundTexture;
//    if (!backgroundTexture.loadFromFile("bg2.jpeg")) {
//        std::cerr << "Error loading background image" << std::endl;
//        return;
//    }
//    Sprite backgroundSprite;
//    backgroundSprite.setScale(1500.f / backgroundTexture.getSize().x, 1000.f / backgroundTexture.getSize().y);
//    backgroundSprite.setTexture(backgroundTexture);
//
//    // Setting Font
//    Font font;
//
//    if (!font.loadFromFile("campus personal use.ttf")) {
//        std::cerr << "Error loading font" << std::endl;
//    }
//
//    // Setting text
//    Text escText;
//
//    escText.setFont(font);
//    escText.setString("Press Esc to go back to menu");
//    escText.setCharacterSize(16);
//    escText.setPosition(10, 970);
//    escText.setFillColor(Color::White);
//
//    Text victoryBlack;
//    victoryBlack.setFont(font);
//    victoryBlack.setString("BLack Wins by CheckMate");
//    victoryBlack.setCharacterSize(70);
//    victoryBlack.setPosition(300, 450);
//    victoryBlack.setFillColor(Color::Black);
//
//    Text victoryWhite;
//    victoryWhite.setFont(font);
//    victoryWhite.setString("White Wins by CheckMate");
//    victoryWhite.setCharacterSize(70);
//    victoryWhite.setPosition(300, 450);
//    victoryWhite.setFillColor(Color::Black);
//
//    Text victoryNone;
//    victoryNone.setFont(font);
//    victoryNone.setString("StaleMate");
//    victoryNone.setCharacterSize(70);
//    victoryNone.setPosition(600, 450);
//    victoryNone.setFillColor(Color::Black);
//
//    Text titleBlack;
//    titleBlack.setFont(font);
//    titleBlack.setString("BLack");
//    titleBlack.setCharacterSize(70);
//    titleBlack.setPosition(30, 50);
//    titleBlack.setFillColor(Color::Black);
//
//    Text titleWhite;
//    titleWhite.setFont(font);
//    titleWhite.setString("White");
//    titleWhite.setCharacterSize(70);
//    titleWhite.setPosition(1220, 850);
//    titleWhite.setFillColor(Color::White);
//
//
//    // Create a chessboard pattern
//    RectangleShape square(Vector2f(squareSize, squareSize));
//    RectangleShape checksquare(Vector2f(squareSize, squareSize));
//    checksquare.setFillColor(Color::Transparent);
//
//    //Filling chessboard
//    Piece* arr[8][8]{ nullptr };
//    for (int i = 0; i < 8; i++) {
//        if (i == 0) {
//            arr[i][7] = new Rook('b', 'r');
//            arr[i][0] = new Rook('b', 'r');
//            arr[i][6] = new Knight('b', 'n');
//            arr[i][1] = new Knight('b', 'n');
//            arr[i][5] = new Bishop('b', 'b');
//            arr[i][2] = new Bishop('b', 'b');
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
//            arr[i][7] = new Rook('w', 'r');
//            arr[i][0] = new Rook('w', 'r');
//            arr[i][6] = new Knight('w', 'n');
//            arr[i][1] = new Knight('w', 'n');
//            arr[i][5] = new Bishop('w', 'b');
//            arr[i][2] = new Bishop('w', 'b');
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
//    // Overlay box
//    RectangleShape overlayBox(Vector2f(squareSize, squareSize));
//    overlayBox.setFillColor(Color::Transparent);
//    overlayBox.setOutlineColor(Color::Transparent);
//    overlayBox.setOutlineThickness(4.0f);
//
//    // Initializing variables
//    int i1, i2, j1, j2;
//    int clicks = 0, turn = 0;
//    int mate = 5;
//    while (newWindow.isOpen()) {
//
//        newWindow.clear();
//        newWindow.draw(backgroundSprite);
//
//        // Drawing the chessboard
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
//        newWindow.draw(checksquare);
//        newWindow.draw(overlayBox);
//
//        // Drawing pieces
//        for (int i = 0; i < boardSize; ++i) {
//            for (int j = 0; j < boardSize; ++j) {
//                arr[i][j]->pieceSprite.setPosition(xOffset + j * squareSize, yOffset + i * squareSize);
//                if (arr[i][j] != nullptr) {
//                    newWindow.draw(arr[i][j]->pieceSprite);
//
//                }
//            }
//        }
//
//
//
//        Event event;
//        while (newWindow.pollEvent(event)) {
//            if (event.type == Event::Closed) {
//                newWindow.close();
//            }
//            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
//                newWindow.close();
//            }
//
//            // Handling click event
//            if (Mouse::isButtonPressed(Mouse::Left)) {
//                Vector2i localPosition = sf::Mouse::getPosition(newWindow);
//                if (isValidPosition(localPosition, xOffset, yOffset)) {
//                    if (clicks % 2 == 0) {
//                        if (handleFirstClick(localPosition, i1, j1, arr, turn, overlayBox)) {
//                            break;
//                        }
//                        clicks++;
//                    }
//                    else if (clicks % 2 != 0) {
//                        if (handleSecondClick(localPosition, i1, j1, i2, j2, arr, turn, overlayBox, square)) {
//                            turn = (turn == 0) ? 1 : 0;
//                            (Piece::KingChecked(arr, 'w', checksquare));
//                            (Piece::KingChecked(arr, 'b', checksquare));
//                            if (!possibleMoves(arr, turn, square)) {
//                                if (Piece::KingChecked(arr, 'w', checksquare)) {
//                                    mate = 0;
//                                }
//                                else if (Piece::KingChecked(arr, 'b', checksquare)) {
//                                    mate = 1;
//                                }
//                                else if (!(Piece::KingChecked(arr, 'w', checksquare)) && !(Piece::KingChecked(arr, 'b', checksquare))) {
//                                    mate = 2;
//                                }
//                            }
//                        }
//                        clicks++;
//                    }
//                }
//            }
//            for (int i = 0; i < 8; i +=7) {
//                for (int j = 0; j < 8; j++) {
//                    if (i == 0 && arr[i][j]->player == 'w' && arr[i][j]->type == 'p') {
//                        char type = promotionWindow('w');
//                        if (type == 'b') {
//                            arr[i][j] = new Bishop('w', 'b');
//                        }
//                        else if (type == 'r') {
//                            arr[i][j] = new Rook('w', 'r');
//                        }
//                        else if (type == 'n') {
//                            arr[i][j] = new Knight('w', 'n');
//                        } 
//                        else if (type == 'q') {
//                            arr[i][j] = new Queen('w', 'q');
//                        }
//                        
//                        break;
//                    }
//                    else if (i == 7 && arr[i][j]->player == 'b' && arr[i][j]->type == 'p') {
//                        char type = promotionWindow('b');
//                        if (type == 'q') {
//                            arr[i][j] = new Queen('b', 'q');
//                        }
//                        else if (type == 'b') {
//                            arr[i][j] = new Bishop('b', 'b');
//                        }
//                        else if (type == 'r') {
//                            arr[i][j] = new Rook('b', 'r');
//                        }
//                        else if (type == 'n') {
//                            arr[i][j] = new Knight('b', 'n');
//                        }
//                        break;
//                    }
//                }
//            }
//            (Piece::KingChecked(arr, 'w', checksquare));
//            (Piece::KingChecked(arr, 'b', checksquare));
//
//        }
//        if (mate == 0) {
//            newWindow.draw(victoryBlack);
//        }
//        else if (mate == 1) {
//            newWindow.draw(victoryWhite);
//        }
//        else if (mate == 2) {
//            newWindow.draw(victoryNone);
//        }
//
//        // Drawing objects
//        newWindow.draw(titleBlack);
//        newWindow.draw(titleWhite);
//
//        newWindow.draw(escText);
//        newWindow.display();
//    }
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            if (arr[i][j] != nullptr)
//            {
//                delete arr[i][j];
//                arr[i][j] = nullptr;
//            }
//        }
//    }
//}
//
//
//int main() {
//    RenderWindow window;
//    window.create(VideoMode(windowWidth, windowHeight), "Chess");
//
//    // loading background image
//    Texture backgroundTexture;
//    if (!backgroundTexture.loadFromFile("bg3.jpg")) {
//        std::cerr << "Error loading background image" << std::endl;
//        return -1;
//    }
//
//    // create sprite for the background
//    Sprite backgroundSprite;
//    backgroundSprite.setScale(1500.f / backgroundTexture.getSize().x, 1000.f / backgroundTexture.getSize().y);
//    backgroundSprite.setTexture(backgroundTexture);
//
//    // create font for text
//    Font font;
//    Font fontButton;
//
//    if (!font.loadFromFile("campus personal use.ttf")) {
//        std::cerr << "Error loading font" << std::endl;
//        return -1;
//    }
//
//    if (!fontButton.loadFromFile("campus personal use.ttf")) {
//        std::cerr << "Error loading font" << std::endl;
//        return -1;
//    }
//
//    // create text object
//    Text text("CHESS", font, 100);
//    text.setFillColor(Color::Yellow);
//    text.setPosition(250, 10);
//
//    // create first block
//    RectangleShape block1(Vector2f(300, 100));
//    block1.setFillColor(Color::Red);
//    block1.setPosition(250, 780);
//
//    // create text for the first block
//    Text textBlock1(" Exit", fontButton, 90);
//    textBlock1.setFillColor(Color::Black);
//    textBlock1.setPosition(250, 780);
//
//    // create second block
//    RectangleShape block2(Vector2f(300, 100));
//    block2.setFillColor(Color(139, 69, 19));
//    block2.setPosition(250, 670);
//
//    // create text for the second block
//    Text textBlock2(" Play", fontButton, 90);
//    textBlock2.setFillColor(Color::Black);
//    textBlock2.setPosition(250, 670);
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
//            // Handling click event
//            if (Mouse::isButtonPressed(Mouse::Left)) {
//                Vector2i localPosition = Mouse::getPosition(window);
//
//                if (isWithinButton(localPosition, 250, 780, 550, 880)) {
//                    window.close();
//                }
//                else if (isWithinButton(localPosition, 250, 670, 550, 770)) {
//                    newWindow();
//                }
//            }
//        }
//
//
//        // clear the window
//        window.clear();
//
//        // draw the background
//        window.draw(backgroundSprite);
//
//        // draw the text
//        window.draw(text);
//        window.draw(block1);
//        window.draw(textBlock1);
//        window.draw(block2);
//        window.draw(textBlock2);
//
//
//        // display what was drawn
//        window.display();
//    }
//
//
//    return 0;
//}