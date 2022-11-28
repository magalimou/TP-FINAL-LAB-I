#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <ctype.h>
#include <conio.h>
#include "Catalogo.h"
#include "Pedido.h"
#include "Menu.h"
#include "varias.h"
#include "Usuario.h"

#define CAT "Catalogo.bin"
#define PED "Pedidos.bin"
#define USU "Usuarios.bin"

///TRABAJO PRACTICO FINAL LAB 1 
///MAGALI MOURIÑO

int main()
{
    int numSwitch;
    char continuar = 's';

    do
    {
        system("cls");
        system("COLOR 70");

        Menu();

        scanf("%d", &numSwitch);
        system("cls");

        switch(numSwitch)
        {
        case 1: /// OPCION CREAR USUARIO
        {
            system("cls");
            printf("\nCREANDO USUARIO...\n");

            guardarUsuarioArchivo(USU);

            system("pause");
            system("COLOR 7A");
            printf("\nUSUARIO REGISTRADO CON EXITO! :) \n");
        }
        break;

        case 2: /// OPCION INICIAR SESION COMO USUARIO
        {

            system("cls");

            printf("\nINICIANDO SESION....\n\n");

            char nomUsuario[20];
            char contraUsuario[8]; //se declara como char
            int contraValida, flag = 0, flag2 = 0;

            do
            {
                printf("Ingrese nombre de Usuario:\n");
                fflush(stdin);
                gets(nomUsuario);

                flag = validarNombreUsu(nomUsuario);

            }
            while(flag == 1);

            do
            {
                printf("Ingrese su contrasenia:\n");
                fflush(stdin);
                gets(contraUsuario);

                flag2 = validarContrasenia(contraUsuario);

            }
            while(flag2 == 0);

            contraValida = atoi(contraUsuario); //lo convierte en entero

            int existe;
            existe = buscarUsuario("Usuarios.bin", contraValida, nomUsuario);

            system("pause");

            if(existe != 0) //si esta registrado
            {
                int numSwitch2;
                char seguir = 's';

                do
                {
                    system("cls");
                    menuUsuario();
                    scanf("%d", &numSwitch2);

                    switch(numSwitch2)
                    {
                    case 1: /// VER CATALOGO Y HACER PEDIDO
                    {
                        system("cls");
                        mostrarCatalogoCarta("Catalogo.bin");

                        char realizarP = 's';

                        printf("\nDesea realizar un pedido? (s/n) \n");
                        fflush(stdin);
                        scanf("%c", &realizarP);

                        if(realizarP == 's')
                        {
                            cargaPedidosArchivo(PED, nomUsuario);

                            //SE PREGUNTA FORMA DE PAGO DE TODOS LOS PEDIDOS
                            cargaPagoArchiUsuario(USU, PED, nomUsuario);
                            mostrarArchivoUsuPago(USU, nomUsuario);
                        }
                    }
                    break;

                    case 2: /// VER PEDIDOS
                    {
                        system("cls");
                        mostrarPedidosActivosUsuario(PED, nomUsuario);
                        mostrarArchivoUsuPago(USU, nomUsuario);
                    }
                    break;

                    case 3: /// CANCELAR PEDIDO
                    {
                        system("cls");
                        char produc[20];
                        char colorCancelar[8];
                        int opcionColor;

                        char cont = 's';

                        while(cont == 's')
                        {
                            printf("Ingrese el nombre del producto que desea cancelar de sus pedidos: \n");
                            fflush(stdin);
                            gets(produc);

                            printf("Ingrese el nombre del color que desea cancelar de sus pedidos: \n");
                            fflush(stdin);
                            gets(colorCancelar);

                            opcionColor = convertirColor(colorCancelar);

                            cancelarPedido(PED, nomUsuario, produc, opcionColor);

                            printf("Desea cancelar otro pedido? (s/n) \n");
                            fflush(stdin);
                            scanf("%c", &cont);
                        }
                        printf(" ___________________________________________________________\n");
                        printf("|                   <<PEDIDOS CANCELADOS>>                  |\n");
                        printf("|___________________________________________________________|\n");

                        mostrarPedidosCancelados (PED, nomUsuario);

                        int total = precioTotalAPagar(PED, nomUsuario);

                        int forma = buscarFormaPago(USU, nomUsuario);

                        actualizarPago(USU, total, nomUsuario, forma);
                        mostrarArchivoUsuPago(USU, nomUsuario);
                    }
                    break;

                    case 4: /// CAMBIAR CONTRASEÑA USUARIO
                    {
                        system("cls");
                        cambiarContraUsuario(USU, nomUsuario);
                        mostrarUsuarioEspecifico(USU, nomUsuario);
                    }
                    break;

                    default:{
                        system("cls");
                        printf("Opcion no valida. Vuelva a intentar\n");
                    }
                    break;

                    }

                    printf("\nDesea seguir navegando como Usuario? (s/n) \n");
                    fflush(stdin);
                    scanf("%c", &seguir);

                }
                while(seguir == 's');

            }
            else{
                printf("Usuario y/o contrasenia incorrecta\n");
            }

        }
        break;

        case 3: /// OPCION USAR COMO ADMINISTRADOR
        {
            int acceso = 0;
            acceso = inicSesionAdministrador();

            system("pause");

            if (acceso == 0)
            {
                char sigo = 's';

                do
                {
                    system("cls");
                    int opcion;

                    menuAdministrador();
                    scanf("%d", &opcion);

                    switch(opcion)
                    {
                    case 1: ///MODIFICAR CATALOGO
                    {
                        system("cls");
                        int switchModCata;
                        char op = 's';

                        do
                        {
                            system("cls");
                            menuModificarCatalogo();
                            scanf("%d", &switchModCata);

                            switch(switchModCata)
                            {
                            case 1: /// AGREGAR PRODUCTO
                            {
                                system("cls");
                                printf("\n-------------AGREGAR PRODUCTO CATALOGO--------------\n\n");

                                agregarElemCatalogo(CAT);

                                Catalogo cata[30];
                                int validosCatalogo = 0;

                                validosCatalogo = FileToArray(CAT, cata, 30, validosCatalogo);

                                ordenarSeleccionCatalogoPrecio(cata, validosCatalogo);
                                copyArrayToFileCatalogo(CAT, cata, validosCatalogo);

                                mostrarCatalogoCarta(CAT);
                            }
                            break;

                            case 2: /// MODIFICAR PRODUCTO
                            {
                                system("cls");

                                char producModificar[20];
                                int existe;

                                printf("Ingrese el nombre del producto que desea modificar\n");
                                fflush(stdin);
                                gets(producModificar);

                                existe = verificarProducto (CAT, producModificar);

                                if(existe == 1)
                                {
                                  modificarCatalogo(CAT, producModificar);
                                }

                                mostrarCatalogoCarta(CAT);
                            }break;

                            case 3: /// ELIMINAR PRODUCTO
                            {
                                system("cls");
                                char eliminar[20];
                                char seguirr = 's';

                                while (seguirr == 's')
                                {
                                    printf("Ingrese el nombre del producto que desea eliminar del Catalogo\n");
                                    fflush(stdin);
                                    gets(eliminar);

                                    eliminarProducto(CAT, eliminar);

                                    printf("Quiere eliminar otro producto? (s/n) \n");
                                    fflush(stdin);
                                    scanf("%c", &seguirr);
                                }

                                printf(" ___________________________________________________________\n");
                                printf("|                  <<CATALOGO ACTUALIZADO>>                 |\n");
                                printf("|___________________________________________________________|\n");

                                mostrarCatalogoCarta(CAT);

                            }break;

                            default:{
                                system("cls");
                                printf("Opcion no disponible. Intente con otra\n");
                            }break;

                            }
                            printf("\nDesea seguir modificando el catalogo? (s/n) \n");
                            fflush(stdin);
                            scanf("%c", &op);

                        }while (op == 's');

                    }break;

                    case 2: ///VER PEDIDOS
                    {
                        int switchVerPedido;
                        char c = 's';

                        do{
                            system("cls");

                            menuVerPedidoAdmin();
                            scanf("%d", &switchVerPedido);

                            switch(switchVerPedido)
                            {
                                case 1: /// VER PEDIDOS ACTIVOS
                                {
                                    system("cls");

                                    printf(" ___________________________________________________________\n");
                                    printf("|                   <<PEDIDOS ACTIVOS>>                     |\n");
                                    printf("|___________________________________________________________|\n");

                                    verPedidosActivos(PED);

                                }break;

                                case 2: /// VER FORMAS DE PAGO
                                {
                                    system("cls");
                                    mostrarPagosConNombre(USU);

                                }break;

                                case 3: /// VER PEDIDOS CANCELADOS
                                {
                                    system("cls");

                                    printf(" ___________________________________________________________\n");
                                    printf("|                   <<PEDIDOS CANCELADOS>>                  |\n");
                                    printf("|___________________________________________________________|\n");

                                    verPedidosCancelados(PED);

                                }break;

                                case 4: /// VER PEDIDOS SEGUN PRODUCTO
                                {
                                    system("cls");
                                    mostrarPedidosProd(PED);

                                }break;

                                case 5: /// VER PEDIDOS MAYORES A X PRECIO
                                {
                                    system("cls");

                                    int price;
                                    printf("Por favor, ingrese un precio: ");
                                    scanf("%d", &price);

                                    mostrarPedidosXprecio(PED, price);

                                }break;

                                default:{
                                    system("cls");
                                    printf("Opcion no disponible, intente con otra\n");
                                }break;

                            }

                        printf("\nDesea seguir viendo pedidos? (s/n) \n");
                        fflush(stdin);
                        scanf("%c", &c);

                        }while(c == 's');

                    }break;

                    default:{
                        printf("Opcion no disponible\n");
                    }break;

                    }
                    printf("\nDesea seguir navegando como Administrador? (s/n) \n");
                    fflush(stdin);
                    scanf("%c", &sigo);

                }while(sigo == 's');

            }else{
                printf("Usuario y/o contrasenia de Administrador incorrecta\n");
            }

        }break;

        default:
        {
            printf("Opcion no valida. Vuelva a intentar\n");
        }
        break;

        }
        printf("\nDesea seguir navegando? (s/n) \n");
        fflush(stdin);
        scanf("%c", &continuar);
    }
    while (continuar == 's');

    return 0;
}









