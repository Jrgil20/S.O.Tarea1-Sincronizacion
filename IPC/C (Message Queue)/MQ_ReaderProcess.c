// Programa en C para Cola de Mensajes (Proceso Lector)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// estructura para la cola de mensajes
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key;
    int msgid;

    // ftok para generar una clave única
    key = ftok("progfile", 65);

    // msgget crea una cola de mensajes
    // y devuelve el identificador
    msgid = msgget(key, 0666 | IPC_CREAT);

    // msgrcv para recibir el mensaje
    // el tercer parámetro es el tamaño del mensaje
    // el cuarto parámetro es el tipo de mensaje que queremos recibir
    // el quinto parámetro son las opciones de recepción (0 para esperar hasta que llegue un mensaje)
    msgrcv(msgid, &message, sizeof(message), 1, 0);

    // mostrar el mensaje recibido
    printf("Datos recibidos: %s \n", 
                    message.mesg_text);

    // destruir la cola de mensajes
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

//https://www.geeksforgeeks.org/ipc-using-message-queues/