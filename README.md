<h1 align="center"> Jogo Do Zumbi </h1>

Finalizada a etapa 2!
### 🚀 O que foi implementado até agora

**Etapa 1:**
* **Base do Jogo:** Criação da estrutura principal, garantindo que ele rode de forma contínua e segura através do Game Loop e do padrão Singleton.
* **Visual e Som:** Suporte inicial para desenhar imagens de fundo na tela (`Sprite`) e tocar uma trilha sonora em repetição (`Music`).
* **Desempenho:** Gerenciamento da janela do jogo e limpeza correta da memória ao fechar o programa.

**Etapa 2:**
* **Novo Sistema de Componentes:** O jogo agora usa uma estrutura modular inteligente (`GameObject` e `Component`). Em vez de lógicas super complexas, cada elemento do jogo ganha comportamentos adicionando pequenos "blocos" independentes.
* **Matemática e Movimento:** Foram criadas ferramentas geométricas (`Vec2` e `Rect`) para facilitar cálculos de distância, colisão e rotação na tela.
* **Animações:** O fundo estático deu lugar ao movimento! O sistema visual agora consegue recortar e exibir sequências de imagens para criar animações fluídas.
* **O Primeiro Inimigo (Zumbi):** Criamos nosso primeiro "ator" autônomo na tela. O Zumbi possui sua própria energia (HP) e muda automaticamente a animação de "correndo" para "morto" quando a vida chega a zero.

---

### 🎮 Como compilar e executar no Linux

Certifique-se de ter os pacotes de desenvolvimento da SDL2 instalados no seu sistema.

- `1º passo` - Para compilar e preparar o jogo, execute o seguinte comando no terminal na raiz do projeto:
  ```bash
  make
- `2º passo` - Para rodar o jogo após compilado, execute o comando abaixo no terminal:
  ```bash
  make run