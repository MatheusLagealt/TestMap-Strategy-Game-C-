#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game", sf::Style::Titlebar | sf::Style::Close);

    // ADICIONAR VIEW CONTROLADO PELO MOUSE / TECLADO
    sf::View view;
    view.reset(sf::FloatRect(0, 0, 800, 600));
    window.setView(view);

    sf::Vector2f lastMousePosition;
    bool dragging = false;

    // Texturas
    sf::Texture terrainTXT;
    terrainTXT.loadFromFile("terrain/gameMap.png");

    // background
    sf::Sprite terrainBG;
    terrainBG.setTexture(terrainTXT);

    // LIMITAR MAPA
    sf::Vector2f mapSize(2000.f, 2000.f);

    while(window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // ARRASTAR COM O MOUSE
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    lastMousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    dragging = true;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left)
                    dragging = false;
            }
            else if (event.type == sf::Event::MouseMoved && dragging) {
                sf::Vector2f mousePosition(event.mouseMove.x, event.mouseMove.y);
                sf::Vector2f delta = lastMousePosition - mousePosition;
                sf::Vector2f newCenter = view.getCenter() + delta;
                sf::Vector2f halfSize = 0.5f * view.getSize();
                newCenter.x = std::max(halfSize.x, std::min(newCenter.x, mapSize.x - halfSize.x));
                newCenter.y = std::max(halfSize.y, std::min(newCenter.y, mapSize.y -halfSize.y));
                view.setCenter(newCenter);
                view.move(delta);
                window.setView(view);
                lastMousePosition = mousePosition;
            }

            // ZOOM COM O MOUSE
            else if (event.type == sf::Event::MouseWheelScrolled) {
                float delta = -event.mouseWheelScroll.delta;
                view.zoom(1.f + delta * 0.1f);
                window.setView(view);
            }
        }
        window.display();
        window.clear();
        window.draw(terrainBG);

     }
};
