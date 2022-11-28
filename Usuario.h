#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

typedef struct
{
    int forma; //0 efectivo || 1 tarjeta
    int precioTotal;
    int desc; //porcentaje de descuento
    int totalConDesc;

} Pago;

typedef struct
{
    char nombreYApellido[40];
    char nombreUsuario[20];
    int contrasenia;
    Pago p;

} Usuario;

Usuario cargarUsuario ();
void guardarUsuarioArchivo (char archivoUsu[]);
int usuarioUnico (char archiusu[], char nombre[]);
int buscarUsuario( char archiUsuario[], int contra, char usu[]);
void buscarNYAenArchiUsuario (char archiUsuario[], char nomUsuBuscar[]);
void mostrarUsuario (Usuario a);
void mostrarUsuarioEspecifico(char archivoUsuarios[], char nombreUsu[]);
void cambiarContraUsuario(char archiUsuario[], char nombreUsu[]);

Pago cargaPago( char archiPedido[], char nombreUsu[]);
void cargaPagoArchiUsuario (char archiUsuario[], char archiPedido[], char nombreUsu[]);
void mostrarPago (Pago a);
void mostrarArchivoUsuPago (char archivoUsu[], char nombreUsuario[]);
Pago descuento( int total, int forma);
int buscarFormaPago (char archiUsuario[], char nombreUsu[]);
void actualizarPago (char archiUsuario[], int total, char nombreUsu[], int forma);
void verPago(Pago a);
void mostrarPagosConNombre(char archiUsuario[]);

#endif // USUARIO_H_INCLUDED
