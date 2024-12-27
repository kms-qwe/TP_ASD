// РК 3 ВАРИАНТ 2 ЗАДАЧА 3

// Рику необходимо попасть на межвселенную конференцию. 
// За каждую телепортацию он платит бутылками лимонада, 
// поэтому хочет потратить их на дорогу как можно меньше 
// (он же всё-таки на конференцию едет!). 
// Однако после K перелетов подряд Рика начинает сильно тошнить, 
// и он ложится спать на день. Ему известны все существующие телепортации. 
// Теперь Рик хочет найти путь (наименьший по стоимости в бутылках лимонада), 
// учитывая, что телепортация не занимает времени, 
// а до конференции осталось 10 минут 
// (то есть он может совершить не более K перелетов)!

// Формат ввода
// В первой строке находятся количество вселенных N, 
// количество существующих телепортаций M, 
// количество перелетов подряд K, 
// номер вселенной Рика S, 
// номер вселенной конференции F 
// (2 ≤ N ≤ 300, 1 ≤ M ≤ 105, 1 ≤ K ≤ 300, 1 ≤ S ≤ N, 1 ≤ F ≤ N).

// Далее идет M строк, задающих телепортации. 
// i-я строка содержит три натуральных числа: 
// Si, Fi и Pi, где Si - номер вселенной, из которой ведет i-я телепортация, 
// Fi - номер вселенной, в которую ведет i-я телепортация, 
// Pi - стоимость i-й телепортации. 1 ≤ Si ≤ N, 1 ≤ Fi ≤ N, 1 ≤ Pi ≤ 106.

// Формат вывода
// Выведите одно число - минимальную стоимость пути,
// подходящего для профессора. 
// Если профессор не сможет за K ночей добраться до конференции, выведите число -1.

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int to, cost;
};

struct State {
    int universe, flights;
    long long cost;
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

int main() {
    int N, M, K, S, F;
    cin >> N >> M >> K >> S >> F;
    S--; F--; 
    vector<vector<Edge>> graph(N);
    for (int i = 0; i < M; ++i) {
        int u, v, p;
        cin >> u >> v >> p;
        u--; v--; 
        graph[u].push_back({v, p});
    }

    vector<vector<long long>> dist(N, vector<long long>(K + 1, LLONG_MAX));
    
    priority_queue<State, vector<State>, greater<State>> pq;
    dist[S][0] = 0;
    pq.push({S, 0, 0});

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int universe = current.universe;
        int flights = current.flights;
        long long current_cost = current.cost;

        if (universe == F) {
            cout << current_cost << endl;
            return 0;
        }

        if (current_cost > dist[universe][flights]) continue;

        for (const auto& edge : graph[universe]) {
            int next_universe = edge.to;
            long long new_cost = current_cost + edge.cost;

            if (flights < K && new_cost < dist[next_universe][flights + 1]) {
                dist[next_universe][flights + 1] = new_cost;
                pq.push({next_universe, flights + 1, new_cost});
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
