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
//    string img;
//    Texture pieceTexture;
//    Sprite pieceSprite;
//    Piece(char p, char t) {
//        player = p;
//        type = t;
//        img = string(1, player) + string(1, type) + ".png";
//        if (!pieceTexture.loadFromFile(img)) {
//            cerr << "Error loading pawn image" << std::endl;
//            return;
//        }
//        pieceSprite.setScale(112.f / pieceTexture.getSize().x, 112.f / pieceTexture.getSize().y);
//        pieceSprite.setTexture(pieceTexture);
//    }
//    virtual bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) = 0;
//    static bool kingChecked(Piece* arr[8][8], int turn, RectangleShape& square, RenderWindow& newWindow) {
//        int kingRow = -1;
//        int kingCol = -1;
//
//        // Find the coordinates of the king
//        for (int i = 0; i < 8; i++) {
//            for (int j = 0; j < 8; j++) {
//                if ((turn == 0 && arr[i][j]->player == 'w' && arr[i][j]->type == 'k') ||
//                    (turn == 1 && arr[i][j]->player == 'b' && arr[i][j]->type == 'k')) {
//                    kingRow = i;
//                    kingCol = j;
//                    break;
//                }
//            }
//            if (kingRow != -1) break; // Exit the loop once the king is found
//        }
//        cout << "King's position: (" << kingRow << ", " << kingCol << ")" << endl;
//        for (int i = 0; i < 8; i++) {
//            for (int j = 0; j < 8; j++) {
//                if ((/*turn == 0 &&*/arr[kingRow][kingCol]->player == 'w' && arr[i][j]->player == 'b' && arr[i][j]->validMove(arr, i, j, kingRow, kingCol)) ||
//                    (/*turn == 1  && */arr[kingRow][kingCol]->player == 'b' && arr[i][j]->player == 'w' && arr[i][j]->validMove(arr, i, j, kingRow, kingCol))) {
//                    cout << "king under check\n"<<i<<" "<<j<<endl;
//                    square.setPosition(xOffset + kingCol * squareSize, yOffset + kingRow * squareSize);
//                    square.setFillColor(Color::Red);
//                    return true;
//                }
//            }
//        }
//        square.setFillColor(Color::Transparent);
//        return false;
//
//        // Print the coordinates of the king
//    }
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
//        else if ((j1 != j2) && (i1 == i2 + 1 * direction)) {
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
//
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
//};
//
//class Bishop :public Piece {
//public:
//    Bishop(char p, char t) :Piece(p, t) {}
//    bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) {
//        int direction = (i1 < i2) ? 1 : -1;
//        int side = (j1 < j2) ? 1 : -1;
//        if ((i1 - i2 == j1 - j2)|| (i2-i1==j1-j2)) {
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
//
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
//        }else
//        if (j1 == j2) {
//            for (int k = i1 + direction; k != i2; k += direction) {
//                if ((*arr[k][j1]).player != 'n') {
//                    return false;
//                }
//            }
//        }
//        else if (i1 == i2) {
//            for (int k = j1 + side; k != j2; k += side) {
//                if ((*arr[i1][k]).player != 'n') {
//                    return false;
//                }
//            }
//        }
//
//
//        return true;
//    }
//
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
//        } else if ((i1 - i2 == j1 - j2) || (i2 - i1 == j1 - j2)) {
//            for (int k = i1 + direction, l = j1 + side; k != i2, l != j2; k += direction, l += side) {
//                if ((*arr[k][l]).player != 'n') {
//                    return false;
//                }
//            }
//            return true;
//        }
//        return false;
//    }
//
//};
//
//class King :public Piece {
//public:
//    King(char p, char t) :Piece(p, t) {}
//    bool validMove(Piece* arr[8][8], int i1, int j1, int i2, int j2) {
//        int direction = (i1 < i2) ? 1 : -1;
//        int side = (j1 < j2) ? 1 : -1;
//        if (((i2 == i1 + direction) && (j2 == j1 + side))||((i2 == i1 + direction) && (j2 == j1) )|| ((i2 == i1) && (j2 == j1 + side))) {
//            return true;
//        }
//        return false;
//    }
//
//};
//
////////////////////////////////////////////////////
//// Making Functions
//
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
//        overlayBox.setOutlineColor(Color::Black);
//        overlayBox.setPosition(xOffset + j1 * squareSize, yOffset + i1 * squareSize);
//    if (arr[i1][j1]->player == 'n' ||
//        (turn == 0 && arr[i1][j1]->player == 'b') ||
//        (turn == 1 && arr[i1][j1]->player == 'w')) {
//        return true; // Break the loop if the clicked piece is invalid for the current turn
//    }
//
//    return false;
//}
//
//// getting position and moving piece
//bool handleSecondClick(const Vector2i& localPosition, int i1, int j1, int& i2, int& j2, Piece* arr[8][8], int turn, RectangleShape& overlayBox) {
//    getCoords(localPosition, i2, j2);
//    overlayBox.setOutlineColor(Color::Transparent);
//    if ((turn == 0 && arr[i1][j1]->player == 'w' && arr[i2][j2]->player != 'w') ||
//        (turn == 1 && arr[i1][j1]->player == 'b' && arr[i2][j2]->player != 'b')) {
//
//        if (arr[i1][j1]->validMove(arr, i1, j1, i2, j2)) {
//            swap(arr[i1][j1], arr[i2][j2]);
//            arr[i1][j1] = new Pawn('n', 's');
//            return true; // Move is valid, end turn
//        }
//    }
//    return false; // Move is invalid, continue with current turn
//}
//
////////////////////////////////////////////////////
//// REndering game window
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
//    // Create a chessboard pattern
//    RectangleShape square(Vector2f(squareSize, squareSize));
//    RectangleShape checksquare(Vector2f(squareSize, squareSize));
//    checksquare.setFillColor(Color::Transparent);
//
//    //Filling chessboard
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
//    // Overlay box
//    RectangleShape overlayBox(Vector2f(squareSize, squareSize));
//    overlayBox.setFillColor(Color::Transparent);
//    overlayBox.setOutlineColor(Color::Transparent);
//    overlayBox.setOutlineThickness(4.0f);
//
//    // Initializing variables
//    int i1, i2, j1, j2;
//    int clicks = 0, turn = 0;
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
//                newWindow.draw(arr[i][j]->pieceSprite);
//            }
//        }
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
//                        if (handleSecondClick(localPosition, i1, j1, i2, j2, arr, turn,overlayBox)) {
//                            turn = (turn == 0) ? 1 : 0;
//                            (Piece::kingChecked(arr, turn, checksquare, newWindow));
//                        }
//                        clicks++;
//                    }
//                }
//            }
//        }
//
//        // Drawing objects
//        newWindow.draw(escText);
//        newWindow.display();
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