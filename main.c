#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int chamada; // variavel menu
    int periodo; // prazo
    double valor; // valor total
    double juros; // taxa juros
    double pagames; // pagamento mensal

    printf("\nSimulador de financiamento Sistema PRICE e SAC\n");

    while (1) {
        printf("\n1- Simular financiamento Price\n");
        printf("2- Simular financiamento SAC\n");
        printf("3- SAIR\n");
        scanf("%d", &chamada);
        system("cls");//limpa terminal

        if (chamada == 1) {
            printf("Financiamento Price\n");

            ValorFinanciado(&valor); // Pega valor total do financiamento
            Prazo(&periodo); // Pega o valor dos meses convertidos
            Tjuros(&juros); // Pega taxa de juros

            CalcPagamento(periodo, valor, juros, &pagames); // calcula pagamento mensal
            double* parcelas = malloc(periodo * sizeof(double));
            double* jurosMensais = malloc(periodo * sizeof(double));
            double* amortizacoes = malloc(periodo * sizeof(double));
            double* saldosDevedores = malloc(periodo * sizeof(double));

            CalculaValoresPrice(periodo, valor, juros, pagames, parcelas, jurosMensais, amortizacoes, saldosDevedores);
            ImprimeTabelaPrice(periodo, parcelas, jurosMensais, amortizacoes, saldosDevedores);
           	ImprimeInformacoesMensais(periodo, parcelas, jurosMensais, amortizacoes, saldosDevedores);

            printf("Deseja salvar a tabela em um arquivo? (s ou n): ");
            char opcaoSalvar;
            fflush(stdin);
            scanf(" %c", &opcaoSalvar);
            if (opcaoSalvar == 's' || opcaoSalvar == 'S') {
                char nomeArquivo[100];
                printf("Digite o nome do arquivo para salvar (por exemplo, tabela_price.txt): ");
                fflush(stdin);
                scanf("%s", nomeArquivo);
                // Chamar a função para salvar a tabela em um arquivo
                SalvarTabelaEmArquivo(nomeArquivo, periodo, parcelas, jurosMensais, amortizacoes, saldosDevedores);
            }
             //Liberar memória alocada
            LiberarMemoria(parcelas, jurosMensais, amortizacoes, saldosDevedores);
            printf("Saindo do programa.\n");
            break;
        } else if (chamada == 2) {
            printf("Financiamento SAC\n");
            ValorFinanciado(&valor); // Pega valor total do financiamento
            Prazo(&periodo); // Pega o valor dos meses convertidos
            Tjuros(&juros); // Pega taxa de juros

            CalcPagamentoSac(periodo, valor, juros, &pagames);
            double* parcelasSac = malloc(periodo * sizeof(double));
            double* jurosMensaisSac = malloc(periodo * sizeof(double));
            double* amortizacoesSac = malloc(periodo * sizeof(double));
            double* saldosDevedoresSac = malloc(periodo * sizeof(double));

            CalculaAmortizacaoSac(periodo, valor, juros, pagames, parcelasSac, jurosMensaisSac, amortizacoesSac, saldosDevedoresSac);
            ImprimeTabelaSac(periodo, parcelasSac, jurosMensaisSac, amortizacoesSac, saldosDevedoresSac);
            ImprimeInformacoesMensaisSac(periodo, parcelasSac, jurosMensaisSac, amortizacoesSac, saldosDevedoresSac);

            printf("Deseja salvar a tabela em um arquivo? (s ou n): ");
            char opcaoSalvar2;
            fflush(stdin);
            scanf(" %c", &opcaoSalvar2);
            if (opcaoSalvar2 == 's' || opcaoSalvar2 == 'S') {
                char nomeArquivo2[100];
                printf("Digite o nome do arquivo para salvar (por exemplo, tabela_sac.txt): ");
                fflush(stdin);
                scanf("%s", nomeArquivo2);
                // Chamar a função para salvar a tabela em um arquivo
                SalvarTabelaEmArquivoSac(nomeArquivo2, periodo, parcelasSac, jurosMensaisSac, amortizacoesSac, saldosDevedoresSac);
            }
            //Liberar memória alocada
            LiberarMemoria(parcelasSac, jurosMensaisSac, amortizacoesSac, saldosDevedoresSac);
            printf("Saindo do programa.\n");
            break;
        }else if (chamada == 3) {
            printf("Saindo do programa.\n");
            break;
        } else {
            printf("Opcao invalida. Por favor, escolha uma opcao valida.\n");
        }
	}

    return 0;
}
