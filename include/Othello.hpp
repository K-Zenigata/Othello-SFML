#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Othello {
   public:
    const int ROWS = 8;
    const int COLS = 8;

    // マスのサイズ
    const int SIZE = 80;

    // 石の情報
    const int RADIUS = 36;
    const int PADDING = 2;

    // 番兵を入れて 10x10 で盤面を -1 で初期化
    int grid[10][10] = {-1};

    // ボードのマスの四角形
    std::vector<sf::RectangleShape> boardGrid;

    // int {0, 1, 2, length}
    enum Cast { NO_DISC, B_DISC, W_DISC, len };

    // [null, 黒の数, 白の数]
    int discCount[3] = {0};

    // 現在の番手
    int turn = B_DISC;

    bool gameOver = false;

    // これが2になると、両者パスでゲーム終了
    int pathCount = 0;

    // 0 = null, 1 = black, 2 = white, 3 = 引き分け(初期値)
    int winner = 3;

    void initBoard();

    bool turnChecker();

    bool moveChecker(int x, int y, bool turnCheck);

    void getMovePoint(sf::Vector2i &pos);

    void CountNumberDisc();

    void update();

    void draw(sf::RenderWindow &window);
};