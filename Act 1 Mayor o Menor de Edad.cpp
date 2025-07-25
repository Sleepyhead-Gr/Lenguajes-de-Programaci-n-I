// Código en C++ que permite determinar si el usuario es mayor de Edad.
// Author: Grecia A. Reyes Gastelum
// Fecha: 24/07/25

#include <iostream>
using namespace std;

int main() {
    int edad;

    cout << "Ingrese su edad: ";
    cin >> edad;

    // Determinar si es mayor de edad o tiene justo 18 años
    if (edad > 18) {
        cout << "Usted es mayor de edad." << endl;
    } 
    else if (edad == 18) {
        cout << "¡Felicidades! Eres justo mayor de edad." << endl;
    } 
    else {
        cout << "Usted es menor de edad." << endl;
    }

    return 0;
}
