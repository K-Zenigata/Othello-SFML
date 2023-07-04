#pragma once
#include <SFML/Graphics.hpp>

#include "iostream"

class GameInfo {
   public:
    // font�̓ǂݍ��ݗp
    sf::Font arial;
    sf::Font digital;

    // �����̕\���p
    sf::Text players[4];
    // �X�R�A�̕\���p
    sf::Text score[3];  // [null, black, white]

    // �Q�[���Ŏg�p���镶���B�z��́A1, 2, �����Ɣ��ɂȂ�悤�ɂ��Ă���
    sf::String cast[4] = {"Winner", "Black", "White", "-------"};

    // �X�R�A���\�������g
    sf::RectangleShape scoreFrame[3];  // [null, black, white]
    // �X�R�A�g�̃T�C�Y
    sf::Vector2f frameSize = {130, 100};

    // �Ԏ�������O�p�`�̈�
    sf::VertexArray checkMark;

    // �O�p�`��\������ׂ̍��W
    sf::Vector2f b_check[3] = {
        sf::Vector2f(740, 30),  //
        sf::Vector2f(760, 30),  //
        sf::Vector2f(750, 70)   //
    };
    sf::Vector2f w_check[3] = {
        sf::Vector2f(910, 30),  //
        sf::Vector2f(930, 30),  //
        sf::Vector2f(920, 70)   //
    };

    GameInfo();
    void SetScoreFrame(sf::RectangleShape& rec, int x, int y);
    void SetTurnCheck(int turn);
    void SetWinnerText(sf::RenderWindow& window, int win);
    void SetTextCenterPos(sf::RectangleShape& rec, sf::Text& text);
    void SetTextPosition(sf::Text& text, int x, int y);
    void SetText(sf::Font& font, sf::Text& text, int size, sf::Color clr);
    void update(int player, int scoreInt);
    void draw(sf::RenderWindow& window);
};