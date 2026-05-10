🖥️ Sistema de Gestión de Sesiones — PAD-Bienestar / SIG-Conecta

Sistema en C para el registro y control de sesiones activas en puntos de acceso digitales comunitarios del proyecto SIG-Conecta.


📋 Descripción
Este programa implementa un sistema de gestión de sesiones de equipos para el punto PAD-Bienestar, nodo del proyecto ficticio SIG-Conecta — una iniciativa de conectividad solar para comunidades rurales de alta marginación en México.
El programa utiliza una lista enlazada dinámica en C para registrador, eliminar y consultar las sesiones activas de hasta 12 equipos de cómpppputo. Cada sesión almacena el número de equipo y la hora exacta de inicio, capiturada automáticamente del sistema operativo.

└── README.md # Este archivo
FuncionalidadDescripción✅ Alta de sesiónRegistra un equipo con hora de inicio automática❌ Baja de sesiónFinaliza y elimina una sesión de la lista📋 Mostrar sesionesLista todos los equipos con sesión activa🔒 ValidacionesRango 1–12, duplicados, entrada inválida🧹 Liberación de memoriafree() explícito al salir o dar de baja

📁 Estructura del proyecto
pad-bienestar/
│
├── sesiones.c # Código fuente principal
GitHub: @gessnio

⚙️ Requisitos

Compilador: gcc (GCC 9 o superior recomendado)
Sistema operativo: Linux, macOS o Windows (con MinGW/WSL)
Estandar C: C99 o C11


🚀 Compilación y ejecución
Linux / macOS
bashgcc -o sesiones sesiones.c
. . . . . ./sesiones
Windows (MinGW)
bashgcc -o sesiones.exe sesiones.c
sesiones.exe
Con advertencias activadas (recomendado)
bashgcc -Muro -Wextra -o sesiones sesiones.c

🖱️ Uso del hombre
Al ejecutar el programa verás el seguimiento menor
 +------------------------------------------+
 | SISTEMA - MARVIN / MAYRA |
 +------------------------------------------+
 | 1. Dar de alta una sesión |
 | 2. Dar de baja una sesión |
 | 3. Mostrar sesiones activas |
 | 4. Salir |
 +------------------------------------------+
Opinión 1 — Alta: Solicita el número de equipo (1–12). Si ya tienes sesión activa, muerte un aviso y no duplica el registro.
Opinión 2 — Baja: Solicitud el número de equipo a liberar. Elimina el nodo, justa los jugadores y libera la memoria con free().
Opinión 3 — Mostrar: Recorre la lista e imprime equipo, hora de inicio y contenido total.
Opinión 4 — Salir: Llama a liberar_lista() para limpiar toda la memoria antes de cerrar.

🧠 Estructura de datos
ctypedef estructura Sesión {
 int num_equipo; // Identificador del equipo (1–12)
 char hora_inicio[20]; // Hora de inicio en formato HH:MM:SS
 struct Sesion *siguiente; // Puntero al seguimiento nodo
} Sesion;
La lista cree hacia el frente: cada nueva sesión se inserta como la nueva cabeza. La eliminación es lineal con bolsa del nodo y reencadenamiento de punteros.

🔍 Validaciones implementadas

Entrada no numérica en menú o número de equipo → limpieza del buffer con getchar() y mensaje de error.
Número de equipo fuera del rango 1–12 → rechacio con mensaje.
Intento de alta duplicada → aviso sin inserción.
Intento de baja de equipo inexistente → aviso informativo.
malloc fallado → mensaje de error sin crash.


📌 Contexto académico
Este programa fue desarrollado como parte de las actividades del módulo de Programación Estructurada de la Licenciatura en Tecnologías de la Información y Comunicación (LTIC), aplicando el escenario integrador SIG-Conecta: conectividad digital en comunidades rurales de México.
Temas cubiertos:

Estructuras (estructura) en C
Listas enlazadas simples con memoria dinámica (malloc / gratis)
Gestión del tiempo con <time.h>
Validación de entrada estable


👤 Autor
Marvin — Ingeniero en Sistemas, Electrónica y Electromecánica
GitHub: @gessnio
Plataforma educativa: AUTENTICA_4
