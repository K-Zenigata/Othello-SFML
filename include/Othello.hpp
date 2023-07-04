#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Othello {
   public:
    const int ROWS = 8;
    const int COLS = 8;

    // �}�X�̃T�C�Y
    const int SIZE = 80;

    // �΂̏��
    const int RADIUS = 36;
    const int PADDING = 2;

    // �ԕ������� 10x10 �ŔՖʂ� -1 �ŏ�����
    int grid[10][10] = {-1};

    // �{�[�h�̃}�X�̎l�p�`
    std::vector<sf::RectangleShape> boardGrid;

    // int {0, 1, 2, length}
    enum Cast { NO_DISC, B_DISC, W_DISC, len };

    // [null, ���̐�, ���̐�]
    int discCount[3] = {0};

    // ���݂̔Ԏ�
    int turn = B_DISC;

    bool gameOver = false;

    // ���ꂪ2�ɂȂ�ƁA���҃p�X�ŃQ�[���I��
    int pathCount = 0;

    // 0 = null, 1 = black, 2 = white, 3 = ��������(�����l)
    int winner = 3;

    void initBoard();

    bool turnChecker();

    bool moveChecker(int x, int y, bool turnCheck);

    void getMovePoint(sf::Vector2i &pos);

    void CountNumberDisc();

    void update();

    void draw(sf::RenderWindow &window);
};