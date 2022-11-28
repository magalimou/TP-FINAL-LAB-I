#ifndef CATALOGO_H_INCLUDED
#define CATALOGO_H_INCLUDED

typedef struct
{
    char producto[20]; //JEAN / POLERA / BUZO / SWEATER / ETC
    int precio;
    int estado; //1 para activo / 0 para eliminado

} Catalogo;

Catalogo cargaCatalogo ();
int cargarArregloCatalogo (Catalogo arreglo[], int dim, int validos);
void copyArrayToFileCatalogo (char archivo[], Catalogo cat[], int validosCat);
void mostrarCatalogoCarta(char catalog[]);
int verificarProducto (char nomArchi[], char producto[]);
int buscarPrecioProducto (char nomArchiCat[], char producto[]);
void agregarElemCatalogo(char catalogo[]);
void modificarCatalogo (char archiCatalogo[], char nombreProduc[]);
Catalogo cambioCatalogo();
void eliminarProducto (char archiCatalogo[], char producto[]);

int FileToArray (char archiCatalogo[], Catalogo arr[], int dim, int val);
int buscarPosMenorPrecio (Catalogo A[], int validos, int posicion);
void ordenarSeleccionCatalogoPrecio (Catalogo A[], int validos);

#endif // CATALOGO_H_INCLUDED
