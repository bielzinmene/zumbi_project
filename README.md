# Jogo do Zumbi

Jogo 2D em C++11 com SDL2, desenvolvido na disciplina de Introdução ao Desenvolvimento de Jogos.

**Etapa atual: trabalho 6.** Há colisões SAT, dano, zumbis perseguidores,
NPCs armados e ondas com curva de dificuldade por fila de comandos (extra).
O jogo também mantém parallax e ordenação por profundidade.

## Compilar e executar

Requer Make, compilador C++ e as bibliotecas de desenvolvimento SDL2, SDL2_image, SDL2_mixer e SDL2_ttf.
No CLion, abra esta pasta como projeto CMake; o Makefile continua disponível.

Na raiz do projeto:

```bash
make
./JOGO
```

## Controles

| Tecla | Ação |
| --- | --- |
| WASD | Mover o personagem |
| Espaço | Criar um zumbi na posição do mouse |
| Clique esquerdo | Atirar na direção do mouse |
| Esc | Sair |

O espaço cria um zumbi manualmente para testes. As ondas começam automaticamente,
e a próxima só inicia depois de derrotar os inimigos da atual. A arma do jogador
dispara três projéteis; tiros de NPCs atingem o jogador. O modo `make debug`
desenha os colisores em vermelho.

Para alternar entre as compilações normal e debug, execute `make clean` antes.
