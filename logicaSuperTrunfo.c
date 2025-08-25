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
void compararCartas(Cartas *carta1, Cartas *carta2, int att);
double calcular_pibPerCapta(Cartas *carta);
double calcular_densidadePopulacional(Cartas *carta);
double calcular_superPoder(Cartas *carta);

int main() {
    setlocale(LC_ALL, "Portuguese");
    setlocale(LC_NUMERIC, "C");

    int numCartas=2, esc1=1, esc2=2, escAtt=0;

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
    do{
        // Menu de escolha de atributo:
        printf("\nEscolha o atributo a ser comparado:\n");
        printf("1.Populacao\n");
        printf("2.Area\n");
        printf("3.PIB\n");
        printf("4.Pontos Turisticos\n");
        printf("5.PIB per Capita\n");
        printf("6.Densidade Populacional\n");
        printf("7.Super Poder\n");
        printf("8.Sair\n");
        printf("Sua escolha: \n");
        scanf("%d", &escAtt);
        while(getchar() != '\n');
        
        // Chama a função de comparar as propriedades de cada carta
        compararCartas(&carta[esc1-1], &carta[esc2-1], escAtt);
    }while(escAtt != 8);

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

void compararCartas(Cartas *carta1, Cartas *carta2, int att){
    switch(att){
        case 1: // População
            printf("\n--- Populacao ---\n\n");
            printf("\nCarta 1: %s(%s): %d\n", carta1->cidade, carta1->estado, carta1->populacao);
            printf("\nCarta 2: %s(%s): %d\n", carta2->cidade, carta2->estado, carta2->populacao);
            if(carta1->populacao > carta2->populacao){
                printf("\n%s vence a rodada!\n\n", carta1->cidade);
            }else if(carta1->populacao < carta2->populacao){
                printf("\n%s vence a rodada!\n\n", carta2->cidade);
            }else{
                printf("\nEmpate!\n\n");  
            }
            break;
        case 2: // Área
            printf("\n--- Area ---\n\n");
            printf("\nCarta 1: %s(%s): %.2lf km2\n", carta1->cidade, carta1->estado, carta1->area);
            printf("\nCarta 2: %s(%s): %.2lf km2\n", carta2->cidade, carta2->estado, carta2->area);
            if(carta1->area > carta2->area){
                printf("\n%s vence a rodada!\n\n", carta1->cidade);
            }else if(carta1->area < carta2->area){
                printf("\n%s vence a rodada!\n\n", carta2->cidade);
            }else{
                printf("\nEmpate!\n\n");  
            }
            break;
        case 3: // PIB
            printf("\n--- PIB ---\n\n");
            printf("\nCarta 1: %s(%s): %.2lf bilhoes de reais\n", carta1->cidade, carta1->estado, carta1->pib);
            printf("\nCarta 2: %s(%s): %.2lf bilhoes de reais\n", carta2->cidade, carta2->estado, carta2->pib);
            if(carta1->pib > carta2->pib){
                printf("\n%s vence a rodada!\n\n", carta1->cidade);
            }else if(carta1->pib < carta2->pib){
                printf("\n%s vence a rodada!\n\n", carta2->cidade);
            }else{
                printf("\nEmpate!\n\n");  
            }
            break;
        case 4: // Pontos Turisticos
            printf("\n--- Pontos Turisticos ---\n\n");
            printf("\nCarta 1: %s(%s): %d\n", carta1->cidade, carta1->estado, carta1->pontosTuristicos);
            printf("\nCarta 2: %s(%s): %d\n", carta2->cidade, carta2->estado, carta2->pontosTuristicos);
            if(carta1->pontosTuristicos > carta2->pontosTuristicos){
                printf("\n%s vence a rodada!\n\n", carta1->cidade);
            }else if(carta1->pontosTuristicos < carta2->pontosTuristicos){
                printf("\n%s vence a rodada!\n\n", carta2->cidade);
            }else{
                printf("\nEmpate!\n\n");  
            }
            break;
        case 5: // PIB per Capita
            printf("\n--- PIB per Capita ---\n\n");
            printf("\nCarta 1: %s(%s): %.2lf R$\n", carta1->cidade, carta1->estado, carta1->pibPerCapta);
            printf("\nCarta 2: %s(%s): %.2lf R$\n", carta2->cidade, carta2->estado, carta2->pibPerCapta);
            if(carta1->pibPerCapta> carta2->pibPerCapta){
                printf("\n%s vence a rodada!\n\n", carta1->cidade);
            }else if(carta1->pibPerCapta < carta2->pibPerCapta){
                printf("\n%s vence a rodada!\n\n", carta2->cidade);
            }else{
                printf("\nEmpate!\n\n");  
            }
            break;
        case 6: // Densidade Populacional
            printf("\n--- Densidade Populacional ---\n\n");
            printf("\nCarta 1: %s(%s): %.2lf hab / km2\n", carta1->cidade, carta1->estado, carta1->densPop);
            printf("\nCarta 2: %s(%s): %.2lf hab / km2\n", carta2->cidade, carta2->estado, carta2->densPop);
            if(carta1->densPop < carta2->densPop){
                printf("\n%s vence a rodada!\n\n", carta1->cidade);
            }else if(carta1->densPop > carta2->densPop){
                printf("\n%s vence a rodada!\n\n", carta2->cidade);
            }else{
                printf("\nEmpate!\n\n");  
            }
            break;
        case 7: // Super Poder
            printf("\n--- Super Poder ---\n\n");
            printf("\nCarta 1: %s(%s): %.2lf\n", carta1->cidade, carta1->estado, carta1->superPoder);
            printf("\nCarta 2: %s(%s): %.2lf\n", carta2->cidade, carta2->estado, carta2->superPoder);
            if(carta1->superPoder > carta2->superPoder){
                printf("\n%s vence a rodada!\n\n", carta1->cidade);
            }else if(carta1->superPoder < carta2->superPoder){
                printf("\n%s vence a rodada!\n\n", carta2->cidade);
            }else{
                printf("\nEmpate!\n\n");  
            }
            break;
        }
    }
