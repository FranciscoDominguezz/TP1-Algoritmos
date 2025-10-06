# TP1 - Algoritmos y Estructuras de Datos

**Nombre:** Francisco Dominguez Navarro 
**Comisión:** K1043


## Versión de g++
g++ (MinGW.org GCC-6.3.0-1) 6.3.0 


## Descripción del Trabajo

Sistema de gestión de reparaciones que permite consultar reparaciones realizadas a clientes. Lee dos archivos binarios (productos y reparaciones), ordena los datos y permite buscar todas las reparaciones de un cliente específico, mostrando costos y calculando ganancias.


## Estructuras de Datos

- **Producto**, que cuenta con SKU, Descripción y Costo Fijo
- **Reparación**, que cuenta con Cliente, Tipo de Producto, SKU, Costo Directo y Presupuestado 


## Funciones

### Lectura de Archivos
La función `contarReparaciones()` hace una primera lectura del archivo para saber cuántos registros hay, y en base a eso reserva la 
memoria que va a necesitar con punteros. Las funciones `leerProductos()` y `leerReparaciones()` leen los archivos binarios campo por campo

### Ordenamiento y búsqueda
La función `shellSort()` implementa el algoritmo de ordenamiento shell usando templates para poder ordenar cualquier tipo de dato. La función 
`buscar_lineal_ord()` hace una búsqueda lineal ordenada en un arreglo que ya está ordenado también usando templates. Las funciones `criterioReparación()` y `criterioCliente()` establecen criterios de ordenamiento y definen cómo se comparan las reparaciones (primero por cliente, luego por tipo de producto, finalmente por SKU) y clientes respectivamente

### Cálculos y utilidades 
La función `obtenerTipoProducto()` convierte el código numérico del tipo de producto a su descripción en texto. La función `buscarCostoFijo()` y `buscarDescripcionProducto()` buscan información del producto en cuestión en base al SKU del mismo. La función `calcularGanancia()` resta los costos del precio presupuestado para obtener la ganancia

### Conversión de datos
La función `charToString()` convierte los campos de caracteres a strings eliminando los espacios de relleno que tienen al final. La función `rellenarCampo()` hace la operación inversa: toma un string y lo convierte en un campo de caracteres con espacios de relleno, necesario para crear la clave de búsqueda


## Librería Agregada

La librería `iomanip` (con manipuladores `setw`, `left`, `right`, `fixed`, `setprecision`) para alinear la salida de datos acorde al archivo salida.txt de los archivos complementarios del TP y mostrar los datos en formato de tabla alineada


## Para compilar y ejecutar

Ejemplo en CMD parándose en la carpeta del trabajo: 

g++ main.cpp -o programa 
programa.exe 


## Archivos Necesarios

- `productos.bin`
- `reparaciones.bin`