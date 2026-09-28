# Jogo do Zumbi

Jogo 2D em C++11 e SDL2, desenvolvido para Introdução ao Desenvolvimento de Jogos. A etapa 7 inclui tela inicial, três ondas de inimigos, condições de vitória e derrota e opção de jogar novamente.

## Executar

Requer Make, compilador C++ e SDL2, SDL2_image, SDL2_mixer e SDL2_ttf instalados.

```bash
make
./JOGO
```

No CLion, abra a pasta como projeto CMake. O modo `make debug` exibe os colisores; execute `make clean` antes de alternar entre os modos normal e debug.

## Controles

| Tela | Tecla | Ação |
| --- | --- | --- |
| Início | Espaço | Começar |
| Partida | WASD | Mover |
| Partida | Clique esquerdo | Atirar |
| Partida | Esc | Voltar ao início |
| Final | Espaço | Jogar novamente |
| Início/final | Esc | Sair |

A próxima onda começa quando todos os inimigos da anterior forem derrotados. O jogador vence após a terceira onda e perde se morrer.
