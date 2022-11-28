#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <ctype.h>
#include <conio.h>
#include "Pedido.h"

#define CAT "Catalogo.bin"
#define PED "Pedidos.bin"
#define USU "Usuarios.bin"

/***************************************
 * \brief CARGA UN PEDIDO
 * \param NOMBRE DE USUARIO
 * \return PEDIDO
 **************************************/

Pedido cargaPedido(char nombreUsu[])
{
    Pedido a;
    int yesProduct, verColor, verTalle;

    do
    {
        printf("Ingrese nombre del producto que desea pedir:\n");
        fflush(stdin);
        gets(a.producto);

        yesProduct= verificarProducto(CAT, a.producto);

    }while(yesProduct == 0);

    a.precio = buscarPrecioProducto(CAT, a.producto);

    do
    {
        printf("Ingrese el numero del color\n");
        scanf("%d", &a.color);

        verColor = verificarColor(a.color);

    }while(verColor == 0);

    do
    {
        printf("Ingrese opcion del talle (numero)\n");
        scanf("%d", &a.talle);

        verTalle = verificarTalle(a.talle);

    }while(verTalle == 0);

    a.estado = 1;

    strcpy(a.nombreUsuario, nombreUsu);

    return a;
}

/***************************************
 * \brief CARGA PEDIDO EN ARCHIVO
 * \param NOMBRE DE ARCHIVO
 * \param NOMBRE DE USUARIO
 * \return VOID
 **************************************/

void cargaPedidosArchivo(char nombreArchiPedido[], char nombreUsu[] )
{
    FILE*buffer;
    char continuar = 's';
    Pedido a;

    buffer= fopen(nombreArchiPedido, "ab");
    if(buffer!= NULL)
    {
        while(continuar == 's')
        {
            a= cargaPedido(nombreUsu);
            fwrite(&a, sizeof(Pedido), 1, buffer);

            printf("Desea seguir cargando pedidos? (s/n) \n");
            fflush(stdin);
            scanf("%c", &continuar);
        }
        fclose(buffer);
    }
}

/***************************************
 * \brief MUESTRA UN PEDIDO
 * \param PEDIDO
 * \return VOID
 **************************************/

void mostrarPedido(Pedido a)
{
    printf(" ________________________________________________________\n");
    printf("| PRODUCTO: %s                                           \n", a.producto);
    printf("| PRECIO: %i                                             \n", a.precio);

    mostrarColor(a.color);
    mostrarTalle(a.talle);
    mostrarEstadoPedido(a.estado);
    mostrarNombreyApellido(a.nombreUsuario);

    printf("|________________________________________________________\n");
}

/***********************************************
 * \brief MUESTRA NOMBRE Y APELLIDO DE USUARIO
 * \param NOMBRE DE USUARIO
 * \return VOID
 **********************************************/

void mostrarNombreyApellido (char nombreUsu[])
{
    buscarNYAenArchiUsuario(USU, nombreUsu);
}

/**************************************************
 * \brief MUESTRA PEDIDOS ACTIVOS DE UN USUARIO
 * \param NOMBRE DE ARCHIVO
 * \param NOMBRE DE USUARIO
 * \return VOID
 *************************************************/

void mostrarPedidosActivosUsuario(char nombreArchi[], char nombreUsu[])
{
    FILE*buffer;
    Pedido a;

    buffer= fopen(nombreArchi, "rb");
    if(buffer!= NULL)
    {
        while(fread(&a, sizeof(Pedido), 1, buffer)> 0)
        {
            if(strcmp(a.nombreUsuario, nombreUsu) == 0)
            {
                if(a.estado == 1)
                {
                    mostrarPedido(a);
                }
            }
        }
        fclose(buffer);
    }
}

/****************************************************
 * \brief CANCELA UN PEDIDO
 * \param NOMBRE DE ARCHIVO PEDIDOS
 * \param NOMBRE DE USUARIO
 * \param NOMBRE DE PRODUCTO
 * \param NOMBRE DE COLOR
 * \return VOID
 *************************************************/

void cancelarPedido (char archiPedidos[], char nombreUsu[], char produc[], int color)
{
    Pedido a;
    char stop = 's';
    int numColor;

    if (color != 0)
    {
        FILE*buffer = fopen(archiPedidos, "r+b");
        if(buffer != NULL)
        {
            while(stop == 's' && fread(&a, sizeof(Pedido), 1, buffer)> 0)
            {
                if(strcmp(a.nombreUsuario, nombreUsu) == 0 && strcmpi(a.producto, produc) == 0)
                {
                    if(a.color = color)
                    {
                        stop = 'n';
                        fseek(buffer, (-1)*sizeof(Pedido), SEEK_CUR);
                        fread (&a, sizeof (Pedido), 1, buffer);

                        a.estado = 0;

                        fseek(buffer, (-1)*sizeof(Pedido), SEEK_CUR);
                        fwrite(&a, sizeof(Pedido), 1, buffer);
                    }
                }
            }
            fclose(buffer);
        }
    }else{
        printf("Opcion de color ingresada inexistente. No se puede cancelar el pedido\n");
    }
}

/**************************************************
 * \brief MUESTRA PEDIDOS CANCELADOS DE UN USUARIO
 * \param NOMBRE DE ARCHIVO
 * \param NOMBRE DE USUARIO
 * \return VOID
 *************************************************/

void mostrarPedidosCancelados (char nombreArchi[], char nombreUsu[])
{
    FILE*buffer;
    Pedido a;

    buffer= fopen(nombreArchi, "rb");
    if(buffer!= NULL)
    {
        while(fread(&a, sizeof(Pedido), 1, buffer)> 0)
        {
            if(strcmp(a.nombreUsuario, nombreUsu) == 0)
            {
                if(a.estado == 0)
                {
                    mostrarPedido(a);
                }
            }
        }
        fclose(buffer);
    }
}

/*****************************************
 * \brief PRECIO TOTAL A PAGAR
 * \param NOMBRE DE ARCHIVO PEDIDOS
 * \param NOMBRE DE USUARIO
 * \return TOTAL A PAGAR
 *****************************************/

int precioTotalAPagar (char nomArchiPedido[], char nombreUsu[])
{
    Pedido a;
    int total = 0;

    FILE*buffer = fopen(nomArchiPedido, "rb");
    if(buffer != NULL)
    {
        while(fread(&a, sizeof(Pedido), 1, buffer) > 0)
        {
            if(strcmp(a.nombreUsuario, nombreUsu) == 0 && a.estado == 1 )
            {
                total = a.precio + total;
            }
        }
        fclose(buffer);
    }
    return total;
}

/*****************************************
 * \brief VER PEDIDOS ACTIVOS
 * \param NOMBRE DE ARCHIVO PEDIDOS
 * \return VOID
 ****************************************/

void verPedidosActivos(char archiPedidos[])
{
    FILE*buffer;
    Pedido a;

    buffer= fopen(archiPedidos, "rb");
    if(buffer!= NULL)
    {
        while(fread(&a, sizeof(Pedido), 1, buffer)> 0)
        {
            if(a.estado == 1)
            {
                mostrarPedido(a);
            }
        }
        fclose(buffer);
    }
}

/*****************************************
 * \brief VER PEDIDOS CANCELADOS
 * \param NOMBRE DE ARCHIVO PEDIDOS
 * \return VOID
 ****************************************/

void verPedidosCancelados(char archiPedidos[])
{
    FILE*buffer;
    Pedido a;

    buffer= fopen(archiPedidos, "rb");
    if(buffer!= NULL)
    {
        while(fread(&a, sizeof(Pedido), 1, buffer)> 0)
        {
            if(a.estado == 0)
            {
                mostrarPedido(a);
            }
        }
        fclose(buffer);
    }
}

/**********************************************
 * \brief MUESTRA LOS PEDIDOS SEGUN PRODUCTO
 * \param NOMBRE DE ARCHIVO PEDIDOS
 * \return VOID
 *********************************************/

void mostrarPedidosProd(char nombreArchi[])
{
    FILE*buffer;
    Pedido a;
    char prod[20];

    printf("Ingrese un producto para ver los pedidos del mismo: ");
    fflush(stdin);
    gets(prod);

    buffer= fopen(nombreArchi, "rb");
    if(buffer!= NULL)
    {
        while(fread(&a, sizeof(Pedido), 1, buffer)> 0)
        {
            if(strcmpi(a.producto, prod) == 0 && a.estado == 1)
            {
                mostrarPedido(a);
            }
        }
        fclose(buffer);
    }
}

/*****************************************
 * \brief MUESTRA PEDIDOS SEGUN UN PRECIO
 * \param NOMBRE DE ARCHIVO PEDIDOS
 * \param PRECIO
 * \return VOID
 ****************************************/

void mostrarPedidosXprecio(char archiPedidos[], int precio) //pedidos activos
{
    Pedido a;
    char prod[20];
    FILE*buffer;

    printf(" ________________________________________________________________\n");
    printf("             <<PEDIDOS MAYORES O IGUALES A %d >>                 \n", precio);
    printf(" ________________________________________________________________\n");

    buffer= fopen(archiPedidos, "rb");
    if(buffer!= NULL)
    {
        while(fread(&a, sizeof(Pedido), 1, buffer)> 0)
        {
            if(a.precio >= precio && a.estado == 1)
            {
                mostrarPedido(a);
            }
        }
        fclose(buffer);
    }
}
