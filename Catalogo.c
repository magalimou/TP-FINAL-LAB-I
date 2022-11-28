#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <ctype.h>
#include <conio.h>
#include "Catalogo.h"

#define CAT "Catalogo.bin"
#define PED "Pedidos.bin"
#define USU "Usuarios.bin"

/**********************************
 * \brief CARGA ESTRUCTURA CATALOGO
 * \return CATALOGO
 **********************************/

Catalogo cargaCatalogo ()
{
    Catalogo a;

    printf("Ingrese Producto: \n");
    fflush(stdin);
    gets(a.producto);

    printf("Ingrese precio del producto: \n");
    fflush(stdin);
    scanf("%d", &a.precio);

    a.estado = 1;

    return a;
}

/********************************************
 * \brief CARGA UN ARREGLO DE TIPO CATALOGO
 * \param ARREGLO CATALOGO
 * \param DIMENSION
 * \param VALIDOS
 * \return VALIDOS
 *******************************************/

int cargarArregloCatalogo (Catalogo arreglo[], int dim, int validos)
{
    char seguir = 's';

    while (validos < dim && seguir == 's')
    {
        arreglo[validos] = cargaCatalogo();

        validos ++;

        printf("Desea seguir cargando?\n");
        fflush(stdin);
        scanf("%c", &seguir);

    }

    return validos;
}

/*****************************************
 * \brief COPIA EL ARREGLO A UN ARCHIVO
 * \param NOMBRE DE ARCHIVO
 * \param ARREGLO DE TIPO CATALOGO
 * \param VALIDOS CATALOGO
 * \return VOID
 ****************************************/

void copyArrayToFileCatalogo (char archivo[], Catalogo cat[], int validosCat)
{
    FILE*buffer;
    int i = 0;

    buffer= fopen(archivo, "wb");
    if(buffer!= NULL)
    {
        while(i<validosCat)
        {
            fwrite(&cat[i], sizeof(Catalogo), 1, buffer);
            i++;
        }
        fclose(buffer);
    }
}

/**********************************
 * \brief MUESTRA EL CATALOGO
 * \param NOMBRE DE ARCHIVO
 * \return VOID
 **********************************/

void mostrarCatalogoCarta (char catalog[])
{
    FILE*buffer;
    Catalogo a;

    buffer = fopen(catalog, "rb");
    if(buffer != NULL)
    {
        printf(" _______________________________________________________________________________\n");
        printf("                                   <<CATALOGO>>                                \n");
        printf(" PRODUCTO---------------------------------------------------------------PRECIO \n");


        while((fread(&a, sizeof(Catalogo),1,buffer)) > 0)
        {
            if(a.estado == 1)
            {
                printf(" %s---------------------------------------------------------------$%d\n", a.producto,a.precio);
            }
        }

        printf(" _____________________________\n");
        printf("|      COLORES DISPONIBLES    |\n");
        printf("|  1- BLANCO                  |\n");
        printf("|  2- NEGRO                   |\n");
        printf("|  3- BEIGE                   |\n");
        printf("|  4- AZUL                    |\n");
        printf("|  5- MARRON                  |\n");
        printf("|_____________________________|\n");

        printf(" ____________________________________________________________________\n");
        printf("| TALLES DISPONIBLES: || 1-S || 2-M || 3-L || 4-XL ||                |\n");
        printf("|____________________________________________________________________|\n");

        fclose(buffer);

    }else{

        printf("ERROR\n");
    }
}

/******************************************************
 * \brief VERIFICA QUE UN PRODUCTO ESTE EN EL ARCHVIO
 * \param NOMBRE DE ARCHIVO
 * \param NOMBRE DEL PRODUCTO
 * \return FLAG
 ******************************************************/

int verificarProducto (char nomArchi[], char producto[])
{
    Catalogo cata;
    int flag = 0;

    FILE *archivo= fopen(nomArchi, "rb");
    if (archivo!= NULL)
    {
        while(flag == 0 && fread(&cata, sizeof(Catalogo), 1, archivo)> 0)
        {
            if (strcmpi(cata.producto, producto)== 0)
            {
                flag =1;
            }
        }
        fclose(archivo);
    }

    return flag; //RETORNA 1 SI LO ENCUENTRA
}

/******************************************
 * \brief BUSCA UN PRECIO EN UN ARCHIVO
 * \param NOMBRE DE ARCHIVO
 * \param NOMBRE DEL PRODCUTO
 * \return PRECIO
 *****************************************/

int buscarPrecioProducto (char nomArchiCat[], char producto[])
{
    Catalogo cata;
    int flag = 0;
    int price;

    FILE *archivo= fopen(nomArchiCat, "rb");
    if (archivo!= NULL)
    {
        while(flag == 0 && fread(&cata, sizeof(Catalogo), 1, archivo)> 0)
        {
            if (strcmpi(cata.producto, producto)== 0)
            {
                price = cata.precio;
                flag = 1;
            }
        }
        fclose(archivo);
    }
    return price;
}

/*****************************************
 * \brief AGREGAR PRODUCTO AL CATALOGO
 * \param NOMBRE DE ARCHIVO CATALOGO
 * \return VOID
 ****************************************/

void agregarElemCatalogo(char catalogo[])
{
    FILE*buffer;
    Catalogo nuevo;
    char continuar ='s';

    buffer = fopen(catalogo, "ab");
    if(buffer!=NULL)
    {
        while(continuar =='s')
        {
            nuevo = cargaCatalogo();

            fwrite(&nuevo, sizeof(Catalogo), 1, buffer);

            printf("Desea seguir agregando nuevos productos? (s/n) \n");
            fflush(stdin);
            scanf("%c", &continuar);
        }
        fclose(buffer);
    }
}

/*****************************************
 * \brief MODIFICAR CATALOGO
 * \param NOMBRE DE ARCHIVO
 * \param NOMBRE DE PRODUCTO
 * \return VOID
 ****************************************/

void modificarCatalogo (char archiCatalogo[], char nombreProduc[])
{
   FILE*archi;
   Catalogo a;
   int flag = 0;

   archi= fopen(archiCatalogo, "r+b");
   if(archi!= NULL)
   {
        while(flag == 0 && fread(&a, sizeof(Catalogo), 1, archi) > 0)
        {
            if(strcmpi(a.producto, nombreProduc) == 0)
            {
                fseek(archi, sizeof(Catalogo)*(-1),SEEK_CUR);
                fread(&a, sizeof(Catalogo), 1, archi);

                a = cambioCatalogo();

                fseek(archi, sizeof(Catalogo)*(-1),SEEK_CUR);
                fwrite(&a, sizeof(Catalogo), 1, archi);
                flag = 1;
            }
        }
        fclose(archi);
   }
}

/*****************************************
 * \brief CAMBIAR UN PRODUCTO DEL CATALOGO
 * \return CATALOGO
 ****************************************/

Catalogo cambioCatalogo()
{
    Catalogo a;

    printf("\nIngrese nuevo nombre del producto\n");
    fflush(stdin);
    gets(a.producto);

    printf("\nIngrese nuevo precio\n");
    scanf("%d", &a.precio);

    a.estado = 1;

    return a;
}

/*******************************************
 * \brief ELIMINA UN PRODUCTO DEL CATALOGO
 * \param NOMBRE DE ARCHIVO
 * \param NOMBRE DE PRODUCTO
 * \return VOID
 ******************************************/

void eliminarProducto (char archiCatalogo[], char producto[])
{
    FILE*buffer;
    Catalogo a;
    int flag = 0;

    buffer = fopen(archiCatalogo, "r+b");
    if(buffer != NULL)
    {
        while(flag == 0 && fread(&a, sizeof(Catalogo), 1, buffer)> 0)
        {
            if(strcmpi(a.producto, producto) == 0)
            {
                flag = 1;
                fseek(buffer, (-1)*sizeof(Catalogo), SEEK_CUR);
                fread (&a, sizeof (Catalogo), 1, buffer);

                a.estado = 0;

                fseek(buffer, (-1)*sizeof(Catalogo), SEEK_CUR);
                fwrite(&a, sizeof(Catalogo), 1, buffer);
            }
        }
        fclose(buffer);
    }
}

/*******************************************
 * \brief PASA ARCHIVO A ARREGLO
 * \param NOMBRE DE ARCHIVO
 * \param NOMBRE DE ARREGLO
 * \param DIMENSION
 * \param VALIDOS
 * \return VALIDOS
 ******************************************/

int FileToArray (char archiCatalogo[], Catalogo arr[], int dim, int val)
{
    FILE*archi;
    Catalogo a;

    archi= fopen(archiCatalogo, "rb");
    if(archi!=NULL)
    {
        while((fread(&a,sizeof(Catalogo), 1, archi))>0)
        {
            if(val < dim)
            {
               arr[val] = a;
               val++;
            }
        }
        fclose(archi);
    }

    return val;
}

/*************************************************
 * \brief POSICION DEL PRODUCTO CON MENOR PRECIO
 * \param NOMBRE DE ARREGLO
 * \param POSICION
 * \param VALIDOS
 * \return POSICION MENOR
 *************************************************/

int buscarPosMenorPrecio (Catalogo A[], int validos, int posicion)
{
    int indice = posicion +1;

    int posmenor= posicion;
    int menor = A[posmenor].precio;

    while(indice <validos )
    {
        if(menor >A[indice].precio)
        {
            menor = A[indice].precio;
            posmenor= indice;
        }
        indice++;
    }

    return posmenor;
}

/*************************************************
 * \brief ORDENACION POR SELECCION
 * \param NOMBRE DE ARREGLO
 * \param VALIDOS
 * \return VOID
 *************************************************/

void ordenarSeleccionCatalogoPrecio (Catalogo A[], int validos)
{
    int posmenor;
    int i = 0;
    Catalogo aux[validos];

    while(i<validos)
    {
        posmenor = buscarPosMenorPrecio(A, validos, i);

        aux[i]= A[i];
        A[i]= A[posmenor];
        A[posmenor]= aux[i];

        i++;
    }
}

