#include "main.h"

int main()
{
    TipoPilha pilha;
    TipoItem item;
    string vetorFrutas[] = {"banana", "laranja", "limão", "goiaba", "tomate"};
    string vetorLegumes[] = {"batata", "cenoura", "cebola", "beterraba", "jiló"};

    cout << "01. Criação da estrutura de dados vazia" << endl;
    iniciaPilha(&pilha);

    cout << endl << "02. Empilhar" << endl;
    for (auto & vetorFruta : vetorFrutas)
    {
        item.chave = vetorFruta;
        empilhar(item, &pilha);
    }
    imprimePilha(&pilha);
    cout <<"tamanho da pilha: " + to_string(tamanho(pilha)) << endl << endl;

    cout << endl <<  "03. Desempilhar" << endl;
    desempilhar(&pilha, &pilha.topo->prox->item);
    imprimePilha(&pilha);

    cout << endl << "04. Inserir um novo item após o i-ésimo item" << endl;
    insereItemAposPosicao("kiwi", 2, &pilha);
    imprimePilha(&pilha);

    cout << endl <<  "05. Retirar i-ésimo item" << endl;
    retira(&pilha, 2);
    imprimePilha(&pilha);

    cout << endl <<  "06. Localizar um item na Lista" << endl;
    localizaItemPosicao(1, &pilha);
    localizaItemPosicao(3, &pilha);

    cout << endl << "07. Combinar duas ou mais estruturas em uma" << endl;
    TipoPilha novaPilha;
    iniciaPilha(&novaPilha);
    for (auto & vetorLegume : vetorLegumes)
    {
        item.chave = vetorLegume;
        empilhar(item, &novaPilha);
    }
    novaPilha = combinarPilhas(&pilha, &novaPilha);
    imprimePilha(&novaPilha);

    cout << endl << "08. Partir uma estrutura em duas ou mais" << endl;
    TipoPilha novaPilhaDireita;
    iniciaPilha(&novaPilhaDireita);
    novaPilhaDireita = dividirPilha(&novaPilha, 3);
    imprimePilha(&novaPilha);
    imprimePilha(&novaPilhaDireita);

    cout << endl << "09. Fazer uma cópia" << endl;
    TipoPilha pilhaCopiada;
    iniciaPilha(&pilhaCopiada);
    pilhaCopiada = copiarPilha(&novaPilhaDireita);
    imprimePilha(&pilhaCopiada);

    cout << endl << "10. Buscar a ocorrência de um valor particular" << endl;
    imprimePilha(&pilhaCopiada);
    localizaItemPosicao(&pilhaCopiada, "laranja");
}
