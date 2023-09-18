int Prazo(int* t); //coverte tempo anual em n�mero de meses
double ValorFinanciado(double* f); //verifica se valor � verdadeiro
double Tjuros(double* i); //verifica se taxa de juros � verdadeira

//Price
double CalcPagamento(int p, double v, double j, double* pmt);//calcular prestacao
void CalcPrice(int periodo, double valor, double juros, double pagames,  double* parcelas, double* jurosMensais, double* amortizacoes, double* saldosDevedores);//calcula diferen�as entre presta��o, juros, amortiza��o e valor total, vetores em tabela

//Sac
double CalcPagamentoSac(int pS, double vS, double jS, double* pmtS);//calcular amortiza��o
void CalcSac(int periodoSac, double valorSac, double jurosSac, double pagamesSac, double* parcelasSac, double* jurosMensaisSac, double* amortizacoesSac, double* saldosDevedoresSac);//calcula diferen�as entre presta��o, juros, amortiza��o e valor total, vetores em tabela
