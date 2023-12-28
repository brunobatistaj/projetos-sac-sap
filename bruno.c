#include <stdio.h>
#include <math.h>
#include "bruno.h"

int Prazo(int* t){
	int tempo;
	do{
		printf("Prazo da divida em meses:\n");
		scanf("%d", &tempo); //pega prazo
	}while((tempo <= MIN_PRAZO) || (tempo >= MAX_PRAZO));//verifica se o prazo é de no minimo um ano
	*t = tempo;	//converte para meses e retorna ponteiro
	return *t;
}

int converteMes(int t) {
    int anosCompletos = t / 12;
    int mesRestante = t % 12;

    if (mesRestante == 0) {
        anosCompletos--; // Se o mês restante for 0, subtrair 1 dos anos completos.
        mesRestante = 12;
    }

    if (anosCompletos < 0) {
        return -1; // Valor negativo é inválido.
    }
    return mesRestante;
}

const char* GetMonthName(int mesRestante) {
    const char* monthNames[] = {
        "Jan", "Fev", "Mar", "Abr", "Mai", "Jun",
        "Jul", "Ago", "Set", "Out", "Nov", "Dez"
    };

    if (mesRestante >= 1 && mesRestante <= 12) {
        return monthNames[mesRestante - 1];
    } else {
        return "Mês Inválido";
    }
}

double ValorFinanciado(double* f){
	double valor;
	double quitado;

	do{
		printf("Valor financiado:\n");
		scanf("%lf", &valor);  //pega valor
	}while(valor <= MIN_VALOR);//verifica se valor é positivo
		printf("Valor de entrada da divida:\n");
		scanf("%lf", &quitado); //pega valor de entrada

	*f = valor-quitado; //salva valor em ponteiro
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

// Função recursiva para calcular valores Price
void CalculaValoresPriceRec(int periodo, double valor, double juros, double pagamento, double* parcelas, double* jurosMensais, double* amortizacoes, double* saldosDevedores, int i) {
    if (i < periodo) {
        double intPmt = (juros * valor);
        double princPmt = (pagamento - intPmt);
        valor = (valor - princPmt);

        parcelas[i] = intPmt + princPmt;
        jurosMensais[i] = intPmt;
        amortizacoes[i] = princPmt;
        saldosDevedores[i] = valor;

        CalculaValoresPriceRec(periodo, valor, juros, pagamento, parcelas, jurosMensais, amortizacoes, saldosDevedores, i + 1);
    }
}

// Função para calcular valores Price (chamada inicial)
void CalculaValoresPrice(int periodo, double valor, double juros, double pagamento, double* parcelas, double* jurosMensais, double* amortizacoes, double* saldosDevedores) {
    int i = 0;

    juros = ((juros / 100) / 12);

    CalculaValoresPriceRec(periodo, valor, juros, pagamento, parcelas, jurosMensais, amortizacoes, saldosDevedores, i);
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

void CalculaAmortizacaoSacRec(int periodoSac, double valorSac, double jurosSac, double pagamentoSac, double* parcelasSac, double* jurosMensaisSac, double* amortizacoesSac, double* saldosDevedoresSac,int j) {

	if (j < periodoSac) {
    double intPmtSac = (jurosSac * valorSac);
    double princPmtSac = pagamentoSac;
    valorSac = (valorSac - princPmtSac);
    double vparcelaSac = intPmtSac + princPmtSac;

    parcelasSac[j] = vparcelaSac;
    jurosMensaisSac[j] = intPmtSac;
    amortizacoesSac[j] = princPmtSac;
    saldosDevedoresSac[j] = valorSac;

    CalculaAmortizacaoSacRec(periodoSac, valorSac, jurosSac, pagamentoSac, parcelasSac, jurosMensaisSac, amortizacoesSac, saldosDevedoresSac, j + 1);
    }
}

void CalculaAmortizacaoSac(int periodoSac, double valorSac, double jurosSac, double pagamentoSac, double* parcelasSac, double* jurosMensaisSac, double* amortizacoesSac, double* saldosDevedoresSac) {
    int j = 0;
    jurosSac = ((jurosSac / 100) / 12);
    CalculaAmortizacaoSacRec(periodoSac, valorSac, jurosSac, pagamentoSac, parcelasSac, jurosMensaisSac, amortizacoesSac, saldosDevedoresSac, j);
}

//IMPRESSAO DE TABELAS
void ImprimeTabelaSac(int periodoSac, double* parcelasSac, double* jurosMensaisSac, double* amortizacoesSac, double* saldosDevedoresSac) {
    int j;

    printf("| Mes | Valor Parcela |  Juros   |  Amortizacao  |   Saldo Devedor    |\n");

    for (j = 0; j < periodoSac; j++) {
    	int mesCorrespondente = converteMes(j + 1);

        if (mesCorrespondente != -1) {
            const char* nomeDoMes = GetMonthName(mesCorrespondente);
            printf("| %s | %13.2lf | %8.2lf | %13.2lf | %19.2lf |\n", nomeDoMes, parcelasSac[j], jurosMensaisSac[j], amortizacoesSac[j], saldosDevedoresSac[j]);
        } else {
            printf("| Mês | %13.2lf | %8.2lf | %13.2lf | %19.2lf |\n", parcelasSac[j], jurosMensaisSac[j], amortizacoesSac[j], saldosDevedoresSac[j]);
        }
    }
}

void ImprimeInformacoesMensaisSac(int periodoSac, double* parcelasSac, double* jurosMensaisSac, double* amortizacoesSac, double* saldosDevedoresSac) {
    int mesRequisitado = 0;
    char opcao;

    while (1) {
        printf("Pesquisar parcela especifica (s ou n)? ");
        scanf(" %c", &opcao);
        if (opcao != 's') {
            break; // Sair do loop se a entrada não for 's'
        }

        do {
            printf("Digite o numero do mes desejado (1 a %d): ", periodoSac);
            scanf("%d", &mesRequisitado);
        } while (mesRequisitado < 1 || mesRequisitado > periodoSac);

        int indiceSac = mesRequisitado - 1;
        int mesCorrespondenteSac = converteMes(indiceSac + 1);

        if (mesCorrespondenteSac != -1) {
            const char* nomeDoMes = GetMonthName(mesCorrespondenteSac);
            printf("| Mes | Valor Parcela |  Juros   |  Amortizacao  |   Saldo Devedor    |\n");
            printf("| %s | %13.2lf | %8.2lf | %13.2lf | %19.2lf |\n", nomeDoMes, parcelasSac[indiceSac], jurosMensaisSac[indiceSac], amortizacoesSac[indiceSac], saldosDevedoresSac[indiceSac]);
        }
    }
}



void ImprimeTabelaPrice(int periodo, double* parcelas, double* jurosMensais, double* amortizacoes, double* saldosDevedores) {
    int i;

    printf("| Mes | Valor Parcela |  Juros   |  Amortizacao  |   Saldo Devedor    |\n");

    for (i = 0; i < periodo; i++) {
    	int mesCorrespondente = converteMes(i + 1);

    	if (mesCorrespondente != -1) {
			const char* nomeDoMes = GetMonthName(mesCorrespondente);
			printf("| %s | %13.2lf | %8.2lf | %13.2lf | %19.2lf |\n", nomeDoMes, parcelas[i], jurosMensais[i], amortizacoes[i], saldosDevedores[i]);
		}else{
			printf("| Mês | %13.2lf | %8.2lf | %13.2lf | %19.2lf |\n", parcelas[i], jurosMensais[i], amortizacoes[i], saldosDevedores[i]);
    	}
	}
}

void ImprimeInformacoesMensais(int periodo, double* parcelas, double* jurosMensais, double* amortizacoes, double* saldosDevedores) {
    int mesDesejado = 0;
    char op;

    while (1) {
        printf("Pesquisar parcela especifica (s ou n)? ");
        scanf(" %c", &op);
        if (op != 's') {
            break; // Sair do loop se a entrada não for 's'
        }

        do {
            printf("Digite o numero do mes desejado (1 a %d): ", periodo);
            scanf("%d", &mesDesejado);
        } while (mesDesejado < 1 || mesDesejado > periodo);

        int indice = mesDesejado - 1;
        int mesCorrespondente = converteMes(indice + 1);

        if (mesCorrespondente != -1) {
            const char* nomeDoMes = GetMonthName(mesCorrespondente);
            printf("| Mes | Valor Parcela |  Juros   |  Amortizacao  |   Saldo Devedor    |\n");
            printf("| %s | %13.2lf | %8.2lf | %13.2lf | %19.2lf |\n", nomeDoMes, parcelas[indice], jurosMensais[indice], amortizacoes[indice], saldosDevedores[indice]);
        }
    }
}

//Salvar tabelas em doc
void SalvarTabelaEmArquivo(const char* nomeArquivo, int periodo, double* parcelas, double* jurosMensais, double* amortizacoes, double* saldosDevedores) {
    int i;
    FILE* arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(arquivo, "| Mes | Valor Parcela |  Juros   |  Amortizacao  |   Saldo Devedor    |\n");

    for (i = 0; i < periodo; i++) {
        int mesCorrespondente = converteMes(i + 1);

        if (mesCorrespondente != -1) {
            const char* nomeDoMes = GetMonthName(mesCorrespondente);
            fprintf(arquivo, "| %s | %13.2lf | %8.2lf | %13.2lf | %19.2lf |\n", nomeDoMes, parcelas[i], jurosMensais[i], amortizacoes[i], saldosDevedores[i]);
        } else {
            fprintf(arquivo, "| Mês | %13.2lf | %8.2lf | %13.2lf | %19.2lf |\n", parcelas[i], jurosMensais[i], amortizacoes[i], saldosDevedores[i]);
        }
    }

    fclose(arquivo);
    printf("Tabela salva com sucesso no arquivo: %s\n", nomeArquivo);
}

void SalvarTabelaEmArquivoSac(const char* nomeArquivo2, int periodoSac, double* parcelasSac, double* jurosMensaisSac, double* amortizacoesSac, double* saldosDevedoresSac) {
    int j;
    FILE* arquivo2 = fopen(nomeArquivo2, "w");

    if (arquivo2 == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(arquivo2, "| Mes | Valor Parcela |  Juros   |  Amortizacao  |   Saldo Devedor    |\n");

    for (j = 0; j < periodoSac; j++) {
    	int mesCorrespondente = converteMes(j + 1);

        if (mesCorrespondente != -1) {
            const char* nomeDoMes = GetMonthName(mesCorrespondente);
            fprintf(arquivo2, "| %s | %13.2lf | %8.2lf | %13.2lf | %19.2lf |\n", nomeDoMes, parcelasSac[j], jurosMensaisSac[j], amortizacoesSac[j], saldosDevedoresSac[j]);
        } else {
            fprintf(arquivo2, "| Mês | %13.2lf | %8.2lf | %13.2lf | %19.2lf |\n", parcelasSac[j], jurosMensaisSac[j], amortizacoesSac[j], saldosDevedoresSac[j]);
        }
    }

    fclose(arquivo2);
    printf("Tabela salva com sucesso no arquivo: %s\n", nomeArquivo2);
}
// Função para liberar a memória alocada dinamicamente
void LiberarMemoria(double* parcelas, double* jurosMensais, double* amortizacoes, double* saldosDevedores) {
    free(parcelas);
    free(jurosMensais);
    free(amortizacoes);
    free(saldosDevedores);
}
