#include "../include/GameInfo.hpp"
#include "../include/Othello.hpp"

class Game {
   public:
    sf::RenderWindow window;
    Othello othello;
    GameInfo info;

    Game() : window(sf::VideoMode(1024, 640), "Othello Game!") {}

    void input() {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                default:
                    break;

                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (!othello.gameOver && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        // �}�E�X�̉����ꂽ���W (x, y)
                        sf::Vector2i pos = sf::Mouse::getPosition(window);

                        // ���W�̕ϊ�
                        othello.getMovePoint(pos);

                        // �΂̐����J�E���g
                        othello.CountNumberDisc();
                    }
            }
        }
    }

    bool update() {
        if (othello.gameOver) return true;

        othello.update();

        // �ǂ����̔Ԏ肩
        info.SetTurnCheck(othello.turn);

        // ���A�΂̐�
        info.update(othello.B_DISC, othello.discCount[othello.B_DISC]);

        // ���A�΂̐�
        info.update(othello.W_DISC, othello.discCount[othello.W_DISC]);

        return true;
    }

    void draw() {
        window.clear();
        othello.draw(window);
        info.draw(window);

        // �Q�[���I���Ȃ�A���҂�\��
        if (othello.gameOver) info.SetWinnerText(window, othello.winner);

        window.display();
    }

    void run() {
        othello.initBoard();

        while (window.isOpen()) {
            input();
            update();
            draw();
        }
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}