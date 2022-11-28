#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <ctype.h>
#include <conio.h>
#include "Catalogo.h"
#include "Pedido.h"
#include "Menu.h"

#define CAT "Catalogo.bin"
#define PED "Pedidos.bin"
#define USU "Usuarios.bin"

/*****************************
 * \brief MENU PRINCIPAL
 * \return VOID
 ****************************/

void Menu ()
{
    printf(" _________________________________________\n");
    printf("|                 <<MENU>>                |\n");
    printf("| 1. REGISTRAR USUARIO                    |\n");
    printf("| 2. INICIAR SESION COMO USUARIO          |\n");
    printf("| 3. USAR COMO ADMINISTRADOR              |\n");
    printf("|_________________________________________|\n");

    printf("\nIngrese el numero de la opcion que desea abrir: ");

}

/*****************************
 * \brief MENU DE USUARIO
 * \return VOID
 ****************************/

void menuUsuario()
{
    printf(" _________________________________________\n");
    printf("|              <<MENU USUARIO>>           |\n");
    printf("|                                         |\n");
    printf("| 1. VER CATALOGO Y HACER PEDIDO          |\n");
    printf("| 2. VER PEDIDOS                          |\n");
    printf("| 3. CANCELAR PEDIDO                      |\n");
    printf("| 4. CAMBIAR CONTRASENIA                  |\n");
    printf("|_________________________________________|\n");

    printf("\nIngrese el numero de la opcion que desea abrir: ");
}

/*************************************
 * \brief MENU PARA EL ADMINISTRADOR
 * \return VOID
 *************************************/

void menuAdministrador()
{
    printf(" _________________________________________\n");
    printf("|          <<MENU ADMINISTRADOR>>         |\n");
    printf("|                                         |\n");
    printf("| 1. MODIFICAR CATALOGO                   |\n");
    printf("| 2. VER PEDIDOS                          |\n");
    printf("|_________________________________________|\n");

    printf("\nIngrese el numero de la opcion que desea abrir: ");

}

/**********************************
 * \brief MENU MODIFICAR CATALOGO
 * \return VOID
 *********************************/

void menuModificarCatalogo()
{
    printf(" _____________________________________________\n");
    printf("|          <<MENU MODIFICAR CATALOGO>>        |\n");
    printf("|                                             |\n");
    printf("| 1. AGREGAR PRODUCTO                         |\n");
    printf("| 2. MODIFICAR PRODUCTO                       |\n");
    printf("| 3. ELIMINAR PRODUCTO                        |\n");
    printf("|_____________________________________________|\n");

    printf("\nIngrese el numero de la opcion que desea abrir: ");
}

/*****************************
 * \brief MENU VER PEDIDOS
 * \return VOID
 ****************************/

void menuVerPedidoAdmin()
{
    printf(" _________________________________________\n");
    printf("|       <<MENU VER PEDIDOS ADMIN>>        |\n");
    printf("|                                         |\n");
    printf("| 1. VER PEDIDOS ACTIVOS                  |\n");
    printf("| 2. VER FORMAS DE PAGO                   |\n");
    printf("| 3. VER PEDIDOS CANCELADOS               |\n");
    printf("| 4. VER PEDIDOS SEGUN PRODUCTO           |\n");
    printf("| 5. VER PEDIDOS MAYORES A 'X' PRECIO     |\n");
    printf("|_________________________________________|\n");

    printf("\nIngrese el numero de la opcion que desea abrir: ");

}
