import matplotlib.pyplot as plt

X = [100,200,300,400,500,600,700,800,900,1000]
CPI = [1.22,1.11,1.07,1.06,1.04,1.04,1.03,1.03,1.02,1.02]
operaciones = ["+", "+10", "%", "*", "/"]


frecuencia = [80, 160, 240]
tiempos = [31.84, 31.95, 32.05]  # Sacado del calculo basado en cyclos, el tiempo medido por RRS era el mismo en 160 (32), el doble en 80 (64) y la dos tercios en 240 (21)
ciclos = [5095, 5112, 5128]
tiempos2 = [64, 32, 21]

plt.plot(frecuencia, tiempos, marker='o', label="Tiempo Ciclos(us)")
plt.plot(frecuencia, tiempos2, marker='o', label="Tiempo RSS(us)")
plt.title("Impacto de la frecuencia")
plt.xlabel("Frecuencia del MCU (MHz)")
plt.ylabel("Tiempo")
plt.legend()
plt.grid(True)
plt.show()

ciclos = [5, 5, 5, 5, 5]  # Ejemplo
plt.bar(operaciones, ciclos, color='teal')
plt.title("Ciclos por operación")
plt.ylabel("Ciclos")
plt.show()

plt.plot(X, CPI, marker='o')
plt.title("CPI vs X")
plt.xlabel("Cantidad de iteraciones (X)")
plt.ylabel("Ciclos por instrucción (CPI)")
plt.grid(True)
#plt.xscale("log")
plt.show()