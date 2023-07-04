#pragma once
#include <SFML/Graphics.hpp>

#include "iostream"

class GameInfo {
   public:
    // fontの読み込み用
    sf::Font arial;
    sf::Font digital;

    // 文字の表示用
    sf::Text players[4];
    // スコアの表示用
    sf::Text score[3];  // [null, black, white]

    // ゲームで使用する文字。配列の、1, 2, が黒と白になるようにしている
    sf::String cast[4] = {"Winner", "Black", "White", "-------"};

    // スコアが表示される枠
    sf::RectangleShape scoreFrame[3];  // [null, black, white]
    // スコア枠のサイズ
    sf::Vector2f frameSize = {130, 100};

    // 番手を示す三角形の印
    sf::VertexArray checkMark;

    // 三角形を表示する為の座標
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