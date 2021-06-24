/*
 ============================================================================
 Name        : Recuperatorio.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utnInputs.h"

#define OCUPADO 1
#define VACIO 0
#define T 1050
#define E 150

typedef struct
{
	int id;
	char nombre[50];
	char apellido[50];
	char cuil[20];
	int isEmpty;

}eContribuyente;

typedef struct
{
	eContribuyente id;
	int mes;
	int tipo;
	char descripcion[20];
	int importe;
	int idRecaudacion;
	int isEmpty;

}eRecaudacion;

void VaciarLista(eContribuyente* listaContribuyentes,int tam);
void VaciarListaR(eRecaudacion* listaRecaudaciones,int tamR);
int BuscarLibre(eContribuyente* listaContribuyentes, int tam);
int BuscarLibreR(eRecaudacion* listaRecaudaciones, int tamR);
int AniadirContribuyente(eContribuyente* listaContribuyentes, int tam, int* id);
int AniadirRecaudacion(eRecaudacion* listaRecaudaciones, int tamR, eContribuyente* listaContribuyentes, int tam, int* id);
eContribuyente AltaContribuyente(int* id);
void ObtenerId(int* idAuto);
void ObtenerIdRecaudaciones(int* idAutoR);
int ModificarContribuyente(eContribuyente* listaContribuyentes,int tam);
void ListarContribuyentes(eContribuyente* listaContribuyentes, int tam, eRecaudacion* listaRecaudaciones, int tamRecaudacion);
eRecaudacion BuscarRecaudacionPorID(eRecaudacion* listaRecaudaciones, int tamRecaudacion, int id);
int BajaContribuyente(eContribuyente* listaContribuyente, int tam, eRecaudacion* listaRecaudaciones, int tamRecaudaciones);
eRecaudacion AltaRecaudacion(eContribuyente* listaContribuyentes, int tam, int* idR);
void ListarRecaudaciones(eRecaudacion* listaRecaudaciones, int tamRecaudaciones, eContribuyente* listaContribuyentes, int tam);
int EncontrarContribuyentePorID(eContribuyente* listaContribuyentes, int tam, int id);
int RefinanciarRecaudacion(eRecaudacion* listaRecaudaciones, int tamR, eContribuyente* listaContribuyentes, int tam);
int SaldarRecaudacion(eRecaudacion* listaRecaudaciones, int tamR, eContribuyente* listaContribuyentes, int tam);
//int Informes(eRecaudacion* listaRecaudaciones, int tamR, eContribuyente* listaContribuyentes, int tam);
//int ContadorRefinanciar(eRecaudacion* listaRecaudaciones, int tamR, eContribuyente* listaContribuyentes, int tam);

int main(void)
{
	setbuf(stdout, NULL);
	int opcion;
	int idAuto = 999;
	int idAutoR = 99;
	int flagAlta = 0;
	int flagRecaudacion = 0;
	int retornoSaldar = 0;

	eRecaudacion listaRecaudaciones[E];
	eContribuyente listaContribuyentes[T];

	VaciarLista(listaContribuyentes, T);
	VaciarListaR(listaRecaudaciones, E);
	//printf("%d ANTES\n", idAuto);
	do
		{
		//printf("%d DESPUES\n", idAuto);
			printf("1- Alta de contribuyente\n");
			printf("2- Modificar datos del contribuyente\n");
			printf("3- Baja de contribuyente\n");
			printf("4- Recaudacion\n");
			printf("5- Refinanciar Recaudacion\n");
			printf("6- Saldar Recaudacion\n");
			printf("7- Imprimir Contribuyentes\n");
			printf("8- Imprimir Recaudacion\n");
			printf("9- Informes\n");
			printf("10- Salir\n");

			utn_getInt(&opcion, "Ingrese una opcion: ", "Error,ingrese una opcion valida\n", 1,9, 2);

			switch(opcion)
			{
				case 1:
						AniadirContribuyente(listaContribuyentes, T, &idAuto);
						flagAlta = 1;
				break;

				case 2:
					if(flagAlta == 1)
					{
						ModificarContribuyente(listaContribuyentes,T);
					}
					else
					{
						printf("\n*************************************************\n");
						printf("Error, no hay contribuyentes dados de alta o no se ingresaron recaudaciones.\n");
						printf("*************************************************\n");
					}
				break;

				case 3:
					if(flagAlta == 1)
					{
						BajaContribuyente(listaContribuyentes, T,listaRecaudaciones, E);
					}
					else
					{
						printf("\n*************************************************\n");
						printf("Error, no hay contribuyentes dados de alta o no se ingresaron recaudaciones.\n");
						printf("*************************************************\n");
					}
				break;

				case 4:
					if(flagAlta == 1)
					{
						AniadirRecaudacion(listaRecaudaciones, E, listaContribuyentes, T, &idAutoR);
						flagRecaudacion = 1;
					}
					else
					{
						printf("\n*************************************************\n");
						printf("Error, no hay contribuyentes dados de alta o no se ingresaron recaudaciones.\n");
						printf("*************************************************\n");
					}
				break;

				case 5:
					if(flagAlta == 1 && flagRecaudacion == 1)
					{
						RefinanciarRecaudacion(listaRecaudaciones, E, listaContribuyentes, T);
					}
					else
					{
						printf("\n*************************************************\n");
						printf("Error, no hay contribuyentes dados de alta o no se ingresaron recaudaciones.\n");
						printf("*************************************************\n");
					}
				break;

				case 6:
					if(flagAlta == 1 && flagRecaudacion == 1)
					{
						retornoSaldar = SaldarRecaudacion(listaRecaudaciones, E,listaContribuyentes, T);
					}
					else
					{
						printf("\n*************************************************\n");
						printf("Error, no hay contribuyentes dados de alta o no se ingresaron recaudaciones.\n");
						printf("*************************************************\n");
					}
				break;

				case 7:
					if(flagAlta == 1 && flagRecaudacion == 1)
					{
						ListarContribuyentes(listaContribuyentes, T, listaRecaudaciones, E);
					}
					else
					{
						printf("\n*************************************************\n");
						printf("Error, no hay contribuyentes dados de alta o no se ingresaron recaudaciones.\n");
						printf("*************************************************\n");
					}
				break;

				case 8:
					if(flagAlta == 1 && flagRecaudacion == 1)
					{
						if(retornoSaldar == 1)
						{
						ListarRecaudaciones(listaRecaudaciones, E, listaContribuyentes, T);
						}
						else
						{
							printf("\n*************************************************\n");
							printf("No hay recaudaciones saldadas\n");
							printf("*************************************************\n");
						}
					}
					else
					{
						printf("\n*************************************************\n");
						printf("Error, no hay contribuyentes dados de alta o no se ingresaron recaudaciones.\n");
						printf("*************************************************\n");
					}
				break;

				case 9:
					if(flagAlta == 1 && flagRecaudacion == 1)
					{
						//Informes(listaRecaudaciones, E, listaContribuyentes, T);
					}
					else
					{
						printf("\n*************************************************\n");
						printf("Error, no hay contribuyentes dados de alta o no se ingresaron recaudaciones.\n");
						printf("*************************************************\n");
					}
				break;

				case 10:
					printf("\n******************************\n");
					printf("Ha salido de la aplicacion.\n");
					printf("******************************\n");
				break;
			}

		}while(opcion != 10);
	return EXIT_SUCCESS;
}

void VaciarLista(eContribuyente* listaContribuyentes, int tam)
{
	int i;

	for(i=0;i<tam;i++)
	{
		listaContribuyentes[i].isEmpty = VACIO;
	}
}

void VaciarListaR(eRecaudacion* listaRecaudaciones, int tamR)
{
	int i;

	for(i=0;i<tamR;i++)
	{
		listaRecaudaciones[i].isEmpty = VACIO;
	}
}

int BuscarLibre(eContribuyente* listaContribuyentes, int tam)
{
	int i;
	int index=-1;

	if(listaContribuyentes!=NULL)
	{
		for(i=0;i<tam;i++)
		{
			if(listaContribuyentes[i].isEmpty==VACIO)
			{
				index=i;
				break;
			}
		}
	}

	return index;
}

int BuscarLibreR(eRecaudacion* listaRecaudaciones, int tamR)
{
	int i;
	int index=-1;

	if(listaRecaudaciones!=NULL)
	{
		for(i=0;i<tamR;i++)
		{
			if(listaRecaudaciones[i].isEmpty==VACIO)
			{
				index=i;
				break;
			}
		}
	}

	return index;
}

eContribuyente AltaContribuyente(int* id)
{
	eContribuyente miContribuyente;

	ObtenerId(id);
	miContribuyente.id=*id;
	printf("La id sera: %d\n", miContribuyente.id);

	/*printf("Ingrese el nombre del empleado: ");
	fflush(stdin);
	scanf("%[^\n]", miContribuyente.nombre);*/

	/*printf("Ingrese el apellido del empleado: ");
	fflush(stdin);
	scanf("%[^\n]", miContribuyente.apellido);*/

	utn_getString(miContribuyente.nombre, "Ingrese el nombre: ","Error, reingrese\n",2, 50, 5);

	utn_getString(miContribuyente.apellido, "Ingrese el apellido: ","Error, reingrese\n",2, 50, 5);

	printf("Ingrese el cuil del empleado: ");
	fflush(stdin);
	scanf("%[^\n]", miContribuyente.cuil);

	miContribuyente.isEmpty = OCUPADO;

	return miContribuyente;
}

int AniadirContribuyente(eContribuyente* listaContribuyentes, int tam, int* id)
{
	int i;
	    i = BuscarLibre(listaContribuyentes, tam);
	    if(i!=-1)
	    {
	    	listaContribuyentes[i] = AltaContribuyente(id);
	    }
	return i;
}

int AniadirRecaudacion(eRecaudacion* listaRecaudaciones, int tamR, eContribuyente* listaContribuyentes, int tam, int* id)
{
	int i;
	    i = BuscarLibreR(listaRecaudaciones, tamR);
	    if(i!=-1)
	    {
	    	listaRecaudaciones[i] = AltaRecaudacion(listaContribuyentes, tam, id);
	    }
	return i;
}

void ObtenerId (int* idAuto)
{
	*idAuto+=1;
}

void ObtenerIdRecaudaciones(int* idAutoR)
{
	*idAutoR+=1;
}

int ModificarContribuyente(eContribuyente* listaContribuyentes,int tam)
{
	int idIngresado;
	int i;
	int opcion;

		utn_getInt(&idIngresado, "Ingrese el ID del contribuyente a modificar: ", "Error ingrese un ID valido", 1, tam, 5);
		//printf("Ingrese el ID: ");
		//scanf("%d", &idIngresado);

		for(i=0; i<tam; i++)
		{
			if(idIngresado == listaContribuyentes[i].id)
			{
				do
				{
				 printf("1.Modificar nombre del contribuyente\n");
				 printf("2.Modificar apellido del contribuyente\n");
				 printf("3.Modificar cuil del contribuyente\n");
				 printf("4.Salir\n");
				 printf("\n¿Que quiere modificar?: ");
				 scanf("%d", &opcion);

				switch(opcion)
				{
					case 1:
						printf("Ingrese el nuevo nombre: ");
						fflush(stdin);
						scanf("%[^\n]", listaContribuyentes[i].nombre);
						printf("Nombre modificado con exito.\n");
					break;

					case 2:
						 printf("Ingrese el nuevo apellido: ");
						 fflush(stdin);
						 scanf("%[^\n]", listaContribuyentes[i].apellido);
						 printf("Apellido modificado con exito.\n");
					break;

					case 3:
						 printf("Ingrese el nuevo apellido: ");
						 fflush(stdin);
						 scanf("%[^\n]", listaContribuyentes[i].cuil);
						 printf("Cuil modificado con exito.\n");
					break;

					case 4:
						printf("Ha salido con exito de las modificaciones.\n");
						printf("**********************************************\n");

					break;

					}
				}while(opcion != 4);

			}
		}
		return i;
}

eRecaudacion BuscarRecaudacionPorID(eRecaudacion* listaRecaudaciones, int tamRecaudacion, int id)
{
	int i;
	eRecaudacion miId;

	for(i=0; i<tamRecaudacion; i++)
	{
		if(listaRecaudaciones[i].tipo == id)
		{
			miId = listaRecaudaciones[i];
			break;
		}
	}

	return miId;
}

int BajaContribuyente(eContribuyente* listaContribuyentes, int tam, eRecaudacion* listaRecaudaciones, int tamRecaudaciones)
{
	int retorno = -1;
	int index;
	int i;
	int opcionIngresada;
	int idIngresado;

	utn_getInt(&opcionIngresada, "¿Desea ver la lista de contribuyentes? 1(si)/2(no)", "Error elija una opcion valida\n", 1, 2, 5);

	if(opcionIngresada == 1)
	{
		ListarContribuyentes(listaContribuyentes, tam, listaRecaudaciones, tamRecaudaciones);
	}

	utn_getInt(&idIngresado, "Ingrese el ID del contribuyente :", "Error, ingrese un id valido", 1000, 1050, 5);
	index = EncontrarContribuyentePorID(listaContribuyentes, tam, idIngresado);

	if(index == 0)
	{
		for(i=0; i<tam; i++)
		{
			listaContribuyentes[i].isEmpty = VACIO;
			retorno = 0;
			break;
		}
	}

	return retorno;
}


eRecaudacion AltaRecaudacion(eContribuyente* listaContribuyentes, int tam, int* idR)
{
	int idIngresado;
	int i;
	eRecaudacion miRecaudacion;

	ObtenerIdRecaudaciones(idR);
	miRecaudacion.idRecaudacion = *idR;
	printf("La id sera: %d\n", miRecaudacion.idRecaudacion);

	utn_getInt(&idIngresado, "Ingrese el ID del contribuyente: ", "Error ingrese un id valido\n", 1000, tam, 5);

	for(i=0; i<tam; i++)
	{
		if(idIngresado == listaContribuyentes[i].id)
		{
			utn_getInt(&miRecaudacion.mes, "Ingrese el mes [1/12]: ", "Error ingrese un mes valido\n", 1, 12, 5);

			printf("1- ARBA\n2- IIBB\n3-GANANCIAS\n");
			utn_getInt(&miRecaudacion.tipo, "Ingrese el tipo :", "Error ingrese un tipo valido\n", 1, 3, 5);

			if(miRecaudacion.tipo == 1)
			{
				strcpy(miRecaudacion.descripcion,"ARBA");
			}

			if(miRecaudacion.tipo == 2)
			{
				strcpy(miRecaudacion.descripcion,"IIBB");
			}

			if(miRecaudacion.tipo == 3)
			{
				strcpy(miRecaudacion.descripcion,"GANANCIAS");
			}

			utn_getInt(&miRecaudacion.importe, "Ingrese el importe: ", "Error, ingrese un importe valido\n", 1, 1000000, 5);

			miRecaudacion.isEmpty = OCUPADO;

		}
	}

	return miRecaudacion;
}

void ListarContribuyentes(eContribuyente* listaContribuyentes, int tam, eRecaudacion* listaRecaudaciones, int tamRecaudaciones)
{
	int i;
	int j;

	printf("*******************************************************************************\n");
	for(i=0; i<tam; i++)
	{
		if(listaContribuyentes[i].isEmpty == OCUPADO)
		{
			for(j=0; j<tamRecaudaciones; j++)
			{
				if(listaRecaudaciones[j].isEmpty == OCUPADO)
				{
					printf("%2d %15s %15s %15s %15s\n",  listaContribuyentes[i].id,
														 listaContribuyentes[i].nombre,
														 listaContribuyentes[i].apellido,
														 listaContribuyentes[i].cuil,
														 listaRecaudaciones[j].descripcion
												);
				}
				/*else
				{
					printf("%2d %15s %15s %15s\n",  listaContribuyentes[i].id,
													listaContribuyentes[i].nombre,
													listaContribuyentes[i].apellido,
													listaContribuyentes[i].cuil
													);
					break;
				}*/
			}
		}
	 }
	printf("*******************************************************************************\n");
}

void ListarRecaudaciones(eRecaudacion* listaRecaudaciones, int tamRecaudaciones, eContribuyente* listaContribuyentes, int tam)
{
	int i;
	int j;

		printf("*******************************************************************************\n");
		for(i=0; i<tamRecaudaciones; i++)
		{
			if(listaRecaudaciones[i].isEmpty == OCUPADO)
			{
				for(j=0; i<tam; j++)
				{
					if(listaContribuyentes[i].isEmpty == OCUPADO)
					{
						printf("%2d %2d %15s %2d %15s %15s\n",  listaRecaudaciones[i].idRecaudacion,
															 	listaRecaudaciones[i].mes,
																listaRecaudaciones[i].descripcion,
																listaRecaudaciones[i].importe,
																listaContribuyentes[j].cuil,
																listaContribuyentes[j].nombre
														);
						break;
					}
				}
			}
		}
		printf("*******************************************************************************\n");
}


int EncontrarContribuyentePorID(eContribuyente* listaContribuyentes, int tam, int id)
{
	int i;
	int index = -1;

	for(i=0; i<tam; i++)
	{
		if(listaContribuyentes[i].isEmpty == OCUPADO)
		{
			if(listaContribuyentes[i].id == id)
			{
				index = 0;
				break;
			}
		}
	}

	return index;
}

int RefinanciarRecaudacion(eRecaudacion* listaRecaudaciones, int tamR, eContribuyente* listaContribuyentes, int tam)
{
	int refinanciar = -1;
	int respuesta;
	int idIngresado;

	utn_getInt(&idIngresado, "Ingrese el ID de la recaudacion: ", "Error ingrese un id valido\n", 100, tamR, 5);

	ListarContribuyentes(listaContribuyentes, tam, listaRecaudaciones, tamR);

	utn_getInt(&respuesta, "¿Esta seguro que desea cambiar el estado a 'refinanciar'? 1[si]/2[no]", "Error, ingrese una respuesta valida", 1, 2, 5);

	if(respuesta == 1)
	{
		refinanciar = 1;
	}

	return refinanciar;
}

int SaldarRecaudacion(eRecaudacion* listaRecaudaciones, int tamR, eContribuyente* listaContribuyentes, int tam)
{
	int respuesta;
	int idIngresado;
	int retorno = -1;

	utn_getInt(&idIngresado, "Ingrese el ID de la recaudacion: ", "Error ingrese un id valido\n", 100, tamR, 5);

	ListarContribuyentes(listaContribuyentes, tam, listaRecaudaciones, tamR);

	utn_getInt(&respuesta, "¿Esta seguro que desea cambiar el estado a 'saldado'? 1[si]/2[no]", "Error, ingrese una respuesta valida", 1, 2, 5);

	if(respuesta == 1)
	{
		retorno = 1;
	}

	return retorno;
}


/*int Informes(eRecaudacion* listaRecaudaciones, int tamR, eContribuyente* listaContribuyentes, int tam)
{
	int opcion;
	int retorno = -1;

	do
	{
		printf("1- Contribuyentes con más recaudaciones en estado “refinanciar”\n");
		printf("2- Cantidad de recaudaciones saldadas de importe mayor a 1000\n");
		printf("3- Informar todos los datos de los contribuyentes de un tipo de recaudación ingresada por el usuario\n");
		printf("4- Nombre y c.u.i.l. de los Contribuyentes que pagaron impuestos en el mes de FEBRERO\n");
		printf("5- Salir\n");

		utn_getInt(&opcion, "Ingrese una opcion: ", "Error elija una opcion valida", 1, 5, 5);

		switch(opcion)
		{
			case 1:

			break;

			case 2:
			break;

			case 3:
			break;

			case 4:
			break;

			case 5:
			break;
		}

	}while(opcion!=5);
}*/

