import random
import tkinter
import numpy
from numpy import arange


def calculate_ruin_probability(S, X, p, N):
    count_ruins = 0
    total_rounds = 0

    for _ in range(N):
        current_capital = S
        rounds = 0

        while 0 < current_capital <= S*2:
            r = random.random()

            if r <= p:
                current_capital += X
            else:
                current_capital -= X

            rounds += 1

        if current_capital <= 0:
            count_ruins += 1

        total_rounds += rounds

    probability_ruin = count_ruins / N
    average_rounds = total_rounds // N

    return probability_ruin, average_rounds


file = open("Deserve.txt", "r+")
for p in arange(0.45, 0.6, 0.01):
    file.write(f"Вероятность победы на каждом отдельном ходу: {p}\n")
    for x in range(100):
        file.write(f"Размер ставки: {x}\n")
        prob_ruin, avg_rounds = calculate_ruin_probability(100, x, p, 10000)
        file.write(f"Вероятность разорения: {prob_ruin}\n")
        file.write(f"Средняя продолжительность игры: {avg_rounds}\n")
