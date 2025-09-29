import sys
import matplotlib.pyplot as plt

x = []  # Número da página
y = []  # Tempo total

with open(sys.argv[1], 'r') as arquivo:
    linhas = [linha.strip() for linha in arquivo if linha.strip() != ""]  # ignora linhas vazias

# Agora processa de 3 em 3 linhas
for i in range(0, len(linhas), 3):
    try:
        linha_pagina = linhas[i]
        linha_tempo_total = linhas[i+1]

        if not linha_pagina.startswith("Pagina:") or not linha_tempo_total.startswith("Tempo total:"):
            continue  # pula blocos inválidos

        num_pagina = int(linha_pagina.split(':')[1])
        tempo_total = float(linha_tempo_total.split(':')[1].split()[0])  # pega só o número

        x.append(num_pagina)
        y.append(tempo_total)
    except (IndexError, ValueError) as e:
        print(f"Erro ao processar linhas {i}-{i+2}: {e}")
        continue  # pula o bloco com erro

# Plotagem
plt.plot(x, y, marker='o')
plt.xlabel("Número de Páginas")
plt.ylabel("Tempo Total (s)")
plt.title("Tempo Total por Página")
plt.grid(True)
plt.show()
