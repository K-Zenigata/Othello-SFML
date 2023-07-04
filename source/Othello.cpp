#include "../include/Othello.hpp"

void Othello::initBoard() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            // �}�X�̐ݒ�
            sf::RectangleShape rec;
            rec.setSize(sf::Vector2f(SIZE, SIZE));
            rec.setOutlineColor(sf::Color::Black);
            rec.setOutlineThickness(2);
            rec.setFillColor(sf::Color::Green);
            rec.setPosition(y * SIZE, x * SIZE);
            boardGrid.push_back(rec);
        }
    }

    // �ԕ��ȊO�̏ꏊ�ɁA0 ������
    for (int y = 1; y <= ROWS; y++) {
        for (int x = 1; x <= COLS; x++) {
            grid[y][x] = 0;
        }
    }

    // �����z�u
    grid[4][4] = B_DISC;
    grid[4][5] = W_DISC;
    grid[5][4] = W_DISC;
    grid[5][5] = B_DISC;

    // �������ꂼ��̌��݂̖������v�Z
    CountNumberDisc();
}

// �u���ꏊ�����邩�ǂ����A�݂̂̊֐�
bool Othello::turnChecker() {
    for (int y = 1; y <= 8; y++) {
        for (int x = 1; x <= 8; x++) {
            // ��}�X�ł��邱�Ƃ��O��
            if (!grid[y][x] && moveChecker(x, y, true)) {
                return true;
            }
        }
    }

    return false;
}

// ���ۂɒu���邩�ǂ����𒲂ׂāA�ύX��������
bool Othello::moveChecker(int x, int y, bool turnCheck = false) {
    bool check = false;

    // �N���b�N�n�ɂ��łɃf�B�X�N������Ȃ�΁Areturn
    if (grid[y][x] != NO_DISC) return check;

    // 8���� ����̃f�B�X�N������̂��H
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int nx = x + dx;
            int ny = y + dy;

            // �ׂ�����̃f�B�X�N�łȂ��ꍇ�́Acontinue
            if (grid[ny][nx] != len - turn) continue;

            // check�����ꏊ��ۑ����Ă����ϐ�
            std::vector<sf::Vector2i> checkPoints;

            // 1���� ����̃f�B�X�N���ǂ��܂ł��邩�H
            while (grid[ny][nx] == len - turn) {
                // check�����ꏊ�����X�g�Ɉꎞ�ۊ�
                checkPoints.push_back({nx, ny});

                nx += dx;
                ny += dy;
            }

            // �����̃f�B�X�N�����邩�A�܂莩���̐΂ŋ���ł��邩
            if (grid[ny][nx] == turn) {
                check = true;

                // turnChecker �p�̎��́A�����Ŋ֐��𔲂���
                if (turnCheck) return check;

                // �����܂ŗ�����u����̂ŁA�N���b�N�n�Ɏ����̃f�B�X�N���Z�b�g
                grid[y][x] = turn;

                // check�����ꏊ�����ׂĎ����̃f�B�X�N�ɕς���
                for (auto &p : checkPoints) {
                    grid[p.y][p.x] = turn;
                }
            }
        }
    }
    return check;
}

// �N���b�N�ŌĂ΂��֐�
void Othello::getMovePoint(sf::Vector2i &pos) {
    // �N���b�N�n�_�̍��W�� 1 ~ 8 �̐��l�ɕϊ�
    int x = pos.x / SIZE + 1;
    int y = pos.y / SIZE + 1;

    // �u������^�[�������ւ�
    if (moveChecker(x, y)) {
        turn = len - turn;

        // �p�X�̃J�E���g�����Z�b�g
        pathCount = 0;
    }
}

// �������ꂼ��̌��݂̖������v�Z
void Othello::CountNumberDisc() {
    // �J�E���g��0�ɖ߂��Ă���
    for (auto &count : discCount) count = 0;

    for (int y = 1; y <= ROWS; y++) {
        for (int x = 1; x <= COLS; x++) {
            if (grid[y][x] == B_DISC) {
                discCount[B_DISC]++;
            } else if (grid[y][x] == W_DISC) {
                discCount[W_DISC]++;
            }
        }
    }
}

void Othello::update() {
    // �u����ꏊ�����邩�ǂ����́A�`�F�b�N
    if (!turnChecker()) {
        // �p�X���Q�x�����ƁA�Q�[���I��
        pathCount++;
        std::cout << pathCount << std::endl;

        // �Ԏ�̓���ւ�
        turn = len - turn;
    }

    // �Ֆʂ����܂��Ă�����A���邢�͗��҃p�X�̏ꍇ�̓Q�[���I��
    if ((discCount[B_DISC] + discCount[W_DISC]) == 64 || pathCount == 2) {
        // ���҂𒲂ׂ�
        winner = discCount[B_DISC] > discCount[W_DISC] ? B_DISC : W_DISC;

        gameOver = true;
    }
}

void Othello::draw(sf::RenderWindow &window) {
    // �}�X�̕\��
    for (auto &b : boardGrid) {
        window.draw(b);
    }

    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            // �΂̔z�u
            sf::CircleShape disc;
            disc.setRadius(RADIUS);
            disc.setPosition(x * SIZE + PADDING, y * SIZE + PADDING);

            switch (grid[y + 1][x + 1]) {
                case 0:
                    disc.setFillColor(sf::Color::Green);
                    break;
                case 1:
                    disc.setFillColor(sf::Color::Black);
                    break;
                case 2:
                    disc.setFillColor(sf::Color::White);
                    break;
                default:
                    break;
            }

            // �΂̕\��
            window.draw(disc);
        }
    }
}