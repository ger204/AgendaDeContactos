#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <conio.h>
using namespace std;
const char DIR_ARCHIVO[] = "contactos.dat";

struct Contacto{
  char nombre[30];
  char apellido[45];
  int edad;
  char correo[45];
  char telefono[16];
};

/**FUNCIONES DEL PROGRAMA**/
void ingresarContacto(Contacto c);
Contacto leerContacto();
bool existeContacto(char nombre[], char apellido[]);
Contacto buscarContacto(char nombre[], char apellido[]);
void mostrarContacto(Contacto c);
void listarContactos();
void eliminarContacto(char nombre[],char apellido[]);
void acctualizarContacto(char nombre[],char apellido[]);
/*****************************/

/**FUNCIONES PARA EL MENÚ**/
void menuIngresar();
void menuBuscar();
void menuListado();
void menuEliminar();
void menuActualizar();
/*****************************/
/**Estetica**/
void hastaPronto();
/*****************************/
int main(){
  system("color f0");
  int op;
  int yn = 0;
  do {
    system("cls");
    std::cout << "\t\t\t=======================================" << '\n';
    std::cout << "\t\t\t||                                   ||" << '\n';
    std::cout << "\t\t\t||             AGENDA                ||" << '\n';
    std::cout << "\t\t\t||                                   ||" << '\n';
    std::cout << "\t\t\t||  Ingresar Contacto...........[1]  ||" << '\n';
    std::cout << "\t\t\t||  Buscar Contacto.............[2]  ||" << '\n';
    std::cout << "\t\t\t||  Listar Contactos............[3]  ||" << '\n';
    std::cout << "\t\t\t||  Eliminar Contacto...........[4]  ||" << '\n';
    std::cout << "\t\t\t||  Actualizar Contacto.........[5]  ||" << '\n';
    std::cout << "\t\t\t||  SALIR.......................[6]  ||" << '\n';
    std::cout << "\t\t\t||                                   ||" << '\n';
    std::cout << "\t\t\t=======================================" << '\n';
    std::cout << "\t\t\t    Ingrese una opcion ->";
    std::cin >> op;
    cin.ignore();
    switch (op) {
      case 1: system("cls"); //CLS = CLean Screen (en la lib <cstdlib> )
              menuIngresar();
              break;
      case 2: system("cls");
              menuBuscar();
              break;
      case 3: system("cls");
              menuListado();
              break;
      case 4: system("cls");
              menuEliminar();
              break;
      case 5: system("cls");
              menuActualizar();
              break;
      case 6: system("cls");
              do {
                std::cout << "\t\t\tSeguro que quieres SALIR? SI[1].....NO[2]: ";
                std::cin >> yn;
                if (yn != 1 &&  yn != 2) {
                  std::cout << "\t\t\t" << yn << " NO es una opcion valida" << '\n';
                }
              } while(yn != 1 && yn !=2);
              system("cls");
              hastaPronto();
              break;

      default: std::cout << "\t\t\tOpcion incorrecta" << '\n';
               break;
    }
  } while(op != 6 || yn == 0 || yn ==2);

  return 0;
}

/*PROGRAMA*/

//Ingresar Contacto
void ingresarContacto(Contacto c){
  ofstream salida;
  salida.open(DIR_ARCHIVO,ios::binary | ios::app);
  salida.write((char*)&c,sizeof (Contacto));
  salida.close();
}

Contacto leerContacto(){
  Contacto c;
  std::cout << "\t\t\tNOMBRE   : ";
  cin.getline(c.nombre,30);
  std::cout << "\t\t\tAPELLIDO : ";
  cin.getline(c.apellido,45);
  std::cout << "\t\t\tEDAD     : ";
  cin >> c.edad;
  cin.ignore();
  std::cout << "\t\t\tCORREO   : ";
  cin.getline(c.correo,45);
  std::cout << "\t\t\tTELEFONO : ";
  cin.getline(c.telefono,16);
  return c;
}

//Buscar Contacto
bool existeContacto(char nombre[], char apellido[]){
  Contacto c;
  ifstream entrada;
  entrada.open(DIR_ARCHIVO,ios::binary);
  if (entrada.good()) {
    while(entrada.read( (char*) &c, sizeof(Contacto) )){
      /*strmcp --- string comparation --- comparacion de cadena*/
      if ( strcmp (nombre, c.nombre) == 0 && strcmp (apellido, c.apellido) == 0) {
        entrada.close();
        return true;
      }
    }
    entrada.close();
    return false;
  }

  else{
    entrada.close();
    return false;
  }
}

Contacto buscarContacto(char nombre[], char apellido[]){
  Contacto c;
  ifstream entrada;
  entrada.open(DIR_ARCHIVO,ios::binary);
  if (entrada.good()) {
    while(entrada.read( (char*) &c, sizeof(Contacto) )){
      /*strmcp --- string comparation --- comparacion de cadena*/
      if ( strcmp (nombre, c.nombre) == 0 && strcmp (apellido, c.apellido) == 0) {
        entrada.close();
        return c;
      }
    }
  }
}

void mostrarContacto(Contacto c){
  std::cout << '\n';
  std::cout << "\t\t\tNOMBRE   : " << c.nombre << '\n';
  std::cout << "\t\t\tAPELLIDO : " << c.apellido << '\n';
  std::cout << "\t\t\tEDAD     : " << c.edad << '\n';
  std::cout << "\t\t\tCORREO   : " << c.correo << '\n';
  std::cout << "\t\t\tTELEFONO : " << c.telefono << '\n';
  std::cout << '\n';
}

//Listar Contactos
void listarContactos(){
  ifstream entrada;
  entrada.open(DIR_ARCHIVO,ios::binary);
  Contacto c;
  if(entrada.good()){
    while(entrada.read( (char*) &c , sizeof (Contacto) )){
      mostrarContacto(c);
    }
    entrada.close();
  }

  else{
    std::cout << "NO se puede leer el archivo" << '\n';
    entrada.close();
  }
}

//Eliminar Contacto
void eliminarContacto(char nombre[],char apellido[]){
  ifstream entrada;
  ofstream temporal;

  entrada.open(DIR_ARCHIVO,ios::binary);
  temporal.open("temp.dat",ios::binary);

  Contacto c;
  if(entrada.good()){
    while(entrada.read( (char*) &c , sizeof (Contacto) )){
      if ( strcmp (nombre, c.nombre) != 0 || strcmp (apellido, c.apellido) != 0) {
        temporal.write( (char*) &c, sizeof(Contacto) );
      }
    }
  }
  entrada.close();
  temporal.close();

  remove(DIR_ARCHIVO);
  rename("temp.dat",DIR_ARCHIVO);
}

//Acctualizar Contacto
void acctualizarContacto(char nombre[],char apellido[]){
  ifstream entrada;
  ofstream temporal;

  entrada.open(DIR_ARCHIVO,ios::binary);
  temporal.open("temp.dat",ios::binary);

  Contacto c;
  if(entrada.good()){
    while(entrada.read( (char*) &c , sizeof (Contacto) )){
      if ( strcmp (nombre, c.nombre) == 0 && strcmp (apellido, c.apellido) == 0) {
        Contacto actualizado = leerContacto();
        temporal.write( (char*) &actualizado, sizeof(Contacto) );
      }
      else{
        temporal.write( (char*) &c, sizeof(Contacto) );
      }
    }
  }
  entrada.close();
  temporal.close();

  remove(DIR_ARCHIVO);
  rename("temp.dat",DIR_ARCHIVO);
}
/**********************************************************/

/*MENU*/
void menuIngresar(){
  std::cout << "\t\t\t\t---------------------------" << '\n';
  std::cout << "\t\t\t\t INGRESO DE NUEVO CONTACTO" << '\n';
  std::cout << "\t\t\t\t---------------------------" << '\n';
  Contacto nuevo = leerContacto();
  ingresarContacto(nuevo);
  std::cout << "\t\t\tContacto agregado con exito" << '\n';
  getch();
}

void menuBuscar(){
  Contacto buscado;
  std::cout << "\t\t\t\t-----------------" << '\n';
  std::cout << "\t\t\t\t BUSCAR CONTACTO" << '\n';
  std::cout << "\t\t\t\t-----------------" << '\n';
  char nombre[30],apellido[45];
  std::cout << "\t\t\tIngrese los datos de busqueda:" << '\n';
  std::cout << "\t\t\tNOMBRE  :";
  cin.getline(nombre,30);
  std::cout << "\t\t\tAPELLIDO:";
  cin.getline(apellido,45);
  if (existeContacto(nombre,apellido)) {
    Contacto buscado = buscarContacto(nombre,apellido);
    mostrarContacto(buscado);
    getch();
  }
  else{
    std::cout << "\t\t\tNO se encuentra ese contacto";
    getch();
  }
}

void menuListado(){
  std::cout << "\t\t\t\t---------------" << '\n';
  std::cout << "\t\t\t\tLISTA CONTACTOS" << '\n';
  std::cout << "\t\t\t\t---------------" << '\n';
  listarContactos();
  getch();//Obtener caracter (en la lib <conio.h>)
}

void menuEliminar(){
  std::cout << "\t\t\t\t-------------------" << '\n';
  std::cout << "\t\t\t\t ELIMINAR CONTACTO" << '\n';
  std::cout << "\t\t\t\t-------------------" << '\n';
  char nombre[30],apellido[45];
  std::cout << "\t\t\tIngrese los datos de eliminacion:" << '\n';
  std::cout << "\t\t\tNOMBRE  :";
  cin.getline(nombre,30);
  std::cout << "\t\t\tAPELLIDO:";
  cin.getline(apellido,45);
  if (existeContacto(nombre,apellido)) {

    Contacto eliminar = buscarContacto(nombre,apellido);
    int opcion;
    std::cout << "\t\t\t-Seguro que desea eliminar el siquiente contacto?";
    mostrarContacto(eliminar);

    do {
      std::cout << "\t\t\tSI[1].....NO[2]: ";
      std::cin >> opcion;
      switch (opcion) {
        case 1: eliminarContacto(nombre,apellido);
                std::cout << "\t\t\tContacto ELIMINADO con exito" << '\n';
                getch();
                break;

        case 2: std::cout << "\t\t\tSe ha CANCELADO la eliminacion" << '\n';
                getch();
                break;

        default: std::cout << "\t\t\tOPCION INCORRECTA" << '\n';
      }
    } while(opcion != 1 && opcion != 2);
  }
  else{
    std::cout << "\t\t\tNO EXISTE EL CONTACTO" << '\n';
    getch();
  }
}

void menuActualizar(){
  std::cout << "\t\t\t\t--------------------" << '\n';
  std::cout << "\t\t\t\t ACTALIZAR CONTACTO" << '\n';
  std::cout << "\t\t\t\t--------------------" << '\n';
  char nombre[30],apellido[45];
  std::cout << "\t\t\tIngrese los datos de modificacion:" << '\n';
  std::cout << "\t\t\tNOMBRE  :";
  cin.getline(nombre,30);
  std::cout << "\t\t\tAPELLIDO:";
  cin.getline(apellido,45);
  std::cout <<'\n';

  if (existeContacto(nombre,apellido)) {
    Contacto buscado = buscarContacto(nombre,apellido);
    std::cout << "\t\t\tRegistro a modificar:";
    mostrarContacto(buscado);
    acctualizarContacto(nombre,apellido);
    std::cout << "\t\t\tSE ACTUALIZO EL CONTACTO" << '\n';
    getch();
  }
  else{
    std::cout << "\t\t\tNO EXISTE EL CONTACTO" << '\n';
    getch();
  }
}

/*Estetica*/
void hastaPronto(){
  std::cout << "\t\t\t      HHH   HHH   AAAAAAAAA    SSSSSSS    TTTTTTTTTTT   AAAAAAAAA" << '\n';
  std::cout << "\t\t\t      HHH   HHH   AAA   AAA   SSS             TTT       AAA   AAA" << '\n';
  std::cout << "\t\t\t      HHHHHHHHH   AAAAAAAAA     SSS           TTT       AAAAAAAAA" << '\n';
  std::cout << "\t\t\t      HHH   AAA   AAA   AAA      SSS          TTT       AAA   AAA" << '\n';
  std::cout << "\t\t\t      HHH   HHH   AAA   AAA   SSSSSSS         TTT       AAA   AAA"  << '\n';
  std::cout << '\n';
  std::cout << "\t\t\tPPPPPPPPP   RRRRRRRRR   OOOOOOOOO   NNN     NNN   TTTTTTTTTTT   OOOOOOOOO" << '\n';
  std::cout << "\t\t\tPPP   PPP   RRR   RR    OOO   OOO   NNNNN   NNN       TTT       OOO   OOO" << '\n';
  std::cout << "\t\t\tPPPPPPPPP   RRRRRRR     OOO   OOO   NNN NN  NNN       TTT       OOO   OOO" << '\n';
  std::cout << "\t\t\tPPP         RRR  RR     OOO   OOO   NNN  NN NNN       TTT       OOO   OOO" << '\n';
  std::cout << "\t\t\tPPP         RRR   RRR   OOOOOOOOO   NNN   NNNNN       TTT       OOOOOOOOO"  << '\n';
}
/******************/
