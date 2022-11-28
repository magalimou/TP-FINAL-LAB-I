#ifndef PEDIDO_H_INCLUDED
#define PEDIDO_H_INCLUDED

typedef struct
{
    char producto[20];
    int precio;
    int color; //1-BLANCO // 2-NEGRO // 3-BEIGE // 4-AZUL // 5-MARRON
    int talle; // 1-S // 2-M // 3-L // 4-XL //
    int estado; // 1 para activo // 0 para cancelado
    char nombreUsuario[20];

} Pedido;

Pedido cargaPedido(char nombreUsu[]);
void cargaPedidosArchivo(char nombreArchiPedido[], char nombreUsu[]);
void mostrarPedido(Pedido a);
void mostrarPedidosActivosUsuario (char nombreArchi[], char nombreUsu[]);
void cancelarPedido (char archiPedidos[], char nombreUsu[], char produc[], int color);
int precioTotalAPagar (char nomArchiPedido[], char nombreUsu[]);
void mostrarPedidosCancelados (char nombreArchi[], char nombreUsu[]);
void mostrarNombreyApellido (char nombreUsu[]);
void verPedidosActivos(char archiPedidos[]);
void verPedidosCancelados(char archiPedidos[]);
void mostrarPedidosProd(char nombreArchi[]);
void mostrarPedidosXprecio(char archiPedidos[], int precio); //pedidos activos

#endif // PEDIDO_H_INCLUDED
