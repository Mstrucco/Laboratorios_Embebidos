import matplotlib.pyplot as plt

# Reemplaza estos valores con los que te imprime el ESP32 en el monitor serial
tipos_memoria = [
    "DRAM (estática)",
    "IRAM (estática)",
    "RTC_DATA",
    "FLASH (.rodata)",
    "DRAM (malloc)",
    "IRAM (exec heap)",
    "PSRAM"
]

ciclos = [
    1536,
    583,
    3662,
    2793,
    264,
    583,
    641
]

plt.figure(figsize=(10, 5))
plt.bar(tipos_memoria, ciclos, color='steelblue')
plt.title("Ciclos de ejecución según tipo de memoria")
plt.ylabel("Ciclos")
plt.xticks(rotation=30, ha='right')
plt.grid(axis='y')
plt.tight_layout()
plt.show()
