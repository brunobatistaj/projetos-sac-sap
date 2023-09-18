#include <stdio.h>

int main(void){
	int chamada;//variavel menu
	int periodo; //prazo
	double valor; //valor total
	double juros;//taxa juros
	double pagames;//pagamento mensal
	
	pv://ponto de retorno
		
	printf("\nSimulador de financiamento Sistema PRICE e SAC\n");
	printf("\n1- Simular financiamento Price\n");
	printf("\n2- Simular financiamento SAC\n");
	printf("\n3- Sobre sistema PRICE\n");
	printf("\n4- Sobre sistema SAC\n");
	printf("\n5- SAIR\n");
	scanf("%d", &chamada);
	
	system("cls");//limpa terminal
	
	while(chamada != 5){
		if(chamada == 1){
			printf("Financiamento Price\n");
			ValorFinanciado(&valor);//Pega valor total do financiamento
			Prazo(&periodo);//Pega o valor dos meses convertidos
			Tjuros(&juros);//Pega taxa de juros
			
			CalcPagamento(periodo, valor, juros, &pagames);//calcula pagamento mensal
			double parcelas[periodo];
			double jurosMensais[periodo];
			double amortizacoes[periodo];
			double saldosDevedores[periodo];
				
			CalcPrice(periodo, valor, juros, pagames, parcelas, jurosMensais, amortizacoes, saldosDevedores);//salva tabela de amortização e valores totais
			
		}else if(chamada == 2){
			printf("Financiamento SAC\n");
			ValorFinanciado(&valor);//Pega valor total do financiamento
			Prazo(&periodo);//Pega o valor dos meses convertidos
			Tjuros(&juros);//Pega taxa de juros
			
			CalcPagamentoSac(periodo, valor, juros, &pagames);
			double parcelasSac[periodo];
			double jurosMensaisSac[periodo];
			double amortizacoesSac[periodo];
			double saldosDevedoresSac[periodo];
			CalcSac(periodo, valor, juros, pagames, parcelasSac, jurosMensaisSac, amortizacoesSac, saldosDevedoresSac);
			
		}else if(chamada == 3){
			printf("Sistema PRICE\n");
			printf("Sistema frances de amortizacao.\nEh um metodo usado em amortizacao de emprestimo cuja principal caracteristica e apresentar prestacoes iguais.");
		}else if(chamada == 4){
			printf("Sistema SAC\n");
			printf("Sistema de Amortizacao Constante.\nIsso significa que: o percentual de juros permanece o mesmo, mas como o saldo devedor diminui, o valor das parcelas tambem cai ao longo do tempo.\n");
		}else{
			printf("Nao contem esta opcao\n");
			goto pv;//marcador de retorno
		}	
	goto pv;	
	}
	
	return 0;
}
