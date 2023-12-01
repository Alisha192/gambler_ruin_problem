#include <iostream>
#include <fstream>
#include <random>

std::pair<double, double> calculate_ruin_probability(int S, int X, double p, int N) {
    int count_ruins = 0;
    int total_rounds = 0;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < N; ++i) {
        int current_capital = S;
        int rounds = 0;

        while (0 < current_capital && current_capital <= S*2) {
            double r = distribution(generator);

            if (r <= p) {
                current_capital += X;
            } else {
                current_capital -= X;
            }

            rounds += 1;
        }

        if (current_capital <= 0) {
            count_ruins += 1;
        }

        total_rounds += rounds;
    }

    double probability_ruin = static_cast<double>(count_ruins) / N;
    double average_rounds = static_cast<double>(total_rounds) / N;

    return std::make_pair(probability_ruin, average_rounds);
}

int main() {
    std::ofstream file;
    file.open("Result.txt");
    for (double p = 0.45; p < 0.6; p += 0.01) {
        file << "Вероятность победы на каждом отдельном ходу: " << p << "\n";
        for (int x = 1; x < 100; ++x) {
            file << "Размер ставки: " << x << "\n";
            auto result = calculate_ruin_probability(100, x, p, 10000);
            file << "Вероятность разорения: " << result.first << "\n";
            file << "Средняя продолжительность игры: " << result.second << "\n";
        }
    }
    file.close();
    return 0;
}
