#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

class Harta {
private:
    std::vector<std::string> layout;
public:
    explicit Harta(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        while (getline(file, line))
            layout.push_back(line);
    }

    Harta(const Harta& other) : layout(other.layout) {}

    Harta& operator=(const Harta& other) {
            layout = other.layout;
            return *this;
    }

    ~Harta() {
        std::cout << "Map 1 - Completed; Next map: loading..." << std::endl;
    }

    char getCell(size_t x, size_t y) const {
    // Verificăm dacă coordonatele sunt în interiorul hărții
    if (y < layout.size() && x < layout[y].size()) {
        return layout[y][x];
    }
    // Returnăm un caracter de umplutură pentru coordonatele în afara hărții
    return ' ';
}


void updateCell(size_t x, size_t y, char symbol) {
    // Verificăm dacă coordonatele sunt în interiorul hărții
    if (y < layout.size() && x < layout[y].size()) {
        layout[y][x] = symbol;
    }
}

    friend std::ostream& operator<<(std::ostream& os, const Harta& map) {
        for (const auto& line : map.layout) {
            os << line << "\n";
        }
        return os;
    }
};

class Bomb {
private:
    int x, y;
    int explosionRange;
public:
    Bomb(int x, int y, int explosionRange) : x(x), y(y), explosionRange(explosionRange) {}

    int getX() const { return x; }
    int getY() const { return y; }

    bool isInRange(int targetX, int targetY) const {
        return abs(targetX - x) <= explosionRange && abs(targetY - y) <= explosionRange;
    }

    friend std::ostream& operator<<(std::ostream& os, const Bomb& bomb) {
        os << "Bomba la (" << bomb.x << ", " << bomb.y << ") cu raza " << bomb.explosionRange;
        return os;
    }
};

class Player {
private:
    std::string name;
    int x, y;
    bool isAlive;
    Harta& map;
    std::vector<Bomb>& bombs;
public:
    Player(const std::string& name, int startX, int startY, Harta& map, std::vector<Bomb>& bombs): name(name), x(startX), y(startY), isAlive(true), map(map), bombs(bombs) {}

    int getX() const { return x; }
    int getY() const { return y; }
    std::string getName() const {return name;}

    void placeBomb(int explosionRange) {
        bombs.push_back(Bomb(x, y, explosionRange));
        map.updateCell(x,y,'x');
    }

    void die() {
        if(isAlive) {
            isAlive = false;
            std::cout << name << " has died." << std::endl << std::endl;
        }
    }

    void move(int deltaX, int deltaY) {
        int newX = x + deltaX;
        int newY = y + deltaY;
        map.updateCell(newX, newY, name[0]);
        if(map.getCell(x, y) != 'x')
            map.updateCell(x, y, '.');
        x = newX;
        y = newY;
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << "Player: " << player.name << " Position: (" << player.x << ", "
        << player.y << ") Alive: " << (player.isAlive ? "Yes" : "No");
        return os;
    }
};

class Game {
private:
    Harta gameMap;
    std::vector<Player> players;
    std::vector<Bomb> bombs;
public:
    Game(const Harta& map) : gameMap(map) {}


    Harta& getMap() {
        return gameMap;
    }

    void addPlayer(const Player& player) {
        players.push_back(player);
        gameMap.updateCell(player.getX(), player.getY(), player.getName()[0]);
    }

    Player& getPlayer(size_t index) {
        if (index < players.size())
            return players[index];
        throw std::out_of_range("Invalid player index");
    }


    std::vector<Bomb>& getBombs() {
        return bombs;
    }

    void explodeAllBombs() {
        for (auto& bomb : bombs) {
            gameMap.updateCell(bomb.getX(), bomb.getY(),'X');
            for (auto& player : players) {
                if (bomb.isInRange(player.getX(), player.getY())) {
                    player.die();
                }
            }
        }
        bombs.clear();
    }

    friend std::ostream& operator<<(std::ostream& os, const Game& game) {
        os << (game.gameMap);
        for (const auto& player : game.players) {
            os << player << "\n";
        }
        for (const auto& bomb : game.bombs) {
            os << bomb << "\n";
        }
        return os;
    }
};

int main() {
    Game game(Harta{("harta.txt")});
    std::cout << "Initial game state:" << std::endl;
    std::cout << game << std::endl;

    std::cout << "Unde se afla Tom? (0<=y<=6 si 0<=x<=9)" << std::endl;
    int y,x, nr_moves;
    std::cout << "y = ";
    std::cin >> y;
    std::cout << "x = ";
    std::cin>>x;
    Player jucator1("Tom", y, x, game.getMap(), game.getBombs());
    game.addPlayer(jucator1);

    std::cout << "Unde se afla Jerry? (0<=y<=6 si 0<=x<=9)" << std::endl;
    std::cout << "y = ";
    std::cin >> y;
    std::cout << "x = ";
    std::cin>>x;
    Player jucator2("Jerry", y, x, game.getMap(), game.getBombs());
    game.addPlayer(jucator2);

    std::cout << "Numarul de mutari: ";
    std::cin >> nr_moves;

    std::unordered_map <char, std::pair<int,int>> dx;
    dx['A']={-1,0};
    dx['S']={0,1};
    dx['W']={0,-1};
    dx['D']={1,0};
    for (int i = 1; i <= nr_moves; i++) {
        char lit;
        std::cout << "Unde se misca Tom? (A, W, S, D): ";
        std::cin >> lit;
        game.getPlayer(0).move(dx[lit].first, dx[lit].second);
        std::cout << "Harta dupa ce Tom s-a mutat" << std::endl;
        std::cout << game << std::endl;

        std::cout << "Plasezi bomba? (D, N) ";
        std::cin >> lit;
        if (lit == 'D')
        {
        game.getPlayer(0).placeBomb(1);
        std::cout << "State after Tom placed another bomb:" << std::endl;
        std::cout << game << std::endl;
        }

        std::cout << "Unde se misca Jerry? (A, W, S, D): ";
        std::cin >> lit;
        game.getPlayer(1).move(dx[lit].first, dx[lit].second);
        std::cout << "Harta dupa ce Jerry s-a mutat" << std::endl;
        std::cout << game << std::endl;

        std::cout << "Plasezi bomba? (D, N) ";
        std::cin >> lit;
        if (lit == 'D')
        {
        game.getPlayer(1).placeBomb(1);
        std::cout << "State after Tom placed another bomb:" << std::endl;
        std::cout << game << std::endl;
        }
    }
    std::cout << "All bombs have exploded" << std::endl;
    game.explodeAllBombs();
    return 0;
}
