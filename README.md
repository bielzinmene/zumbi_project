# Jogo do Zumbi

Jogo 2D em C++11 com SDL2, desenvolvido na disciplina de Introdução ao Desenvolvimento de Jogos.

**Etapa atual: trabalho 4**, com input, temporização, câmera e parallax.

## Compilar e executar

Requer Make, compilador C++ e as bibliotecas de desenvolvimento SDL2, SDL2_image, SDL2_mixer e SDL2_ttf.

Na raiz do projeto:

```bash
make
./JOGO
```

## Controles

| Tecla | Ação |
| --- | --- |
| Setas ou WASD | Mover a câmera |
| Espaço | Criar um zumbi na posição do mouse |
| Clique esquerdo | Causar dano ao zumbi |
| Esc | Sair |

Cada zumbi tem 100 HP e recebe 10 de dano por clique. Após morrer, desaparece em 5 segundos.
O parallax pode ser observado nas estrelas visíveis através do lago ao mover a câmera.