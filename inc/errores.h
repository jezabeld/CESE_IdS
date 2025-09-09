#ifndef ERRORES_H
#define ERRORES_H

#define registrarDebug(msg) registrarMsgError(DEBUG, __func__, __LINE__, msg);
#define registrarInfo(msg) registrarMsgError(INFO, __func__, __LINE__, msg);
#define registrarWarning(msg) registrarMsgError(WARNING, __func__, __LINE__, msg);
#define registrarError(msg) registrarMsgError(ERROR, __func__, __LINE__, msg);

typedef enum gravedad_e {
    DEBUG,   //!< Mensajes de depuración
    INFO,    //!< Mensajes informativos
    WARNING, //!< Advertencias
    ERROR    //!< Mensajes de error
} gravedad_t;

/**
 * @brief Funcion para registrar un mensaje en la biblioteca de errores.
 *
 * @param gravedad La gravedad del mensaje (DEBUG, INFO, WARNING, ERROR).
 * @param funcion El nombre de la función que realiza el registro del error.
 * @param linea La línea de código donde se registra el error.
 * @param mensaje El mensaje de error a registrar.
 */
void registrarMsgError(gravedad_t gravedad, const char* funcion, int linea, const char* mensaje);

#endif // ERRORES_H
