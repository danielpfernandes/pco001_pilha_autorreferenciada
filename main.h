//
// Created by Daniel Paiva Fernandes on 29/09/2021.
//

#ifndef PCO001_PILHA_AUTORREFERENCIADA_MAIN_H
#define PCO001_PILHA_AUTORREFERENCIADA_MAIN_H

#include <iostream>
#include <cstring>
#include <utility>
#include <vector>

using namespace std;

typedef struct 
{
    string chave;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula 
{
    TipoItem item;
    TipoApontador prox{};
} TipoCelula;

typedef struct
{
    TipoApontador fundo, topo;
    int tamanho;
} TipoPilha;

void iniciaPilha(TipoPilha *pilha)
{
    pilha->topo = (TipoApontador) malloc(sizeof(TipoCelula));
    pilha->fundo = pilha->topo;
    pilha->topo->prox = nullptr;
    pilha->tamanho = 0;
}

int isVazia(TipoPilha pilha)
{ 
    return (pilha.topo == pilha.fundo);
}

void imprimePilha(TipoPilha* pilha)
{
    if (isVazia(*pilha))
    {
        cout << "Erro: lista vazia" << endl;
        return;
    }
    cout << "Pilha: " <<endl;
    TipoApontador aux = pilha->topo->prox;
    vector<string> saida;
    int i = 0;
    while (aux->prox != nullptr)
    {
        saida.push_back(to_string(i) + ". " + aux->item.chave);
        aux = aux->prox;
        i++;
    }
    saida.push_back(to_string(i++) + ". " + pilha->fundo->item.chave);
    for (const string& chave: saida)
    {
        cout << chave << endl;
    }
}

void empilhar(TipoItem x, TipoPilha *pilha)
{
    TipoApontador aux;
    aux = (TipoApontador) malloc(sizeof(TipoCelula));
    pilha->topo->item = x;
    aux->prox = pilha->topo;
    pilha->topo = aux;
    pilha->tamanho++;
}

void desempilhar(TipoPilha *pilha, TipoItem* item)
{
    TipoApontador aux;
    if (isVazia(*pilha))
    {
        cout << "Erro: lista vazia" << endl;
        return;
    }
    aux = pilha->topo;
    pilha->topo = aux->prox;
    *item = aux->prox->item;
    free(aux);
    pilha->tamanho--;
}

int tamanho(TipoPilha pilha)
{ 
    return (pilha.tamanho); 
}

void descarregaPilhaAuxiliarNaPilha(TipoPilha *pilhaAux, TipoPilha *pilha)
{
    for (int j = pilhaAux->tamanho; j != 0; j--)
    {
        empilhar(pilhaAux->topo->prox->item, pilha);
        desempilhar(pilhaAux, &pilhaAux->topo->prox->item);
    }
}

TipoPilha* carregaPilhaAuxiliarAtePosicao(int posicao, TipoPilha* pilha, TipoPilha* pilhaAux)
{
    for (int i = 0; i < posicao; i++)
    {
        empilhar(pilha->topo->prox->item, pilhaAux);
        desempilhar(pilha, &pilha->topo->prox->item);
    }
    return pilhaAux;
}

TipoPilha *carregaPilhaAuxiliarAtePosicao(int posicao, TipoPilha *pilha) {
    TipoPilha pilhaAux;
    iniciaPilha(&pilhaAux);
    return carregaPilhaAuxiliarAtePosicao(posicao, pilha, &pilhaAux);
}

void insereItemAposPosicao(string x, int posicao, TipoPilha* pilha)
{
    TipoItem item;
    item.chave = x;
    TipoPilha* pilhaAux = carregaPilhaAuxiliarAtePosicao(posicao, pilha);
    empilhar(item, pilha);
    descarregaPilhaAuxiliarNaPilha(pilhaAux, pilha);
}

void retira(TipoPilha* pilha, int posicao)
{
    if(isVazia(*pilha)) return;
    TipoPilha *pilhaAux = carregaPilhaAuxiliarAtePosicao(posicao+1, pilha);
    desempilhar(pilha, &pilha->topo->prox->item);
    descarregaPilhaAuxiliarNaPilha(pilhaAux, pilha);
}

void localizaItemPosicao(int posicao, TipoPilha* pilha)
{
    if(isVazia(*pilha)) return;
    string shouldChange = "n";
    TipoPilha* pilhaAux = carregaPilhaAuxiliarAtePosicao(posicao+1, pilha);
    cout << "O valor na posição " + to_string(posicao) + " é " + pilha->topo->prox->item.chave << endl;
    cout << "Deseja alterar o valor (s/n)? ";
    // cin >> shouldChange;
    if (shouldChange == "s")
    {
        TipoItem novoItem;
        cout << "Entre com o novo valor: ";
        cin >> novoItem.chave;
        desempilhar(pilha, &pilha->topo->prox->item);
        empilhar(novoItem, pilha);
    }
    descarregaPilhaAuxiliarNaPilha(pilhaAux, pilha);
}

TipoPilha combinarPilhas(TipoPilha* pilhaUm, TipoPilha* pilhaDois)
{
    TipoPilha  novaPilha;
    iniciaPilha(&novaPilha);
    carregaPilhaAuxiliarAtePosicao(0, pilhaUm, &novaPilha);
    carregaPilhaAuxiliarAtePosicao(0, pilhaDois, &novaPilha);
    return  novaPilha;
}

TipoPilha dividirPilha(TipoPilha* original, int posicao)
{
    TipoPilha novaPilha;
    iniciaPilha(&novaPilha);
    if(isVazia(*original)) return novaPilha;
    carregaPilhaAuxiliarAtePosicao(posicao + 1, original, &novaPilha);
    return novaPilha;
}

TipoPilha copiarPilha(TipoPilha* original)
{
    TipoPilha pilhaAux;
    iniciaPilha(&pilhaAux);
    carregaPilhaAuxiliarAtePosicao(0, original, &pilhaAux);
    TipoPilha copia;
    iniciaPilha(&copia);
    for (int i = pilhaAux.tamanho; i >= 0; i--)
    {
        empilhar(pilhaAux.topo->prox->item, original);
        empilhar(pilhaAux.topo->prox->item, &copia);
        desempilhar(&pilhaAux, &pilhaAux.topo->prox->item);
    }
    return copia;
}

void localizaItemPosicao(TipoPilha* pilha, const string& valorBuscado)
{
    if(isVazia(*pilha)) return;
    int ocorrencia = 0;
    bool isPresent = false;
    TipoPilha copia = copiarPilha(pilha);
    while(copia.topo->prox != nullptr)
    {
        if(copia.topo->prox->item.chave == valorBuscado)
        {
            isPresent = true;
        }
        desempilhar(&copia, &copia.topo->prox->item);
    }
    if (isPresent)
    {
        cout << to_string(ocorrencia) + " ocorrências do valor " + valorBuscado + " encontradas" << endl;
        return;
    }
    cout << "ERRO! Valor " + valorBuscado + " não encontrado" << endl;
}


#endif //PCO001_PILHA_AUTORREFERENCIADA_MAIN_H