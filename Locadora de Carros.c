#include <stdio.h>
#include <stdlib.h>

typedef struct modelo{
	char nomeModelo[20];
	char placaModelo[20];
	struct modelo *proxModelo;
	struct modelo *topoModelo;
	char nomeCliente[20];
	struct modelo *proxCliente;
	struct modelo *finalCliente;
}modelo;

//cria uma lista vazia para armazenar os modelos//
modelo *criaLista(){
	struct modelo *novaLista;
	novaLista = malloc(sizeof(struct modelo));
	novaLista->proxModelo = NULL;
	return novaLista;
}

int verificaLista(modelo *lista){
	if(lista->proxModelo != NULL) return 1;
	else return 0;
} 

//FUNÇÕES MODELO//
//-----------------------------------------------------------------------------------------------------//
//cria um novo modelo e adciona na lista//
void *criaModelo(modelo *lista){
	struct modelo *aux, *novoModelo;
	novoModelo = malloc(sizeof(struct modelo));
	aux = malloc(sizeof(struct modelo));
	aux = lista;
	printf("DIGITE O MODELO A SER CRIADO:\n");
	fflush(stdin);
	gets(novoModelo->nomeModelo);
	fflush(stdin);
	system("cls");
	while(novoModelo->nomeModelo == NULL){
		printf("MODELO NAO CRIADO TENTE NOVAMENTE\n");
		fflush(stdin);
		gets(novoModelo->nomeModelo);
		fflush(stdin);
		system("cls");
	}
	printf("==========================\n");
	printf("MODELO   %s   CRIADO     \n", novoModelo->nomeModelo);
	printf("==========================\n");
	novoModelo->proxCliente = NULL;
	novoModelo->topoModelo = NULL;
	novoModelo->proxModelo = aux->proxModelo;
	aux->proxModelo = novoModelo;
	system("pause");
	system("cls");
}

//mostra todos os modelos dentro da lista//
void consultaModelos(modelo *lista){
	struct modelo *aux;
	aux = lista->proxModelo;
	printf("============================\n");
	printf("      MODELOS LISTADOS      \n");
	while(aux != NULL){
		printf("============================\n");
		printf("           %s\n", aux->nomeModelo);
		aux = aux->proxModelo;
	}
	printf("============================\n");
	system("pause");
	system("cls");
}

//busca e retorna o modelo selecionado//
modelo *selecionaModelo(modelo *lista){
	struct modelo *modelo;
	modelo = malloc(sizeof(struct modelo));
	modelo = lista->proxModelo;
	int op = 0;
	while(op!=1){
		printf("===================================\n");
		printf(" MODELO: %s\n", modelo->nomeModelo);
		printf("===================================\n");
		printf("DIGITE 1 PARA SELECIONAR O MODELO  \n");
		printf("DIGITE 2 PARA PASSAR AO PROXIMO    \n");
		scanf("%d", &op);
		switch (op){
			case 1: 
				system("cls");
				return modelo;
			break;
			case 2:
				if(modelo->proxModelo!=NULL){
					modelo = modelo->proxModelo;
				}else{
					printf("NAO HA MAIS MODELOS DISPONIVEIS\n");
					system("pause");
				}
			break;
			default:
				printf("OPCAO INVALIDA\n");
				system("pause");
				op=0;
			break;
		}
		system("cls");
	}
}
//acrescenta um novo veiculo a pilha do modelo selecionado//
void empilhaNovoModelo(modelo *listaModelo){
	struct modelo *pilhaModelo, *aux;
	aux = malloc(sizeof(struct modelo));
	printf("SELECIONE O MODELO QUE GOSTARIA DE INSERIR\n");
	pilhaModelo = selecionaModelo(listaModelo);
	printf("DIGITE O VEICULO QUE GOSTARIA DE INSERIR NO MODELO %s\n",pilhaModelo->nomeModelo);
	fflush(stdin);
	gets(aux->placaModelo);
	fflush(stdin);
	aux->topoModelo =  pilhaModelo->topoModelo;
	pilhaModelo->topoModelo = aux;
	aux = pilhaModelo->topoModelo;
	if(pilhaModelo->topoModelo != NULL){
		printf("VEICULO: %s INSERIDO COM SUCESSO NO MODELO: %s\n", aux->placaModelo, pilhaModelo->nomeModelo);
		system("pause");
	}
	else{
		printf("ERRO TENTE NOVAMENTE");
		system("cls");
	}
	system("cls");
}

//retira o modelo do final da pilha e o retorna//
modelo *desempilhaModelo(modelo *modelo){
	struct modelo *aux;
	aux = modelo->topoModelo;
	modelo->topoModelo = aux->topoModelo;
	return aux;
}
//empilha um modelo ao final da pilha e o retorno//
void *empilhaModelo(modelo *pilhaModelo, modelo *aux2){
	struct modelo *aux;
	aux = malloc(sizeof(struct modelo));
	aux = aux2;
	aux->topoModelo = pilhaModelo->topoModelo;
	pilhaModelo->topoModelo = aux;	
}

//verifica os veiculos na pilha do modelo selecionado//
void *consultaPilha(modelo *listaModelo){
	struct modelo *pilhaModelo, *aux, *aux2;
	pilhaModelo = malloc(sizeof(struct modelo));
	aux = malloc(sizeof(struct modelo));
	aux->topoModelo = NULL;
	printf("SELECIONE O MODELO QUE GOSTARIA DE CONSULTAR\n");
	pilhaModelo = selecionaModelo(listaModelo);
	if(verificaDisponivel(pilhaModelo)){	
		while(pilhaModelo->topoModelo != NULL){
			aux2 = desempilhaModelo(pilhaModelo);
			empilhaModelo(aux, aux2);
		}
		while(aux->topoModelo != NULL){
			aux2 = desempilhaModelo(aux);
			empilhaModelo(pilhaModelo, aux2);
			printf("%s\n", aux2->placaModelo);
		}
		printf("===FIM DOS VEICULOS===\n");
	}else{
		printf("NAO EXISTEM VEICULOS DISPONIVEIS DESSE MODELO\n");
	}
	system("pause");
	system("cls");
}

//verifica se a pilha do modelo esta vazia//
int verificaDisponivel(modelo *modelo){
	if(modelo->topoModelo != NULL) return 1;
	else return 0;
}

//FUNÇÕES CLIENTE
//--------------------------------------------------------------------------------------------//

//insere um cliente na fila do modelo selecionado//
void enfileraNovoCliente(modelo *listaModelo){
	struct modelo *modeloFila, *aux, *finalFila;
	aux = malloc(sizeof(struct modelo));
	printf("SELECIONE O MODELO QUE GOSTARIA DE ADCIONAR O CLIENTE NA FILA\n");
	modeloFila = selecionaModelo(listaModelo);
	printf("DIGITE O NOME DO CLIENTE PARA ENTRAR NA FILA DO MODELO: %s\n", modeloFila->nomeModelo);
	fflush(stdin);
	gets(aux->nomeCliente);
	fflush(stdin);
	aux->proxCliente = modeloFila->proxCliente;
	modeloFila->proxCliente = aux;
	printf("%s ADICIONADO A FILA DO MODELO %s\n", modeloFila->proxCliente->nomeCliente, modeloFila->nomeModelo);
}

//busca o proximo cliente a ser atendido na fila do modelo//
modelo *fimFilaCliente(modelo *modelo){
	struct modelo *aux;
	aux = modelo;
	while(aux->proxCliente != NULL){
		aux = aux->proxCliente;
	}
	return aux;
}
//insere um cliente na fila do modelo enviado//
void *enfileraCliente(modelo *modeloCliente, modelo *aux2){
	aux2->proxCliente = modeloCliente->proxCliente;
	modeloCliente->proxCliente = aux2;
}

//retira o primeiro cliente o retorna e anda a fila//
modelo *desinfileraCliente(modelo *modelo){
	struct modelo *aux, *fim;
	aux = malloc(sizeof(struct modelo));
	fim = fimFilaCliente(modelo);
	aux = modelo;
	while(aux->proxCliente != fim){
		aux = aux->proxCliente;
	}
	aux->proxCliente = fim->proxCliente;
	return fim;
}

void *consultaClientes(modelo *lista){
	struct modelo *modeloFila, *aux, *aux2;
	aux = malloc(sizeof(struct modelo));
	aux->proxCliente = NULL;
	aux2 = malloc(sizeof(struct modelo));
	printf("SELECIONE O MODELO QUE GOSTARIA DE CONSULTAR OS CLIENTES DA FILA\n");
	modeloFila = selecionaModelo(lista);
	if(verificaCliente(modeloFila)){
		while(modeloFila->proxCliente != NULL){
			aux2 = desinfileraCliente(modeloFila);
			enfileraCliente(aux,aux2);
			printf("%s ESTA NA FILA DO MODELO: %s\n", aux2->nomeCliente,modeloFila->nomeModelo);
		}
		while(aux->proxCliente != NULL){
			aux2 = desinfileraCliente(aux);
			enfileraCliente(modeloFila,aux2);
		}
	}else{
		printf("NAO EXISTEM CLIENTES NA FILA DESSE MODELO\n");
	}
	system("pause");
	system("cls");
}

//retira o cliente da fila do modelo selecionado o retorna e movimenta a fila//
modelo *desistenciaCliente(struct modelo *listaModelo){
	struct modelo *modeloFila, *clienteDesiste;
	clienteDesiste = malloc(sizeof(struct modelo));
	printf("SELECIONE O MODELO QUE GOSTARIA DE RETIRAR O CLIENTE DA FILA\n");
	modeloFila = selecionaModelo(listaModelo);
	if(verificaCliente(modeloFila) == 1){
		clienteDesiste = desinfileraCliente(modeloFila);
		printf("O CLIENTE %s FOI RETIRADO DA FILA PARA O MODELO %s\n", clienteDesiste->nomeCliente, modeloFila->nomeModelo);
		system("pause");
		system("cls");
		return clienteDesiste;
	}else{
		printf("O MODELO SELECIONADO NAO TEM CLIENTES NA FILA\n");
		system("pause");
		system("cls");
		return NULL;
	}
}


//vrifica se a fila de clientes está vazia//
int verificaCliente(modelo *modelo){
	if(modelo->proxCliente != NULL) return 1;
	else return 0;
}

//----------------------------------------------------------------------------------------------//
//FUNÇÃO DE LOCAÇÃO
//realiza a locacao de um cliente com um veiculo do modelo selecionado//
void locacao(modelo *lista){
	struct modelo *modelo, *aux;
	aux = malloc(sizeof(struct modelo));
	printf("SELECIONE O MODELO PARA REALIZAR A LOCACAO\n");
	modelo = selecionaModelo(lista);
	if(verificaDisponivel(modelo) == 1 && verificaCliente(modelo) == 1){
		aux = desinfileraCliente(modelo);
		printf("O CLIENTE %s ",aux->nomeCliente);
		aux = desempilhaModelo(modelo);
		printf("LOCOU O VEICULO %s MODELO %s COM SUCESSO\n", aux->placaModelo, modelo->nomeModelo);
	}else{
		if(verificaDisponivel(modelo)!=1){
			printf("NAO EXISTEM MODELOS DISPONIVEIS\n");
		}
		if(verificaCliente(modelo)!=1){
			printf("NAO EXISTEM CLIENTES NA FILA DESSE MODELO\n");
		}
	}
	system("pause");
	system("cls");
}
void verificaLocacao(modelo *lista){
	struct modelo *locacao, *modeloAux, *clienteAux;
	locacao = lista->proxModelo;
	while(locacao != NULL){
		modeloAux = locacao;
		if(verificaDisponivel(modeloAux) && verificaCliente(modeloAux)){
			printf("LOCACAO DISPONIVEL PARA O MODELO:  %s\n", modeloAux->nomeModelo);
		}else{
			printf("NAO HA LOCACAO DISPONIVEL PARA O MODELO: %s\n", modeloAux->nomeModelo);
		}
		locacao = locacao->proxModelo;
	}
	system("pause");
}
//---------------------------------------------------------------------------------------------//

//FUNÇÕES MENU

int menuModelo(modelo *lista){
	struct modelo *veiculo, *modeloE;
	int opcao = 0;
	while(opcao != 6){
		printf("SELECIONE A OPERACAO QUE GOSTARIA DE REALIZAR\n");
		printf("1 - PARA ADCIONAR UM NOVO MODELO A LISTA\n");
		printf("2 - PARA CONSULTAR A LISTA DE MODELOS\n");
		printf("3 - PARA ADCIONAR UM NOVO VEICULO A PILHA DE MODELOS\n");
		printf("4 - PARA CONSULTAR OS VEICULOS DISPONIVEIS DE DETERMINADO MODELO\n");
		printf("5 - PARA RETIRAR UM VEICULO DE DETERMINADO MODELO\n");
		printf("6 - PARA VOLTAR AO MENU ANTERIOR\n");
		printf("\nOPERACAO: ");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				system("cls");
				criaModelo(lista);
			break;
			case 2:
				system("cls");
				if(verificaLista(lista)){
					consultaModelos(lista);
				}else{
					printf("NAO EXISTEM MODELOS NA LISTA\n");
					system("pause");
				}
			break;
			case 3:
				system("cls");
				if(verificaLista(lista)){
					empilhaNovoModelo(lista);
				}else{
					printf("NAO EXISTEM MODELOS NA LISTA\n");
					system("pause");
				}
			break;
			case 4:
				system("cls");
				if(verificaLista(lista)){
					consultaPilha(lista);
				}else{
					printf("NAO EXISTEM MODELOS NA LISTA\n");
					system("pause");
				}
			break;
			case 5:
				system("cls");
				if(verificaLista(lista)){
					veiculo = malloc(sizeof(struct modelo));
					modeloE = malloc(sizeof(struct modelo));
					modeloE->topoModelo = NULL;
					modeloE = selecionaModelo(lista);
					if(verificaDisponivel(modeloE)){
						veiculo = desempilhaModelo(modeloE);
						printf("%s FOI RETIRADO DA PILHA %s\n", veiculo->placaModelo,modeloE->nomeModelo);				
						system("pause");
					}else{
						printf("NAO EXISTEM VEICULOS NO MODELO ESCOLHIDO\n");
						system("pause");
					}
				}else{
					printf("NAO EXISTEM MODELOS NA LISTA\n");
					system("pause");
				}
			break;
			case 6: 
				system("cls");
			return 0;
			default: 
				printf("\n OPCAO INVALIDA TENTE NOVAMENTE \n");
				system("pause");
			break;
		}
		system("cls");
	}
	return 0;
}

int menuCliente(modelo *lista){
	int opcao = 0;
	while(opcao != -1){
		printf("SELECIONE A OPERACAO QUE GOSTARIA DE REALIZAR\n");
		printf("1 - PARA INSERIR UM CLIENTE NA FILA UM MODELO\n");
		printf("2 - PARA CONSULTAR QUAIS CLIENTES ESTAO NA FILA DE UM MODELO\n");
		printf("3 - PARA RETIRAR UM CLIENTE DA FILA DE UM MODELO\n");
		printf("4 - PARA VOLTAR AO MENU ANTERIOR\n");
		printf("\nOPERACAO: ");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				system("cls");
				if(verificaLista(lista)){
					enfileraNovoCliente(lista);
				}else{
					printf("NAO EXISTEM MODELOS NA LISTA\n");
					system("pause");
				}
			break;
			case 2:
				system("cls");
				if(verificaLista(lista)){
					consultaClientes(lista);
				}else{
					printf("NAO EXISTEM MODELOS NA LISTA\n");
					system("pause");
				}
			break;
			case 3:
				system("cls");
				if(verificaLista(lista)){
					desistenciaCliente(lista);
				}else{
					printf("NAO EXISTEM MODELOS NA LISTA\n");
					system("pause");
				}
			break;
			case 4:
				system("cls");
			return 0;
			default: 
				printf("\n OPCAO INVALIDA TENTE NOVAMENTE \n");
				system("pause");
			break;
		}
		system("cls");
	}
	return 0;
}

int menuLocacao(modelo *lista){
	int opcao=0;
	while(opcao!=3){
		printf("SELECIONE A OPERACAO QUE GOSTARIA DE REALIZAR\n");
		printf("1 - PARA REALIZAR UMA LOCACAO DE VEICULO\n");
		printf("2 - PARA VERIFICAR SE EXISTEM LOCACOES POSSIVEIS\n");
		printf("3 - PARA VOLTAR AO MENU ANTERIOR\n");
		printf("\nOPERACAO: ");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				system("cls");
				if(verificaLista(lista)){
					locacao(lista);	
				}else{
					printf("NAO EXISTEM MODELOS NA LISTA\n");
					system("pause");
				}
			break;
			case 2:
				system("cls");
				if(verificaLista(lista)){
					verificaLocacao(lista);
				}else{
					printf("NAO EXISTEM MODELOS NA LISTA\n");
					system("pause");
				}
			break;
			case 3:
				system("cls");
			return 0;
			default: 
				printf("\n OPCAO INVALIDA TENTE NOVAMENTE \n");
				system("pause");
			break;
				
		}
		system("cls");
	}
	return 0;
}



int main(){
	struct modelo *lista;
	lista = criaLista();
	int op = 0;
	while(op!=4){
		printf("SELECIONE O MENU QUE GOSTARIA DE INTERAGIR\n");
		printf("1 - PARA O MENU DE MODELOS E VEICULOS\n");
		printf("2 - PARA O MENU DE CLIENTES\n");
		printf("3 - PARA O MENU DE LOCACAO\n");
		printf("4 - PARA FINALIZAR O PROGRAMA\n");
		printf("\nOPCAO: ");
		scanf("%d", &op);
		switch(op){
			case 1:
				system("cls");
				op = menuModelo(lista);
			break;
			case 2:
				system("cls");
				op = menuCliente(lista);
			break;
			case 3:
				system("cls");
				op = menuLocacao(lista);
			break;
			case 4:
				system("cls");
				printf("VOLTE SEMPRE\n");
			break;
			default:
				printf("\n  OPCAO INVALIDA TENTE NOVAMENTE  \n");
				system("pause");
				system("cls");
			break;
		}
	}
	return 0;
}




















