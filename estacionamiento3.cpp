#include <iostream>
#include <vector>//falta
#include <queue>
#include <string>
#include <map>

using namespace std;

enum TipoEspacio { NORMAL, ELECTRICO }; //para solo usar estos valores en vez de 0 o 1, agregar discap y carga y descarga opcional

struct Espacio { //agrupar diferentes tipos de datos bajo un solo nombre
    bool ocupado = false;
    TipoEspacio tipo;
    string idAuto = ""; //almacena el ID del auto
};//espacio tiene 3 propiedades tipo, si está ocupado y id del carro
//usar esto ahorra mucho desmadre

map<string, Espacio> estacionamiento;
queue<string> fila_espera;

void inicializarEstacionamiento() { //inicia cantidad de lugares, ocupacion y tipo
    estacionamiento["01"] = {false, NORMAL};
    estacionamiento["02"] = {false, NORMAL};
    estacionamiento["03"] = {false, NORMAL};
    estacionamiento["04"] = {false, NORMAL};
    estacionamiento["04"] = {false, NORMAL};
    estacionamiento["05"] = {false, NORMAL};
    estacionamiento["06"] = {false, NORMAL};
    estacionamiento["07"] = {false, NORMAL};
    estacionamiento["08"] = {false, ELECTRICO};
    estacionamiento["09"] = {false, ELECTRICO};
}//añadir mas, desocupados por default

void dibujarEstacionamiento() {
    string colorLibre = "\033[32m";   // Verde
    string colorOcupado = "\033[31m"; // Rojo
    string reset = "\033[0m";//reset necesario despues de asignar color

    cout << "\nVisualización del estacionamiento:\n";
    for (const auto& par : estacionamiento) {
        string tipo = (par.second.tipo == ELECTRICO) ? "E" : "N";
        string estado = par.second.ocupado ? "O" : "L";
        string color = par.second.ocupado ? colorOcupado : colorLibre;
        string info = par.second.ocupado ? (" - " + par.second.idAuto) : "";

        cout << color << "[" << par.first << " - " << tipo << "-" << estado << info << "] " << reset;//concatena todo el desmadre de claves valor y colores
    }
    cout << "\n\nLeyenda: N = Espacio normal, E = Estación eléctrica\n";
    cout << colorLibre << "         L = Libre (verde)   "<< reset << colorOcupado << "O = Ocupado (rojo)\n"<< reset;//trucazo para los colores
}

bool asignarEspacio(string idAuto, TipoEspacio preferido) {
    for (auto& par : estacionamiento) {//itera y deduce automaticamente el tipo de variable 
        if (!par.second.ocupado && par.second.tipo == preferido) {//si ese espacio no está ocupado y si el tipo del espacio es igual al tipo que el auto necesita
            
            par.second.ocupado = true;//lo marca entonces como ocupado
            par.second.idAuto = idAuto;
            cout << "Auto " << idAuto << " asignado a " << par.first << "\n";
            return true;
            //falta un else por si no encuentra espacio
        }
    }
    fila_espera.push(idAuto);
    cout << "no hay espacio disponible. " << idAuto << " a la espera.\n";
    return false;
}

void liberarEspacio(string idEspacio) {
    
    auto it = estacionamiento.find(idEspacio);
    if (it != estacionamiento.end() && it->second.ocupado) {
        it->second.ocupado = false;
        it->second.idAuto = "";
        cout << "espacio " << idEspacio << " ha sido liberado.\n";
        if (!fila_espera.empty()) {
            string siguiente = fila_espera.front();
            fila_espera.pop();
            asignarEspacio(siguiente, it->second.tipo);
        }
    } else {
        cout << "no existe espacio o esta libre\n";
    }
}

void mostrarEstado() {
    cout << "\nEstado del estacionamiento:\n";
    for (const auto& par : estacionamiento) {
        cout << par.first << " - "
             << (par.second.tipo == ELECTRICO ? "Eléctrico" : "Normal") << " - "
             << (par.second.ocupado ? ("Ocupado por " + par.second.idAuto) : "Libre") << "\n";
    }
    cout << "\nEn espera: ";
    if (fila_espera.empty()) cout << "ninguno\n";
    else {
        queue<string> copia = fila_espera;
        while (!copia.empty()) {
            cout << copia.front() << " ";
            copia.pop();
        }
        cout << "\n";
    }
}


int main() {
    inicializarEstacionamiento();
    int opcion;
    string idAuto, idEspacio;
    do {
        cout << "\n\n\033[34mmenu\033[0m\n";
        cout << "\n1. Mostrar estado\n";
        cout << "2 estacionar auto normal\n";
        cout << "3 estacionar auto eléctrico\n";
        cout << "4 eiberar espacio\n";
        cout << "5 dibujar estacionamiento\n";
        cout << "6 agregar carritto a la cola\n";
        cout << "7 salir\n\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                mostrarEstado();
                break;
            case 2:
                cout << "placa: ";
                cin >> idAuto;
                asignarEspacio(idAuto, NORMAL);
                break;
            case 3:
                cout << "placa: ";
                cin >> idAuto;
                asignarEspacio(idAuto, ELECTRICO);
                break;
            case 4:
                cout << "espacio a liberar: ";
                cin >> idEspacio;
                liberarEspacio(idEspacio);
                break;
            case 5:
                dibujarEstacionamiento();
                break;
            case 6:
                cout << "placa del auto a agregar a la fila: ";
                cin >> idAuto;
                fila_espera.push(idAuto);
                cout << "auto " << idAuto << " agregado a la fila de espera\n";
                break;
            case 7:
                cout << "bai\n";
                break;
            default:
                cout << "no valido\n";
        }
    } while (opcion != 7);//7 de salir
    return 0;
}
