# 🖥️ Sistema de Gestión de Sesiones — PAD-Bienestar / SIG-Conecta

> Sistema en C para el registro y control de sesiones activas en puntos de acceso digital comunitarios del proyecto SIG-Conecta.

---

## 📋 Descripción

Este programa implementa un **sistema de gestión de sesiones de equipos** para el punto **PAD-Bienestar**, nodo del proyecto ficticio **SIG-Conecta** — una iniciativa de conectividad solar para comunidades rurales de alta marginación en México.

El programa utiliza una **lista enlazada dinámica** en C para registrar, eliminar y consultar las sesiones activas de hasta 12 equipos de cómputo. Cada sesión almacena el número de equipo y la hora exacta de inicio, capturada automáticamente del sistema operativo.

---

## 🛠️ Características

| Funcionalidad | Descripción |
|---|---|
| ✅ Alta de sesión | Registra un equipo con hora de inicio automática |
| ❌ Baja de sesión | Finaliza y elimina una sesión de la lista |
| 📋 Mostrar sesiones | Lista todos los equipos con sesión activa |
| 🔒 Validaciones | Rango 1–12, duplicados, entrada inválida |
| 🧹 Liberación de memoria | `free()` explícito al salir o dar de baja |

---

## 📁 Estructura del proyecto

```
pad-bienestar/
│
├── sesiones.c        # Código fuente principal
└── README.md         # Este archivo
```

---

## ⚙️ Requisitos

- Compilador: `gcc` (GCC 9 o superior recomendado)
- Sistema operativo: Linux, macOS o Windows (con MinGW/WSL)
- Estándar C: C99 o C11

---

## 🚀 Compilación y ejecución

### Linux / macOS

```bash
gcc -o sesiones sesiones.c
./sesiones
```

### Windows (MinGW)

```bash
gcc -o sesiones.exe sesiones.c
sesiones.exe
```

### Con advertencias activadas (recomendado)

```bash
gcc -Wall -Wextra -o sesiones sesiones.c
```

---

## 🖱️ Uso del menú

Al ejecutar el programa verás el siguiente menú:

```
  +------------------------------------------+
  |             SISTEMA - MARVIN /           |
  +------------------------------------------+
  |  1. Dar de alta una sesion               |
  |  2. Dar de baja una sesion               |
  |  3. Mostrar sesiones activas             |
  |  4. Salir                                |
  +------------------------------------------+
```

**Opción 1 — Alta:** Solicita el número de equipo (1–12). Si ya tiene sesión activa, muestra un aviso y no duplica el registro.

**Opción 2 — Baja:** Solicita el número de equipo a liberar. Elimina el nodo, ajusta los punteros y libera la memoria con `free()`.

**Opción 3 — Mostrar:** Recorre la lista e imprime equipo, hora de inicio y conteo total.

**Opción 4 — Salir:** Llama a `liberar_lista()` para limpiar toda la memoria antes de cerrar.

---

## 🧠 Estructura de datos

```c
typedef struct Sesion {
    int  num_equipo;        // Identificador del equipo (1–12)
    char hora_inicio[20];   // Hora de inicio en formato HH:MM:SS
    struct Sesion *siguiente; // Puntero al siguiente nodo
} Sesion;
```

La lista crece hacia el frente: cada nueva sesión se inserta como la nueva `cabeza`. La eliminación es lineal con búsqueda del nodo y reencadenamiento de punteros.

---

## 🔍 Validaciones implementadas

- Entrada no numérica en menú o número de equipo → limpieza del buffer con `getchar()` y mensaje de error.
- Número de equipo fuera del rango 1–12 → rechazo con mensaje.
- Intento de alta duplicada → aviso sin inserción.
- Intento de baja de equipo inexistente → aviso informativo.
- `malloc` fallido → mensaje de error sin crash.

---

## 📌 Contexto académico

Este programa fue desarrollado como parte de las actividades del módulo de **Programación Estructurada** de la **Licenciatura en Tecnologías de la Información y Comunicación (LTIC)**, aplicando el escenario integrador **SIG-Conecta**: conectividad digital en comunidades rurales de México.

**Temas cubiertos:**
- Estructuras (`struct`) en C
- Listas enlazadas simples con memoria dinámica (`malloc` / `free`)
- Gestión del tiempo con `<time.h>`
- Validación de entrada estándar

---

## 👤 Autor

Marvin Valdez Ingeniero en Sistemas, Electronica y Electromecanica | Redes | Ciberseguridad | IA
GitHub: [@gessniio](https://github.com/gessniio)  
Plataforma educativa: **AUTENTICA_MODULO2 / BLOQUE 2 / SEGUNDO SEMESTRE (ESTRUCTURA DE DATOS)**

---

## 📄 Licencia

Este proyecto es de uso educativo y puede reutilizarse libremente con fines académicos.
