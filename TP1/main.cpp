#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Producto {
    char sku[10];
    char descripcion[20];
    float costoFijo;
};


struct Reparacion {
    char cliente[15];
    int tipoProducto;
    char sku[10];
    float costoDirecto;
    float presupuestado;
};

string charToString(const char* campo, int tam) {
    string resultado = "";
    int i;

    for (i = 0; i < tam && campo[i] != '\0'; i++) {
        resultado += campo[i];
    }

    i = resultado.length() - 1;
    while (i >= 0 && resultado[i] == ' ') {
        i--;
    }

    string resultadoFinal = "";
    for (int j = 0; j <= i; j++) {
        resultadoFinal += resultado[j];
    }

    return resultadoFinal;
}


string obtenerTipoProducto (int codigo) { 
    if (codigo == 0) {
        return "Electrónico";
    }
    if (codigo == 1) {
        return "Mecánico";
    }
    if (codigo == 2) {
        return "Mecatrónico";
    }
    return "???";
}

bool criterioReparacion (const Reparacion& r1, const Reparacion& r2) { 
    string cliente1 = charToString(r1.cliente, 15);
    string cliente2 = charToString(r2.cliente, 15);

    if (cliente1 != cliente2) {
        return cliente1 < cliente2;
    }

    if (r1.tipoProducto != r2.tipoProducto) {
        return r1.tipoProducto < r2.tipoProducto;
    }

    string sku1 = charToString(r1.sku, 10);
    string sku2 = charToString(r2.sku, 10);
    return sku1 < sku2;
}

bool criterioCliente(const Reparacion& r1, const Reparacion& r2) {
    string cliente1 = charToString(r1.cliente, 15);
    string cliente2 = charToString(r2.cliente, 15);
    return cliente1 < cliente2;
}

template <typename T, typename Criterio> void shellSort(T v[], int dim, Criterio criterio) {
    int i, j, gap;
    T temp;

    gap = dim / 2;
    while (gap > 0) {
        for (i = gap; i < dim; i++) {
            temp = v[i];
            j = i - gap;
            while ((j >= 0) && criterio(temp, v[j])) {
                v[j + gap] = v[j];
                j -= gap;
            }
			v[j + gap] = temp;
        }
        gap /= 2;
    }
}

template <typename T, typename Criterio> int buscar_lineal_ord(T v[], int dim, T clave, Criterio criterio) {
    int i;
    for (i = 0; i < dim && criterio(v[i], clave); i++);
    return (i < dim && !criterio(clave, v[i])) ? i : -1;
}

int leerProductos(Producto productos[], const string& nombreArchivo) {
    ifstream archi;
    archi.open(nombreArchivo, ios::in | ios::binary);

    if (!archi) {
        cout << "Error al tratar de abrir el archivo" << endl;
		return 0;
    }

    int cantProductos;
    int tope = 10;

    for (cantProductos = 0; cantProductos < tope; cantProductos++) {
        archi.read(productos[cantProductos].sku, 10);
        archi.read(productos[cantProductos].descripcion, 20);
        archi.read(reinterpret_cast<char*>(&productos[cantProductos].costoFijo), sizeof(float));

        if (!archi) {
            break;
        }
    }

    archi.close();
    return cantProductos;
}   

int contarReparaciones(const string& nombreArchivo) {
    ifstream archi;
    archi.open(nombreArchivo, ios::in | ios::binary);

    if (!archi) {
        cout << "Error al tratar de abrir el archivo" << endl;
        return 0;
    }

    int cant = 0;
    Reparacion temp;

    while (true) {
        archi.read(temp.cliente, 15);
        if (!archi) {
            break;
        }
        archi.read(reinterpret_cast<char*>(&temp.tipoProducto), sizeof(int));
        archi.read(temp.sku, 10);
        archi.read(reinterpret_cast<char*>(&temp.costoDirecto), sizeof(float));
        archi.read(reinterpret_cast<char*>(&temp.presupuestado), sizeof(float));

        cant++;
    }

    archi.close();
    return cant;
}

int leerReparaciones(Reparacion reparaciones[], const string& nombreArchivo) {
    ifstream archi;
    archi.open(nombreArchivo, ios::in | ios::binary);

    if (!archi) {
        cout << "Error al tratar de abrir el archivo" << endl;
        return 0;
    }

    int cantReparaciones = 0;

    while (true) {
        archi.read(reparaciones[cantReparaciones].cliente, 15);
        if (!archi) {
            break;
        }
        archi.read(reinterpret_cast<char*>(&reparaciones[cantReparaciones].tipoProducto), sizeof(int));
        archi.read(reparaciones[cantReparaciones].sku, 10);
        archi.read(reinterpret_cast<char*>(&reparaciones[cantReparaciones].costoDirecto), sizeof(float));
        archi.read(reinterpret_cast<char*>(&reparaciones[cantReparaciones].presupuestado), sizeof(float));

        cantReparaciones++;
    }

    archi.close();
    return cantReparaciones;
}

float buscarCostoFijo(Producto productos[], int cantProductos, const string& sku) {
    for (int i = 0; i < cantProductos; i++) {
        string skuProducto = charToString(productos[i].sku, 10);
        if (skuProducto == sku) {
            return productos[i].costoFijo;
        }
    }
    return -1; 
}

string buscarDescripcionProducto(Producto productos[], int cantProductos, const string& sku) {
    for (int i = 0; i < cantProductos; i++) {
        string skuProducto = charToString(productos[i].sku, 10);
        if (skuProducto == sku) {
            return charToString(productos[i].descripcion, 20);
        }
    }
    return "No encontrado";
}

float calcularGanancia(const Reparacion& reparacion, float costoFijo) {
    return reparacion.presupuestado - (reparacion.costoDirecto + costoFijo);
}

void rellenarCampo(char campo[], const string& valor, int tam) {
    for (int i = 0; i < tam; i++) {
        if (i < valor.length()) {
            campo[i] = valor[i];  
        } else {
            campo[i] = ' ';       
        }
    }
}
int main() {
    Producto productos[10];

    int cantProductos = leerProductos(productos, "productos.bin");

    if (cantProductos == 0) {
        cout << "Error al cargar archivo de productos" << endl;
        return 0;
    }

    int cantReparaciones = contarReparaciones("reparaciones.bin");

    if (cantReparaciones == 0) {
        cout << "Error al cargar archivo de reparaciones" << endl;
        return 0;
    }

    Reparacion* reparaciones = new Reparacion[cantReparaciones];

    leerReparaciones(reparaciones, "reparaciones.bin");
    shellSort(reparaciones, cantReparaciones, criterioReparacion);

    string clienteBuscado;
    cout << "Ingrese el cliente a consultar: ";

    while (getline(cin, clienteBuscado)) {
        if (clienteBuscado == "") {
             cout << "\nIngrese el cliente a consultar: ";
            continue;
        }
        
        Reparacion clave;
        rellenarCampo(clave.cliente, clienteBuscado, 15);
        
        int pos = buscar_lineal_ord(reparaciones, cantReparaciones, clave, criterioCliente);

        if (pos == -1) {
            cout << "Cliente no encontrado." << endl;
        } else {
            cout << left << setw(18) << "Cliente"
                 << setw(15) << "Tipo Prod."
                 << setw(12) << "SKU"
                 << setw(20) << "Producto"
                 << right << setw(15) << "Costo Fijo"
                 << setw(15) << "Costo Direc."
                 << setw(15) << "Presupuestado" << endl;

            float gananciaTotal = 0;

            for (int i = pos; i < cantReparaciones; i++) {
                string clienteActual = charToString(reparaciones[i].cliente, 15);

                if (clienteActual != charToString(clave.cliente, 15)) {
                    break; 
                }

                string skuReparacion = charToString(reparaciones[i].sku, 10);
                float costoFijo = buscarCostoFijo(productos, cantProductos, skuReparacion);

                if (costoFijo < 0) {
                    cout << "Costo fijo no encontrado para SKU: " << skuReparacion << endl;
                    continue;
                }

                string descripcion = buscarDescripcionProducto(productos, cantProductos, skuReparacion);
                float ganancia = calcularGanancia(reparaciones[i], costoFijo);

                cout << left << setw(18) << clienteActual
                     << setw(15) << obtenerTipoProducto(reparaciones[i].tipoProducto)
                     << setw(12) << skuReparacion
                     << setw(20) << descripcion
                     << right << fixed << setprecision(2)
                     << setw(15) << costoFijo
                     << setw(15) << reparaciones[i].costoDirecto
                     << setw(15) << reparaciones[i].presupuestado << endl;

                gananciaTotal += ganancia;
            }

            cout << "Ganancia total: " << fixed << setprecision(2) << gananciaTotal << endl;
        }

        cout << "\nIngrese el cliente a consultar: ";
    }
    delete[] reparaciones;
    return 0;
}
