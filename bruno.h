#define MIN_PRAZO 1
#define MAX_PRAZO 600
#define MIN_VALOR 1000.00
#define MIN_JUROS 1.0
#define MAX_JUROS 100

int Prazo(int* t); //Valida numero de prestaçoes e armazena em ponteiro
double ValorFinanciado(double* f); //verifica se valor é verdadeiro e armazena em ponteiro
double Tjuros(double* i); //verifica se taxa de juros é verdadeira e armazena em ponteiro

//salvar meses em vetores
int converteMes(int t); //converte em meses de 1 a 12
const char* GetMonthName(int mesRestante);//converte funcao anterior em nome dos meses

// calculos Price
double CalcPagamento(int p, double v, double j, double* pmt);//calcular prestacao
void CalculaValoresPrice(int periodo, double valor, double juros, double pagames,  double* parcelas, double* jurosMensais, double* amortizacoes, double* saldosDevedores);//Prepara e chama recursiva --zera indice
void CalculaValoresPriceRec(int periodo, double valor, double juros, double pagamento, double* parcelas, double* jurosMensais, double* amortizacoes, double* saldosDevedores, int i);//calcula diferenças entre prestação, juros, amortização e valor total, vetores em tabela

//impressao tabelas price
void ImprimeTabelaPrice(int periodo, double* parcelas, double* jurosMensais, double* amortizacoes, double* saldosDevedores);//omprime tabela
void ImprimeInformacoesMensais(int periodo, double* parcelas, double* jurosMensais, double* amortizacoes, double* saldosDevedores);//imprime linha especifica

//calculos Sac
double CalcPagamentoSac(int pS, double vS, double jS, double* pmtS);//calcular amortização
void CalculaAmortizacaoSac(int periodoSac, double valorSac, double jurosSac, double pagamesSac, double* parcelasSac, double* jurosMensaisSac, double* amortizacoesSac, double* saldosDevedoresSac);//Prepara e chama recursiva --zera indice
void CalculaAmortizacaoSacRec(int periodoSac, double valorSac, double jurosSac, double pagamentoSac, double* parcelasSac, double* jurosMensaisSac, double* amortizacoesSac, double* saldosDevedoresSac, int j);//calcula diferenças entre prestação, juros, amortização e valor total, vetores em tabela

//impressao tabelas sac
void ImprimeTabelaSac(int periodoSac, double* parcelasSac, double* jurosMensaisSac, double* amortizacoesSac, double* saldosDevedoresSac);//imprime vetores
void ImprimeInformacoesMensaisSac(int periodoSac, double* parcelasSac, double* jurosMensaisSac, double* amortizacoesSac, double* saldosDevedoresSac);

//salvar em doc
void SalvarTabelaEmArquivo(const char* nomeArquivo, int periodo, double* parcelas, double* jurosMensais, double* amortizacoes, double* saldosDevedores);
void SalvarTabelaEmArquivoSac(const char* nomeArquivo2, int periodoSac, double* parcelasSac, double* jurosMensaisSac, double* amortizacoesSac, double* saldosDevedoresSac);

//liberar memoria
void LiberarMemoria(double* parcelas, double* jurosMensais, double* amortizacoes, double* saldosDevedores);
