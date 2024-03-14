#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  char nome[30];
  char id_produto[6];
  int qtd_disp;
  int n_vendas;
  int n_compras;
  int status;
  float preco;
} Produto;

int inserir_produto(Produto *produtos, int tamanho, int posicao, Produto novo);
int remover_produto(Produto *prdts, int tam, char id[6]);
int buscar(Produto* produtos, int tamanho, char id[6]);
int comprar(Produto* produtos, int tamanho, char id[6]);
int vender(Produto* produtos, int tamanho, char id[6]);
Produto obter_produto_novo(Produto *produtos, int tamanho);
void gerar_relatorios(Produto *prdts, int tam);
void imprimir_mais_vendidos(Produto *produtos, int tamanho);
void imprimir_mais_comprados(Produto *prdts, int tam);
void imprimir_estoque(Produto *prdts, int tam);
void imprimir_extrato(Produto *prdts, int tam);

int main (void) {
  int tamanho_produto = 0, escolha, tamanho = 0; //quantidade de produtos no vetor
  char codigo[6];
  Produto novo;  //novo produto
  Produto* produtos = malloc(sizeof(Produto));

  while (escolha != 0)
  {
    int permitir;
    int indice;
    
    printf("\t\tBEM-VINDO AO SISTEMA!!\n\n- Digite: 1 (para inserir um produto)\n- Digite: 2 (para remover um produto)\n- Digite: 3 (para buscar um produto)\n- Digite: 4 (para comprar um produto)\n- Digite: 5 (para vender um produto)\n- Digite: 6 (para gerar relatórios)\n- Digite: 0 (para sair)\n\n-->  ");
    scanf("%i", &escolha);
    getchar();
    system ("clear");

    switch (escolha)
    {
      case 1:
        novo = obter_produto_novo(produtos, tamanho);
        permitir = inserir_produto(produtos, tamanho, 0, novo);
        tamanho++;
        
        if (permitir)
        {
          produtos = realloc(produtos, (tamanho + 1) * sizeof (Produto));
          printf ("\nProduto inserido com sucesso!\n");
        }
        else printf ("\nProduto não inserido devido ao erro.\n");

        printf ("\n\nDigite qualquer tecla para continuar: ");
        getchar();
        system ("clear");
        break;
      case 2:
        if (!tamanho) printf ("\nCadastre pelo menos um produto para realizar esta operação.");
        else
        {
          permitir = remover_produto(produtos, tamanho, codigo);
          if (permitir) printf("\nProduto removido com sucesso!");
          else printf("\nErro: Produto não removido.");
        }
        
        printf ("\n\nDigite qualquer tecla para continuar: ");
        getchar();
        system ("clear");
        break;
      case 3:
        if (!tamanho) printf ("\nCadastre pelo menos um produto para realizar esta operação.");
        else
        {
          indice = buscar(produtos, tamanho, codigo);
          if (indice >= 0) printf("\nO índice do produto é: %i", indice);   
          else printf("\nErro: produto não cadastrado.");
        }

        printf ("\n\nDigite qualquer tecla para continuar: ");
        getchar();
        system ("clear");
        break;
      case 4:
        if (!tamanho) printf ("\nCadastre pelo menos um produto para realizar esta operação.");
        else
        {
          permitir = comprar(produtos, tamanho, codigo);
          if (permitir) printf("\nCompra realizada com sucesso!");
          else printf("\nNão foi possível realizar a compra.");
        }
        
        printf ("\n\nDigite qualquer tecla para continuar: ");
        getchar();
        system ("clear");
        break;
      case 5:
        if (!tamanho) printf ("\nCadastre pelo menos um produto para realizar esta operação.");
        else
        {
          permitir = vender(produtos, tamanho, codigo);
          if (permitir) printf("\nVenda realizada com sucesso!");
          else printf("\nVenda não realizada.");
        }

        printf ("\n\nDigite qualquer tecla para continuar: ");
        getchar();
        system ("clear");
      break;
      case 6:
        if (!tamanho)
        {
          printf ("\nCadastre pelo menos um produto para realizar esta operação.");
          printf ("\n\nDigite qualquer tecla para continuar: ");
          getchar();
          system ("clear");
        }
        else gerar_relatorios (produtos, tamanho);
      default:
        break;
    }
  }
  
  return 0;
}

//Função que permite a inserção do produto
int inserir_produto(Produto* produtos, int tamanho, int posicao, Produto novo) {
  produtos[tamanho] = novo;
  return 1;
}

//Função para retornar um produto novo
Produto obter_produto_novo(Produto* prdts, int tam) {
  int length, existe; //Variável de comprimento do vetor
  Produto prdt;
  memset(&prdt, 0, sizeof(Produto));  //Zerando o produto para limpar o "lixo"

  do
  {
    existe = 0;
    char string[10];
    
    printf ("\nDigite o Código do produto: ");
    fgets (string, 9, stdin);
    
    length = strlen(string) - 1;

    if (length > 5) printf ("\nErro: Código não pode exceder 5 caracteres.");
    else strncpy (prdt.id_produto, string, 5);

    for (int i = 0; i < tam; i++)
    {
      if (strcmp (prdts[i].id_produto, prdt.id_produto) == 0 && prdts[i].status==1) existe = 1;
    }

    if (existe) 
    {
      printf ("\nErro: ID já cadastrado.");
      printf ("\nDigite qualquer tecla para continuar: ");
      getchar();
      system ("clear");
    }
  } while (length > 5 || existe);
  
  printf ("\nDigite o nome do produto: ");
  fgets(prdt.nome, 29, stdin); 
  
  printf ("\nDigite o preço do produto: ");
  scanf ("%f", &prdt.preco);
  getchar();
  
  prdt.qtd_disp = 0;
  prdt.status = 1;
  
  return prdt;
}

//Função para remover produto
int remover_produto(Produto* prdts, int tam, char id[6]) {
  int length, existe = 0, retorno;
  
  do
  {
    char string[10];
    printf ("\nDigite o código do produto: ");
    fgets (string, 10, stdin);
    
    length = strlen(string) - 1;
    if (length > 5) printf ("\nErro: Código não pode exceder 5 caracteres.");
    else strncpy(id, string, 5);
  } while (length > 5);
  
  for (int i = 0; i < tam; i++)
  {
    if (strcmp(prdts[i].id_produto, id) == 0 && prdts[i].status == 1)
    {
      prdts[i].status = 0;
      existe++;
      retorno = 1;
    }
  }
  
  if (!existe)
  {
    printf("\nErro: Código de produto não cadastrado.");
    retorno = 0;
  }
  
  return retorno;
}
 
//Função buscar produto

int buscar(Produto* produtos, int tamanho, char codigo[6]){
  int length, existe = 0, retorno;

  //Laço que recebe o ID somente se for menor que 6.
  do
  {
    char string[10];
    printf ("\nDigite o código do produto: ");
    fgets (string, 9, stdin);
    
    length = strlen(string) - 1;
    
    if (length > 5) printf ("\nErro: Código não pode exceder 5 caracteres.");
    else strncpy (codigo, string, 5);   
  } while (length > 5);

  //Laço que verifica se o código digitado existe no vetor de produtos.
  for (int i = 0; i < tamanho; i++)
  {
    if (strcmp(produtos[i].id_produto, codigo) == 0 && produtos[i].status ==1)
    {
      printf ("\nO produto buscado é:");
      printf ("\nCódigo do Produto: %s", produtos[i].id_produto);
      printf ("\nNome: %s", produtos[i].nome);
      printf ("Preço: R$%2.f", produtos[i].preco);
      printf ("\nQuantidade disponível: %d", produtos[i].qtd_disp);
      printf ("\nNúmero de Vendas: %d", produtos[i].n_vendas);
      printf ("\nNúmero de Compras: %d", produtos[i].n_compras);
      
      existe = 1;
      retorno = i;
      break;
    }       
  }
  
  if(!existe) retorno = -1;

  return retorno;
}

//Função para comprar produto
/* Deve verificar se o produto com o “código” existe. Se existir, deve incrementar a “quantidade_disponivel” e retornar 1 para informar o sucesso. Caso contrário, deve retornar 0. */
int comprar(Produto* produtos, int tamanho, char codigo[6]){
  int length, existe = 0, retorno;

  //Laço que recebe o ID somente se for menor que 6
  do
  {
    char string[10];
    printf ("\nDigite o código do produto: ");
    fgets (string, 9, stdin);
    
    length = strlen(string) - 1;
    
    if (length > 5) printf ("\nErro: Código não pode exceder 5 caracteres.");
    else strncpy(codigo, string, 5); 
  } while(length > 5);

  //verifica se o código existe e compra quantidade desejada
  for (int i = 0; i < tamanho; i++)
  {
    if (strcmp(produtos[i].id_produto, codigo) == 0 && produtos[i].status ==1 )
    {
      int qtd;
      
      do
      {
        printf("\nDigite a quantidade a ser comprada: ");
        scanf("%i", &qtd);
        getchar();
      } while (qtd <= 0);
      
      produtos[i].qtd_disp += qtd; 
      produtos[i].n_compras += qtd;
      existe = 1;
      
      printf("\nVocê comprou %i unidades de %s", qtd, produtos[i].nome);
      retorno = 1;
      break;
    }
  }

  if (!existe)
  {
    printf("\nErro: Código de produto não cadastrado.");
    retorno = 0;
  }

  return retorno;
}

//Função para vender um produto
/*Deve-se verificar se o produto com o “codigo” existe. Se existir e a “quantidade_disponivel” for maior que zero, deve-se decrementar a “quantidade_disponivel” e retornar 1 para informar o sucesso. Caso contrário, deve-ser retornar 0. */
int vender(Produto* produtos, int tamanho, char codigo[6]){
  int length, existe = 0, retorno;
  
  do
  {
    char string[10];
    printf ("\nDigite o código do produto: ");
    fgets (string, 9, stdin);
    
    length = strlen(string) - 1;
    
    if (length > 5) printf ("\nErro: Código não pode exceder 5 caracteres.");
    else strncpy(codigo, string, 5);
  } while(length > 5);

  for (int i = 0; i < tamanho; i++)
  {
    //verificar se codigo existe
    if (strcmp(produtos[i].id_produto, codigo) == 0 && produtos[i].qtd_disp > 0 && produtos[i].status ==1)
    {
      int qtd_vender;
      printf("\nA quantidade disponível de %sé: %i", produtos[i].nome, produtos[i].qtd_disp);

      //Vende a quantidade solicitada
      do
      {
        printf("\nDigite a quantidade a ser vendida: ");
        scanf("%i", &qtd_vender);
        getchar();

        if (qtd_vender > produtos[i].qtd_disp)
        {
          printf("\nErro: Quantidade desejada maior que quantidade disponível.");
          printf ("\nDigite qualquer tecla para tentar novamente: ");
          getchar();
          system ("clear");
        }
      } while (qtd_vender <= 0 || qtd_vender > produtos[i].qtd_disp);
      
      produtos[i].n_vendas += qtd_vender;
      produtos[i].qtd_disp -= qtd_vender;
      
      printf("Você vendeu %i unidades de %s", qtd_vender, produtos[i].nome);
      
      existe = 1;
      retorno = 1; 
      break;
    }
  }

  //Imprime erro de venda se o produto não existe.
  if (!existe)
  {
    printf ("\nErro: produto não cadastrado ou não está disponível.");
    retorno = 0;
  }

  return retorno;
}

void gerar_relatorios(Produto *prdts, int tam) {
  int escolha;

  printf("\t\t\tRELATÓRIOS\n\n- Digite: 1 (para relatório de produtos mais vendidos)\n- Digite: 2 (para relatório de produtos mais comprados)\n- Digite: 3 (para extrato)\n- Digite: 4 (para produtos em estoque)\n- Digite: 0 (para sair)\n\n-->  ");
  scanf ("%i", &escolha);
  getchar();
  system ("clear");
  
  switch (escolha)
  {
    case 0:
      break;
    case 1:
      imprimir_mais_vendidos(prdts, tam);
      break;
    case 2:
      imprimir_mais_comprados(prdts, tam);
      break;
    case 3:
      imprimir_extrato(prdts, tam);
      break;
    case 4:
      imprimir_estoque(prdts, tam);
      break;
    default:
      break;
  } 
}

//Função que imprime os produtos mais vendidos
void imprimir_mais_vendidos (Produto* prdts, int tam) { 
int aux, len, qtd_status = 0, contador = 0;

  //Laço que verifica a quantidade de produtos com status 1
  for (int i = 0; i < tam; i++)
  {
    if(prdts[i].status == 1) qtd_status++;    
  }

  //Inicializa um vetor de produtos a serem ordenados
  Produto prdts_comp[qtd_status];

  //Laço que inicializa o vetor a ser ordenado
  for(int i = 0; i < tam; i++)
  {
    if (prdts[i].status == 1)
    {
      prdts_comp[contador] = prdts[i];
      contador++;
    }
  }

  //Ordenação do vetor de produtos mais comprados
  for (int i = 1; i < qtd_status; i++)
  {
    for (int j = 0; j < qtd_status - 1; j++) 
    {
      if (prdts_comp[j].n_vendas < prdts_comp[i].n_vendas) 
      {        
        aux = prdts_comp[j].n_vendas;
        prdts_comp[j].n_vendas = prdts_comp[i].n_vendas;
        prdts_comp[i].n_vendas = aux;
        
        len = strlen(prdts_comp[j].nome);
        char temp_s[len];
        
        strcpy(temp_s, prdts_comp[j].nome);
        strcpy(prdts_comp[j].nome, prdts_comp[i].nome);
        strcpy(prdts_comp[i].nome, temp_s);
      }
    }
  }

  printf("\tITENS MAIS VENDIDOS\n");
  printf("===========================\n\n");
  
  for(int i = 0; i < qtd_status; i++)
  {
    printf("Produto: %s\n%i vendas\n\n", prdts_comp[i].nome, prdts_comp[i].n_vendas);
    printf("============================\n\n");
  } 
  
  printf ("\nDigite qualquer tecla para continuar: ");
  getchar();
  system ("clear");
}

//Função que gera relatório sobre os itens mais comprados
void imprimir_mais_comprados(Produto* prdts, int tam) {
  int aux, len, qtd_status = 0, contador = 0;

  //Laço que verifica a quantidade de produtos com status 1
  for (int i = 0; i < tam; i++)
  {
    if(prdts[i].status == 1) qtd_status++;    
  }

  //Inicializa um vetor de produtos a serem ordenados
  Produto prdts_comp[qtd_status];

  //Laço que inicializa o vetor a ser ordenado
  for(int i = 0; i < tam; i++)
  {
    if (prdts[i].status == 1)
    {
      prdts_comp[contador] = prdts[i];
      contador++;
    }
  }

  //Ordenação do vetor de produtos mais comprados
  for (int i = 1; i < qtd_status; i++)
  {
    for (int j = 0; j < qtd_status - 1; j++) 
    {
      if (prdts_comp[j].n_compras < prdts_comp[i].n_compras) 
      {        
        aux = prdts_comp[j].n_compras;
        prdts_comp[j].n_compras = prdts_comp[i].n_compras;
        prdts_comp[i].n_compras = aux;
        
        len = strlen(prdts_comp[j].nome);
        char temp_s[len];
        
        strcpy(temp_s, prdts_comp[j].nome);
        strcpy(prdts_comp[j].nome, prdts_comp[i].nome);
        strcpy(prdts_comp[i].nome, temp_s);
      }
    }
  }

  printf("\tITENS MAIS COMPRADOS\n");
  printf("============================\n\n");
  
  for (int i = 0; i < qtd_status; i++)
  {
    printf("Produto: %s\n%i compras\n\n", prdts_comp[i].nome, prdts_comp[i].n_compras);
    printf("============================\n\n");
  } 
  
  printf ("\nDigite qualquer tecla para continuar: ");
  getchar();
  system ("clear");
}

//Função que imprime o relatório de estoque
void imprimir_estoque(Produto* prdts, int tam) {
  printf("\tPRODUTOS EM ESTOQUE\n");
  printf("===========================\n\n");

  //Laço que percorre o vetor de produtos e imprime as características dos produtos em estdoque
  for (int i = 0; i < tam; i++)
  {
    //Imprime somente se o status do produto diferir de zero
    if (prdts[i].status != 0)
    {
      printf ("Produto: %s\n", prdts[i].nome);
      printf ("Código do produto: %s\n", prdts[i].id_produto);
      printf ("Quantidade em estoque: %i\n", prdts[i].qtd_disp);
      printf ("\nPreço do produto: R$%.2f\n\n", prdts[i].preco);
      printf("=========================\n");
    }
  }

  printf ("\n\nDigite qualquer tecla para continuar: ");
  getchar();
  system ("clear");
}

//Função para gerar relatório de extrato
void imprimir_extrato(Produto* prdts, int tam) {
  float receita;
  
  printf("\t\t  EXTRATO\n");
  printf("===========================\n\n");

  //Percorre o vetor de produtos para imprimir a quantidade de vendas e a receita pelos produtos.
  for (int i = 0; i < tam; i++)
  {
    if (prdts[i].status != 0)
    {
      printf ("Produto: %s\n", prdts[i].nome);
      printf ("Quantidade vendida: %i\n", prdts[i].n_vendas);
      printf ("\nPreço do produto: R$%.2f\n", prdts[i].preco);
      printf ("\nReceita: R$%.2f\n\n", prdts[i].preco * prdts[i].n_vendas);
      receita += prdts[i].preco * prdts[i].n_vendas;
      printf("===========================\n\n");
    }
  }
  
  printf("Total arrecadado: R$%.2f\n\n", receita);
  printf("===========================\n");

  printf ("\n\nDigite qualquer tecla para continuar: ");
  getchar();
  system ("clear");
}