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

/****************************
 * \brief CARGA UN USUARIO
 * \return USUARIO
 ****************************/

Usuario cargarUsuario ()
{
    Usuario a;
    char contra[9];
    int flag = 0;
    int usuUnico;
    int flag2;

    printf("\nIngrese su Nombre y Apellido\n");
    fflush(stdin);
    gets(a.nombreYApellido);

    do
    {
        printf("Ingrese nombre de usuario (SOLO LETRAS)\n");
        fflush(stdin);
        gets(a.nombreUsuario);

        flag = validarNombreUsu(a.nombreUsuario);
        usuUnico = usuarioUnico(USU, a.nombreUsuario);

    }while(flag == 1 || usuUnico == 1);

    do{
        printf("Ingrese una contrasenia de 7 caracteres (SOLO NUMEROS) \n");
        scanf( "%s", contra);

        flag2 = validarContrasenia(contra);

    }while(flag2 == 0);

    a.contrasenia = atoi(contra);//lo convierte en una variable de tipo entero.

    a.p.desc = 0;
    a.p.forma = 2;
    a.p.precioTotal = 0;
    a.p.totalConDesc = 0;

    return a;
}


/*****************************************************
 * \brief CARGA UN USUARIO Y LO GUARDA EN UN ARCHIVO
 * \param NOMBRE DEL ARCHIVO
 * \return VOID
 ****************************************************/

void guardarUsuarioArchivo (char archivoUsu[])
{
    FILE*buffer;
    Usuario a;

    buffer= fopen(archivoUsu, "ab");
    if(buffer!= NULL)
    {
        a = cargarUsuario();
        fwrite(&a, sizeof(Usuario), 1, buffer);

        fclose(buffer);
    }
}

/*********************************************
 * \brief VERIFICA QUE EL USUARIO NO EXISTA
 * \param NOMBRE DEL ARCHIVO
 * \param NOMBRE DE USUARIO
 * \return FLAG
 *********************************************/

int usuarioUnico (char archiusu[], char nombre[])
{
    Usuario a;
    int unico =0;

    FILE*buffer = fopen(archiusu, "rb");
    if (buffer != NULL)
    {
        while(unico == 0 && fread(&a, sizeof(Usuario), 1, buffer) > 0)
        {
            if (strcmp(a.nombreUsuario, nombre) == 0)
            {
                unico = 1;
            }
        }
        fclose(buffer);
    }
    return unico;
}

/**********************************
 * \brief BUSCA UN USUARIO
 * \param NOMBRE DE ARCHIVO
 * \param CONTRASEÑA DE USUARIO
 * \param NOMBRE DE USUARIO
 * \return FLAG
 **********************************/

int buscarUsuario( char archiUsuario[], int contra, char usu[])
{
    int flag = 0;
    FILE*buffer;
    Usuario aux;

    buffer = fopen(archiUsuario, "rb");
    if(buffer != NULL)
    {
        while(flag == 0 && fread(&aux, sizeof(Usuario), 1, buffer)> 0)
        {
            if(aux.contrasenia == contra && strcmp(aux.nombreUsuario,usu) == 0)
            {
                printf("Usuario Registrado\n\n");
                flag = 1;
            }
        }
        fclose(buffer);
    }

    return flag; //1 si lo encontro / 0 si no lo encontro
}

/*******************************************************
 * \brief BUSCA Y MUESTRA NOMBRE Y APELLIDO EN ARCHIVO
 * \param NOMBRE DE ARCHIVO
 * \param NOMBRE DE USUARIO
 * \return VOID
 ******************************************************/

void buscarNYAenArchiUsuario(char archiUsuario[], char nomUsuBuscar[])
{
    Usuario a;
    FILE*buffer = fopen(archiUsuario, "rb");
    if(buffer != NULL)
    {
        while(fread(&a, sizeof(Usuario), 1, buffer) > 0)
        {
            if(strcmp(a.nombreUsuario, nomUsuBuscar) == 0)
            {
                printf("| NOMBRE Y APELLIDO: %s \n", a.nombreYApellido);
            }
        }
        fclose(buffer);
    }
}

/**********************************
 * \brief MUESTRA UN USUARIO
 * \param USUARIO
 * \return VOID
 **********************************/

void mostrarUsuario (Usuario a)
{
    printf(" _____________________________________________\n");
    printf("|                  <<USUARIO>>                |\n");
    printf(" NOMBRE Y APELLIDO: %s                         \n", a.nombreYApellido);
    printf(" CONTRASENIA: %d                               \n", a.contrasenia);
    printf(" USUARIO: %s                                   \n", a.nombreUsuario);
    printf("|_____________________________________________|\n");

}

/****************************************
 * \brief MUESTRA UN USUARIO ESPECIFICO
 * \param NOMBRE DE ARCHIVO
 * \param NOMBRE DE USUARIO
 * \return VOID
 ****************************************/

void mostrarUsuarioEspecifico(char archivoUsuarios[], char nombreUsu[])
{
    FILE*archi;
    Usuario a;

    archi = fopen(archivoUsuarios, "rb");
    if(archi != NULL)
    {
        while(fread(&a, sizeof(Usuario), 1, archi) > 0 )
        {
            if(strcmp(a.nombreUsuario, nombreUsu) == 0)
            {
              mostrarUsuario(a);
            }
        }
        fclose(archi);
    }
}

/*****************************************
 * \brief CAMBIA CONTRASEÑA DE USUARIO
 * \param NOMBRE DE ARCHIVO USUARIOS
 * \param NOMBRE DE USUARIO
 * \return VOID
 ****************************************/

void cambiarContraUsuario(char archiUsuario[], char nombreUsu[])
{
    int flag = 0, flag2 = 0;
    int contra;
    char contraVerificar[9];
    Usuario aux;

    printf("Ingrese su contrasenia actual\n");
    fflush(stdin);
    scanf("%d", &contra);

    FILE*buffer;
    buffer = fopen(archiUsuario, "r+b");
    if(buffer != NULL)
    {
        while(flag == 0 && fread(&aux, sizeof(Usuario), 1, buffer)> 0)
        {
            if(aux.contrasenia == contra && strcmp(aux.nombreUsuario,nombreUsu) == 0)
            {
                flag = 1;
                fseek(buffer, (-1)*sizeof(Usuario), SEEK_CUR);
                fread (&aux, sizeof (Usuario), 1, buffer);

                do
                {
                    printf("Ingrese una nueva contrasenia de 7 caracteres (SOLO NUMEROS) \n");
                    fflush(stdin);
                    scanf( "%s", &contraVerificar);

                    flag2 = validarContrasenia(contraVerificar);

                }while(flag2 == 0);

                aux.contrasenia = atoi(contraVerificar);//lo convierte en una variable de tipo entero.

                fseek(buffer, (-1)*sizeof(Usuario), SEEK_CUR);
                fwrite(&aux, sizeof(Usuario), 1, buffer);
            }
        }
        fclose(buffer);
    }
}

/********************************
 * \brief CARGA PAGO
 * \param NOMBRE DE ARCHIVO
 * \param NOMBRE DE USUARIO
 * \return PAGO
 *******************************/

Pago cargaPago( char archiPedido[], char nombreUsu[])
{
    Pago a;
    int desc;

    printf("\n");
    printf(" ______________________________________________________________\n");
    printf("|          <<FORMA DE PAGO DE TODOS LOS PEDIDOS>>              |\n");
    printf("|______________________________________________________________|\n");

    printf("\nDesea abonar con tarjeta o efectivo?\n");
    printf("Ingrese 1 para abonar con tarjeta\n");
    printf("Ingrese 0 para abonar en efectivo\n");
    fflush(stdin);
    scanf("%d", &a.forma);

    a.precioTotal = precioTotalAPagar(PED, nombreUsu);

    if(a.forma == 0) //si lo abona en efectivo
    {
        if(a.precioTotal >= 10500) //si la compra supera los 10500
        {
            a.desc = 10;
            desc = 10*a.precioTotal/100; //se le hace un despuesto del %10
            a.totalConDesc = a.precioTotal -desc;

        }else{
            a.desc = 0;
            a.totalConDesc = a.precioTotal;
        }
    }else  //si abona con tarjeta
    {
        a.desc = 0;
        a.totalConDesc = a.precioTotal;
    }

    return a;
}

/**************************************
 * \brief CARGA PAGO EN UN ARCHIVO
 * \param NOMBRE DE ARCHIVO USUARIOS
 * \param NOMBRE DE ARCHIVO PEDIDOS
 * \param NOMBRE DE USUARIO
 * \return VOID
 ************************************/

void cargaPagoArchiUsuario (char archiUsuario[], char archiPedido[], char nombreUsu[])
{
    Usuario a;
    int flag = 0;

    FILE*buffer = fopen(archiUsuario, "r+b");
    if(buffer != NULL)
    {
        while(flag == 0 && fread(&a, sizeof(Usuario), 1, buffer) > 0)
        {
            if(strcmp(a.nombreUsuario, nombreUsu) == 0)
            {
                flag = 1;
                fseek(buffer, (-1)*sizeof(Usuario), SEEK_CUR);
                fread (&a, sizeof (Usuario), 1, buffer);

                a.p = cargaPago(archiPedido, nombreUsu);

                fseek(buffer, (-1)*sizeof(Usuario), SEEK_CUR);
                fwrite(&a, sizeof(Usuario), 1, buffer);
            }
        }
        fclose(buffer);
    }
}

/******************************
 * \brief MUESTRA PAGO
 * \param PAGO
 * \return VOID
 ******************************/

void mostrarPago (Pago a)
{
    printf(" ________________________________________________________\n");
    if(a.forma == 0)
    {
        printf("| PAGO EN EFECTIVO\n");
    }
    else if (a.forma == 1){

        printf("| PAGO CON TARJETA\n");
    }else{

        printf("| NO SE REALIZO UN PEDIDO AUN\n");
    }

    printf("| PRECIO TOTAL: %d\n", a.precioTotal);
    printf("| DESCUENTO APLICADO: %d\n", a.desc);
    printf("| PRECIO TOTAL CON DESCUENTO: %d\n", a.totalConDesc);
    printf("|________________________________________________________\n");

}

/*********************************************
 * \brief MUESTRA PAGO CARGADO EN ARCHIVO
 * \param NOMBRE DE ARCHIVO USUARIOS
 * \param NOMBRE DE USUARIO
 * \return VOID
 ********************************************/

void mostrarArchivoUsuPago (char archivoUsu[], char nombreUsuario[])
{
    FILE*archi;
    Usuario a;

    archi = fopen(archivoUsu, "rb");
    if(archi != NULL)
    {
        while(fread(&a, sizeof(Usuario), 1, archi) > 0 )
        {
            if(strcmp(nombreUsuario, a.nombreUsuario) == 0)
            {
                mostrarPago(a.p);
            }
        }
        fclose(archi);
    }
}

/*******************************************************
 * \brief ACTUALIZA EL PAGO CUANDO SE CANCELA UN PEDIDO
 * \param NOMBRE DE ARCHIVO USUARIOS
 * \param NOMBRE DE USUARIO
 * \param TOTAL (precio)
 * \param FORMA (de pago)
 * \return VOID
 ******************************************************/

void actualizarPago (char archiUsuario[], int total, char nombreUsu[], int forma)
{
    Usuario a;
    int flag = 0;

    FILE*buffer = fopen(archiUsuario, "r+b");
    if(buffer != NULL)
    {
        while(flag == 0 && fread(&a, sizeof(Usuario), 1, buffer) > 0)
        {
            if(strcmp(a.nombreUsuario, nombreUsu) == 0)
            {
                flag = 1;
                fseek(buffer, (-1)*sizeof(Usuario), SEEK_CUR);
                fread (&a, sizeof (Usuario), 1, buffer);

                a.p = descuento(total, forma);

                fseek(buffer, (-1)*sizeof(Usuario), SEEK_CUR);
                fwrite(&a, sizeof(Usuario), 1, buffer);
            }
        }
        fclose(buffer);
    }
}

/***************************************
 * \brief BUSCA LA FORMA DE PAGO
 * \param NOMBRE DE ARCHIVO USUARIOS
 * \param NOMBRE DE USUARIO
 * \return FORMA
 ***************************************/

int buscarFormaPago (char archiUsuario[], char nombreUsu[])
{
    Usuario a;
    int flag = 0;
    int forma;

    FILE*buffer = fopen(archiUsuario, "r+b");
    if(buffer != NULL)
    {
        while(flag == 0 && fread(&a, sizeof(Usuario), 1, buffer) > 0)
        {
            if(strcmp(a.nombreUsuario, nombreUsu) == 0)
            {
                if (a.p.forma == 0)
                {
                    forma = 0;
                }else{
                    forma = 1;
                }
            }
        }
        fclose(buffer);
    }
    return forma;
}

/*************************************
 * \brief ACTUALIZA EL DESCUENTO
 * \param TOTAL A PAGAR
 * \param FORMA DE PAGO
 * \return PAGO (struct)
 ************************************/

Pago descuento( int total, int forma)
{
    Pago a;

    a.precioTotal = total;
    a.forma = forma;

    if(a.forma == 0) //si lo abona en efectivo
        {
            if(total >= 10500) //si la compra supera los 10500
            {
                a.desc = 10;
                int desc = 10*total/100; //se le hace un despuesto del %10
                a.totalConDesc = total -desc;

            }else{
                a.desc = 0;
                a.totalConDesc = total;
            }
        }else  //si abona con tarjeta
        {
            a.desc = 0;
            a.totalConDesc = total;
        }

    return a;
}

/**********************************************************
 * \brief MOSTRAR PAGOS CON NOMBRE Y APELLIDO DEL USUARIO
 * \param NOMBRE DE ARCHIVO USUARIOS
 * \return VOID
 *********************************************************/

void mostrarPagosConNombre(char archiUsuario[])
{
    FILE*buffer;
    Usuario a;

    buffer= fopen(archiUsuario, "rb");
    if(buffer!= NULL)
    {
        while(fread(&a, sizeof(Usuario), 1, buffer)> 0)
        {
            verPago(a.p);
            printf("| NOMBRE Y APELLIDO: %s\n", a.nombreYApellido);
            printf("|________________________________________________________\n");

        }
        fclose(buffer);
    }
}

/****************************
 * \brief MUESTRA PAGOS
 * \param PAGO
 * \return VOID
 **************************/

void verPago(Pago a)
{
    printf(" ________________________________________________________\n");
    if(a.forma == 0)
    {
        printf("| PAGO EN EFECTIVO\n");
    }
    else
    {
        printf("| PAGO CON TARJETA:\n");
    }

    printf("| PRECIO TOTAL: %d\n", a.precioTotal);
    printf("| DESCUENTO APLICADO: %d\n", a.desc);
    printf("| PRECIO TOTAL CON DESCUENTO: %d\n", a.totalConDesc);
}






