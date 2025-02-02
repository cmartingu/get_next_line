# 📄 get_next_line – Lectura eficiente de líneas en C

`get_next_line` es una función en C que permite leer una línea de un archivo o de la entrada estándar de manera eficiente. Este proyecto de 42 refuerza el manejo de memoria dinámica y buffers.

## 🚀 Características
- Lee línea por línea desde un descriptor de archivo.
- Maneja archivos de cualquier tamaño de forma eficiente.
- Funciona con `stdin` y cualquier `fd` válido.
- Uso de `BUFFER_SIZE` para ajustar el rendimiento.

## 🛠️ Compilación e instalación
Para compilar `get_next_line`, usa:
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
```
Después incluye la cabecera en tu código:
```C
#include "get_next_line.h"
```
