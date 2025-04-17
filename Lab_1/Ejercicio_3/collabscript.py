import cv2
import numpy as np
import matplotlib.pyplot as plt
import urllib.request
import numpy as np

# Descargar imagen desde URL
url = "https://upload.wikimedia.org/wikipedia/en/3/30/Stormlight_Logo.jpg"
urllib.request.urlretrieve(url, "input.jpg")

# Leer la imagen
img = cv2.imread("input.jpg")

# Convertir a escala de grises
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# Redimensionar a 96x96
resized = cv2.resize(gray, (96, 96), interpolation=cv2.INTER_AREA)


plt.title("Grises 96x96")
plt.imshow(resized, cmap='gray')
plt.axis('off')
plt.show()

# Guardar como .csv
np.savetxt("imagen96x96.csv", resized, fmt="%d", delimiter=",")

# También como .npy si prefieres cargarlo en C como binario
np.save("imagen96x96.npy", resized)

# Cargar la imagen en escala de grises desde un archivo CSV
imagen = np.loadtxt("imagen96x96.csv", delimiter=",", dtype=int)

# Generar código C
c_array = "uint8_t image[96][96] = {\n"

for row in imagen:
    row_str = ", ".join(str(int(val)) for val in row)
    c_array += "    {" + row_str + "},\n"

c_array += "};"

# Mostrar parte del resultado
print(c_array[:1000])  # Solo los primeros 1000 caracteres (para no colapsar el output)

# Guardar a archivo de texto si quieres copiar fácilmente
with open("image_array_c.txt", "w") as f:
    f.write(c_array)