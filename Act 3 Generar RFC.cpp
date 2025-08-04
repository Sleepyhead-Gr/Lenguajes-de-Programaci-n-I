// Código en C++ que permite generar RFC sin homoclave
// Author: Grecia A. Reyes Gastelum
// Fecha: 03/08/25

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept> 
#include <regex>     // Se usa para validar el formato de fecha

// Diccionario de palabras que NO permitimos!
const std::vector<std::string> palabrasProhibidas = {
    "PENE", "POPO", "PUTO", "MAMO", "CULO", "QULO", "TETA", "PEDO", "JOTO",
    "VERG", "KAKA", "CAGO", "CAGA", "FETO", "PUTA", "RUIN", "COGE", "COJE",
    "KULO", "MION", "PITO", "LOCO", "VAGO", "VAGA", "SENO"
};

// Validar y modificar palabras prohibidas del Diccionario
std::string corregirRFC(const std::string rfc) {
    for (const std::string& palabra : palabrasProhibidas) {
        if (rfc == palabra) {
            return rfc.substr(0, 3) + "X"; // Remplaza la última letra por 'X'
        }
    }
    return rfc;
}

// Función para obtener la primera vocal interna de una cadena ingresada
char obtenerPrimeraVocalInterna(const std::string& str) {
    for (size_t i = 1; i < str.length(); i++) {
        char c = std::toupper(str[i]);
        if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            return c;
        }
    }
    return 'X';
}

// Función para validar la fecha (YYYY-MM-DD) utilizando regex y un poco de lógica
bool validarFecha(const std::string& fecha) {
    // Verifica el formato de la fecha
    std::regex formatoFecha(R"(^\d{4}-\d{2}-\d{2}$)");
    if (!std::regex_match(fecha, formatoFecha)) {
        return false;
    }

    try {
        int anio = std::stoi(fecha.substr(0, 4));
        int mes = std::stoi(fecha.substr(5, 2));
        int dia = std::stoi(fecha.substr(8, 2));

        if (anio < 1900 || anio > 2025) {
            return false;
        }

        if (mes < 1 || mes > 12) {
            return false;
        }

        int diasEnMes;
        if (mes == 2) {
            diasEnMes = 28;
        } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
            diasEnMes = 30;
        } else {
            diasEnMes = 31;
        }

        if (dia < 1 || dia > diasEnMes) {
            return false;
        }

    } catch (...) {
        return false;
    }

    return true;
}

// Función para generar el RFC y que este se obtenga en letras mayusculas
std::string calcularRFC(const std::string& nombre, const std::string& 
apellidoPaterno, const std::string& apellidoMaterno, const std::string& fechaNacimiento) {
    std::string rfc;

    char letraInicial = std::toupper(apellidoPaterno[0]);
    char primeraVocalInterna = obtenerPrimeraVocalInterna(apellidoPaterno);

    char inicialApellidoMaterno = (apellidoMaterno.empty()) ? 'X' : std::toupper(apellidoMaterno[0]);
    char inicialNombre = std::toupper(nombre[0]);

    std::string anio = fechaNacimiento.substr(2, 2);
    std::string mes = fechaNacimiento.substr(5, 2);
    std::string dia = fechaNacimiento.substr(8, 2);

    rfc = letraInicial;
    rfc += primeraVocalInterna;
    rfc += inicialApellidoMaterno;
    rfc += inicialNombre;

    rfc = corregirRFC(rfc);

    rfc += anio;
    rfc += mes;
    rfc += dia;

    return rfc;
}

// Aqui se pedira que se ingresen los datos del usuario

int main() {
    std::string nombre, apellidoPaterno, apellidoMaterno, fechaNacimiento;

    std::cout << "Introduce tu nombre: ";
    std::getline(std::cin, nombre);
    std::cout << "Introduce tu apellido paterno: ";
    std::getline(std::cin, apellidoPaterno);
    std::cout << "Introduce tu apellido materno (Si no cuenta con apellido materno, presione Enter): ";
    std::getline(std::cin, apellidoMaterno);

    bool fechaValida = false;
    while (!fechaValida) {
        std::cout << "Introduce la fecha de nacimiento en el siguiente formato (YYYY-MM-DD): ";
        std::getline(std::cin, fechaNacimiento);

        if (validarFecha(fechaNacimiento)) {
            fechaValida = true;
        } else {
            std::cout << "Error: Fecha no válida. Por favor, intente de nuevo." << std::endl;
        }
    }

    std::string rfc = calcularRFC(nombre, apellidoPaterno, apellidoMaterno, fechaNacimiento);
    std::cout << "RFC: " << rfc << std::endl;

    return 0;
}
