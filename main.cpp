#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Forca {
private:
    string palavraSecreta;
    vector<char> letrasTentadas;
    int maxTentativas;
    int tentativasRestantes;

public:
    Forca(const string& palavra) : palavraSecreta(palavra), maxTentativas(6), tentativasRestantes(maxTentativas) {}

    void jogar() {
        while (tentativasRestantes > 0 && !jogoGanho()) {
            exibirStatus();

            char letra;
            cout << "Digite uma letra: ";
            cin >> letra;

            if (tentativaValida(letra)) {
                letrasTentadas.push_back(letra);
                if (!letraNaPalavra(letra)) {
                    tentativasRestantes--;
                }
            } else {
                cout << "Letra já usada." << endl;
            }
        }

        exibirResultado();
    }

private:
    void exibirStatus() const {
        cout << "Palavra: ";
        for (char c : palavraSecreta) {
            if (letraTentada(c)) {
                cout << c << " ";
            } else {
                cout << "_ ";
            }
        }
        cout << endl;

        cout << "Letras usadas: ";
        for (char c : letrasTentadas) {
            cout << c << " ";
        }
        cout << endl;

        cout << "Tentativas: " << tentativasRestantes << endl;
    }

    bool letraNaPalavra(char letra) const {
        for (char c : palavraSecreta) {
            if (c == letra) {
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
        for (char c : palavraSecreta) {
            if (!letraTentada(c)) {
                return false;
            }
        }
        return true;
    }

    void exibirResultado() const {
        if (jogoGanho()) {
            cout << "Você ganhou. A palavra era: " << palavraSecreta << endl;
        } else {
            cout << "Você perdeu. A palavra era: " << palavraSecreta << endl;
        }
    }
};

vector<string> lerPalavrasDeArquivo(const string& nomeArquivo) {
    vector<string> palavras;
    ifstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        string palavra;
        while (arquivo >> palavra) {
            palavras.push_back(palavra);
        }
        arquivo.close();
    } else {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
    }

    return palavras;
}

int main() {
    vector<string> palavras = lerPalavrasDeArquivo("C:/Users/Fagundes/Desktop/projeto/text/palavras.txt");

    if (palavras.empty()) {
        cerr << "Nenhuma palavra encontrada no arquivo." << endl;
        return 1;
    }

    srand(time(0));
    int indice = rand() % palavras.size();
    string palavraEscolhida = palavras[indice];

    Forca jogo(palavraEscolhida);

    jogo.jogar();

    return 0;
}
