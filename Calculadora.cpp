#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

const int Mx_Bina = 30, Mx_Hist = 10;

void M_Erro(){
	printf("\n________________________________________________________\n");
	printf("|              !!!      ERRO      !!!                  |\n");
	printf("|______________________________________________________|\n\n");
	printf(" Possiveis erros: \n\n");
	printf(" 1 - O Valor inserido não corresponde a uma opção existente.\n");
	printf(" 2 - O Valor inserido possui caracteres invalidos.\n\n");
	getchar();
	system("cls");
}

void Mover_D(char B[]){
	while(B[0] != '1' && B[0] != ','){
		for(int P = 0; P <= strlen(B); P++){
			B[0+P] = B[P+1];
		}
		if(B[0] != '1'){
			break;
		}
	}
}

void Validacao(char B[], int *V){
	for(int Cont = 0; Cont < (strlen(B)); Cont++){
		if(B[Cont] != '0' && B[Cont] != '1'){
			*V = 0;
		}
	}
	while(B[0] == '0' && strlen(B) > 1){
			Mover_D(B);
		}
	if(B[0] != '1'){
		B[0] = '0';
		B[1] = 0;
	}
}

void Mover_E(char B[]){
	int P = strlen(B);
	for (P = P; P >= 0; P--){
		B[P + 1] = B[P];
		B[P] = 0;
	}
	B[0] = '0';
	B[strlen(B)] = 0;
}

void Somar(char B1[], char B2[], char R[]){
	while(strlen(B1) < strlen(B2)){
		Mover_E(B1);
	}
	while((strlen(B1) > strlen(B2))){
		Mover_E(B2);
	}
	for(int C = strlen(B1) - 1; C >= 0; C--){
		if((B1[C] != '1' && B2[C]!= '1' && R[0] == '1')||(B1[C] != '1' && B2[C]== '1' && R[0] != '1')||(B1[C] == '1' && B2[C]!= '1' && R[0] != '1')){
			R[0] = '1';
			if(C != 0){
			Mover_E(R);}
		} else if((B1[C] != '1' && B2[C]== '1' && R[0] == '1')||(B1[C] == '1' && B2[C]!= '1' && R[0] == '1')||(B1[C] == '1' && B2[C]== '1' && R[0] != '1')){
			R[0] = '0';
			Mover_E(R);
			R[0] = '1';
		} else if (B1[C] != '1' && B2[C]!= '1' && R[0] != '1'){
			R[0] = '0';
			if(C != 0){
			Mover_E(R);}
		} else if (B1[C] == '1' && B2[C]== '1' && R[0] == '1'){
			R[0] = '1';
			Mover_E(R);
			R[0] = '1';
		}
	}
}

void Subtrair(char B1[], char B2[], char R[]){
	int N = 0;
	int I = 0;
	if(strlen(B1) == strlen(B2)){
		if(strcmp(B1, B2) < 0){
			N = 1;
		} 
		if(strcmp(B1, B2) == 0){
			I = 1;
		}
	}
	while(strlen(B1) < strlen(B2)){
		Mover_E(B1);
		N = 1;
	}
	while((strlen(B1) > strlen(B2))){
		Mover_E(B2);
	}
	
	char M1[Mx_Bina], M2[Mx_Bina], S[Mx_Bina], U[Mx_Bina];
	M1[1] = 0;
	M2[1] = 0;
	S[0] = '1';
	S[1] = 0;
	R[0] = '0';
	R[1] = 0;
	
	if(N == 1){
		strcpy(U, B1);
	} else{
		strcpy(U, B2);
	}
	
	for(int C = 0; C < strlen(U); C++){
		if(U[C] == '1'){
			M1[C] = '0';
		} else {
			M1[C] = '1';
		}
	}
	Somar(M1, S, M2);
	if(N == 1){
		Somar(B2, M2, R);
		R[0] = '0';
		while(R[0] == '0' && strlen(R) > 1){
			Mover_D(R);
		}
		Mover_E(R);
		R[0] = '-';
	}else if(I == 1){
		R[0] = '0';
		R[1] = 0;
	}else{	
		Somar(B1, M2, R);
		R[0] = '0';
		while(R[0] == '0' && strlen(R) > 1){
			Mover_D(R);
		}
	}
}

void Clean(char B[]){
	for(int C = strlen(B); C >= 0; C--){
		B[C] = 0;
	}
	B[0] = 32;
}

void Multiplicar(char B1[], char B2[], char R[]){
	char S[Mx_Bina];
	S[0] = 32;
	S[1] = 0;
	char Q[Mx_Bina];
	Q[0] = 32;
	Q[1] = 0;
	
	while(strlen(B1) < strlen(B2)){
		Mover_E(B1);
	}
	while((strlen(B1) > strlen(B2))){
		Mover_E(B2);
	}
	
	for( int B = strlen(B2) - 1; B >= 0; B--){
		for(int D = (strlen(B2) - B); D > 1; D--){
				Mover_E(S);
		}
		for( int C = strlen(B2) - 1; C >= 0; C--){
			if(B1[C] == '1' && B2[B] == '1'){
				S[0] = '1';
				Mover_E(S);
			} else if((B1[C] != '1' && B2[B] == '1') || (B1[C] == '1' && B2[B] != '1') || (B1[C] != '1' && B2[B] != '1')){
				S[0] = '0';
				Mover_E(S);	
			}
		}
		Somar(S, Q, R);
		Clean(S);
		Clean(Q);
		strcpy(Q, R);
		Clean(R);
	}
	Mover_D(Q);
	strcpy(R, Q);
	while(R[0] == '0' && strlen(R) > 1){
		Mover_D(R);
	}
}

void Dividir(char B1[], char B2[], char R[]){
	char S[Mx_Bina], C[Mx_Bina];
	int P = 0, V = 0, V2 = 0;
	S[0] = '0';
	S[1] = 0;
	C[0] = '0';
	C[1] = 0; 
	R[0] = '0';
	R[1] = 0;
	while((P <= strlen(B1) || S[0] != '0') && strlen(R) < Mx_Bina - 1){
		Clean(C);
		Subtrair(S, B2, C);
		printf("%s", C);
		if(C[0] != '-'){
			V2 = 0;
			strcpy(S,C);
			R[strlen(R)] = '1';
			R[strlen(R) + 1] = 0;
		} else{
			if(P <= strlen(B1)){
				S[strlen(S)] = B1[P];
				S[strlen(S) + 1] = 0;
				if(V2 != 0){
					R[strlen(R)] = '0';
					R[strlen(R) + 1] = 0;
				}
				V2 = 1;
				P++;
			} else {
				if(V == 0){
					R[strlen(R)] = ',';
					R[strlen(R) + 1] = 0;
					S[strlen(S)] = '0';
					S[strlen(S) + 1] = 0;
					V = 1;
				} else {
					R[strlen(R)] = '0';
					R[strlen(R) + 1] = 0;
					S[strlen(S)] = '0';
					S[strlen(S) + 1] = 0;
					
				}
			}
		}
		Mover_D(R);
		while(B2[0] == '0' && strlen(B2) > 1){
			Mover_D(B2);
		}
		while(S[0] == '0' && strlen(S) > 1){
			Mover_D(S);
		}
	}
	if(R[0] == ','){
		Mover_E(R);
	}
}

int main(){

setlocale(LC_ALL, "portuguese-brazilian");
//VARIAVEIS

int Execucao = 1, S_Menu = 0, S_Calc = 0, Val = 0, HF = 0;;
char L_Calc[4][13];
char NBin_1[Mx_Bina], NBin_2[Mx_Bina], Resul[Mx_Bina];
char HB1[Mx_Hist][Mx_Bina], HB2[Mx_Hist][Mx_Bina], HR[Mx_Hist][Mx_Bina], HOP[Mx_Hist];

strcpy(L_Calc[0], "Soma");
strcpy(L_Calc[1], "Subtração");
strcpy(L_Calc[2], "Multipicação");
strcpy(L_Calc[3], "Divisão");

while (Execucao != 0){
	
	S_Menu = 0;
	if(S_Calc < 5 && S_Calc > 0){
		S_Calc = 0;
		Val = 0;
		for( int C = 0; C <= Mx_Bina; C++){
			NBin_1[C] = 0;
			NBin_2[C] = 0;
			Resul[C] = 0;
		}
	}
	//refresh
	
	while(S_Menu < 1 || S_Menu > 3){
		//Menu
		printf("_____________________________________________________________________\n");
		printf("|                        MENU DE SELEÇÃO                            |\n");
		printf("|___________________________________________________________________|\n\n");
		printf(" 1 - Calcular\n");
		printf(" 2 - Histórico\n");
		printf(" 3 - Fechar\n\n");
		printf(" SELECIONE -> ");
		scanf("%i", &S_Menu);
		getchar();
		system("cls");
		if(S_Menu < 1 || S_Menu > 3){
			M_Erro();
		}
	}
	
	switch (S_Menu){
		case 1:
			//calculo
			while (S_Calc < 1 || S_Calc > 5){
				//menu calculo
				printf("_____________________________________________________________________\n");
				printf("|                        MENU DE CALCULO                            |\n");
				printf("|___________________________________________________________________|\n\n");
				printf(" 1 - Soma\n");
				printf(" 2 - Subtração\n");
				printf(" 3 - Multiplicação\n");
				printf(" 4 - Divisão\n");
				printf(" 5 - Voltar\n\n");
				printf(" SELECIONE -> ");
				scanf("%i", &S_Calc);
				getchar();
				system("cls");
				if(S_Calc < 1 || S_Calc > 5){
					M_Erro();
				}
			}
			while (Val == 0 && S_Calc <= 4){
				//validação e recebimento
				printf("_____________________________________________________________________\n");
				printf("|                   INSERIR NÚMEROS BINÁRIOS                        |\n");
				printf("|___________________________________________________________________|\n\n");
				printf(" ATENÇÃO: Números binarios são compostos apenas por Zeros '0' e Ums '1'.\n");
				printf(" Qualquer caractere que não seje um deles ira ocasionar em erro !!\n\n");
				printf(" Função selecionada: %s\n\n", L_Calc[S_Calc - 1]);
				printf(" 1° número binário -> ");
				fgets(NBin_1 , Mx_Bina , stdin);
				Val = 1;
				NBin_1[strlen(NBin_1) - 1] = 0;
				Validacao(NBin_1, &Val);
				if(Val == 1){
					printf("\n\n 2° número binário -> ");
					fgets(NBin_2 , Mx_Bina , stdin);
					NBin_2[strlen(NBin_2) - 1] = 0;
					Validacao(NBin_2, &Val);
				}
				if(S_Calc == 4 && (NBin_1[0] == '0' || NBin_2[0] == '0')){
					Val = 0;
				}
				if(Val == 0){
					system("cls");
					M_Erro();
				}
			}
			switch (S_Calc){
				case 1:
					Somar(NBin_1, NBin_2, Resul);
					break;
				case 2:
					//subtração
					Subtrair(NBin_1, NBin_2, Resul);
					break;
				case 3:
					//multiplicação
					Multiplicar(NBin_1, NBin_2, Resul);
					break;
				case 4:
					Dividir(NBin_1, NBin_2, Resul);
					//divisão
					break;
			}
			if(S_Calc <= 4){
				while(NBin_1[0] == '0' && strlen(NBin_1) > 1){
						Mover_D(NBin_1);
					}
				while(NBin_2[0] == '0' && strlen(NBin_2) > 1){
					Mover_D(NBin_2);
				}
				if(HF >= Mx_Hist){
					for(int Cont = 1; Cont < Mx_Hist - 1; Cont ++){
						strcpy(HB1[Cont - 1], HB1[Cont]);
						strcpy(HB2[Cont - 1], HB2[Cont]);
						strcpy(HR[Cont - 1], HR[Cont]);
						HOP[Cont - 1] = HOP[Cont];
					}
					strcpy(HB1[Mx_Hist - 1], "0");
					strcpy(HB2[Mx_Hist - 1], "0");
					strcpy(HR[Mx_Hist - 1], "0");
					HF = Mx_Hist - 1;
				}
				if(HF <= Mx_Hist - 1){
					strcpy(HB1[HF], NBin_1);
					strcpy(HB2[HF], NBin_2);
					strcpy(HR[HF], Resul);
					switch (S_Calc){
					case 1:
						HOP[HF] = '+';
						break;
					case 2:
						HOP[HF] = '-';
						break;
					case 3:
						HOP[HF] = 'x';
						break;
					case 4:
						HOP[HF] = '/';
						break;
				}
					system("cls");
					printf(" - RESULTADO - \n\n");
					printf(" %s %c %s = %s \n\n", HB1[HF], HOP[HF], HB2[HF], HR[HF]);
					printf("\n Pressione [Enter] -> ");
					getchar();
					system("cls");
					HF ++;
				}
			}
			//salvar
			//printar
			break;
		case 2:
			printf(" - HISTÓRICO - \n\n");
			if(HF <= 0){
				printf(" - Erro, nenhum calculo feito ainda.\n\n");
				printf("\n Pressione [Enter] -> ");
				getchar();
				system("cls");
			} else {
				for( int C = 0; C < HF; C++){
					printf(" %i -> %s %c %s = %s \n", C + 1, HB1[C], HOP[C], HB2[C], HR[C]);	
				}
				printf("\n Pressione [Enter] -> ");
				getchar();
				system("cls");
			}
			break;
		case 3:
			Execucao = 0;
			break;
	}
}
}
