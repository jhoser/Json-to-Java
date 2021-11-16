#include "GeradorClasses.hpp"

int main () {
    FILE *saida;
    saida = fopen("Classes.java", "w");
    while(!std::cin.eof())
        trataEntrada('\0');
    imprimeClasses(saida);
    fclose (saida);
    return 0;
}
