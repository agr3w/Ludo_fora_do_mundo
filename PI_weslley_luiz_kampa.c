#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

#define RESET   "\x1b[0m"
#define RED     "12"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"

#define BOLD    "\x1b[1m"
#define UNDERLINE "\x1b[4m"

#define BOLD_RED     "\x1b[1;31m"
#define BOLD_GREEN   "\x1b[1;32m"
#define BOLD_BLUE    "\x1b[1;34m"
#define BOLD_YELLOW  "\x1b[1;33m"

#define BORDA_SUPERIOR_ESQUERDA 201
#define BORDA_SUPERIOR_DIREITA 187
#define BORDA_INFERIOR_ESQUERDA 200
#define BORDA_INFERIOR_DIREITA 188
#define HORIZONTAL 205
#define VERTICAL 186
#define VERTICAL_TUBO_ESQUERDO 204
#define VERTICAL_TUBO_DIREITO 185

#define VERTICAL_TUBO_GERAL 206
#define VERTICAL_TUBO_T_SUPERIOR 203
#define VERTICAL_TUBO_T_INFERIOR 202

#define TAMANHO_TABULEIRO 11

#define MAX_JOGADORES 4
#define MAX_NOME 10

typedef enum { PORTUGUES, INGLES } Idioma;
Idioma idiomaAtual = INGLES;

void definirIdioma(Idioma idioma) {
    idiomaAtual = idioma;
}

typedef struct {
    char nome[MAX_NOME];
    int posicoes[4]; // Posi��es das 4 pe�as do jogador
} Jogador;

Jogador jogadores[MAX_JOGADORES];
int jogadorAtual = 1;
int numJogadores = 4;

// Fun??o para aguardar a qualquer tecla
void aguardarTecla() {
     if (idiomaAtual == PORTUGUES) {
         printf("\nPressione qualquer tecla para continuar...");
    } else {
          printf("\nPress any key to continue..."); 
           }
    getch(); // Aguarda qualquer tecla
}

// Fun??o para limpar o terminal
void limparTerminal() {
    system("cls || clear");
}

// Fun??o para posicionar o cursor na tela
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int ForgC) {
    WORD wColor;
    // We will need this handle to get the current background attribute
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        // Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

// Fun??o para exibir o menu de idiomas
void menuIdioma() {
    int escolha;
    do {
        limparTerminal();
        printf("%c", BORDA_SUPERIOR_ESQUERDA);
        for (int i = 0; i < 51; ++i) {
            printf("%c", HORIZONTAL);
        }
        printf("%c\n", BORDA_SUPERIOR_DIREITA);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c                Language Selection                 %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c  1. English                                       %c\n", VERTICAL, VERTICAL);
        printf("%c  2. Portuguese                                    %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c  Choose an option:                                %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c", BORDA_INFERIOR_ESQUERDA);
        for (int i = 0; i < 51; ++i) {
            printf("%c", HORIZONTAL);
        }
        printf("%c\n", BORDA_INFERIOR_DIREITA);
        
        escolha = getch() - '0'; // Converter o caractere digitado para um n?mero inteiro

        switch (escolha) {
            case 1:
                definirIdioma(INGLES);
                break;
            case 2:
                definirIdioma(PORTUGUES);
                break;
            default:
                if (idiomaAtual == PORTUGUES) {
                   setlocale(LC_ALL,"Portuguese");
                    printf("\nOpção inválida. Tente novamente.\n");
                    setlocale(LC_ALL,"C");
                } else {
                    printf("\nInvalid option. Try again.\n");
                }
                aguardarTecla();
        }
    } while (escolha < 1 || escolha > 2);
}

// Fun??o para exibir a tela de boas-vindas
void telaBoasVindas() {
    limparTerminal();    

    printf("%c", BORDA_SUPERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_SUPERIOR_DIREITA);
    if (idiomaAtual == PORTUGUES) {
        printf("%c                                                   %c\n", VERTICAL, VERTICAL );
        printf("%c           Bem-vindo ao Jogo de Ludo!              %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c  Pressione qualquer tecla para iniciar o jogo...  %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        } else {
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c               LUDO FORA DO MUNDO                  %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c        Press any key to start the game...         %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    }
    printf("%c", BORDA_INFERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_INFERIOR_DIREITA);

    getch();
}

// Fun??o para exibir o menu de sele??o (Login ou Registro)
int menuSelecaoLoginRegistro() {
    int escolha;
    system("cls || clear");
    printf("%c", BORDA_SUPERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_SUPERIOR_DIREITA);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    if (idiomaAtual == PORTUGUES) {
        printf("%c             Selecione Login ou Registro:          %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c  1. Login                                         %c\n", VERTICAL, VERTICAL);
        printf("%c  2. Registrar                                     %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c  Escolha uma op%c%co                                %c\n", VERTICAL,135, 198, VERTICAL);
    } else {
        printf("%c            Select Login or Register:              %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c  1. Login                                         %c\n", VERTICAL, VERTICAL);
        printf("%c  2. Register                                      %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c  Choose an option                                 %c\n", VERTICAL, VERTICAL);
    }
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c", BORDA_INFERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_INFERIOR_DIREITA);
    
    do {
        escolha = getch() - '0'; // Converter o caractere digitado para um n?mero inteiro
    } while (escolha != 1 && escolha != 2); // Repetir at? que a escolha seja 1 ou 2
    
    return escolha; // Retornando para o menu
}

void capturarInputOculto(char *input, int tamanho) {
    int i = 0;
    char c;
    while ((c = getch()) != '\r' && i < tamanho - 1) {
        if (c == '\b' && i > 0) {
            printf("\b \b");
            i--;
        } else if (c != '\b') {
            input[i++] = c;
            printf("*");
        }
    }
    input[i] = '\0';
    printf("\n");
}

// Fun??o para o sistema de login
void sistemaLogin() {
    char usuario[50];
    char senha[50];
    int tentativas = 3; // N?mero m?ximo de tentativas de login

    do {
        limparTerminal();
        printf("%c", BORDA_SUPERIOR_ESQUERDA);
        for (int i = 0; i < 51; ++i) {
            printf("%c", HORIZONTAL);
        }
        printf("%c\n", BORDA_SUPERIOR_DIREITA);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        if (idiomaAtual == PORTUGUES) {
            printf("%c                 Sistema de Login                  %c\n", VERTICAL, VERTICAL);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c  Tentativas restantes: %d                          %c\n", VERTICAL, tentativas, VERTICAL);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c  Usu%crio:                                         %c\n", VERTICAL, 160, VERTICAL);
            printf("%c  Senha:                                           %c\n", VERTICAL, VERTICAL);
        } else {
            printf("%c                 Login System                      %c\n", VERTICAL, VERTICAL);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c  Remaining attempts: %d                            %c\n", VERTICAL, tentativas, VERTICAL);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c  Username:                                        %c\n", VERTICAL, VERTICAL);
            printf("%c  Password:                                        %c\n", VERTICAL, VERTICAL);
        }

        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c", BORDA_INFERIOR_ESQUERDA);
        for (int i = 0; i < 51; ++i) {
            printf("%c", HORIZONTAL);
        }
        printf("%c\n", BORDA_INFERIOR_DIREITA);
        
        if (idiomaAtual == PORTUGUES) {
            gotoxy(11, 6); // Posiciona o cursor para digitar o usu?rio
            scanf("%s", usuario);
            gotoxy(9, 7); // Posiciona o cursor para digitar a senha
            capturarInputOculto(senha, sizeof(senha));
        } else {
            gotoxy(12, 6); // Posiciona o cursor para digitar o usu?rio
            scanf("%s", usuario);
            gotoxy(12, 7); // Posiciona o cursor para digitar a senha
            capturarInputOculto(senha, sizeof(senha));
        }

       setlocale(LC_ALL,"Portuguese");
        
        if (strcmp(usuario, "admin") == 0 && strcmp(senha, "admin") == 0) {
            if (idiomaAtual == PORTUGUES) {
                printf("\n\n\nLogin realizado com sucesso para o usuário: %s\n", usuario);
            } else {
                printf("\n\n\nLogin successful for user: %s\n", usuario);
            }
            aguardarTecla();
            setlocale(LC_ALL,"C");
            return; // Encerra a fun??o ap?s o login bem-sucedido
        } else {
            if (idiomaAtual == PORTUGUES) {
                printf("\n\n\nUsuário ou senha incorretos. Tente novamente.\n");
            } else {
                printf("\n\n\nIncorrect username or password. Try again.\n");
            }
            tentativas--;
            aguardarTecla();
            setlocale(LC_ALL,"C");
        }
        
    } while (tentativas > 0);
    setlocale(LC_ALL,"Portuguese");
    if (idiomaAtual == PORTUGUES) {
        printf("\n\nNúmero máximo de tentativas excedido. Encerrando o programa.\n");
    } else {
        printf("\n\nMaximum number of attempts exceeded. Exiting the program.\n");
    }
    setlocale(LC_ALL,"c");
    aguardarTecla();
    exit(0); // Encerra o programa ap?s o n?mero m?ximo de tentativas
}

// Fun??o para o sistema de registro
void sistemaRegistro() {
    char usuario[50];
    char senha[50];
    char confirmacaoSenha[50];

    do {
        limparTerminal();
        printf("%c", BORDA_SUPERIOR_ESQUERDA);
        for (int i = 0; i < 51; ++i) {
            printf("%c", HORIZONTAL);
        }
        printf("%c\n", BORDA_SUPERIOR_DIREITA);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        if (idiomaAtual == PORTUGUES) {
            printf("%c            Registro de Novo Usu%crio               %c\n", VERTICAL, 160, VERTICAL);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c  Digite as credenciais abaixo:                    %c\n", VERTICAL, VERTICAL);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c  Usu%crio:                                         %c\n", VERTICAL, 160, VERTICAL);
            printf("%c  Senha:                                           %c\n", VERTICAL, VERTICAL);
            printf("%c  Confirme a senha:                                %c\n", VERTICAL, VERTICAL);
        } else {
            printf("%c             New User Registration                 %c\n", VERTICAL, VERTICAL);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c  Enter the credentials below:                     %c\n", VERTICAL, VERTICAL);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c  User:                                            %c\n", VERTICAL, VERTICAL);
            printf("%c  password:                                        %c\n", VERTICAL, VERTICAL);
            printf("%c  confirm password:                                %c\n", VERTICAL, VERTICAL);
        }    
        
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c", BORDA_INFERIOR_ESQUERDA);
        for (int i = 0; i < 51; ++i) {
            printf("%c", HORIZONTAL);
        }
        printf("%c\n", BORDA_INFERIOR_DIREITA);
        
        if (idiomaAtual == PORTUGUES) {
            gotoxy(12, 6); // Posiciona o cursor para digitar o usu?rio
            scanf("%s", usuario);
            gotoxy(10, 7); // Posiciona o cursor para digitar a senha
            capturarInputOculto(senha, sizeof(senha));
            gotoxy(21, 8); // Posiciona o cursor para digitar a confirma??o de senha
            capturarInputOculto(confirmacaoSenha, sizeof(confirmacaoSenha));          
        } else {
            gotoxy(8, 6); // Posiciona o cursor para digitar o usu?rio
            scanf("%s", usuario);
            gotoxy(12, 7); // Posiciona o cursor para digitar a senha
            capturarInputOculto(senha, sizeof(senha));
            gotoxy(20, 8); // Posiciona o cursor para digitar a confirma??o de senha
            capturarInputOculto(confirmacaoSenha, sizeof(confirmacaoSenha));
        }
        
       

        // Verifica se as senhas coincidem
        if (strcmp(senha, confirmacaoSenha) == 0) {
            if (idiomaAtual == PORTUGUES) {
               printf("\n\n\nRegistro realizado com sucesso para o usu%crio: %s\n", 160, usuario);
            } else {
               printf("\n\n\nRegistration completed successfully for the user: %s\n", usuario);
            }
            aguardarTecla();
            break; // Sai do loop se o registro for bem-sucedido
        } else {
            if (idiomaAtual == PORTUGUES) {
               printf("\n\n\nAs senhas n%co coincidem. Tente novamente.\n", 198 );
               setlocale(LC_ALL,"C");
            } else {
               printf("\n\n\nPasswords do not match. Try again.\n"); 
               setlocale(LC_ALL,"C");
            }
            aguardarTecla();
        }    
        
    } while (1); // Loop infinito at? que o registro seja bem-sucedido
    setlocale(LC_ALL,"C");
}


// Fun??o para exibir os termos e condi??es
void termosCondicoes() {
     char opcao;
     do {
            limparTerminal();

            printf("%c", BORDA_SUPERIOR_ESQUERDA);
            for (int i = 0; i < 51; ++i) {
                printf("%c", HORIZONTAL);
            }
            printf("%c\n", BORDA_SUPERIOR_DIREITA);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            if (idiomaAtual == PORTUGUES) {
                printf("%c            Termos e Condi%c%ces de Uso              %c\n", VERTICAL, 135, 228, VERTICAL);
                printf("%c                                                   %c\n", VERTICAL, VERTICAL);
                printf("%c                  Visite o site:                   %c\n", VERTICAL, VERTICAL);
                printf("%c                                                   %c\n", VERTICAL, VERTICAL);
                printf("%c        https://termos-servicos.vercel.app/        %c\n", VERTICAL, VERTICAL);
                printf("%c                                                   %c\n", VERTICAL, VERTICAL);
                printf("%c           Leia os termos com aten%c%co              %c\n", VERTICAL, 135, 228, VERTICAL);
            } else {
                printf("%c           Terms and Conditions of Use             %c\n", VERTICAL, VERTICAL);
                printf("%c                                                   %c\n", VERTICAL, VERTICAL);
                printf("%c                  Visit website:                   %c\n", VERTICAL, VERTICAL);
                printf("%c                                                   %c\n", VERTICAL, VERTICAL);
                printf("%c        https://termos-servicos.vercel.app/        %c\n", VERTICAL, VERTICAL);
                printf("%c                                                   %c\n", VERTICAL, VERTICAL);
                printf("%c             Read the terms carefully              %c\n", VERTICAL, VERTICAL);
            }
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c", BORDA_INFERIOR_ESQUERDA);
            for (int i = 0; i < 51; ++i) {
                printf("%c", HORIZONTAL);
            }
            printf("%c\n", BORDA_INFERIOR_DIREITA);

            aguardarTecla();
            limparTerminal();

            printf("%c", BORDA_SUPERIOR_ESQUERDA);
            for (int i = 0; i < 51; ++i) {
                printf("%c", HORIZONTAL);
            }
            printf("%c\n", BORDA_SUPERIOR_DIREITA);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            if (idiomaAtual == PORTUGUES) {
                printf("%c            Termos e Condi%c%ces de Uso              %c\n", VERTICAL, 135, 228, VERTICAL);
                printf("%c                                                   %c\n", VERTICAL, VERTICAL);
                printf("%c         Bem-vindo ao LUDO FORA DO MUNDO!          %c\n", VERTICAL, VERTICAL);
                printf("%c       Ao continuar, voc%c concorda com os          %c\n", VERTICAL, 136, VERTICAL);
                printf("%c          termos e condi%c%ces de uso.               %c\n", VERTICAL, 135, 228, VERTICAL);
                printf("%c                                                   %c\n", VERTICAL, VERTICAL);
                printf("%c  Digite 'S' para aceitar ou 'N' para recusar:     %c\n", VERTICAL, VERTICAL);
            } else {
                printf("%c           Terms and Conditions of Use             %c\n", VERTICAL, VERTICAL);
                printf("%c                                                   %c\n", VERTICAL, VERTICAL);
                printf("%c        Welcome to the LUDO FORA DO MUNDO!         %c\n", VERTICAL, VERTICAL);
                printf("%c       When you continue, you agree to the         %c\n", VERTICAL, VERTICAL);
                printf("%c           terms and conditions of use.            %c\n", VERTICAL, VERTICAL);
                printf("%c                                                   %c\n", VERTICAL, VERTICAL);
                printf("%c      Type 'Y' to accept or 'N' to decline:        %c\n", VERTICAL, VERTICAL);
            }
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c", BORDA_INFERIOR_ESQUERDA);
            for (int i = 0; i < 51; ++i) {
                printf("%c", HORIZONTAL);
            }
            printf("%c\n", BORDA_INFERIOR_DIREITA);
    
            
            opcao = getch(); // Aguarda o input do usu?rio
          
            if (opcao == 'S' || opcao == 's' || opcao == 'Y' || opcao == 'y') {
                 if (idiomaAtual == PORTUGUES) {
                   printf("\nVoc%c aceitou os termos e condi%c%ces. Obrigado!\n", 136, 135, 228);
                } else {
                   printf("\nYou have accepted the terms and conditions. Thank you!\n");  
                }
                aguardarTecla();
                return; // Encerra a fun??o ap?s aceitar os termos
            } else if (opcao == 'N' || opcao == 'n') {
                  if (idiomaAtual == PORTUGUES) {
                   printf("\n\nVoc%c recusou os termos e cond%c%ces. O jogo não pode continuar.\n", 136 ,135, 228);
                } else {
                   printf("\n\nYou have refused the terms and conditions. The game cannot continue.\n");       
                }
                aguardarTecla();
                exit(1); // Sai do programa ap?s recusar os termos
            } else {
                if (idiomaAtual == PORTUGUES) {
                    printf("\n\nOp%c%co inv%clida. Digite 'S' para aceitar ou 'N' para recusar.\n\n", 135, 228, 160);

                } else {
                    printf("\n\nInvalid option. Type 'Y' to accept or 'N' to decline.\n\n");       
                }
                aguardarTecla();
                limparTerminal(); // Limpa a tela e exibe os termos novamente
            }
        } while (1); // Loop at? que o usu?rio escolha uma op??o v?lida
        setlocale(LC_ALL,"C");
}

// Fun??o para exibir o menu principal
int menuSelecao() {
    setlocale(LC_ALL,"C");
    int escolha;

    limparTerminal();
    printf("%c", BORDA_SUPERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_SUPERIOR_DIREITA);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    if (idiomaAtual == PORTUGUES) {
        printf("%c                   Menu Principal                  %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c  1. Iniciar Jogo                                  %c\n", VERTICAL, VERTICAL);
        printf("%c  2. Ver Regras                                    %c\n", VERTICAL, VERTICAL);
        printf("%c  3. Ver Ranking                                   %c\n", VERTICAL, VERTICAL);
        printf("%c  4. Sair                                          %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c  Escolha uma op%c%co:                               %c\n", VERTICAL, 135, 198 , VERTICAL);
    } else {
        printf("%c                      Main Menu                    %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c  1. Start Game                                    %c\n", VERTICAL, VERTICAL);
        printf("%c  2. See Rules                                     %c\n", VERTICAL, VERTICAL);
        printf("%c  3. See Ranking                                   %c\n", VERTICAL, VERTICAL);
        printf("%c  4. Exit                                          %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c  Chose an option:                                 %c\n", VERTICAL, VERTICAL);
    }
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c", BORDA_INFERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_INFERIOR_DIREITA);

    do {
        escolha = getch() - '0'; // Converter o caractere digitado para um n?mero inteiro
    } while (escolha < 1 || escolha > 4); // Repetir at? que a escolha seja v?lida

    return escolha; // Retornar a escolha para o programa principal
}

// Fun??o para exibir as regras do Ludo
void telaRegrasLudo() {
    limparTerminal();
    printf("%c", BORDA_SUPERIOR_ESQUERDA);
    for (int i = 0; i < 53; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_SUPERIOR_DIREITA);
    printf("%c                                                     %c\n", VERTICAL, VERTICAL);
    if (idiomaAtual == PORTUGUES) {
        printf("%c                   Regras do Ludo                    %c\n", VERTICAL, VERTICAL);
        printf("%c                                                     %c\n", VERTICAL, VERTICAL);
        printf("%c - Movimente suas pe%cas com base nos dados lan%cados. %c\n", VERTICAL, 135, 135, VERTICAL);
        printf("%c - Capture as pe%cas advers%crias para envi%c-las de    %c\n", VERTICAL, 135, 160, 160, VERTICAL);
        printf("%c   volta %c base.                                     %c\n", VERTICAL, 160, VERTICAL);
        printf("%c - O primeiro jogador a levar todas as pe%cas %c casa  %c\n", VERTICAL, 135 ,133, VERTICAL);
        printf("%c   final vence!                                      %c\n", VERTICAL, VERTICAL);
    } else {
        printf("%c                      Ludo Rules                     %c\n", VERTICAL, VERTICAL);
        printf("%c                                                     %c\n", VERTICAL, VERTICAL);
        printf("%c - Move your pieces based on the rolled dice.        %c\n", VERTICAL, VERTICAL);
        printf("%c - Capture opponent's pieces to send them back to    %c\n", VERTICAL, VERTICAL);
        printf("%c   the start.                                        %c\n", VERTICAL, VERTICAL);
        printf("%c - The first player to get all pieces to the home    %c\n", VERTICAL, VERTICAL);
        printf("%c   base wins!                                        %c\n", VERTICAL, VERTICAL);
    }
    printf("%c                                                     %c\n", VERTICAL, VERTICAL);
    printf("%c", BORDA_INFERIOR_ESQUERDA);
    for (int i = 0; i < 53; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_INFERIOR_DIREITA);

    aguardarTecla();
}

// Fun??o para exibir o ranking dos melhores jogadores
void telaRanking() {
    limparTerminal();
    printf("%c", BORDA_SUPERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_SUPERIOR_DIREITA);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    if (idiomaAtual == PORTUGUES) {
        printf("%c              Ranking de Jogadores                 %c\n", VERTICAL, VERTICAL);
    } else {
        printf("%c                 Player Ranking                    %c\n", VERTICAL, VERTICAL);
    }
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    if (idiomaAtual == PORTUGUES) {
        printf("%c  1. Player1 - Vit%crias: 15                        %c\n", VERTICAL, 162, VERTICAL);
        printf("%c  2. Player2 - Vit%crias: 8                         %c\n", VERTICAL, 162, VERTICAL);
        printf("%c  3. Player3 - Vit%crias: 5                         %c\n", VERTICAL, 162, VERTICAL);
        printf("%c  4. Player4 - Vit%crias: 4                         %c\n", VERTICAL, 162, VERTICAL);
        printf("%c  5. Player5 - Vit%crias: 2                         %c\n", VERTICAL, 162, VERTICAL);
    } else {
        printf("%c  1. Player1 - Victories: 15                       %c\n", VERTICAL, VERTICAL);
        printf("%c  2. Player2 - Victories: 8                        %c\n", VERTICAL, VERTICAL);
        printf("%c  3. Player3 - Victories: 5                        %c\n", VERTICAL, VERTICAL);
        printf("%c  4. Player4 - Victories: 4                        %c\n", VERTICAL, VERTICAL);
        printf("%c  5. Player5 - Victories: 2                        %c\n", VERTICAL, VERTICAL);
    }
    // Aqui voc? pode exibir a lista de jogadores com suas pontua??es
    // Por enquanto, vamos simular alguns jogadores fict?cios
    
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c", BORDA_INFERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_INFERIOR_DIREITA);

    aguardarTecla();
}

// Fun??o para exibir a tela de sa?da do jogo
int telaSair() {
    char escolha;
    limparTerminal();
    printf("%c", BORDA_SUPERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_SUPERIOR_DIREITA);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    if (idiomaAtual == PORTUGUES) {
        printf("%c                Deseja realmente sair?             %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c                      S - Sim                      %c\n", VERTICAL, VERTICAL);
        printf("%c                      N - N%co                      %c\n", VERTICAL, 198, VERTICAL);
    } else {
        printf("%c              Do you really want to exit?          %c\n", VERTICAL, VERTICAL);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c                      Y - Yes                      %c\n", VERTICAL, VERTICAL);
        printf("%c                      N - No                       %c\n", VERTICAL, VERTICAL);
    }
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c", BORDA_INFERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_INFERIOR_DIREITA);

    do {
        escolha = getch();
        if (escolha == 'n' || escolha == 'N') {
            return;
        }
    } while ((idiomaAtual == PORTUGUES && escolha != 'S' && escolha != 's') ||
             (idiomaAtual == INGLES && escolha != 'Y' && escolha != 'y'));
    exit(1);
}

//Sele??o de jogadores
int selecaoJogadores(void) {
     int repetir = 0;
     int jogadoresQuant = 0;
     do {
         limparTerminal();
        printf("%c", BORDA_SUPERIOR_ESQUERDA);
        for (int i = 0; i < 51; ++i) {
            printf("%c", HORIZONTAL);
        }
        printf("%c\n", BORDA_SUPERIOR_DIREITA);
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        if (idiomaAtual == PORTUGUES) {
            printf("%c              Quantidade de Jogadores              %c\n", VERTICAL, VERTICAL);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c         ---------   ---------   ---------         %c\n", VERTICAL, VERTICAL);
            printf("%c         --  2  --   --  3  --   --  4  --         %c\n", VERTICAL, VERTICAL);
            printf("%c         ---------   ---------   ---------         %c\n", VERTICAL, VERTICAL);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c  Escolha uma op%c%co:                               %c\n", VERTICAL, 135, 198 , VERTICAL);
        } else {
            printf("%c                Numbers of Players                 %c\n", VERTICAL, VERTICAL);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c         ---------   ---------   ---------         %c\n", VERTICAL, VERTICAL);
            printf("%c         --  2  --   --  3  --   --  4  --         %c\n", VERTICAL, VERTICAL);
            printf("%c         ---------   ---------   ---------         %c\n", VERTICAL, VERTICAL);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c                                                   %c\n", VERTICAL, VERTICAL);
            printf("%c  Chose an option:                                 %c\n", VERTICAL, VERTICAL);
        }
        printf("%c                                                   %c\n", VERTICAL, VERTICAL);
        printf("%c", BORDA_INFERIOR_ESQUERDA);
        for (int i = 0; i < 51; ++i) {
            printf("%c", HORIZONTAL);
        }
        printf("%c\n", BORDA_INFERIOR_DIREITA);
        
        do {
            jogadoresQuant = getch() - '0'; // Converter o caractere digitado para um n?mero inteiro
                      
        } while (jogadoresQuant < 2 || jogadoresQuant > 4); // Repetir at? que a escolha seja v?lida
        switch (jogadoresQuant) {
            case 2:
                gotoxy(14, 7);
                printf("^");
                gotoxy(0, 13);
                break;
            case 3:
                 gotoxy(26, 7);
                printf("^");
                gotoxy(0, 13);
                break;
            case 4:
                 gotoxy(38, 7);
                printf("^");
                gotoxy(0, 13);
                break;
        }
       if (idiomaAtual == PORTUGUES) {        
           gotoxy(22, 9); 
           printf("%i\n", jogadoresQuant);
           gotoxy(0, 13);
           printf("Deseja continuar? [s] ou [n]");
       } else {
           gotoxy(20, 9); 
           printf("%i\n", jogadoresQuant);
           gotoxy(0, 13);
           printf("\nWant continue? [y] ou [n]");
       }
       repetir = getch();
    } while (repetir == 'n' || repetir == 'N');
    
    return jogadoresQuant;
}

//Sele??o dos times do jogador
void nomeJogadores(int jogadoresQuant, char jogadores[MAX_JOGADORES][MAX_NOME]) {
    limparTerminal();
    int x = 3;
    int y = 5;

    printf("%c", BORDA_SUPERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_SUPERIOR_DIREITA);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    
    if (idiomaAtual == PORTUGUES) {
      printf("%c                Nome dos Jogadores                 %c\n", VERTICAL, VERTICAL);
    } else {
      printf("%c                  Players names                    %c\n", VERTICAL, VERTICAL);
    }
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c  ----------  ----------  ----------  ---------    %c\n", VERTICAL, VERTICAL);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c  ----------  ----------  ----------  ---------    %c\n", VERTICAL, VERTICAL);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c", BORDA_INFERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_INFERIOR_DIREITA);
    
    gotoxy(x, y);
    for (int i = 0; i < jogadoresQuant; i++) {
        gotoxy(x, y);
        scanf("%s", jogadores[i]);
        x += 12;
    }
}

void timeSelecao(int jogadoresQuant, char jogadores[MAX_JOGADORES][MAX_NOME]) {
    limparTerminal();
    int selecaoTime;
    char nomeTime[15];
    int repetir;
    int x,y;
    
    x = 3;
    y = 9;

    printf("%c", BORDA_SUPERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_SUPERIOR_DIREITA);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    
    if (idiomaAtual == PORTUGUES) {
       printf("%c                Time dos Jogadores                 %c\n", VERTICAL, VERTICAL);
    } else {
       printf("%c                   Players Team                    %c\n", VERTICAL, VERTICAL);
    }
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c  ----------  ----------  -----------  ---------   %c\n", VERTICAL, VERTICAL);
    if (idiomaAtual == PORTUGUES) {
       printf("%c  Astronauta  Engenheiro  Pesquisador    Alien     %c\n", VERTICAL, VERTICAL);
    } else {
       printf("%c  Astronaut    Engineer   Researcher     Alien     %c\n", VERTICAL, VERTICAL);
    }  
    printf("%c  ----------  ----------  -----------  ---------   %c\n", VERTICAL, VERTICAL);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c", BORDA_INFERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_INFERIOR_DIREITA);
    
    for (int cont = 0; cont < jogadoresQuant; cont++) { 
        do {
            gotoxy(3, 16);
            if (idiomaAtual == PORTUGUES) {
               printf("%s, escolha um time (1-4): ", jogadores[cont]);
            } else {
               printf("%s, chose a team (1-4): ", jogadores[cont]);
            }
            do {
                selecaoTime = getch() - '0'; // Converter o caractere digitado para um n�mero inteiro
            } while (selecaoTime < 1 || selecaoTime > 4); // Repetir at� que a escolha seja v�lida

            switch (selecaoTime) {
                case 1:
                    gotoxy(8, 7);
                    printf("^");
                    if (idiomaAtual == PORTUGUES) {
                       strcpy(nomeTime, "Astronauta");
                    } else {
                       strcpy(nomeTime, "Astronaut");
                    }
                    break;
                case 2:
                    gotoxy(20, 7);
                    printf("^");
                    if (idiomaAtual == PORTUGUES) {
                       strcpy(nomeTime, "Engenheiro");
                    } else {
                       strcpy(nomeTime, "Engineer");
                    }
                    break;
                case 3:
                    gotoxy(32, 7);
                    printf("^");
                    if (idiomaAtual == PORTUGUES) {
                       strcpy(nomeTime, "Pesquisador");
                    } else {
                       strcpy(nomeTime, "Researcher");
                    }
                    break;
                case 4:
                    gotoxy(44, 7);
                    printf("^");
                    strcpy(nomeTime, "Alien");
                    break;
            }
            gotoxy(x, y);
            if (idiomaAtual == PORTUGUES) {
               printf("Time %s por %s ", nomeTime, jogadores[cont]);
            } else {
               printf("Team %s by %s ", nomeTime, jogadores[cont]);
            }
            y++;
            gotoxy(3, 16);          
            if (idiomaAtual == PORTUGUES) {
               printf("deseja continuar? [s] ou [n] ");
            } else {
               printf("Want continue? [y] or [n] ");
            }
            repetir = getch();
            
            if (repetir == 'n' || repetir == 'N') {
                y--; // Corrige a posi��o vertical para sobrescrever a linha anterior
                 gotoxy(3, 16);
                 printf("                                                 "); // Limpa a linha da pergunta
                if (selecaoTime == 1) {
                    gotoxy(0, y);
                    printf("%c                                                   %c\n", VERTICAL, VERTICAL); // Limpa a linha do time
                    gotoxy(8, 7);
                    printf(" "); // Limpa a seta de sele��o
                }
                // Limpa qualquer outra seta de sele��o se necess�rio
                if (selecaoTime == 2) {
                   gotoxy(0, y);
                    printf("%c                                                   %c\n", VERTICAL, VERTICAL); // Limpa a linha do time
                    gotoxy(20, 7);
                    printf(" ");
                } else if (selecaoTime == 3) {
                    gotoxy(0, y);
                    printf("%c                                                   %c\n", VERTICAL, VERTICAL); // Limpa a linha do time
                    gotoxy(32, 7);
                    printf(" ");
                } else if (selecaoTime == 4) {
                    gotoxy(0, y);
                    printf("%c                                                   %c\n", VERTICAL, VERTICAL); // Limpa a linha do time
                    gotoxy(44, 7);
                    printf(" ");
                }
            }

        } while (repetir == 'n' || repetir == 'N');
    }
}

void exibir_tabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    SetColor(7); // Define a cor padr?o do console
    printf("%c", BORDA_SUPERIOR_ESQUERDA);
    for (int i = 0; i < TAMANHO_TABULEIRO; ++i) {
        printf("%c", HORIZONTAL);
        printf("%c", HORIZONTAL);
        printf("%c", HORIZONTAL);
        if (i < 10) {
            printf("%c", VERTICAL_TUBO_T_SUPERIOR);
        }
    }
    printf("%c\n", BORDA_SUPERIOR_DIREITA);
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%c", VERTICAL);
        
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) { // AQUI ? O MEIO DO TABULEIRO
            char *cor = RESET;
            switch (tabuleiro[i][j]) {
                case '1':
                    SetColor(9);
                    break;
                case '2':
                    SetColor(13);
                    break;
                case '3':
                    SetColor(14);
                    break;
                case '4':
                    SetColor(2);
                    break;
            }
            if (tabuleiro[i][j] == 'x') {
                printf(" X ");
        	} else if(tabuleiro[i][j] == ' ') {
				printf("   ");
            } else if(tabuleiro[i][j] == '1') {
				printf(" 1 ");
            } else if(tabuleiro[i][j] == '2') {
				printf(" 2 ");
            } else if(tabuleiro[i][j] == '3') {
				printf(" 3 ");
            } else if(tabuleiro[i][j] == '4') {
				printf(" 4 ");
            } else if(tabuleiro[i][j] == 'w') {
				printf(" W ");
            } else if(tabuleiro[i][j] == '*') {
				printf(" * ");
            } else if(tabuleiro[i][j] == '0') {
            	printf(" X ");
			}
			
            // antes desse
			else {
                printf("%c", tabuleiro[i][j]);
            }
            SetColor(7); // Retorna ? cor padr?o do console
            printf("%c", VERTICAL);
        }
        printf("\n");
        
        if (i < TAMANHO_TABULEIRO - 1) {
            printf("%c", VERTICAL_TUBO_ESQUERDO);
            for (int k = 0; k < TAMANHO_TABULEIRO; ++k) {
                printf("%c", HORIZONTAL);
                printf("%c", HORIZONTAL);
                printf("%c", HORIZONTAL);
                if (k < 10) {
                    printf("%c", VERTICAL_TUBO_GERAL);
                }
            }
            printf("%c\n", VERTICAL_TUBO_DIREITO);
        }
    }

    printf("%c", BORDA_INFERIOR_ESQUERDA);
    for (int i = 0; i < TAMANHO_TABULEIRO; ++i) {
        printf("%c", HORIZONTAL);
        printf("%c", HORIZONTAL);
        printf("%c", HORIZONTAL);
        if (i < 10) {
            printf("%c", VERTICAL_TUBO_T_INFERIOR);
        }
    }
    printf("%c\n", BORDA_INFERIOR_DIREITA);
    
    
}

void janelaRolarDado(int dado) {
     int cont = 0;
     int x = 48;
     gotoxy(x, cont);
     printf("%c", BORDA_SUPERIOR_ESQUERDA);
    for (int i = 0; i < 11; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c", BORDA_SUPERIOR_DIREITA);
    cont++;
    gotoxy(x, cont);
    if (idiomaAtual == PORTUGUES) {
    	printf("%c    Dado   %c", VERTICAL, VERTICAL);
	} else {
		printf("%c    Dice   %c", VERTICAL, VERTICAL);
	}
    
    cont++;
    gotoxy(x, cont);
    printf("%c     %i     %c", VERTICAL, dado, VERTICAL);
    cont++;
    gotoxy(x, cont);
    printf("%c           %c", VERTICAL, VERTICAL);
    cont++;
    gotoxy(x, cont);
    printf("%c", BORDA_INFERIOR_ESQUERDA);
    for (int i = 0; i < 11; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c", BORDA_INFERIOR_DIREITA);
    gotoxy(3, 23);
}

void janelaVezJogador(int jogadoresQuant, char jogadores[MAX_JOGADORES][MAX_NOME] ) {
	int cont = 12;
	int t = 0;
     int x = 48;
     
     for (t = 0; t < jogadoresQuant; t++) {
     	if (t < 2) {
	     	gotoxy(x, cont);
            if(t == 0) {
                SetColor(9);
            }  else if (t == 1) {
                SetColor(5);
            }
			printf("%c", BORDA_SUPERIOR_ESQUERDA);
			for (int i = 0; i < 11; ++i) {
			    printf("%c", HORIZONTAL);
			}
			printf("%c", BORDA_SUPERIOR_DIREITA);
			cont++;
			gotoxy(x, cont);
			if (idiomaAtual == PORTUGUES) {
				printf("   Jogador   ");
			} else {
				printf("   Player   ");
			}
            SetColor(7);
			cont++;
			gotoxy(x, cont);
			printf("   %s      ", jogadores[t]);
			cont = cont + 3;
		} else {
			x = 63;
			if (t < 3) {
				cont = 12;
                SetColor(6);
			} else {
				cont = 12 + 5;
                SetColor(2);
			}
			
			gotoxy(x, cont);
			printf("%c", BORDA_SUPERIOR_ESQUERDA);
			for (int i = 0; i < 11; ++i) {
			    printf("%c", HORIZONTAL);
			}
			printf("%c", BORDA_SUPERIOR_DIREITA);
			cont++;
			gotoxy(x, cont);
			if (idiomaAtual == PORTUGUES) {
				printf("   Jogador   ");
			} else {
				printf("   Player   ");
			}
            SetColor(7);
			cont++;
			gotoxy(x, cont);
			printf("   %s      ", jogadores[t]);
			cont = cont + 3;
		}
	}
    gotoxy(3, 23);
}

    char identificacao[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {
		{'x', 'x', 'x', 'x', ' ', ' ', ' ', 'x', 'x', 'x', 'x'},
        {'x', 'M', 'N', 'x', ' ', '*', ' ', 'x', 'A', 'B', 'x'},
        {'x', 'O', 'P', 'x', ' ', '*', ' ', 'x', 'C', 'D', 'x'},
        {'x', 'x', 'x', 'x', ' ', '*', ' ', 'x', 'x', 'x', 'x'},
        {' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' '},
        {' ', '*', '*', '*', '*', 'w', '*', '*', '*', '*', ' '},
        {' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' '},
        {'x', 'x', 'x', 'x', ' ', '*', ' ', 'x', 'x', 'x', 'x'},
        {'x', 'I', 'J', 'x', ' ', '*', ' ', 'x', 'E', 'F', 'x'},
        {'x', 'K', 'L', 'x', ' ', '*', ' ', 'x', 'G', 'H', 'x'},
        {'x', 'x', 'x', 'x', ' ', ' ', ' ', 'x', 'x', 'x', 'x'}
    };


void movimentar(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], char identificacao[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int dado, int jogadoresQuant) {
    int i, j;
    int encontrouJogador = 0;
    int casaInicial = 0;
    int nova_i, nova_j;
    char pecaEscolhida;
    
    gotoxy(0,0);

    exibir_tabuleiro(tabuleiro);
    
    // Solicita ao jogador que escolha a pe�a para mover
    if (idiomaAtual == PORTUGUES) {
        printf("Jogador %d, escolha a pe%ca para mover: ", jogadorAtual, 135);
        if (jogadorAtual == 1) {
        	printf("(A, B, C OU D)");
		}
		else if (jogadorAtual == 2) {
			printf("(E, F, G OU H)");
		}
		else if (jogadorAtual == 3) {
			printf("(I, J, K OU L)");
		}
		else if (jogadorAtual == 4) {
			printf("(M, N, O OU P)");
		}
    } else {
        printf("Player %d, choose the piece to move: ", jogadorAtual);
        if (jogadorAtual == 1) {
        	printf("(A, B, C OU D)");
		}
		else if (jogadorAtual == 2) {
			printf("(E, F, G OU H)");
		}
		else if (jogadorAtual == 3) {
			printf("(I, J, K OU L)");
		}
		else if (jogadorAtual == 4) {
			printf("(M, N, O OU P)");
		}
    }
    pecaEscolhida = getch();
    //scanf(" %c", &pecaEscolhida);

    // Encontra a pe�a escolhida no tabuleiro
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (identificacao[i][j] == pecaEscolhida && tabuleiro[i][j] == jogadorAtual + '0') {
                encontrouJogador = 1;
                nova_i = i;
                nova_j = j;
                break;
            }
        }
        if (encontrouJogador) break;
    }
    
    if (!encontrouJogador) {
        if (idiomaAtual == PORTUGUES) {
            
            printf("\nPe%ca n%co encontrada ou n%co pertence ao jogador atual. Tente novamente.\n", 135, 198, 198 );
        } else {
            printf("\nPiece not found or does not belong to the current player. Try again.\n");
        }
        
        aguardarTecla();
        gotoxy(0,24);
        printf("                                                                        ");
        return;
    }

    // Remove a pe�a da posi��o atual no tabuleiro e na matriz de identifica��o
    tabuleiro[nova_i][nova_j] = ' ';
    identificacao[nova_i][nova_j] = ' ';

    // Verifica se o dado caiu em 6 para liberar uma pe�a
    if (dado == 6) {
        // Verifica se a pe�a est� em sua casa inicial
        if ((jogadorAtual == 1 && (pecaEscolhida == 'A' || pecaEscolhida == 'B' || pecaEscolhida == 'C' || pecaEscolhida == 'D')) ||
            (jogadorAtual == 2 && (pecaEscolhida == 'E' || pecaEscolhida == 'F' || pecaEscolhida == 'G' || pecaEscolhida == 'H')) ||
            (jogadorAtual == 3 && (pecaEscolhida == 'I' || pecaEscolhida == 'J' || pecaEscolhida == 'K' || pecaEscolhida == 'L')) ||
            (jogadorAtual == 4 && (pecaEscolhida == 'M' || pecaEscolhida == 'N' || pecaEscolhida == 'O' || pecaEscolhida == 'P'))) {
            casaInicial = 1;
        }

        // Se a pe�a est� na casa inicial, coloca-a na posi��o inicial correspondente e remove da casa
        if (casaInicial) {
            if (jogadorAtual == 1) {
                tabuleiro[2][6] = jogadorAtual + '0';
                identificacao[2][6] = pecaEscolhida;
            } else if (jogadorAtual == 2) {
                tabuleiro[6][8] = jogadorAtual + '0';
                identificacao[6][8] = pecaEscolhida;
            } else if (jogadorAtual == 3) {
                tabuleiro[8][4] = jogadorAtual + '0';
                identificacao[8][4] = pecaEscolhida;
            } else if (jogadorAtual == 4) {
                tabuleiro[4][2] = jogadorAtual + '0';
                identificacao[4][2] = pecaEscolhida;
            }
            return;
        }
    }

    // Movimenta��o de uma pe�a j� em jogo
    for (int k = 0; k < dado; k++) {
        if (jogadorAtual == 1 || jogadorAtual == 2 || jogadorAtual == 3 || jogadorAtual == 4 ) {
            // Movimentos permitidos apenas para o jogador atual
            // if (nova_i == 2 && nova_j > 6) nova_j++; // Move para a direita
             if (nova_i == 2 && nova_j == 6) nova_i++; // Desce
            else if (nova_i == 3 && nova_j == 6) nova_i++; // Desce
            else if (nova_i == 4 && nova_j < 10 && nova_j >= 6) nova_j++; // Move para a direita
            else if (nova_i == 4 && nova_j < 4) nova_j++; // Move para a direita
            
            else if (nova_i == 4 && nova_j == 10) nova_i++; // Desce

            else if (nova_i == 4 && nova_j == 4) nova_i--; // Sobe
            else if (nova_i > 0 && nova_j == 4 && nova_i < 4) nova_i--; // Sobe

            else if (nova_i == 5 && nova_j == 10) nova_i++; // Desce

            else if (nova_i == 6 && nova_j > 6) nova_j--; // Move para a esquerda
            else if (nova_i == 6 && nova_j == 6) nova_i++; // Desce
            else if (nova_i == 7 && nova_j == 6) nova_i++; // Desce
            else if (nova_i == 8 && nova_j == 6) nova_i++; // Desce
            else if (nova_i == 9 && nova_j == 6) nova_i++; // Desce
            else if (nova_i == 10 && nova_j > 4 && nova_j != 10) nova_j--; // Move para a esquerda


            else if (nova_i > 6 && nova_j == 4) nova_i--; // Sobe
            else if (nova_i == 6 && nova_j == 4) nova_j--; // Move para a esquerda
            else if (nova_i == 6 && nova_j > 0 && nova_j != 4 && nova_j != 5) nova_j--; // Move para a esquerda
            else if (nova_i == 6 && nova_j == 0) nova_i--; // Sobe
            else if (nova_i > 0 && nova_j == 0) nova_i--; // Sobe
            else if (nova_i == 0 && nova_j == 4) nova_j++; // move para direita
            else if (nova_i == 0 && nova_j == 3) nova_j++; // move para direita
            else if (nova_i == 0 && nova_j == 6) nova_i++; // Desce
            else if (nova_i < 4 && nova_j == 6) nova_i++; // Desce
        }
        if (jogadorAtual == 1 || jogadorAtual == 2 || jogadorAtual == 4 ) {
            if (nova_i == 10 && nova_j == 4) nova_i--; // Sobe
        }

        // Verifica se a pe�a est� entrando no caminho da vit�ria
        if (jogadorAtual == 1) { // caminho da vit�ria do jogador 1
            if (nova_i >= 0 && nova_i <= 4 && nova_j == 5) nova_i++; // Desce no caminho da vit�ria para jogador 1
        } else if (jogadorAtual == 2 || jogadorAtual == 3 || jogadorAtual == 4) {
            // Movimentos para jogadores que n?o s?o o jogador atual
            if (nova_i == 0 && nova_j >= 4 && nova_j <= 6) nova_j++; // Movimento para a direita na faixa de bloqueio
            // Verifica o caminho da vit�ria para o jogador 2
            if (jogadorAtual == 2) {
                if (nova_i == 5 && nova_j <= 10 && nova_j >= 6) nova_j--; // Move para a esquerda no caminho da vit�ria para jogador 2
            }
            // Verifica o caminho da vit�ria para o jogador 3
            if (jogadorAtual == 3) {
                if (nova_i <= 10 && nova_i >= 6 && nova_j == 5) nova_i--; // Sobe no caminho da vit�ria para jogador 3   
            }
            if (jogadorAtual == 4) {
                if (nova_i == 5 && nova_j >= 0 && nova_j <= 4) nova_j++; // Move para a direita no caminho da vit�ria para jogador 4
            }
        }
    }
 // Coloca a pe�a na nova posi��o
    tabuleiro[nova_i][nova_j] = jogadorAtual + '0';
    identificacao[nova_i][nova_j] = pecaEscolhida;
}

void rodadaDoJogador(int jogador, int dado ,char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int cont = 6;
    int x = 48;
    gotoxy(x, cont);
    if (jogador == 1) {
        SetColor(9);
    } else if (jogador == 2) {
        SetColor(5);
    } else if (jogador == 3) {
        SetColor(6);
    } else if (jogador == 4) {
        SetColor(2);
    }
    printf("%c", BORDA_SUPERIOR_ESQUERDA);
    for (int i = 0; i < 12; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c", BORDA_SUPERIOR_DIREITA);
    cont++;
    gotoxy(x, cont);
    printf("%c            %c\n", VERTICAL, VERTICAL);
    cont++;
    gotoxy(x, cont);
    if (idiomaAtual == PORTUGUES) {
        printf("%c  Jogador %d %c\n", VERTICAL,jogador, VERTICAL);
    } else {
        printf("%c  player %d  %c\n", VERTICAL,jogador, VERTICAL);
    }
    cont++;
    gotoxy(x, cont);
    printf("%c            %c\n", VERTICAL, VERTICAL);
    cont++;
    gotoxy(x, cont);
    printf("%c", BORDA_INFERIOR_ESQUERDA);
    for (int i = 0; i < 12; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c", BORDA_INFERIOR_DIREITA);
     SetColor(7);
    movimentar(tabuleiro,identificacao, dado, jogador); // Fun�?o de movimenta�?o adaptada para cada jogador

}

void telaVitoria(char *nomeJogador) {
    limparTerminal();
    printf("%c", BORDA_SUPERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_SUPERIOR_DIREITA);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    if (idiomaAtual == PORTUGUES) {
        printf("           PARAB%cNS, %s, VOC%c VENCEU!               \n", 202, nomeJogador ,202 );
    } else {
        printf("         CONGRATULATIONS, %s, YOU WON!              \n", nomeJogador);
    }
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    if (idiomaAtual == PORTUGUES) {
        printf("%c   Pressione qualquer tecla para continuar...       %c\n", VERTICAL, VERTICAL);
    } else {
        printf("%c   Press any key to continue...                    %c\n", VERTICAL, VERTICAL);
    }
    printf("%c                                                   %c\n", VERTICAL, VERTICAL);
    printf("%c", BORDA_INFERIOR_ESQUERDA);
    for (int i = 0; i < 51; ++i) {
        printf("%c", HORIZONTAL);
    }
    printf("%c\n", BORDA_INFERIOR_DIREITA);
}


// Fun??o principal
int main() {
    srand(time(NULL)); // Inicializa o gerador de n�meros aleat�rios
    int opcao = 0;
    int jogadoresQuant = 0;
    int selecaoTime = 0;
    int pecaEscolhida = -1;
    int dado = 0;
    char jogadores[MAX_JOGADORES][MAX_NOME];
    char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {
		{'x', 'x', 'x', 'x', ' ', ' ', ' ', 'x', 'x', 'x', 'x'},
        {'x', '4', '4', 'x', ' ', '*', ' ', 'x', '1', '1', 'x'},
        {'x', '4', '4', 'x', ' ', '*', ' ', 'x', '1', '1', 'x'},
        {'x', 'x', 'x', 'x', ' ', '*', ' ', 'x', 'x', 'x', 'x'},
        {' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' '},
        {' ', '*', '*', '*', '*', 'w', '*', '*', '*', '*', ' '},
        {' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' '},
        {'x', 'x', 'x', 'x', ' ', '*', ' ', 'x', 'x', 'x', 'x'},
        {'x', '3', '3', 'x', ' ', '*', ' ', 'x', '2', '2', 'x'},
        {'x', '3', '3', 'x', ' ', '*', ' ', 'x', '2', '2', 'x'},
        {'x', 'x', 'x', 'x', ' ', ' ', ' ', 'x', 'x', 'x', 'x'}
    };

    // char movimentosPossiveis[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {
	// 	{'x', 'x', 'x', 'x', '04', '05', '06', 'x', 'x', 'x', 'x'},
    //     {'x', '4', '4', 'x', '14', '1', '16', 'x', '1', '1', 'x'},
    //     {'x', '4', '4', 'x', '24', '1', '26', 'x', '1', '1', 'x'},
    //     {'x', 'x', 'x', 'x', '34', '1', '36', 'x', 'x', 'x', 'x'},
    //     {'40', '41', '42', '43', '44', '1', '46', '47', '48', '49', '410'},
    //     {'50', '4', '4', '4', '4', 'w', '2', '2', '2', '2', '510'},
    //     {'60', '61', '62', '63', '64', '*', '66', '67', '68', '69', '610'},
    //     {'x', 'x', 'x', 'x', '74', '3', '76', 'x', 'x', 'x', 'x'},
    //     {'x', '3', '3', 'x', '84', '3', '86', 'x', '2', '2', 'x'},
    //     {'x', '3', '3', 'x', '94', '3', '96', 'x', '2', '2', 'x'},
    //     {'x', 'x', 'x', 'x', '104', '105', '106', 'x', 'x', 'x', 'x'}
    // };

    menuIdioma();
    telaBoasVindas(); // Chamando a fun??o de boas-vindas

    int escolhaLoginRegistro = menuSelecaoLoginRegistro(); // Sele??o entre login e registro
    

    switch (escolhaLoginRegistro) {
        case 1: // Em caso do valor ser 1 (Login)
            sistemaLogin();
            break;
        case 2: // Em caso do valor ser 2 (Registro)
            sistemaRegistro();
            termosCondicoes();
            break;
        default:
            printf("\nOpção inválida. Tente novamente.\n");
            aguardarTecla();
            return 0;
    }

    do {
        opcao = menuSelecao(); // Definindo que opcao vai ser o mesmo valor de menuSelecao()

        switch (opcao) { // Abrindo o switch
            case 1: // Em caso do valor ser 1
                limparTerminal();
                numJogadores = selecaoJogadores();
                nomeJogadores(numJogadores, jogadores);
                timeSelecao(numJogadores, jogadores);
                limparTerminal();
                exibir_tabuleiro(tabuleiro);
                printf("Precione qualquer tecla para iniciar o jogo.");
                getch();
				do {
          
      
                    
                    // limparTerminal();
                    dado = (rand() % 6) + 1;
                    janelaRolarDado(dado);
                    janelaVezJogador(numJogadores, jogadores);
                    gotoxy(48,8);
                    rodadaDoJogador(jogadorAtual, dado, tabuleiro);
                    // Atualize o jogador atual para o pr�ximo jogador
                    jogadorAtual = (jogadorAtual % numJogadores) + 1;
                    gotoxy(0,0);
                    
                     // Rodada do jogador atual
              
                        

                } while (tabuleiro[5][5] == 'w');
                limparTerminal();
                        int indiceVencedor = (jogadorAtual == 1) ? numJogadores - 1 : jogadorAtual - 2;
                telaVitoria(jogadores[indiceVencedor]);

                getch();
                break;
            case 2: // Em caso do valor ser 2
                telaRegrasLudo();
                break; // Fim do caso 2
            case 3: // Em caso do valor ser 3
                telaRanking();
                break; // Fim do caso 3
            case 4: // Em caso do valor ser 4
                telaSair();
                break; // Fim do caso 4
            default:
                limparTerminal();
                printf("\nOpção inválida. Tente novamente.\n");
                aguardarTecla();
        }
    } while (opcao != 5);

    return 0;
}
