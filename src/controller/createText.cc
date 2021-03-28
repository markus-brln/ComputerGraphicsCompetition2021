#include "controller.ih"

sf::Text Controller::createText()
{
    sf::Text text;
    // select the font
    sf::Font font;
    font.loadFromFile("../fonts/jackInputMonospace.TTF");
    text.setFont(font); // font is a sf::Font

    // set the character size
    text.setCharacterSize(10); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Black);

    // set the text style
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    return text;
}

