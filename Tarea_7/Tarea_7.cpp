#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
class AVLNode {
public:
    T key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(T k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    int getHeight(AVLNode<T>* node) {
        return node ? node->height : 0;
    }

    int getBalanceFactor(AVLNode<T>* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    AVLNode<T>* rotateRight(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* subtree = x->right;

        x->right = y;
        y->left = subtree;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    AVLNode<T>* rotateLeft(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* subtree = y->left;

        y->left = x;
        x->right = subtree;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    AVLNode<T>* insertNode(AVLNode<T>* node, T key) {
        if (!node) return new AVLNode<T>(key);

        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else
            return node; // No duplicates allowed

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        if (balance > 1 && key < node->left->key)
            return rotateRight(node);
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void drawTree(sf::RenderWindow& window, AVLNode<T>* node, float x, float y, float offsetX, float offsetY) {
        if (!node) return;

        // Draw lines to children
        if (node->left) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y), sf::Color::Black),
                sf::Vertex(sf::Vector2f(x - offsetX, y + offsetY), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
            drawTree(window, node->left, x - offsetX, y + offsetY, offsetX / 1.5, offsetY);
        }

        if (node->right) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y), sf::Color::Black),
                sf::Vertex(sf::Vector2f(x + offsetX, y + offsetY), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
            drawTree(window, node->right, x + offsetX, y + offsetY, offsetX / 1.5, offsetY);
        }

        // Draw node
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color(51, 153, 137)); // Match color from second code
        circle.setOutlineThickness(2);
        circle.setOutlineColor(sf::Color::Black);
        circle.setPosition(x - circle.getRadius(), y - circle.getRadius());

        window.draw(circle);

        // Draw node key
        sf::Font font;
        if (!font.loadFromFile("C:\\Windows\\Fonts\\cambriab.ttf")) {
            cerr << "Font loading error!" << endl;
            return;
        }

        sf::Text text;
        text.setFont(font);
        text.setString(to_string(node->key));
        text.setCharacterSize(15);
        text.setFillColor(sf::Color(226, 250, 219));

        // Center text in the circle
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
        text.setPosition(x, y);

        window.draw(text);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(T key) {
        root = insertNode(root, key);
    }

    void visualize() {
        sf::RenderWindow window(sf::VideoMode(800, 600), "AVL Tree Visualization");

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);
            drawTree(window, root, 400, 50, 150, 100);
            window.display();
        }
    }
};

int main() {
    AVLTree<int> avl;

    avl.insert(15);
    avl.insert(10);
    avl.insert(20);
    avl.insert(8);
    avl.insert(12);
    avl.insert(17);
    avl.insert(25);
    avl.insert(6);
    avl.insert(13);

    avl.visualize();
    return 0;
}
