#include <stdio.h>
#include <math.h>
#include "bruno.h"

#define MIN_PRAZO 1
#define MAX_PRAZO 700
#define MIN_VALOR 1000.00
#define MIN_JUROS 1.0
#define MAX_JUROS 100

int Prazo(int* t){ 
	int tempo;

	do{
		printf("Prazo da divida em meses:\n");
		scanf("%d", &tempo); //pega prazo
	}while((tempo <= MIN_PRAZO) || (tempo >= MAX_PRAZO));//verifica se o prazo é de no minimo um ano
	*t = tempo;	//converte para meses e retorna ponteiro
	return *t;
}

double ValorFinanciado(double* f){
	double valor;
	
	do{
		printf("Valor financiado:\n");
		scanf("%lf", &valor);  //pega valor	
	}while(valor <= MIN_VALOR);//verifica se valor é positivo
	
	*f = valor; //salva valor em ponteiro
	return *f;
}

double Tjuros(double* i){
	double taxa;

	do{
		printf("taxa de juros anual:\n");
		scanf("%lf", &taxa); //pega valor de juros

	}while((taxa <= MIN_JUROS) || (taxa >= MAX_JUROS));//verifica se juros é maior que 0
	
	*i = taxa; //salva em ponteiro
	return *i;
}


double CalcPagamento(int p, double v, double j, double* pmt){
	double pd = (double) p;
	double rAdOne;
	double pagamento;

	j =((j / 100.0) / 12);//tranforma porcentagem anual em mensal
	rAdOne = (j + 1.0);//(1+juros)

	pagamento = (pow(rAdOne,pd) - 1.0);//(1+juros)^n - 1
	pagamento = (pagamento / (j * pow(rAdOne, pd)));//   (1+juros)^n - 1 / (1+juros)^n * juros
	pagamento = (v / pagamento);

	*pmt = pagamento;	//calculo price retorna em ponteiro
	return *pmt;
} 

void CalcPrice(int periodo, double valor, double juros, double pagamento,  double* parcelas, double* jurosMensais, double* amortizacoes, double* saldosDevedores){
	int i;
	double intPmt;
	double princPmt;
	double vparcela;
	double intTot = 0;//flag para incrementar juros
	double princTot = 0;//flag para incrementar valor real

	juros = ((juros / 100) / 12); //transforma em juros mensal
	
	printf("| Mes | Valor Parcela |  Juros   |  Amortizacao  |   Saldo Devedor    |\n");
	
	for(i = 0; i < periodo; i++){
		intPmt = (juros * valor);//valor do juros mes a mes-----juros mensal x valor saldo devedor
		princPmt = (pagamento - intPmt);//valor amortizaçao------- prestacao - valor juros mes
		valor = (valor - princPmt);//saldo devedor ------ valor financiamento - amortizacao
	
		princTot = (princTot + princPmt);//valor amortizado -----soma amortizacao de cada mes
		intTot = (intTot + intPmt);//juros total-----soma juros de cada mes
		vparcela = (intPmt + princPmt);//valor da parcela no mes-------juros mes a mes + amortizazaçao
		
		parcelas[i] = vparcela; // Armazena a parcela no vetor
		jurosMensais[i] = intPmt; // Armazena os juros no vetor
		amortizacoes[i] = princPmt; // Armazena a amortização no vetor
		saldosDevedores[i] = valor; // Armazena o saldo devedor no vetor
		
		
		printf("| %03d | %13.2lf | %8.2lf | %13.2lf | %19.2lf |\n", i+1, parcelas[i], jurosMensais[i], amortizacoes[i], saldosDevedores[i]);
	}
	printf("Total pago no financiamento: R$%.2lf\n", (intTot + princTot));
	printf("Total pago de juros:   R$%.2lf\n", intTot);
	printf("Total pago de amortizacao: R$%.2lf\n", princTot); 	
}


double CalcPagamentoSac(int pS, double vS, double jS, double* pmtS){
	double pagamentoSac;
	double amo;
	double pdS = (double) pS;
	
	jS =((jS / 100.0) / 12);//tranforma porcentagem anual em mensal
	
	amo = vS/pdS; //amo = div/n ------amortização = divida/prazoemmeses
	
	*pmtS = amo;
	return *pmtS;

} 


void CalcSac(int periodoSac, double valorSac, double jurosSac, double pagamentoSac, double* parcelasSac, double* jurosMensaisSac, double* amortizacoesSac, double* saldosDevedoresSac){
	int j;
	double intPmtSac;
	double princPmtSac;
	double vparcelaSac;
	double intTotSac = 0;//flag para incrementar juros
	double princTotSac = 0;//flag para incrementar valor real

	jurosSac = ((jurosSac / 100) / 12); //transforma em juros mensal
	
	printf("| Mes | Valor Parcela |  Juros   |  Amortizacao  |   Saldo Devedor    |\n");
	
	for(j = 0; j < periodoSac; j++){

		intPmtSac = (jurosSac * valorSac);//valor do juros mes a mes-----juros mensal x valor saldo devedor
		princPmtSac = pagamentoSac;//valor amortizaçao------- prestacao - valor juros mes
		valorSac = (valorSac - princPmtSac);//saldo devedor ------ valor financiamento - amortizacao
	
		princTotSac = (princTotSac + princPmtSac);//valor amortizado -----soma amortizacao de cada mes
		intTotSac = (intTotSac + intPmtSac);//juros total-----soma juros de cada mes
		vparcelaSac = (intPmtSac + princPmtSac);//valor da parcela no mes-------juros mes a mes + amortizazaçao
		
		parcelasSac[j] = vparcelaSac; // Armazena a parcela no vetor
		jurosMensaisSac[j] = intPmtSac; // Armazena os juros no vetor
		amortizacoesSac[j] = princPmtSac; // Armazena a amortização no vetor
		saldosDevedoresSac[j] = valorSac; // Armazena o saldo devedor no vetor
		
		printf("| %03d | %13.2lf | %8.2lf | %13.2lf | %19.2lf |\n", j+1, parcelasSac[j], jurosMensaisSac[j], amortizacoesSac[j], saldosDevedoresSac[j]);
	}
	printf("Total pago no financiamento: R$%8.2lf\n", (intTotSac + princTotSac));
	printf("Total pago de juros:   R$%8.2lf\n", intTotSac);
	printf("Total pago de amortizacao: R$%8.2lf\n", princTotSac);
}
