#include "../include/GameInfo.hpp"

GameInfo::GameInfo() {
    // font �t�@�C������荞��
    if (!arial.loadFromFile("../assets/arial.ttf")) {
        throw("Could Not Load Font!");
    }
    if (!digital.loadFromFile("../assets/digital-7.ttf")) {
        throw("Could Not Load Font!");
    }

    // �`�悷��v���~�e�B�u�̃^�C�v���O�p�`�ɐݒ� ...�v���~�e�B�u??
    checkMark.setPrimitiveType(sf::Triangles);

    // �z��̃T�C�Y
    checkMark.resize(3);

    // ���� Black �̕\��
    SetText(arial, players[1], 50, sf::Color::Green);
    SetTextPosition(players[1], 680, 80);
    players[1].setString(cast[1]);

    // ���� white �̕\��
    SetText(arial, players[2], 50, sf::Color::Green);
    SetTextPosition(players[2], 850, 80);
    players[2].setString(cast[2]);

    // �X�R�A�{�[�h��\��
    SetScoreFrame(scoreFrame[1], 680, 200);
    SetScoreFrame(scoreFrame[2], 850, 200);

    // �X�R�A�̐��l��\��
    SetText(digital, score[1], 90, sf::Color::White);
    SetText(digital, score[2], 90, sf::Color::White);
}

// �X�R�A�{�[�h�̎l�p�`�������Őݒ�
void GameInfo::SetScoreFrame(sf::RectangleShape& rec, int x, int y) {
    //
    rec.setSize(frameSize);
    rec.setOutlineColor(sf::Color::Green);
    rec.setOutlineThickness(2);
    rec.setFillColor(sf::Color::Black);
    rec.setPosition(x, y);
}

// �Ԏ�������O�p�`�������Őݒ�
void GameInfo::SetTurnCheck(int turn) {
    // �Ԏ肪�����ǂ���ɂ���̂����擾���āA�O�p�`�̍��W�����߂�
    sf::Vector2f* pos = turn == 1 ? b_check : w_check;

    // �O�p�`�̓_�̍��W
    checkMark[0].position = pos[0];
    checkMark[1].position = pos[1];
    checkMark[2].position = pos[2];

    // �F�A�d�g�݂͂悭�킩��Ȃ�
    checkMark[0].color = sf::Color::Blue;
    checkMark[1].color = sf::Color::Blue;
    checkMark[2].color = sf::Color::Blue;
}

// �Q�[�����I�������Ƃ��́A���������̕\��
void GameInfo::SetWinnerText(sf::RenderWindow& window, int win) {
    // ���� Winner �̕\��
    SetText(arial, players[0], 60, sf::Color::Red);
    SetTextPosition(players[0], 730, 350);
    players[0].setString(cast[0]);

    // ���� ���҂̕\��
    SetText(arial, players[win], 60, sf::Color::Yellow);
    SetTextPosition(players[win], 750, 450);
    players[win].setString(cast[win]);

    // �Q�[�����I���������݂̂̕\���Ȃ̂ŁA������draw����B
    window.draw(players[0]);
    window.draw(players[win]);
}

// �X�R�A�{�[�h�ɕ\������A���l���Z���^�����O�\������ׂ̊֐�
void GameInfo::SetTextCenterPos(sf::RectangleShape& rec, sf::Text& text) {
    //
    auto textLB = text.getLocalBounds();       // text���́Alocal
    auto rectangleGB = rec.getGlobalBounds();  // �g���́Aglobal

    text.setOrigin(textLB.width / 2, textLB.height / 2);

    int x = rectangleGB.width / 2 + rectangleGB.left - textLB.left;
    int y = rectangleGB.height / 2 + rectangleGB.top - textLB.top;

    SetTextPosition(text, x, y);
}

// text�̃|�W�V�������Z�b�g
void GameInfo::SetTextPosition(sf::Text& text, int x, int y) {
    //
    text.setPosition(x, y);
}

// text���Z�b�g
void GameInfo::SetText(sf::Font& font, sf::Text& text, int size, sf::Color clr) {
    //
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(clr);
    text.setStyle(sf::Text::Bold);
}

void GameInfo::update(int player, int scoreInt) {
    // text�\������ׂ� score �� int -> string
    sf::String s = scoreInt < 10 ? "0" + std::to_string(scoreInt) : std::to_string(scoreInt);

    // ���݂̃X�R�A�̐��l���Z�b�g
    score[player].setString(s);
    // ���l�̃|�W�V�������Z���^�����O�֐��ɓn��
    SetTextCenterPos(scoreFrame[player], score[player]);
}

// ����܂ł́A���ׂĂ�\��
void GameInfo::draw(sf::RenderWindow& window) {
    //
    window.draw(checkMark);      // �Ԏ�̈�
    window.draw(players[1]);     // ���� black
    window.draw(players[2]);     // ���� white
    window.draw(scoreFrame[1]);  // �X�R�A�g ��
    window.draw(scoreFrame[2]);  // �X�R�A�g ��
    window.draw(score[1]);       // �X�R�A ��
    window.draw(score[2]);       // �X�R�A ��
}