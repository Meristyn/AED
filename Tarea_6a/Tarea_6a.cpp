#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Node {
    int value;
    Node* hijos[2];
    int nivel;

    Node(int val, int lev = 1) {
        nivel = lev;
        value = val;
        hijos[0] = hijos[1] = nullptr;
    }
};

struct Tree {
    Node* root;
    Tree() : root(nullptr) {};
    ~Tree();
    void deleteTree(Node* node);
    bool find(int x, Node**& p, int& nivel);
    bool ins(int x);
    bool rem(int x);
    bool findPadreYNivel(int x, Node**& p, Node**& parent, int& nivel);
    Node** rep(Node** p);
};

Tree::~Tree() {
    deleteTree(root);
}

void Tree::deleteTree(Node* node) {
    if (node != nullptr) {
        deleteTree(node->hijos[0]);
        deleteTree(node->hijos[1]);
        delete node;
    }
}

bool Tree::find(int x, Node**& p, int& nivel)
{
    for (p = &root; *p && (*p)->value != x; p = &((*p)->hijos[(*p)->value < x])) { nivel++; };
    return *p != 0;
}

bool Tree::ins(int x)
{
    Node** p;
    int nivel = 1;
    if (find(x, p, nivel)) return 0;
    *p = new Node(x);
    (*p)->nivel = nivel;
    return 1;
}

bool Tree::rem(int x)
{
    Node** p;
    int nivel = 1;
    if (!find(x, p, nivel)) return 0;
    if ((*p)->hijos[0] && (*p)->hijos[1]) {
        Node** q = rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    Node* t = *p;
    *p = (*p)->hijos[(*p)->hijos[1] != 0];
    delete t;
    return 1;
}

Node** Tree::rep(Node** p)
{
    p = &root->hijos[0];
    while (*p) {
        p = &(*p)->hijos[1];
    }
    return p;
}

bool Tree::findPadreYNivel(int x, Node**& p, Node**& parent, int& nivel) {
    p = &root;
    parent = nullptr;
    nivel = 1;

    while (*p) {
        if ((*p)->value == x) {
            return true;  // Nodo encontrado
        }

        parent = p;
        p = &((*p)->hijos[(*p)->value < x]);
        nivel++;
    }

    return false;
}


void drawTree(sf::RenderWindow& window, Node* node, float x, float y, float xOffset, float yOffset, int depth, int n, Node** parent) {
    if (node == nullptr) return;

    // Dibuja líneas hacia los hijos
    if (node->hijos[0]) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y)),
            sf::Vertex(sf::Vector2f(x - xOffset, y + yOffset))
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->hijos[0], x - xOffset, y + yOffset, xOffset / 2, yOffset, depth + 1, n, parent);
    }

    if (node->hijos[1]) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y)),
            sf::Vertex(sf::Vector2f(x + xOffset, y + yOffset))
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->hijos[1], x + xOffset, y + yOffset, xOffset / 2, yOffset, depth + 1, n, parent);
    }

    // Dibuja el nodo actual
    sf::CircleShape circle(20);
    if (parent && node != (*parent) && node != (*parent)->hijos[0] && node != (*parent)->hijos[1] && ( node->nivel == n || node->nivel == n - 1)) {
        //Color del primo y del tio
        circle.setFillColor(sf::Color(200, 62, 77));
    }
    else {
        //Color predeterminado
        circle.setFillColor(sf::Color(51, 153, 137));
    }
    
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
    text.setFillColor(sf::Color(226, 250, 219));

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
    Tree tree;
    tree.ins(20);
    tree.ins(10);
    tree.ins(40);
    tree.ins(5);
    tree.ins(15);
    tree.ins(30);
    tree.ins(50);
    tree.ins(25);
    tree.ins(35);
    tree.ins(45);
    tree.ins(60);

    int n = 50;
    int nivel = 1;
    Node** parent = nullptr;
    Node** p = nullptr;

    // Extraer el nodo, su nivel, y obtener el padre
    if (!tree.findPadreYNivel(n, p, parent, nivel)) {
        cout << "Nodo no encontrado" << endl;
        return 0;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        drawTree(window, tree.root, 400, 50, 150, 100, 0, nivel, parent);
        window.display();
    }

    return 0;
}

