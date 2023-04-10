#include "Plot/include/TextBox.hpp"
#include "Plot/include/Button.hpp"
#include "Plot/include/Graph.hpp"
#include <SFML/Graphics.hpp>

int main() {
    double width = 1628;
    double height = 600;
    sf::ContextSettings settings;

    settings.antialiasingLevel = 8.0;

    sf::RenderWindow App(sf::VideoMode(width, height), "PlotF", sf::Style::Default, settings);

    sf::Font font;
    font.loadFromFile("arial.ttf");
    Textbox boxText(width*0.35, height * 0.05, width*0.15, height * 0.03, font);
    Textbox boxA(width*0.55, height * 0.05, width*0.05, height * 0.03, font);
    Textbox boxB(width*0.65, height * 0.05, width*0.05, height * 0.03, font);
    Button sent(width*0.75, height * 0.05, width*0.03, height*0.03, font);
    sent.setText("GO!");
    
    int numberPoints = 1000;

    Graph graph(0, 0, width, height, 0.05, 0.05, numberPoints, font);

    sf::RectangleShape shape(sf::Vector2f(10, 10));
    shape.setPosition(sf::Vector2f(10, 10));

    bool condText = false;
    bool condTextA = false;
    bool condTextB = false;

    std::string txtBox = "";
    std::string txtBoxA = "";
    std::string txtBoxB = "";

    bool condElab = false;



    while (App.isOpen()) {
        sf::Event event;

        while (App.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                App.close();

            if (event.type == sf::Event::Resized) {

                width = static_cast<float>(event.size.width);
                height = static_cast<float>(event.size.height);

                boxText.setPosition(width * 0.35, height * 0.05);
                boxText.setSize(width*0.15, height*0.03);

                boxA.setPosition(width * 0.55, height * 0.05);
                boxA.setSize(width * 0.05, height * 0.03);

                boxB.setPosition(width * 0.65, height * 0.05);
                boxB.setSize(width * 0.05, height * 0.03);

                sent.setPosition(width * 0.75, height * 0.05);
                sent.setSize(width * 0.03, height * 0.03);

                graph.setSize(width, height);
                graph.replot();

                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                App.setView(sf::View(visibleArea));
            }

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
                std::cout << "x:"<<sf::Mouse::getPosition(App).x << " y:" << sf::Mouse::getPosition(App).y << "\n";

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

                    double multiplierA = 1;
                    double multiplierB = 1;

                    std::string startNumberString = txtBoxA;
                    std::string endNumberString = txtBoxB;

                    if (txtBoxA[0] == '-')
                        startNumberString = txtBoxA.substr(1), multiplierA = -1;
                    if (txtBoxB[0] == '-')
                        endNumberString = txtBoxB.substr(1), multiplierB = -1;

                    graph.setFunction(txtBox, stold(startNumberString) * multiplierA, stold(endNumberString) * multiplierB);

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
        App.draw(shape);
        App.draw(boxText);
        App.draw(boxA);
        App.draw(boxB);
        App.draw(sent);
        App.display();
    }

    return 0;
}
