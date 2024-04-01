#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

class Harta {
private:
    std::vector<std::string> layout; // salvam harta in memorie ca un vector de string-uri
public:
    // Constructor care incarca harta in joc
    Harta(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        while (getline(file, line))
            layout.push_back(line);
    }

    Harta(const Harta& other) : layout(other.layout) {}

    Harta& operator=(const Harta& other) {
            layout = other.layout;
    }

    ~Harta() {
        layout.clear();
        std::cout << "Map 1 - Completed; Next map: loading..." << std::endl;
    }

    // Getter pentru layout (harta sub forma de string)
    const std::vector<std::string>& getLayout() const {
        return layout;
    }

    // Actualizează o patratica de pe harta
    void updateCell(int x, int y, char symbol) {
            layout[y][x] = symbol;
    }

    // supraincarcam operator<< pentru afișare (in loc de functia display de mai jos)
    friend std::ostream& operator<<(std::ostream& os, const Harta& map) {
        for (const auto& line : map.layout) {
            os << line << "\n";
        }
        return os;
    }
};

class Bomb {
private:
    int x, y; // pozitia bombei pe harta, in sistemul de coordonate xOy
    int explosionRange; // distanta pe care bomba explodeaza (sus, jos, stanga, dreapta)
public:
    // Constructor
    Bomb(int x, int y, int explosionRange) : x(x), y(y), explosionRange(explosionRange) {}

    // Getteri si Setteri
    int getX() const { return x; }
    int getY() const { return y; }
    int getExplosionRange() const { return explosionRange; }
    void setExplosionRange(int newRange) { explosionRange = newRange; }

    // verifica daca target-ul este in explosionRange
    bool isInRange(int targetX, int targetY) const {
        return abs(targetX - x) <= explosionRange && abs(targetY - y) <= explosionRange;
    }

    // afiseaza locatia bombei folosind operatorul<< supraincarcat
    friend std::ostream& operator<<(std::ostream& os, const Bomb& bomb) {
        os << "Bomba la (" << bomb.x << ", " << bomb.y << ") cu raza " << bomb.explosionRange;
        return os;
    }
};

class Player {
private:
    std::string name;
    int x, y; // pozitia jucatorului pe orizontala si verticala
    bool isAlive; // starea jucatorului
    Harta& map;
public:
    // Constructor
    Player(const std::string& name, int startX, int startY, Harta& map): name(name), x(startX), y(startY), isAlive(true), map(map) {}

    // Getteri pentru pozitie
    int getX() const { return x; }
    int getY() const { return y; }
    std::string getName() const {return name;}

    // Plasare bomba (= adaugarea bombei curente pusa de jucator in vectorul de bombe)
    void placeBomb(std::vector<Bomb>& bombs, int explosionRange) {
        bombs.push_back(Bomb(x, y, explosionRange));
        map.updateCell(x,y,'x');
    }

    // Jucatorul este distrus de bomba
    void die() {
        if(isAlive) {
            isAlive = false;
            std::cout << name << " has died." << std::endl << std::endl;
        }
    }

    // Jucatorul se deplaseaza cu deltaX (pe orizontala) si deltaY (pe verticala)
    void move(int deltaX, int deltaY) {
        int newX = x + deltaX;
        int newY = y + deltaY;
        map.updateCell(newX, newY, name[0]); // Actualizăm harta cu noua poziție
        if(map.getLayout()[y][x]!='x')
            map.updateCell(x, y, '.'); // Marchează vechea poziție ca liberă
        x = newX;
        y = newY;
    }

    // afiseaza locatia si starea jucatorului folosind operatorul<< supraincarcat
    friend std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << "Player: " << player.name << " Position: (" << player.x << ", "
        << player.y << ") Alive: " << (player.isAlive ? "Yes" : "No");
        return os;
    }
};

class Game {
private:
    std::unique_ptr<Harta> gameMap; // incarca harta curenta
    std::vector<Player> players; // vectorul de jucatori
    std::vector<Bomb> bombs; // vectorul cu toate bombele neexplodate din joc
public:

    // Setter pentru harta jocului
    void setMap(std::unique_ptr<Harta> map) {
        gameMap = std::move(map);
    }

    // Getter pentru harta jocului
    Harta& getMap() {
        return *gameMap;
    }

    // adauga un jucator nou
    void addPlayer(const Player& player) {
        players.push_back(player);
        gameMap->updateCell(player.getX(), player.getY(), player.getName()[0]);
    }

    // Getter pentru jucători
    std::vector<Player>& getPlayers()  {
        return players;
    }

    // Getter pentru bombe
    std::vector<Bomb>& getBombs() {
        return bombs;
    }

    // simuleaza explozia tuturor bombelor in acelasi timp
    void explodeAllBombs() {
        for (auto& bomb : bombs) {
            gameMap->updateCell(bomb.getX(), bomb.getY(),'X');
            for (auto& player : players) {
                if (bomb.isInRange(player.getX(), player.getY())) {
                    player.die(); // jucatorii aflati inRange vor fi distrusi
                }
            }
        }
        bombs.clear(); // elimina bombele care au explodat din vectorul de bombe
    }

    friend std::ostream& operator<<(std::ostream& os, const Game& game) {
        os << *(game.gameMap); // Afiseaza harta
        for (const auto& player : game.players) {
            os << player << "\n"; // Afiseaza fiecare jucător
        }
        for (const auto& bomb : game.bombs) {
            os << bomb << "\n"; // Afiseaza fiecare bomba
        }
        return os;
    }
};

int main() {
    // Initializare joc si incarcare harta din fisierul harta.txt
    // Format harta.txt
    // # = zid
    // . = zona libera
    // A = player A
    // B = player B
    // X = bomba care a explodat
    // x = bomba plantata
    Game game;
    game.setMap(std::make_unique<Harta>("harta.txt"));

    // Adauga 2 jucatori
    Player player1("Tom", 1, 1, game.getMap()); // Starting position (0,0)
    Player player2("Jerry", 8, 1, game.getMap());   // Starting position (3,3)
    game.addPlayer(player1);
    game.addPlayer(player2);

    // Afisaza starea initiala a jocului
    std::cout << "Initial game state:" << std::endl;
    std::cout << game << std::endl;

    // Jucatorii se muta
    game.getPlayers()[0].move(1, 0); // Player1 moves right
    game.getPlayers()[1].move(-1, 0); // Player2 moves left

    // Afisaza starea jocului dupa mutarile jucatorilor
    std::cout << "State after moves:" << std::endl;
    std::cout << game << std::endl;

    // Jucatorul 1 plaseaza bomba
    game.getPlayers()[0].placeBomb(game.getBombs(), 1); // Player1 places a bomb with explosion range 2
    std::cout << "State after Tom placed a bomb:" << std::endl;
    std::cout << game << std::endl;

    // Jucatorul 1 se muta la dreapta si mai pune o bomba
    game.getPlayers()[0].move(1, 0);
    std::cout << "State after Tom moved again " << std::endl;
    std::cout << game << std::endl;

    game.getPlayers()[0].placeBomb(game.getBombs(), 1);
    std::cout << "State after Tom placed another bomb:" << std::endl;
    std::cout << game << std::endl;

    // Explodeaza toate bombele
    std::cout << "All bombs have exploded" << std::endl;
    game.explodeAllBombs();

    // Afisaza starea finala a jocului
    std::cout << "Final game state after explosion:" << std::endl;
    std::cout << game << std::endl;

    return 0;
}
