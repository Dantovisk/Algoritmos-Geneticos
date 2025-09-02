import matplotlib.pyplot as plt
import matplotlib.animation as animation
import pandas as pd
import os

# Função de animação
def animate(i):
    # Verifica se o arquivo existe antes de tentar lê-lo
    file_path = "Knapsack-Mochila/output/dados.txt"
    if not os.path.exists(file_path):
        return  # Se o arquivo não existe, sai da função

    # Lê o arquivo com os dados
    data = pd.read_csv(file_path, sep=" ", names=["Geração", "Melhor Fit", "Fit Medio"], engine='python')
    
    # Define os dados para o gráfico
    x = data["Geração"]
    y = data["Melhor Fit"]
    z = data["Fit Medio"]

    # Limpa o gráfico antes de redesenhar
    plt.cla()
    plt.plot(x, y, label="Melhor Fit", color='blue')
    plt.plot(x, z, label="Fit Medio", color='orange', linestyle='--')

    # Configurações do gráfico
    plt.xlabel("Geração")
    plt.ylabel("Fit")
    plt.title("Progresso do Melhor Fit ao Longo das Gerações")
    plt.legend(loc="upper left")
    plt.grid(True)

# Configurações para animação
ani = animation.FuncAnimation(plt.gcf(), animate, interval=1000, cache_frame_data=False)  # Atualiza a cada segundo

# Ajusta layout e exibe o gráfico
plt.tight_layout()
plt.show()
