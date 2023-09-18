int Prazo(int* t); //coverte tempo anual em número de meses
double ValorFinanciado(double* f); //verifica se valor é verdadeiro
double Tjuros(double* i); //verifica se taxa de juros é verdadeira

//Price
double CalcPagamento(int p, double v, double j, double* pmt);//calcular prestacao
void CalcPrice(int periodo, double valor, double juros, double pagames,  double* parcelas, double* jurosMensais, double* amortizacoes, double* saldosDevedores);//calcula diferenças entre prestação, juros, amortização e valor total, vetores em tabela

//Sac
double CalcPagamentoSac(int pS, double vS, double jS, double* pmtS);//calcular amortização
void CalcSac(int periodoSac, double valorSac, double jurosSac, double pagamesSac, double* parcelasSac, double* jurosMensaisSac, double* amortizacoesSac, double* saldosDevedoresSac);//calcula diferenças entre prestação, juros, amortização e valor total, vetores em tabela
