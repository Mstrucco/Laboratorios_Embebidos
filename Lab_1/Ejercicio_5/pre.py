import numpy as np
from scipy.io import wavfile
from scipy.signal import spectrogram
import matplotlib.pyplot as plt

# Leer archivo
rate, data = wavfile.read("Lab_1/Ejercicio_5/guitar_riff.wav")
data = data[175869:] #voy a hacer cuatro cortes data[:58623], data[58623:117246],data[117246:175869] y data[175869:] 
# separandolo en archivos mas pequeños, lo separe en cuatro para poder usar los .h en el flash y poder guardar el resultado en el flash, despues lo saco y proceso y dejo en el analisis.
# Si estéreo, convertir a mono
if len(data.shape) == 2:
    data = data[:, 0]
print(len(data))


# Normalizar si es int16
if data.dtype == np.int16:
    data = data.astype(np.float32) / 32768.0

# Espectrograma
f, t, Sxx = spectrogram(data, fs=rate, nperseg=1024, noverlap=512)

# Graficar espectrograma de referencia
plt.pcolormesh(t, f, 10 * np.log10(Sxx), shading='gouraud')
plt.title('Espectrograma de referencia (Python)')
plt.ylabel('Frecuencia [Hz]')
plt.xlabel('Tiempo [s]')
plt.colorbar(label='dB')
plt.tight_layout()
plt.show()

# Guardar señal y espectrograma
np.savetxt("audio_data.csv", data, fmt="%.6f", delimiter=",")
np.savetxt("spectrogram_ref.csv", Sxx, delimiter=",")

# Exportar a .h
with open("audio_data.h", "w") as f:
    f.write(f"#define AUDIO_LEN {len(data)}\n")
    f.write("const float audio_data[AUDIO_LEN] = {\n")
    for i, val in enumerate(data):
        f.write(f"{val:.6f}f")
        if i < len(data) - 1:
            f.write(", ")
        if (i+1) % 8 == 0:
            f.write("\n")
    f.write("};\n")

