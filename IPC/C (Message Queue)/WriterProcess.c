// Programa en C para Cola de Mensajes (Proceso Escritor)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 10

// estructura para la cola de mensajes
struct mesg_buffer {
    long mesg_type;       // tipo de mensaje
    char mesg_text[100];  // contenido del mensaje
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
    message.mesg_type = 1;

    // Solicitar al usuario que escriba los datos
    printf("Escribe los datos: ");
    fgets(message.mesg_text, MAX, stdin);

    // msgsnd para enviar el mensaje
    msgsnd(msgid, &message, sizeof(message), 0);

    // mostrar el mensaje enviado
    printf("Datos enviados: %s \n", message.mesg_text);

    return 0;
}
