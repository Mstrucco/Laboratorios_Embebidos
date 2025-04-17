import serial

# CONFIGURA TU PUERTO Y BAUDRATE
PORT = 'COM4'  # Cambia esto por el puerto correcto (ej. 'COM4', '/dev/ttyUSB0', etc.)
BAUDRATE = 115200
OUTPUT_FILE = 'spectrogram_esp32.csv'

ser = serial.Serial(PORT, BAUDRATE, timeout=1)
print("Esperando datos desde el ESP32...")

buffer = []
reading = False

try:
    while True:
        line = ser.readline().decode('utf-8', errors='ignore').strip()

        if not line:
            continue

        if '<<START>>' in line:
            print("Inicio del espectrograma detectado")
            buffer = []
            reading = True
            continue

        if '<<END>>' in line:
            print("Fin del espectrograma detectado")
            break

        if reading:
            buffer.append(line)

except KeyboardInterrupt:
    print("Lectura interrumpida")

finally:
    ser.close()

# Guardar como CSV
with open(OUTPUT_FILE, 'w') as f:
    for line in buffer:
        f.write(line + '\n')

print(f"Espectrograma guardado como {OUTPUT_FILE}")
