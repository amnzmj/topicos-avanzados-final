#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>

using namespace std;

enum TipoEspacio { NORMAL, ELECTRICO }; //para solo usar estos valores en vez de 0 o 1, agregar discap y carga y descarga opcional

struct Espacio { //agrupar diferentes tipos de datos bajo un solo nombre
    bool ocupado = false;
    TipoEspacio tipo;
};//espacio tiene dos propiedades tipo y si está ocupado
//usar esto ahorra mucho desmadre

map<string, Espacio> estacionamiento;
queue<string> fila_espera;

void inicializarEstacionamiento() { //inicia cantidad de lugares, ocupacion y tipo
    estacionamiento["E1"] = {false, NORMAL};
    estacionamiento["E2"] = {false, NORMAL};
    estacionamiento["E3"] = {false, NORMAL};
    estacionamiento["E4"] = {false, NORMAL};
    estacionamiento["C1"] = {false, ELECTRICO};
    estacionamiento["C2"] = {false, ELECTRICO};
}//añadir mas, desocupados por default1

int main() {
    inicializarEstacionamiento();
    int opcion;
    string idAuto, idEspacio;
    do {
        cout << "\n\n\033[34m----menu----\033[0m\n";
        cout << "\n1. Mostrar estado\n";
        cout << "2. Estacionar auto normal\n";
        cout << "3. Estacionar auto eléctrico\n";
        cout << "4. Liberar espacio\n";
        cout << "5. Visualizar estacionamiento\n";
        cout << "6. Salir\n\n";
        cout << "Selecciona una opción: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "mostrar estado";
                //mostrarEstado();
                break;
            case 2:
                cout << "ID del auto: ";
                cin >> idAuto;
                //asignarEspacio(idAuto, NORMAL);
                break;
            case 3:
                cout << "ID del auto: ";
                cin >> idAuto;
                //asignarEspacio(idAuto, ELECTRICO);
                break;
            case 4:
                cout << "ID del espacio a liberar: ";
                cin >> idEspacio;
                //liberarEspacio(idEspacio);
                break;
            case 5:
                //dibujarEstacionamiento();
                break;
            case 6:
                cout << "exit\n";
                break;
            default:
                cout << "opcion no valida.\n";
        }
    } while (opcion != 6);
    return 0;
}
