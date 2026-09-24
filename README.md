# Jogo do Zumbi

Jogo 2D em C++11 com SDL2, desenvolvido na disciplina de Introdução ao Desenvolvimento de Jogos.

**Etapa atual: trabalho 5**, com personagem jogável, arma, projéteis, rotação,
espelhamento e escala. Inclui parallax e o extra de ordenação por profundidade (Z/Y sorting).

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
| WASD | Mover o personagem |
| Espaço | Criar um zumbi na posição do mouse |
| Clique esquerdo | Atirar na direção do mouse |
| Esc | Sair |

A câmera acompanha o personagem. A arma recarrega automaticamente entre disparos,
e os projéteis desaparecem ao atingir seu alcance máximo. As colisões dos tiros
entram na etapa 6; o dano por clique direto nos zumbis da etapa 4 foi mantido.

O Z/Y sorting faz o personagem passar à frente ou atrás dos zumbis conforme sua
posição no cenário. O parallax pode ser observado nas estrelas através do lago.