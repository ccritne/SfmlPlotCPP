#include "Plot/include/TextBox.hpp"
#include "Plot/include/Button.hpp"
#include "Plot/include/Graph.hpp"
#include <SFML/Graphics.hpp>

int main() {

    double width = 1920;
    double height = 1080;
    sf::ContextSettings settings;

    settings.antialiasingLevel = 8.0;

    sf::RenderWindow App(sf::VideoMode(width, height), "PlotF", sf::Style::Default, settings);

    sf::Font font;
    font.loadFromFile("arial.ttf");
    Textbox boxText(width*0.36, height * 0.05, width*0.15, height * 0.03, font);
    Textbox boxA(width*0.54, height * 0.05, width*0.05, height * 0.03, font);
    Textbox boxB(width*0.6, height * 0.05, width*0.05, height * 0.03, font);
    Button sent(width*0.67, height * 0.05, width*0.03, height*0.03, font);
    sent.setText("GO!");

    boxText.setText("");
    Graph graph(0, 0, width, height, 0.1, 0.1, font);

    bool condText = false;
    bool condTextA = false;
    bool condTextB = false;

    std::string txtBox = "";
    std::string txtBoxA = "";
    std::string txtBoxB = "";

    bool condElab = false;

    int numberPoints = 100;

    while (App.isOpen()) {
        sf::Event event;

        while (App.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                App.close();

            if (event.type == sf::Event::TextEntered and event.text.unicode != 8 and event.text.unicode != 13) {
                if (condText) txtBox += static_cast<char>(event.text.unicode);
                if (condTextA) txtBoxA += static_cast<char>(event.text.unicode);
                if (condTextB) txtBoxB += static_cast<char>(event.text.unicode);
            }

            if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::BackSpace) {
                if (condText and !txtBox.empty()) txtBox.pop_back();
                if (condTextA and !txtBoxA.empty()) txtBoxA.pop_back();
                if (condTextB and !txtBoxB.empty()) txtBoxB.pop_back();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (boxText.contains(sf::Mouse::getPosition(App))) {
                    condText = true;
                    condTextA = false;
                    condTextB = false;
                }

                if (boxA.contains(sf::Mouse::getPosition(App))) {
                    condText = false;
                    condTextA = true;
                    condTextB = false;
                }

                if (boxB.contains(sf::Mouse::getPosition(App))) {
                    condText = false;
                    condTextA = false;
                    condTextB = true;
                }

                if (sent.contains(sf::Mouse::getPosition(App))) {
                    condText = false;
                    condTextA = false;
                    condTextB = false;

                    int multiplierA = 1;
                    int multiplierB = 1;

                    std::string startNumberString = txtBoxA;
                    std::string endNumberString = txtBoxB;

                    if (txtBoxA[0] == '-')
                        startNumberString = txtBoxA.substr(1), multiplierA = -1;
                    if (txtBoxB[0] == '-')
                        endNumberString = txtBoxB.substr(1), multiplierB = -1;

                    graph.setFunction(txtBox, evaluate(startNumberString) * multiplierA, evaluate(endNumberString) * multiplierB, numberPoints);

                }
            }
        }

        if (condText)
            boxText.setText(txtBox);

        if (condTextA)
            boxA.setText(txtBoxA);

        if (condTextB)
            boxB.setText(txtBoxB);


        App.clear();
        App.draw(graph);
        App.draw(boxText);
        App.draw(boxA);
        App.draw(boxB);
        App.draw(sent);
        App.display();
    }


    return 0;
}