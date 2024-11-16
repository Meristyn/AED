#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};


void drawTree(sf::RenderWindow& window, Node* node, float x, float y, float xOffset, float yOffset, int depth) {
    if (node == nullptr) return;

    // Dibuja líneas hacia los hijos
    if (node->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y)),
            sf::Vertex(sf::Vector2f(x - xOffset, y + yOffset))
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->left, x - xOffset, y + yOffset, xOffset / 2, yOffset, depth + 1);
    }

    if (node->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y)),
            sf::Vertex(sf::Vector2f(x + xOffset, y + yOffset))
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->right, x + xOffset, y + yOffset, xOffset / 2, yOffset, depth + 1);
    }

    // Dibuja el nodo actual
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color(51,153,137));
    circle.setPosition(x - 20, y - 20);
    window.draw(circle);

    // Dibuja el valor del nodo centrado
    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\cambriab.ttf")) {
        std::cerr << "No se pudo cargar la fuente." << std::endl;
    }
    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(node->value));
    text.setCharacterSize(15);
    text.setFillColor(sf::Color(226,250,219));

    // Calcular el tamaño del texto para centrarlo
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text.setPosition(x, y);

    window.draw(text);
}



int main() {
    // Crear ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Árbol Binario");

    // Crear el árbol binario
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    // Loop principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        drawTree(window, root, 400, 50, 150, 100, 0);
        window.display();
    }

    return 0;
}
