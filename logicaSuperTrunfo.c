#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char estado[3];
    char codCarta[5];
    char cidade[30];
    unsigned long long populacao;
    double pib;
    double area;
    double densPop;
    double pibPerCapta;
    int pontosTuristicos;
    double superPoder;
}Cartas;

void cadastroCartas(Cartas *carta);
void mostrarCartas(Cartas *carta, int numCartas);
void calcularPropriedades(Cartas *carta);
void compararCartas(Cartas *carta1, Cartas *carta2, int att1, int att2);
double calcular_pibPerCapta(Cartas *carta);
double calcular_densidadePopulacional(Cartas *carta);
double calcular_superPoder(Cartas *carta);
double getValorAtributo(Cartas *carta, int att);
const char* getNomeAtributo(int att);


int main() {
    setlocale(LC_ALL, "Portuguese");
    setlocale(LC_NUMERIC, "C");

    int numCartas=2, esc1=1, esc2=2, escAtt1=0, escAtt2=0;

    Cartas *carta = (Cartas *)malloc(numCartas * sizeof(Cartas)); // Criando um array de cartas

    if(carta ==  NULL){
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    //Cadastro das cartas
    printf("----- Cadastro de Cartas SUPER TRUNFO -----\n\n");

    for(int i = 0; i < numCartas; i++){
        printf("----- Cadastro da Carta #%d -----\n", i+1);
        cadastroCartas(&carta[i]);
        calcularPropriedades(&carta[i]);
    }

    // Output das cartas
    mostrarCartas(carta, numCartas);

    // Comparação das Cartas
    printf("\n     ----- Comparacao das Cartas -----\n");
        

    do {
        // Menu de escolha de atributo:
        printf("\nEscolha os atributos para a batalha:\n");
        printf("1. Populacao\n");
        printf("2. Area\n");
        printf("3. PIB\n");
        printf("4. Pontos Turisticos\n");
        printf("5. PIB per Capita\n");
        printf("6. Densidade Populacional\n");
        printf("7. Super Poder\n");
        printf("8. Sair\n");
        printf("\nEscolha o primeiro atributo (1-7): ");
        scanf("%d", &escAtt1);
        if (escAtt1 == 8) break; // Sai do loop

        printf("Escolha o segundo atributo (1-7): ");
        scanf("%d", &escAtt2);
        while(getchar() != '\n');

        if (escAtt1 < 1 || escAtt1 > 7 || escAtt2 < 1 || escAtt2 > 7 || escAtt1 == escAtt2) {
            printf("\nOpcoes invalidas. Escolha dois atributos diferentes entre 1 e 7.\n\n");
        } else {
            compararCartas(&carta[esc1-1], &carta[esc2-1], escAtt1, escAtt2);
        }
    } while (escAtt1 != 8);

    // libera o malloc
    free(carta); 
    carta = NULL; 

    printf("Pressione qualquer tecla para finalizar...\n");
    while(getchar() != '\n');
    getchar();

    return 0;
}

void calcularPropriedades(Cartas *carta){
    carta->pibPerCapta=calcular_pibPerCapta(carta);
    carta->densPop=calcular_densidadePopulacional(carta);
    carta->superPoder=calcular_superPoder(carta);
}

void cadastroCartas(Cartas *carta){
    char tempCod[3];

    printf("Estado(SP,RJ,RS,BA):");
    scanf(" %2s", carta->estado);
    while(getchar() != '\n');

    printf("Codigo da Carta (01, 02): ");
    scanf(" %2s", tempCod);
    while(getchar() != '\n');

    sprintf(carta->codCarta, "%s%s", carta->estado, tempCod);

    printf("Cidade: ");
    fgets(carta->cidade, sizeof(carta->cidade), stdin);
    carta->cidade[strcspn(carta->cidade, "\n")] = 0;

    printf("Populacao: ");
    scanf("%llu", &carta->populacao);
    while(getchar() != '\n');
    
    printf("Quantidade de pontos turisticos: ");
    scanf("%d", &carta->pontosTuristicos);
    while(getchar() != '\n');

    printf("Area(em km2): ");
    scanf("%lf", &carta->area);
    while(getchar() != '\n');
   
    printf("PIB(em bi): ");
    scanf("%lf", &carta->pib);
    while(getchar() != '\n');

}

double calcular_pibPerCapta(Cartas *carta){
    // Função para calcular pib per capta das cartas
    // Parâmetros:
    // - carta: A struct da carta 
    // Return:
    // O pib per capta calculado ou 0, caso a população seja 0

    // (pib * 1000000000) / populacao
    if(carta->populacao > 0){

        return (carta->pib * 1e9) / carta->populacao;
    }
    
    return 0.0;
}

double calcular_densidadePopulacional(Cartas *carta){
    // Função para calcular densidade populacional das cartas
    // Parâmetros:
    // - carta: A struct da carta 
    // Return:
    // A densidade populacional calculada ou 0, caso a area seja 0

    if(carta->area > 0){
        return (double)carta->populacao / carta->area; // Cast de double para populacao lida em int anteriormente.
    }

    return 0.0;
}

double calcular_superPoder(Cartas *carta){
    double inversoDens = 0.0;

    if(carta->densPop > 0){
        inversoDens = 1.0 / carta->densPop;
    }
    // Soma todos os atributos numéricos. Dividindo por 1 milhão para deixar mais legível.
    return ((double)carta->populacao + carta->area + carta->pib +
    (double)carta->pontosTuristicos + carta->pibPerCapta + inversoDens)  / 1e6;
}

void mostrarCartas(Cartas *carta, int numCartas){
    printf("\n\n----- Cartas Cadastradas -----\n\n");
    for(int i=0;i<numCartas;i++){
        printf("\n----- Carta #%d -----\n",i+1);
        printf("Estado: %s\n",carta[i].estado);
        printf("Codigo da Carta: %s\n",carta[i].codCarta);
        printf("Cidade: %s\n",carta[i].cidade);
        printf("Populacao: %llu\n",carta[i].populacao);
        printf("PIB: %.2lf bilhoes de reais\n",carta[i].pib);
        printf("PIB per capta: %.2lf R$\n",carta[i].pibPerCapta);
        printf("Area: %.2lf km²\n",carta[i].area);
        printf("Densidade Populacional: %.2lf hab/km²\n",carta[i].densPop);
        printf("Pontos Turisticos: %d\n",carta[i].pontosTuristicos);
        printf("Super Poder: %.2lf\n", carta[i].superPoder);
    }
}

void compararCartas(Cartas *carta1, Cartas *carta2, int att1, int att2){
    // Carta 01
    double c1Att1 = getValorAtributo(carta1, att1);
    double c1Att2 = getValorAtributo(carta1, att2);
    double c1Total = c1Att1 + c1Att2;

    // Carta 02
    double c2Att1 = getValorAtributo(carta2, att1);
    double c2Att2 = getValorAtributo(carta2, att2);
    double c2Total = c2Att1 + c2Att2;

    // Comparação de Atributos
    printf("--- Comparacao ---\n");
    printf("Comparando atributos: '%s' e '%s'\n", getNomeAtributo(att1), getNomeAtributo(att2));
    
    // Carta 01
    printf("\n\nCarta: %s(%s)\n", carta1->cidade, carta1->estado);
    printf(" %s: %.2lf\n",getNomeAtributo(att1),c1Att1);
    printf(" %s: %.2lf\n",getNomeAtributo(att2),c1Att2);
    printf(" Total -> %.2lf\n", c1Total);

    // Carta 02
    printf("\n\nCarta: %s(%s)\n", carta2->cidade, carta2->estado);
    printf(" %s: %.2lf\n",getNomeAtributo(att1),c2Att1);
    printf(" %s: %.2lf\n",getNomeAtributo(att2),c2Att2);
    printf(" Total -> %.2lf\n", c2Total);

    printf("----------------------------\n");
    if (c1Total > c2Total) {
        printf("Vencedor da rodada: %s!\n\n", carta1->cidade);
    } else if (c2Total > c1Total) {
        printf("Vencedor da rodada: %s!\n\n", carta2->cidade);
    } else {
        printf("Empate!\n\n");
    }
}

double getValorAtributo(Cartas *carta, int att){
    // Retorna o valor do atributo
    switch(att){
        case 1: return (double)carta->populacao;
        case 2: return  carta->area;
        case 3: return carta->pib;
        case 4: return (double)carta->pontosTuristicos;
        case 5: return carta->pibPerCapta;
        case 6: return carta->densPop;
        case 7: return carta->superPoder;
    }
    return 0.0;
}

const char* getNomeAtributo(int att){
    // Retorna o nome do atributo
    switch(att){
        case 1: return "Populacao";
        case 2: return "Area";
        case 3: return "PIB";
        case 4: return "Pontos Turisticos";
        case 5: return "PIB per capita";
        case 6: return "Densidade Populacional";
        case 7: return "Super Poder";
        default: return "NULL";
    }
}
