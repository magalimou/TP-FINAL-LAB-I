#ifndef VARIAS_H_INCLUDED
#define VARIAS_H_INCLUDED

int validarNombreUsu (char nombre[]);
int validarContrasenia (char contra[]);
int verificarColor (int color);
int verificarTalle (int talle);
int inicSesionAdministrador();
int validarAdministrador (char nombreAdm[], int password);
void mostrarEstadoPedido (int estado);
void mostrarColor (int color);
void mostrarTalle (int talle);
int convertirColor (char color[]);

#endif // VARIAS_H_INCLUDED
