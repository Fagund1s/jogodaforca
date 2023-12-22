#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cstring>

class Jogo {

public:
    virtual void jogar() = 0;
    virtual ~Jogo() {}
};

class Forca : public Jogo {
    
private:
    char* palavraSecreta;
    std::vector<char> letrasTentadas;
    int maxTentativas;
    int tentativasRestantes;

public:

    Forca() : palavraSecreta(nullptr), maxTentativas(6), tentativasRestantes(maxTentativas) {}

    Forca(const std::string& palavra) : maxTentativas(6), tentativasRestantes(maxTentativas) {
        alocarMemoria(palavra);
    }

    ~Forca() {
        liberarMemoria();
    }

    void alocarPalavra() {
        std::vector<std::string> palavras = lerPalavrasDeArquivo("C:/Users/Fagundes/Desktop/projeto/text/palavras.txt");

        if (palavras.empty()) {
            std::cerr << "Nenhuma palavra encontrada no arquivo." << std::endl;
            exit(1);
        }

        std::srand(std::time(0));
        int indice = std::rand() % palavras.size();
        alocarMemoria(palavras[indice]);
    }

    void alocarPalavra(const std::string& palavra) {
        alocarMemoria(palavra);
    }

    void alocarPalavra(const std::string& palavra, int maxTentativas) {
        this->maxTentativas = maxTentativas;
        alocarMemoria(palavra);
    }

    void jogar() override{
        while (tentativasRestantes > 0 && !jogoGanho()) {
            exibirStatus();

            char letra;
            std::cout << "Digite uma letra: ";
            std::cin >> letra;

            if (tentativaValida(letra)) {
                letrasTentadas.push_back(letra);
                if (!letraNaPalavra(letra)) {
                    tentativasRestantes--;
                }
            } else {
                std::cout << "Letra já tentada. Tente novamente." << std::endl;
            }
        }

        exibirResultado();
        gerarRelatorio();
    }

    static std::vector<std::string> lerPalavrasDeArquivo(const std::string& nomeArquivo) {
        std::vector<std::string> palavras;
        std::ifstream arquivo(nomeArquivo);

        if (arquivo.is_open()) {
            std::string palavra;
            while (arquivo >> palavra) {
                palavras.push_back(palavra);
            }
            arquivo.close();
        } else {
            std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
        }

        return palavras;
    }

private:

    void exibirStatus() const {
        std::cout << "Palavra: ";
        for (char* ptr = palavraSecreta; *ptr != '\0'; ++ptr) {
            if (letraTentada(*ptr)) {
                std::cout << *ptr << " ";
            } else {
                std::cout << "_ ";
            }
        }
        std::cout << std::endl;

        std::cout << "Letras Tentadas: ";
        for (char c : letrasTentadas) {
            std::cout << c << " ";
        }
        std::cout << std::endl;

        std::cout << "Tentativas Restantes: " << tentativasRestantes << std::endl;
    }

    bool letraNaPalavra(char letra) const {
        for (char* ptr = palavraSecreta; *ptr != '\0'; ++ptr) {
            if (*ptr == letra) {
                return true;
            }
        }
        return false;
    }

    bool letraTentada(char letra) const {
        for (char c : letrasTentadas) {
            if (c == letra) {
                return true;
            }
        }
        return false;
    }

    bool tentativaValida(char letra) const {
        return !letraTentada(letra);
    }

    bool jogoGanho() const {
        for (char* ptr = palavraSecreta; *ptr != '\0'; ++ptr) {
            if (!letraTentada(*ptr)) {
                return false;
            }
        }
        return true;
    }

    void exibirResultado() const {
        if (jogoGanho()) {
            std::cout << "Jogo ganho." << palavraSecreta << std::endl;
        } else {
            std::cout << "Jogo perdido." << palavraSecreta << std::endl;
        }
    }

    void gerarRelatorio() const {
        std::ofstream relatorio("C:/Users/Fagundes/Desktop/projeto/text/relatorio.txt");
        if (relatorio.is_open()) {
            relatorio << "Relatório do Jogo da Forca\n";
            relatorio << "Palavra: " << palavraSecreta << "\n";
            relatorio << "Tentativas Restantes: " << tentativasRestantes << "\n";
            relatorio << "Palavra Descoberta: " << (jogoGanho() ? "Sim" : "Não") << "\n";
            relatorio.close();
            std::cout << "Arquivo gerado com sucesso.'.\n";
        } else {
            std::cerr << "Erro.\n";
        }
    }

    void alocarMemoria(const std::string& palavra) {
        liberarMemoria();

        palavraSecreta = new char[palavra.length() + 1];
        std::strcpy(palavraSecreta, palavra.c_str());
    }

    void liberarMemoria() {
        delete[] palavraSecreta;
        palavraSecreta = nullptr;
    }
};

int main() {
    Forca jogo;
    jogo.alocarPalavra();

    jogo.jogar();

    return 0;
}
