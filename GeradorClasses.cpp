#include "GeradorClasses.hpp"

#include <stdio.h>

std::vector<Classe*> classes;

bool IdExiste (std::string id, Classe* estaClasse) {
    if(classes.size() > 0) {
        for (auto atributo : estaClasse->atributos_string)
            if(atributo == id)
                return true;
        for (auto atributo : estaClasse->atributos_lista)
            if(atributo == id)
                return true;        
    }
    
    for (auto cls : classes)
        if(cls->nome == id)
            return true;

    return false;
}


void limpa_entrada (size_t i, std::string linha, char abre_bloco) {
    char fecha_bloco;
    int cont = 1;
    if (abre_bloco == '[')
        fecha_bloco = ']';
    else
        fecha_bloco = '}';
    i++;
    do {
        while (i < linha.size()) {
            if (linha[i] == abre_bloco)
                cont++;
            else if (linha[i] == fecha_bloco) {
                if (--cont == 0)
                return;
            }
            i++;
        }
        linha.clear();
        i = 0;
    } while (getline(std::cin, linha));
}


void trataEntrada(char abre_bloco) {
    std::string linha;
    std::string id;
    Classe* classeAtual;
    
    if (abre_bloco != '\0')  //Se foi chamado recursivamente, classe já foi criada
        classeAtual = classes.back();
    
    while (getline(std::cin, linha)) {
        for (size_t i = 0; i < linha.size(); i++) {
            if(linha[i] == '"') {
                for( i++; (i < linha.size()) && (linha[i] != '"'); i++)
                    id.push_back(linha[i]);

                for (i++; i < linha.size(); i++) {
                    if (linha[i] == '"' && IdExiste(id, classeAtual) == false) {
                        classeAtual->atributos_string.push_back(id);
                    }
                    if((linha[i] == '{') || (linha[i] == '[')) {
                        if (IdExiste(id, classeAtual) == false) {
                            if(abre_bloco != '\0') {
                                classeAtual->atributos_lista.push_back(id);
                                Classe* classe{new Classe};
                                classe->nome = id;
                                classes.push_back(classe);
                            }
                            else {
                                classeAtual = new Classe;
                                classeAtual->nome = id;
                                classes.push_back(classeAtual);
                            }   
                            trataEntrada(linha[i]);
                            break;
                        }
                        else {
                           classeAtual->atributos_lista.push_back(id);
                           limpa_entrada (i, linha, linha[i]);
                           break;
                        }
                    }
                }
                id.clear();
            }

            if(linha[i] == ']')
                return;
            
            if (linha[i] == '}') {
                if (abre_bloco == '[') {
                    limpa_entrada (i, linha, '[');
                    return;
                }
                else
                    return;
            } 
        }
    }
}


void imprimeAtributos(Classe* classe, FILE *saida) {
    std::string nome_tmp;
    for (auto atributo : classe->atributos_string) {
        fprintf (saida, "    String %s;\n", atributo.c_str());
    }
    
    for (auto lista : classe->atributos_lista) {
        nome_tmp = lista;
        fprintf (saida, "    ArrayList<%s>", lista.c_str());
        nome_tmp[0] = std::tolower(nome_tmp[0]);
        fprintf (saida, "%s", nome_tmp.c_str());
        if (nome_tmp.back() != 's')
            fputc ('s', saida);
        fputc(';', saida);
        fputc('\n', saida);
    }
    fputc('}', saida);
    fputc('\n', saida);
    fputc('\n', saida);
}


void imprimeClasses(FILE *saida) {
    for (auto classe : classes) {
        fprintf (saida, "class %s {\n", classe->nome.c_str());
        imprimeAtributos (classe, saida);
    }
    fprintf (saida, "class Programa {\n");
    fprintf (saida, "    public static void main (String args[]){\n");
    fprintf (saida, "    }\n");
    fprintf (saida, "}\n");
}
