#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* -------------------------------------------------------
   Aquí definimos nuestra sesión. Es como una ficha de
   registro, pero sin tener que buscar pluma.
   ------------------------------------------------------- */
typedef struct Sesion {
    int numEquipo;          /* Número del equipo (del 1 al 12 */
    char usuario[50];       /* Nombre del usuario que llegó a "solo un momento" */
    char horaInicio[20];    /* Hora en que empezó la sesión */
    struct Sesion *siguiente; 
} Sesion;

/* La cabeza de la lista: empieza vacía
Sesion *cabeza = NULL;

/* -------------------------------------------------------
   Función para obtener la hora actual como texto.
   ------------------------------------------------------- */
void obtenerHora(char *buffer) {
    time_t ahora = time(NULL);
    struct tm *t = localtime(&ahora);
    strftime(buffer, 20, "%H:%M:%S", t);
}

/* -------------------------------------------------------
   ALTA DE SESIÓN
   Llega un usuario, le pedimos su nombre y el equipo
   que va a usar. Si el equipo ya está ocupado, mala suerte.
   Usamos malloc para pedirle memoria al sistema operativo
   (él decide si nos la da con buena cara o no).
   ------------------------------------------------------- */
void altaSesion() {
    int numEquipo;
    char usuario[50];

    printf("\n--- NUEVA SESION ---\n");

    /* Pedimos número de equipo y validamos que no sea un número inventado */
    printf("Ingrese numero de equipo (1-12): ");
    if (scanf("%d", &numEquipo) != 1 || numEquipo < 1 || numEquipo > 12) {
        printf("Numero de equipo invalido. Solo del 1 al 12, no somos NASA.\n");
        while (getchar() != '\n'); /* Limpiamos el buffer de entrada malportado */
        return;
    }
    while (getchar() != '\n');

    /* Revisamos si ese equipo ya tiene dueño en la lista */
    Sesion *temp = cabeza;
    while (temp != NULL) {
        if (temp->numEquipo == numEquipo) {
            printf("El equipo %d ya tiene una sesion activa. Alguien se le adelanto.\n", numEquipo);
            return;
        }
        temp = temp->siguiente;
    }

    /* Pedimos el nombre del usuario  */
    printf("Ingrese nombre del usuario: ");
    fgets(usuario, 50, stdin);
    usuario[strcspn(usuario, "\n")] = '\0'; /* Le quitamos el salto de línea que se coló */

    /* Aquí le pedimos memoria al sistema.  */
    Sesion *nueva = (Sesion *)malloc(sizeof(Sesion));
    if (nueva == NULL) {
        /* Si malloc falla, el sistema anda muy ocupado o muy cansado */
        printf("Error: no hay memoria disponible. Apague y vuelva a intentar.\n");
        return;
    }

    /* Llenamos los datos de la nueva sesión */
    nueva->numEquipo = numEquipo;
    strcpy(nueva->usuario, usuario);
    obtenerHora(nueva->horaInicio);
    nueva->siguiente = NULL;

    /* Insertamos al inicio de la lista (el más nuevo manda) */
    nueva->siguiente = cabeza;
    cabeza = nueva;

    printf("Sesion registrada: Equipo %d - Usuario: %s - Hora: %s\n",
           nueva->numEquipo, nueva->usuario, nueva->horaInicio);
}

/* -------------------------------------------------------
   BAJA DE SESIÓN
   El usuario terminó, o se fue sin avisar .
   Buscamos su equipo, lo sacamos de la lista y liberamos
   la memoria con free. El sistema recupera lo suyo.
   ------------------------------------------------------- */
void bajaSesion() {
    int numEquipo;

    printf("\n--- FINALIZAR SESION ---\n");
    printf("Ingrese numero de equipo a dar de baja (1-12): ");

    if (scanf("%d", &numEquipo) != 1 || numEquipo < 1 || numEquipo > 12) {
        printf("Ese numero no existe en este universo (ni en el 1-12).\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    Sesion *actual = cabeza;
    Sesion *anterior = NULL;

    /* Recorremos la lista buscando el equipo.  */
    while (actual != NULL) {
        if (actual->numEquipo == numEquipo) {

            /* Reensamblamos la cadena sin este nodo  */
            if (anterior == NULL) {
                cabeza = actual->siguiente; /* Era el primero de la lista */
            } else {
                anterior->siguiente = actual->siguiente; 
            }

            printf("Sesion del equipo %d finalizada. Adios, %s.\n",
                   actual->numEquipo, actual->usuario);

            /* Liberamos la memoria. */
            free(actual);
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    /* Si llegamos aquí, ese equipo no estaba en la lista */
    printf("No se encontro sesion activa para el equipo %d. ¿Ya lo dio de baja sin avisar?\n", numEquipo);
}

/* -------------------------------------------------------
   MOSTRAR SESIONES ACTIVAS
   Recorremos toda la lista y mostramos quién está
   usando qué. 
   ------------------------------------------------------- */
void mostrarSesiones() {
    printf("\n--- SESIONES ACTIVAS ---\n");

    if (cabeza == NULL) {
        /* La lista está vacía.  */
        printf("No hay sesiones activas en este momento. El sistema descansa.\n");
        return;
    }

    Sesion *temp = cabeza;
    int contador = 0;

    /* Recorremos nodo por nodo hasta llegar al final */
    while (temp != NULL) {
        contador++;
        printf("[%d] Equipo: %-3d | Usuario: %-30s | Hora inicio: %s\n",
               contador, temp->numEquipo, temp->usuario, temp->horaInicio);
        temp = temp->siguiente; /* Avanzamos al siguiente nodo */
    }

    printf("Total de sesiones activas: %d de 12 equipos.\n", contador);
}

/* -------------------------------------------------------
   LIMPIAR LISTA AL SALIR
   Antes de cerrar el programa, liberamos toda la memoria
   que usamos. 
   ------------------------------------------------------- */
void liberarLista() {
    Sesion *temp;
    while (cabeza != NULL) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp); /* Adiós, nodo. Fue un placer. */
    }
}

/* -------------------------------------------------------
   MAIN: El jefe de todo. Muestra el menú y decide
   qué función llamar. Si el usuario elige mal, se lo decimos
   sin drama.
   ------------------------------------------------------- */
int main() {
    int opcion;

    printf("=============================================\n");
    printf("   SISTEMA PAD-BIENESTAR - SESIONES ACTIVAS  \n");
    printf("=============================================\n");

    do {
        /* El menú de opciones */
        printf("\n1. Dar de alta una sesion\n");
        printf("2. Dar de baja una sesion\n");
        printf("3. Mostrar sesiones activas\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            /* Si el usuario escribe letras en lugar de números */
            printf("Opcion invalida. Se esperaba un numero, no una novela.\n");
            while (getchar() != '\n');
            opcion = 0;
            continue;
        }
        while (getchar() != '\n');

        /* Switch: cada caso llama a su función correspondiente */
        switch (opcion) {
            case 1:
                altaSesion();
                break;
            case 2:
                bajaSesion();
                break;
            case 3:
                mostrarSesiones();
                break;
            case 4:
                /* Salida ordenada: limpiamos antes de irnos */
                liberarLista();
                printf("Sistema cerrado. Hasta la proxima sesion.\n");
                break;
            default:
                printf("Opcion no reconocida. El menu tiene 4 opciones, no 47.\n");
        }

    } while (opcion != 4); /* Repetimos hasta que el usuario quiera salir */

    return 0;
}