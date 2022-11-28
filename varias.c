#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <ctype.h>
#include <conio.h>
#include "Catalogo.h"
#include "Pedido.h"
#include "Menu.h"
#include "varias.h"

#define CAT "Catalogo.bin"
#define PED "Pedidos.bin"
#define USU "Usuarios.bin"

/****************************************
 * \brief VALIDA EL NOMBRE DEL USUARIO
 * \param NOMBRE DE USUARIO
 * \return FLAG
 ****************************************/

int validarNombreUsu (char nombre[])
{
    int i = 0;
    int flag = 0;

    while ( flag == 0 && i< strlen(nombre))
    {
        int esLetra = isalpha(nombre[i]); //omprueba si el carácter es alfabético; DA 0 CUANDO ES FALSO

        if (esLetra !=0)
        {
            i++;
        }
        else
        {
            printf("Error, usuario invalido. Intente de nuevo\n");
            flag =1;
        }
    }

    return flag; //Si es 1 tiene un Error
}

/******************************************
 * \brief VALIDA LA CONTRASEÑA DEL USUARIO
 * \param CONTRASEÑA DE TIPO CHAR
 * \return FLAG
 *****************************************/

int validarContrasenia (char contra[])
{
    int i = 0;

    for(i=0; i<strlen(contra); i++)
    {
        if (!(isdigit(contra[i])))
        {
            printf("\nError, contrasenia invalida. Intentelo de nuevo\n");
            return 0;
        }
    }
    return 1; //0 si es invalida// 1 si es valida
}

/***************************************
 * \brief VERIFICA QUE EL COLOR EXISTA
 * \param OPCION DEL COLOR (int)
 * \return FLAG
 **************************************/

int verificarColor (int color)
{
    int flag = 0;

    if (color == 1 || color == 2 || color == 3 || color == 4 || color == 5 )
    {
        flag = 1;
    }
    else
    {
        printf("Opcion no disponible. Vuelva a intentar e ingrese otra opcion\n");
    }

    return flag; //1 si la opcion esta disponible
}

/***************************************
 * \brief VERIFICA QUE EL TALLE EXISTA
 * \param OPCION DEL TALLE (int)
 * \return FLAG
 **************************************/

int verificarTalle (int talle)
{
    int flag = 0;

    if (talle == 1 || talle == 2 || talle == 3 || talle == 4)
    {
        flag = 1;
    }
    else
    {
        printf("Opcion no disponible. Vuelva a intentar e ingrese otra\n");
    }

    return flag; //1 si existe la opcion
}

/***************************************
 * \brief INGRESO SESION DEL ADMIN
 * \return RESULTADO
 ***************************************/

int inicSesionAdministrador()
{
    char datNomU[20];
    int datConU;
    int result =0;

    do
    {
        printf("Ingrese el nombre de acceso:\n");
        fflush(stdin);
        gets(datNomU);

        printf("Ingrese la clave:\n");
        fflush(stdin);
        scanf("%d", &datConU);

        result = validarAdministrador(datNomU, datConU);

    }
    while(result != 0);

    return result; //RETORNA 0 SI ES CORRECTO
}

/*************************************
 * \brief VALIDA LA SESION DEL ADMIN
 * \param NOMBRE ADMIN
 * \param CONTRASEÑA
 * \return FLAG
 *************************************/

int validarAdministrador (char nombreAdm[], int password)
{
    //id y contraseña de admin//
    char nomAcc[]= {"ADMIN03"};
    int pass = 23302330;
    int flag = 0;

    if(strcmp(nombreAdm, nomAcc) == 0 && pass == password)
    {
        printf("Sesion de Administrador abierta con exito\n\n");
        flag = 0;
    }
    else{

        printf("Codigo de acceso y/o clave incorrecta. Vuelva a intentar\n\n");
        flag = 1;
    }

    return flag; //retorna 1 si es incorrecta, si es correcta 0
}

/***************************************
 * \brief MUESTRA ESTADO DEL PEDIDO
 * \param ESTADO (numero)
 * \return VOID
 **************************************/

void mostrarEstadoPedido (int estado)
{
    if(estado == 1)
    {
        printf("| ESTADO: ACTIVO \n");

    }else{

        printf("| ESTADO: CANCELADO \n");
    }
}

/*************************
 * \brief MUESTRA COLOR
 * \param OPCION COLOR
 * \return VOID
 ************************/

void mostrarColor (int color)
{
    if (color ==1)
    {
        printf("| COLOR: BLANCO \n");
    }
    else if (color==2)
    {
        printf("| COLOR: NEGRO \n");

    }
    else if (color==3)
    {
        printf("| COLOR: BEIGE \n");
    }
    else if (color==4)
    {
        printf("| COLOR: AZUL \n");
    }
    else if (color==5)
    {
        printf("| COLOR: MARRON \n");
    }

}

/***************************
 * \brief MUESTRA TALLE
 * \param OPCION TALLE
 * \return VOID
 *************************/

void mostrarTalle (int talle)
{
    if (talle ==1)
    {
        printf("| TALLE: S \n");
    }
    else if (talle==2)
    {
        printf("| TALLE: M \n");
    }
    else if (talle==3)
    {
        printf("| TALLE: L \n");
    }
    else if (talle==4)
    {
        printf("| TALLE: XL \n");
    }

}

/********************************************************
 * \brief CONVIERTE NOMBRE DEL COLOR EN NUMERO DE OPCION
 * \param NOMBRE DE COLOR
 * \return NUMERO DEL COLOR
 ******************************************************/

int convertirColor (char color[]) //convierte el nombre del color en el numero de la opcion del catalogo.
{
    int colorNum = 0;

    if(strcmpi(color, "blanco") == 0)
    {
        colorNum = 1;

    }else if(strcmpi(color, "negro") == 0){

        colorNum = 2;

    }else if(strcmpi(color, "beige") == 0){

        colorNum = 3;

    }else if(strcmpi(color, "azul") == 0){

        colorNum = 4;

    }else if (strcmpi(color, "marron") == 0){

        colorNum = 5;

    }else{

        printf("Color no disponible\n");
        colorNum = 0;
    }

    return colorNum;
}
