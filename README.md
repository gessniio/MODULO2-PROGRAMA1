# 🖥️ PAD-Bienestar — Sistema de Gestión de Sesiones

> **Proyecto SIG-Conecta** · Punto de Acceso Digital para comunidades rurales de alta marginación

Dos versiones funcionales del mismo sistema, escritas en **lenguaje C**, que gestionan las sesiones activas en un punto PAD-Bienestar mediante una **lista enlazada simple con memoria dinámica**.

---

## 📁 Estructura del repositorio

```
pad-bienestar/
├── pad_formal.c       # Versión académica / producción
├── pad_humor.c        # Versión comentada con humor didáctico
└── README.md
```

---

## 🔀 Comparativa de versiones

| Característica | `pad_formal.c` | `pad_humor.c` |
|---|---|---|
| **Estilo** | Académico / producción | Didáctico con humor |
| **Comentarios** | Técnicos y precisos | Narrativos y accesibles |
| **Datos del nodo** | `num_equipo`, `hora_inicio` | `numEquipo`, `usuario`, `horaInicio` |
| **Campo usuario** | ❌ No incluye | ✅ Captura nombre del usuario |
| **Convención de nombres** | `snake_case` | `camelCase` |
| **Mensajes al usuario** | Formales con prefijos `[OK]`, `[ERROR]` | Informales y descriptivos |
| **Menú** | Con bordes ASCII artísticos | Lista plana numerada |
| **Audiencia objetivo** | Entrega académica / evaluación | Aprendizaje y referencia didáctica |

---

## ⚙️ Funcionamiento general

Ambas versiones implementan las mismas cuatro operaciones sobre una **lista enlazada dinámica**:

```
┌──────────┐    ┌──────────┐    ┌──────────┐
│ Equipo 3 │───▶│ Equipo 7 │───▶│ Equipo 1 │───▶ NULL
│ 09:15:02 │    │ 10:03:44 │    │ 10:47:11 │
└──────────┘    └──────────┘    └──────────┘
     ▲
   cabeza
```

### Operaciones disponibles

| Opción | Función | Descripción |
|--------|----------|-------------|
| `1` | Alta de sesión | Crea un nodo con `malloc()` e inserta al frente |
| `2` | Baja de sesión | Busca el equipo, desconecta el nodo y libera con `free()` |
| `3` | Mostrar sesiones | Recorre la lista de cabeza a `NULL` e imprime cada nodo |
| `4` | Salir | Libera todos los nodos antes de cerrar (`liberar_lista`) |

---

## 🔧 Compilación y ejecución

Requiere cualquier compilador compatible con **C99** o superior (`gcc`, `clang`, `MinGW`).

### Versión formal

```bash
gcc -o pad_formal pad_formal.c
./pad_formal
```

### Versión con humor

```bash
gcc -o pad_humor pad_humor.c
./pad_humor
```

### En Windows (MinGW)

```cmd
gcc -o pad_formal.exe pad_formal.c
pad_formal.exe
```

> **Nota:** No se requieren librerías externas. Solo se usan `stdio.h`, `stdlib.h`, `string.h` y `time.h` de la biblioteca estándar de C.

---

## 💡 Conceptos clave implementados

- **Lista enlazada simple** — estructura `Sesion` con puntero `*siguiente`
- **Memoria dinámica** — `malloc()` en el alta, `free()` en la baja y al salir
- **Inserción al frente** — O(1), el nuevo nodo apunta a la antigua cabeza
- **Eliminación con reenlace** — se ajustan punteros anterior/actual para desconectar el nodo
- **Recorrido iterativo** — desde `cabeza` hasta `NULL` para mostrar o liberar la lista
- **Validación de entrada** — rango 1–12 para equipos, limpieza de buffer de entrada
- **Hora del sistema** — capturada con `time()` + `strftime()` en formato `HH:MM:SS`

---

## 🗺️ Contexto del proyecto

Este sistema forma parte del escenario académico **SIG-Conecta**, una propuesta de infraestructura de conectividad con energía solar para comunidades rurales de alta marginación en México. El módulo PAD-Bienestar simula la gestión de hasta **12 equipos de cómputo** en un punto de acceso comunitario.

---

## 👤 Autor

**Marvin** · [@gessniio](https://github.com/gessniio)  
Ingeniería en Sistemas · LTIC — Programación Estructurada  
Plataforma educativa: **AUTENTICA_4**

---

## 📄 Licencia

Uso educativo. Libre para referencia académica y didáctica.
