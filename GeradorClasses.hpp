#ifndef GERADOR_CODIGO_JSON_HPP
#define GERADOR_CODIGO_JSON_HPP

#include "Classe.hpp"

#include <bits/stdc++.h>

void trataEntrada(char);
void imprimeClasses(FILE *);
void imprimeAtributos(Classe*, FILE *);
bool IdExiste(std::string, Classe*);


//class GeradorCodigoJson {
//public:
//    void trataEntrada();
//    void imprimeObjetos();
//    void imprime(Objeto* objeto);
//private:
//    bool verificaSeIdExiste(std::string id);
//    std::vector<Objeto*> objetos;
//};

#endif
