// Решением задачи является приведение к виду: 
// [ 1 2 3 4 ] 
// [ 5 6 7 8 ] 
// [ 9 10 11 12]
//  [ 13 14 15 0 ], 
//  где 0 задает пустую ячейку. Достаточно найти хотя бы какое-то решение. 
//  Число перемещений костяшек не обязано быть минимальным.

// Формат ввода
// Начальная расстановка.

// Формат вывода
// Если вам удалось найти решение, то в первой строке файла выведите число перемещений, 
// которое требуется сделать в вашем решении. 
// А во второй строке выведите соответствующую последовательность ходов: 
// L означает, что в результате перемещения костяшка сдвинулась влево, R – вправо, U – вверх, D – вниз. 
// Если же выигрышная конфигурация недостижима, то выведите в выходной файл одно число −1.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <unordered_map>
#include <inttypes.h>

using namespace std;

class State {
public:
    uint8_t emptyCellPos, cells[16], shortestDistance, astarHeuristic;

    State() : emptyCellPos(0), cells{}, shortestDistance(0), astarHeuristic(0) {}
    
    bool operator==(const State &state) const {
        return emptyCellPos == state.emptyCellPos && equal(cells, cells + 16, state.cells);
    }

    bool operator!=(const State &state) const {
        return !(*this == state);
    }

    struct HashFunc {
        size_t operator()(const State &state) const {
            size_t result = 0;
            for (int i = 0; i < 16; ++i) {
                result = result * 16 + state.cells[i];
            }
            return result;
        }
    };

    struct Comparator {
        bool operator()(const State &s1, const State &s2) const {
            return s1.astarHeuristic == s2.astarHeuristic ? s1.shortestDistance < s2.shortestDistance : s1.astarHeuristic < s2.astarHeuristic;
        }
    };

    void calcHeuristic() {
        astarHeuristic = 0;
        for (size_t i = 0; i < 16; ++i) {
            if (cells[i] != 0) {
                astarHeuristic += abs((int)cells[i] - (int)(i + 1));
            }
        }
    }

   
    bool canMoveUp() const { return emptyCellPos > 3; }
    bool canMoveDown() const { return emptyCellPos < 12; }
    bool canMoveLeft() const { return emptyCellPos % 4 != 0; }
    bool canMoveRight() const { return emptyCellPos % 4 != 3; }

    State move(int delta) const {
        State newState(*this);
        newState.emptyCellPos += delta;
        swap(newState.cells[emptyCellPos], newState.cells[newState.emptyCellPos]);
        newState.calcHeuristic();
        return newState;
    }

    bool isSolvable() const {
        if (emptyCellPos != 15) {
            return false;
        }
        for (size_t index = 0; index < 15; index++) {
            if (cells[index] != index + 1) {
                return false;
            }
        }
        return true;
    }
};


void Astar(unordered_map<State, pair<State, char>, State::HashFunc> &visited,
                  set<State, State::Comparator> &pq, State &currentState, State nextState, char step) {
    auto it = visited.find(nextState);
    if (it == visited.end() || nextState.shortestDistance > currentState.shortestDistance + 1) {
        visited[nextState] = {currentState, step};
        nextState.shortestDistance = currentState.shortestDistance + 1;
        pq.insert(nextState);
    }
}

bool solvePuzzle(State &startState, string &result) {
    startState.calcHeuristic();
    unordered_map<State, pair<State, char>, State::HashFunc> visited = {{startState, {startState, 0}}};
    set<State, State::Comparator> pq = {startState};

    while (!pq.empty()) {
        State currentState = *pq.begin();
        pq.erase(pq.begin());

        if (currentState.isSolvable()) {
            for (State s = currentState; s != startState; s = visited[s].first) {
                result += visited[s].second;
            }
            reverse(result.begin(), result.end());
            return true;
        }

        if (currentState.canMoveUp()) Astar(visited, pq, currentState, currentState.move(-4), 'D');
        if (currentState.canMoveDown()) Astar(visited, pq, currentState, currentState.move(4), 'U');
        if (currentState.canMoveLeft()) Astar(visited, pq, currentState, currentState.move(-1), 'R');
        if (currentState.canMoveRight()) Astar(visited, pq, currentState, currentState.move(1), 'L');
    }

    return false;
}


int main() {
    State startState;
    unsigned short number;
    for (size_t index = 0; index < 16; index++) {
        cin >> number;
        startState.cells[index] = number;
        if (number == 0) {
            startState.emptyCellPos = index;
        }
    }
    string result;
    if (solvePuzzle(startState, result)) {
        cout << result.length() << endl << result;
    } else {
        cout << -1;
    }
    return 0;
}
