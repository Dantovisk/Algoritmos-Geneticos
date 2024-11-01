import matplotlib.pyplot as plt
import matplotlib.animation as animation
import pandas as pd
import os
import time

def animate(i):
    # Verifica se o arquivo existe antes de tentar lê-lo
    if not os.path.exists("Knapsack-Mochila\output\dados.txt"):
        return  # Se não existe, sai da função e tenta na próxima chamada

    data = pd.read_csv("Knapsack-Mochila\output\dados.txt", sep=" ", names=["Geração", "Melhor Fit"])
    x = data["Geração"]
    y = data["Melhor Fit"]
    plt.cla()  # Limpa o gráfico
    plt.plot(x, y, label="Melhor Fit")
    plt.xlabel("Geração")
    plt.ylabel("Melhor Fit")
    plt.title("Progresso do Melhor Fit ao Longo das Gerações")
    plt.legend(loc="upper left")

ani = animation.FuncAnimation(plt.gcf(), animate, interval=1000, cache_frame_data=False)  # Atualiza a cada segundo
plt.tight_layout()
plt.show()
