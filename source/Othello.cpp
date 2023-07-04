#include "../include/Othello.hpp"

void Othello::initBoard() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            // マスの設定
            sf::RectangleShape rec;
            rec.setSize(sf::Vector2f(SIZE, SIZE));
            rec.setOutlineColor(sf::Color::Black);
            rec.setOutlineThickness(2);
            rec.setFillColor(sf::Color::Green);
            rec.setPosition(y * SIZE, x * SIZE);
            boardGrid.push_back(rec);
        }
    }

    // 番兵以外の場所に、0 を入れる
    for (int y = 1; y <= ROWS; y++) {
        for (int x = 1; x <= COLS; x++) {
            grid[y][x] = 0;
        }
    }

    // 初期配置
    grid[4][4] = B_DISC;
    grid[4][5] = W_DISC;
    grid[5][4] = W_DISC;
    grid[5][5] = B_DISC;

    // 黒白それぞれの現在の枚数を計算
    CountNumberDisc();
}

// 置く場所があるかどうか、のみの関数
bool Othello::turnChecker() {
    for (int y = 1; y <= 8; y++) {
        for (int x = 1; x <= 8; x++) {
            // 空マスであることが前提
            if (!grid[y][x] && moveChecker(x, y, true)) {
                return true;
            }
        }
    }

    return false;
}

// 実際に置けるかどうかを調べて、変更を加える
bool Othello::moveChecker(int x, int y, bool turnCheck = false) {
    bool check = false;

    // クリック地にすでにディスクがあるならば、return
    if (grid[y][x] != NO_DISC) return check;

    // 8方向 相手のディスクがあるのか？
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int nx = x + dx;
            int ny = y + dy;

            // 隣が相手のディスクでない場合は、continue
            if (grid[ny][nx] != len - turn) continue;

            // checkした場所を保存しておく変数
            std::vector<sf::Vector2i> checkPoints;

            // 1方向 相手のディスクがどこまであるか？
            while (grid[ny][nx] == len - turn) {
                // checkした場所をリストに一時保管
                checkPoints.push_back({nx, ny});

                nx += dx;
                ny += dy;
            }

            // 自分のディスクがあるか、つまり自分の石で挟んでいるか
            if (grid[ny][nx] == turn) {
                check = true;

                // turnChecker 用の時は、ここで関数を抜ける
                if (turnCheck) return check;

                // ここまで来たら置けるので、クリック地に自分のディスクをセット
                grid[y][x] = turn;

                // checkした場所をすべて自分のディスクに変える
                for (auto &p : checkPoints) {
                    grid[p.y][p.x] = turn;
                }
            }
        }
    }
    return check;
}

// クリックで呼ばれる関数
void Othello::getMovePoint(sf::Vector2i &pos) {
    // クリック地点の座標を 1 ~ 8 の数値に変換
    int x = pos.x / SIZE + 1;
    int y = pos.y / SIZE + 1;

    // 置けたらターンを入れ替え
    if (moveChecker(x, y)) {
        turn = len - turn;

        // パスのカウントをリセット
        pathCount = 0;
    }
}

// 黒白それぞれの現在の枚数を計算
void Othello::CountNumberDisc() {
    // カウントを0に戻しておく
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
    // 置ける場所があるかどうかの、チェック
    if (!turnChecker()) {
        // パスが２度続くと、ゲーム終了
        pathCount++;
        std::cout << pathCount << std::endl;

        // 番手の入れ替え
        turn = len - turn;
    }

    // 盤面が埋まっていたら、あるいは両者パスの場合はゲーム終了
    if ((discCount[B_DISC] + discCount[W_DISC]) == 64 || pathCount == 2) {
        // 勝者を調べる
        winner = discCount[B_DISC] > discCount[W_DISC] ? B_DISC : W_DISC;

        gameOver = true;
    }
}

void Othello::draw(sf::RenderWindow &window) {
    // マスの表示
    for (auto &b : boardGrid) {
        window.draw(b);
    }

    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            // 石の配置
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

            // 石の表示
            window.draw(disc);
        }
    }
}