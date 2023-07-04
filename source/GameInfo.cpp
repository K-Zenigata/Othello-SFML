#include "../include/GameInfo.hpp"

GameInfo::GameInfo() {
    // font ファイルを取り込む
    if (!arial.loadFromFile("../assets/arial.ttf")) {
        throw("Could Not Load Font!");
    }
    if (!digital.loadFromFile("../assets/digital-7.ttf")) {
        throw("Could Not Load Font!");
    }

    // 描画するプリミティブのタイプを三角形に設定 ...プリミティブ??
    checkMark.setPrimitiveType(sf::Triangles);

    // 配列のサイズ
    checkMark.resize(3);

    // 文字 Black の表示
    SetText(arial, players[1], 50, sf::Color::Green);
    SetTextPosition(players[1], 680, 80);
    players[1].setString(cast[1]);

    // 文字 white の表示
    SetText(arial, players[2], 50, sf::Color::Green);
    SetTextPosition(players[2], 850, 80);
    players[2].setString(cast[2]);

    // スコアボードを表示
    SetScoreFrame(scoreFrame[1], 680, 200);
    SetScoreFrame(scoreFrame[2], 850, 200);

    // スコアの数値を表示
    SetText(digital, score[1], 90, sf::Color::White);
    SetText(digital, score[2], 90, sf::Color::White);
}

// スコアボードの四角形をここで設定
void GameInfo::SetScoreFrame(sf::RectangleShape& rec, int x, int y) {
    //
    rec.setSize(frameSize);
    rec.setOutlineColor(sf::Color::Green);
    rec.setOutlineThickness(2);
    rec.setFillColor(sf::Color::Black);
    rec.setPosition(x, y);
}

// 番手を示す三角形をここで設定
void GameInfo::SetTurnCheck(int turn) {
    // 番手が黒白どちらにあるのかを取得して、三角形の座標を決める
    sf::Vector2f* pos = turn == 1 ? b_check : w_check;

    // 三角形の点の座標
    checkMark[0].position = pos[0];
    checkMark[1].position = pos[1];
    checkMark[2].position = pos[2];

    // 色、仕組みはよくわからない
    checkMark[0].color = sf::Color::Blue;
    checkMark[1].color = sf::Color::Blue;
    checkMark[2].color = sf::Color::Blue;
}

// ゲームが終了したときの、勝ち負けの表示
void GameInfo::SetWinnerText(sf::RenderWindow& window, int win) {
    // 文字 Winner の表示
    SetText(arial, players[0], 60, sf::Color::Red);
    SetTextPosition(players[0], 730, 350);
    players[0].setString(cast[0]);

    // 文字 勝者の表示
    SetText(arial, players[win], 60, sf::Color::Yellow);
    SetTextPosition(players[win], 750, 450);
    players[win].setString(cast[win]);

    // ゲームが終了した時のみの表示なので、ここでdrawする。
    window.draw(players[0]);
    window.draw(players[win]);
}

// スコアボードに表示する、数値をセンタリング表示する為の関数
void GameInfo::SetTextCenterPos(sf::RectangleShape& rec, sf::Text& text) {
    //
    auto textLB = text.getLocalBounds();       // text側は、local
    auto rectangleGB = rec.getGlobalBounds();  // 枠側は、global

    text.setOrigin(textLB.width / 2, textLB.height / 2);

    int x = rectangleGB.width / 2 + rectangleGB.left - textLB.left;
    int y = rectangleGB.height / 2 + rectangleGB.top - textLB.top;

    SetTextPosition(text, x, y);
}

// textのポジションをセット
void GameInfo::SetTextPosition(sf::Text& text, int x, int y) {
    //
    text.setPosition(x, y);
}

// textをセット
void GameInfo::SetText(sf::Font& font, sf::Text& text, int size, sf::Color clr) {
    //
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(clr);
    text.setStyle(sf::Text::Bold);
}

void GameInfo::update(int player, int scoreInt) {
    // text表示する為に score を int -> string
    sf::String s = scoreInt < 10 ? "0" + std::to_string(scoreInt) : std::to_string(scoreInt);

    // 現在のスコアの数値をセット
    score[player].setString(s);
    // 数値のポジションをセンタリング関数に渡す
    SetTextCenterPos(scoreFrame[player], score[player]);
}

// これまでの、すべてを表示
void GameInfo::draw(sf::RenderWindow& window) {
    //
    window.draw(checkMark);      // 番手の印
    window.draw(players[1]);     // 文字 black
    window.draw(players[2]);     // 文字 white
    window.draw(scoreFrame[1]);  // スコア枠 黒
    window.draw(scoreFrame[2]);  // スコア枠 白
    window.draw(score[1]);       // スコア 黒
    window.draw(score[2]);       // スコア 白
}