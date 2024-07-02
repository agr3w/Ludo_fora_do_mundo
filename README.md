# PI_Weslley_Luiz_Kampa

Este repositório contém o código-fonte de um jogo desenvolvido em C. O jogo suporta múltiplos jogadores e inclui funcionalidades de manipulação de texto no terminal.

## Funcionalidades

- Suporte para até 4 jogadores.
- Definição de idioma (Português e Inglês).
- Interface de terminal com manipulação de cores e posicionamento de cursor.
- Várias definições de bordas e layout para a interface.

## Pré-requisitos

- Compilador C (como GCC).
- Sistema operacional Windows (devido ao uso de bibliotecas específicas como `windows.h`).

## Como compilar e executar

1. Clone este repositório:
    ```sh
    git clone https://github.com/seu-usuario/PI_Weslley_Luiz_Kampa.git
    cd PI_Weslley_Luiz_Kampa
    ```

2. Compile o código:
    ```sh
    gcc -o jogo PI_weslley_luiz_kampa.c -lgdi32
    ```

3. Execute o jogo:
    ```sh
    ./jogo
    ```

## Estrutura do Código

- **Definições de Cores e Layout**: Variáveis para definir cores e layout da interface do terminal.
- **Funções de Utilidade**: Funções para limpar o terminal, aguardar por uma tecla, posicionar o cursor, e definir cores.
- **Estruturas de Dados**: Estruturas para definir jogadores e suas posições no jogo.
- **Funções Principais**: Funções para iniciar o jogo, definir idioma, e controlar a lógica do jogo.

## Contribuição

Sinta-se à vontade para contribuir com este projeto. Para contribuir:

1. Faça um fork do projeto.
2. Crie uma branch para sua feature (`git checkout -b feature/MinhaFeature`).
3. Commit suas mudanças (`git commit -m 'Adicionando MinhaFeature'`).
4. Faça um push para a branch (`git push origin feature/MinhaFeature`).
5. Abra um Pull Request.
