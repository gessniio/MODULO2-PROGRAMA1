🖥️ Sistema de Gestión de Sesiones — PAD-Bienestar / SIG-Conecta
Sistema en C para el registro y control de sesiones activas en puntos de acceso digitales comunitarios del proyecto SIG-Conecta.


📋 Descripción
Este programa implementa un sistema de gestión de sesiones de equipos para el punto PAD-Bienestar, nodo del proyecto ficticio SIG-Conecta — una iniciativa de conectividad solar para comunidades rurales de alta marginación en México.
El programa utiliza una lista enlazada dinámica en C para registrador, eliminar y consultar las sesiones activas de hasta 12 equipos de cómpputo. Cada sesión almacena el número de equipo y la hora exacta de inicio, capiturada automáticamente del sistema operativo.


🛠️ Características
FuncionalidadDescripción✅ Alta de sesiónRegistra un equipo con hora de inicio automática❌ Baja de sesiónFinaliza y elimina una sesión de la lista📋 Mostrar sesionesLista todos los equipos con sesión activa🔒 ValidacionesRango 1–12, duplicados, entrada inválida🧹 Liberación de memoriafree() explícito al salir o dar de baja
