import subprocess

arquivo1 = open('arquivo.txt', 'w')

for p in range(1000):

    processo = subprocess.run(["./so", str(p), "10000"], encoding="utf-8", capture_output=True)
    print(processo.stdout) # vai printar a saída do processo q rodou
    arquivo1.write(f"Pagina:{p}\n")
    arquivo1.write(processo.stdout)
    arquivo1.write("\n")





