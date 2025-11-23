#include "dominios.hpp"
#include <stdexcept>
#include <string>
#include <cctype>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath> // Para round

using namespace std;

// ============================================================================
// CLASSE NUMERO
// ============================================================================

void Numero::validar(int valor) {
    if(valor < 1 || valor > 999) {
        throw invalid_argument("Numero invalido. O valor deve estar entre 1 e 999.");
    }
}

void Numero::setValor(int novoValor) {
    validar(novoValor);
    this->valor = novoValor;
}

// ============================================================================
// CLASSE SENHA
// ============================================================================

void Senha::validar(const string& valor) {
    const int TAMANHO = 5;

    if(valor.length() != TAMANHO) {
        throw invalid_argument("Senha deve conter exatamente 5 caracteres.");
    }

    bool temDigito = false;
    bool temMaiuscula = false;
    bool temMinuscula = false;
    bool temEspecial = false;

    const string CARACTERES_ESPECIAIS = "!\"#$%&?";

    for(char c : valor) {
        if (isdigit(c)) temDigito = true;
        else if (isupper(c)) temMaiuscula = true;
        else if (islower(c)) temMinuscula = true;
        else if (CARACTERES_ESPECIAIS.find(c) != string::npos) temEspecial = true;
        else throw invalid_argument("Caracter invalido na senha.");
    }

    if(!temDigito || !temMaiuscula || !temMinuscula || !temEspecial) {
        throw invalid_argument("Senha deve conter pelo menos uma letra minuscula, uma maiuscula, um digito e um caracter especial.");
    }

    // Verifica caracteres sequenciais repetidos (tipo por tipo)
    for(size_t i = 0; i < valor.length() - 1; i++) {
        char atual = valor[i];
        char proximo = valor[i+1];

        if(isalpha(atual) && isalpha(proximo)) {
            throw invalid_argument("Letra nao pode ser seguida por letra.");
        }
        if(isdigit(atual) && isdigit(proximo)) {
            throw invalid_argument("Digito nao pode ser seguido por digito.");
        }
    }
}

void Senha::setValor(const string& novoValor) {
    validar(novoValor);
    this->valor = novoValor;
}

// ============================================================================
// CLASSE ENDERECO
// ============================================================================

void Endereco::validar(const string& valor) {
    const size_t TAMANHO_MIN = 5;
    const size_t TAMANHO_MAX = 30;
    const string CARACTERES_ESPECIAIS = ",. ";

    if(valor.length() < TAMANHO_MIN || valor.length() > TAMANHO_MAX) {
        throw invalid_argument("Endereco deve conter entre 5 e 30 caracteres.");
    }

    for(size_t i = 0; i < valor.length(); i++) {
        char c = valor[i];

        if (!(isalnum(c) || CARACTERES_ESPECIAIS.find(c) != string::npos)) {
            throw invalid_argument("Caracter invalido no endereco.");
        }

        if((i == 0 || i == valor.length()-1) && CARACTERES_ESPECIAIS.find(c) != string::npos) {
            throw invalid_argument("Primeiro e ultimo caracter nao pode ser virgula, ponto ou espaco em branco.");
        }
    }

    for(size_t i = 0; i < valor.length() - 1; i++) {
        char atual = valor[i];
        char proximo = valor[i+1];

        if(atual == ',' && (proximo == ',' || proximo == '.')) {
            throw invalid_argument("Virgula nao pode ser seguida por virgula ou ponto.");
        }
        if(atual == '.' && (proximo == ',' || proximo == '.')) {
            throw invalid_argument("Ponto nao pode ser seguido por virgula ou ponto.");
        }
        if(atual == ' ' && !isalnum(proximo)) {
            throw invalid_argument("Espaco em branco deve ser seguido por letra ou digito.");
        }
    }
}

void Endereco::setValor(const string& novoValor) {
    validar(novoValor);
    this->valor = novoValor;
}

// ============================================================================
// CLASSE DINHEIRO
// ============================================================================

void Dinheiro::validar(long long valor) {
    if (valor < 1 || valor > 100000000) { // 1 centavo a 1 milhão de reais (em centavos)
       throw invalid_argument("Valor monetario fora do intervalo permitido (0,01 a 1.000.000,00).");
    }
}

void Dinheiro::setValor(double valor) {
    // Converte para centavos com arredondamento para evitar problemas de precisão
    long long valorEmCentavos = static_cast<long long>(std::round(valor * 100));
    validar(valorEmCentavos);
    this->valor = valorEmCentavos;
}

double Dinheiro::getValor() const {
    return static_cast<double>(valor) / 100.0;
}

// ============================================================================
// CLASSE CARTAO
// ============================================================================

void Cartao::validar(const string& valor){
    if(valor.size() != 16)
        throw invalid_argument("O numero do cartao deve conter exatamente 16 digitos.");

    for(char c : valor){
        if(!isdigit(c))
            throw invalid_argument("O cartao deve conter apenas digitos (0-9).");
    }

    // Algoritmo de Luhn
    int soma = 0;
    for(int i = 14; i >= 0; i--){
        int digito = valor[i] - '0';

        // O algoritmo dobra alternadamente, começando do penúltimo (índice par se considerarmos 0-based da direita, ou ímpar da esquerda se tamanho par)
        // Como size é 16 (par), índices pares (0, 2... 14) são os que dobram.
        if(i % 2 == 0) {
            digito *= 2;
            if(digito > 9) digito -= 9;
        }
        soma += digito;
    }

    int digitoVerificadorCalculado = (10 - (soma % 10)) % 10;
    int digitoVerificadorReal = valor[15] - '0';

    if(digitoVerificadorCalculado != digitoVerificadorReal)
        throw invalid_argument("Numero do cartao invalido (falha no algoritmo de Luhn).");
}

void Cartao::setValor(const string& valor){
    validar(valor);
    this->valor = valor;
}

// ============================================================================
// CLASSE NOME
// ============================================================================

void Nome::validar(const string& valor){
    if(valor.size() < 5 || valor.size() > 20)
        throw invalid_argument("Nome deve conter entre 5 e 20 caracteres.");

    // O HPP define que precisamos de validações, vamos garantir algumas básicas
    // Mas respeitando o código original da equipe que estava bom:

    if(valor.back() == ' ')
        throw invalid_argument("Ultimo caractere nao deve ser espaco em branco.");

    // Verifica caractere inicial
    if(!isupper(valor[0]))
        throw invalid_argument("Primeiro caractere deve ser letra maiuscula.");

    bool espacoAnterior = false;
    for(size_t i = 0; i < valor.size(); i++){
        char c = valor[i];

        if (c == ' ') {
            if (espacoAnterior) throw invalid_argument("Nao pode haver espacos seguidos.");
            espacoAnterior = true;
            continue;
        }

        if (espacoAnterior) {
            if (!isupper(c)) throw invalid_argument("Primeiro caractere de cada termo deve ser maiusculo.");
            espacoAnterior = false;
        } else {
            if (!isalpha(c) && c != ' ') throw invalid_argument("Nome deve conter apenas letras e espacos.");
        }
    }
}

void Nome::setValor(const string& valor){
    validar(valor);
    this->valor = valor;
}

// ============================================================================
// CLASSE CAPACIDADE
// ============================================================================

void Capacidade::validar(unsigned short capacidade) const {
    if (capacidade < 1 || capacidade > 4)
        throw invalid_argument("Capacidade deve ser 1, 2, 3 ou 4.");
}

void Capacidade::setValor(unsigned short capacidade) {
    validar(capacidade);
    this->capacidade = capacidade;
}

// ============================================================================
// CLASSE DATA
// ============================================================================

string Data::letraMaiuscula(const string &s) const {
    string convertida = s;
    for (char &c : convertida) {
        c = toupper(c);
    }
    return convertida;
}

unsigned short Data::mesParaIndice(const string &mes) const {
    string m = letraMaiuscula(mes);
    if (m == "JAN") return 1;
    if (m == "FEV") return 2;
    if (m == "MAR") return 3;
    if (m == "ABR") return 4;
    if (m == "MAI") return 5;
    if (m == "JUN") return 6;
    if (m == "JUL") return 7;
    if (m == "AGO") return 8;
    if (m == "SET") return 9;
    if (m == "OUT") return 10;
    if (m == "NOV") return 11;
    if (m == "DEZ") return 12;
    return 0;
}

bool Data::ehBissexto(unsigned short ano) const {
    return (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
}

unsigned short Data::diasNoMes(const string &mes, unsigned short ano) const {
    unsigned short indice = mesParaIndice(mes);
    switch (indice) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return ehBissexto(ano) ? 29 : 28;
        default: return 0;
    }
}

bool Data::mesValido(const string &mes) const {
    return mesParaIndice(mes) != 0;
}

void Data::validar(unsigned short dia, const string &mes, unsigned short ano) const {
    if (ano < ANO_MIN || ano > ANO_MAX)
        throw invalid_argument("Ano fora do intervalo permitido (2000-2999).");

    if (!mesValido(mes))
        throw invalid_argument("Mes invalido. Use JAN, FEV, MAR, etc.");

    unsigned short limite = diasNoMes(mes, ano);
    if (dia < 1 || dia > limite)
        throw invalid_argument("Dia invalido para o mes e ano informados.");
}

void Data::setValor(unsigned short dia, const string &mes, unsigned short ano) {
    validar(dia, mes, ano);
    this->dia = dia;
    this->mes = letraMaiuscula(mes);
    this->ano = ano;
}

// ============================================================================
// CLASSE TELEFONE
// ============================================================================

void Telefone::validar(const string &telefone) {
    if (telefone.empty() || telefone[0] != '+')
        throw invalid_argument("Telefone deve comecar com '+'.");

    // +DDDDDDDDDDDDDD (15 chars: + e 14 dígitos) ou 16 chars se for + e 15 dígitos?
    // O documento diz "+DDDDDDDDDDDDDD" com D sendo digito.
    // Se contar os D's no exemplo visual do PDF, as vezes parece ter 14 ou 15.
    // Mas a tabela diz "Telefone: +DDDDDDDDDDDDDD".
    // Vamos assumir a validação do código original da equipe que pedia 16 chars totais.

    // Assumindo + e 15 digitos = 16 chars.
    if (telefone.size() != 16)
        throw invalid_argument("Telefone deve ter formato + e 15 digitos (Total 16 chars).");

    for (size_t i = 1; i < telefone.size(); i++) {
        if (!isdigit(telefone[i]))
            throw invalid_argument("Telefone deve conter apenas digitos apos o '+'.");
    }
}

void Telefone::setValor(const string &novoValor) {
    validar(novoValor);
    this->telefone = novoValor;
}

// ============================================================================
// CLASSE CODIGO
// ============================================================================

void Codigo::validar(const string& codigo) {
    if(codigo.length() != 10) {
        throw invalid_argument("Codigo deve ter 10 caracteres.");
    }

    for(char c : codigo) {
        if(!isalnum(c)) {
            throw invalid_argument("Codigo deve conter apenas letras e numeros.");
        }
    }
}

void Codigo::setValor(const string& novoValor) {
    validar(novoValor);
    this->codigo = novoValor;
}

// ============================================================================
// CLASSE EMAIL
// ============================================================================

void EMAIL::validar(const string& email) {
    // Verifica estrutura básica
    size_t posArroba = email.find("@");
    if(posArroba == string::npos) {
        throw invalid_argument("Email deve conter '@'.");
    }

    string parte_local = email.substr(0, posArroba);
    string dominio = email.substr(posArroba + 1);

    if(parte_local.length() > MAX_PARTE_LOCAL) throw invalid_argument("Parte local muito longa.");
    if(dominio.length() > MAX_DOMINIO) throw invalid_argument("Dominio muito longo.");

    // Validação Parte Local
    // Pode conter letra, digito, ponto ou hifen. Não pode iniciar/terminar com ponto/hifen.
    if(parte_local.empty()) throw invalid_argument("Parte local vazia.");

    if(parte_local.front() == '.' || parte_local.front() == '-')
        throw invalid_argument("Parte local nao pode iniciar com ponto ou hifen.");
    if(parte_local.back() == '.' || parte_local.back() == '-')
        throw invalid_argument("Parte local nao pode terminar com ponto ou hifen.");

    bool anteriorPontoOuHifen = false;
    for(char c : parte_local) {
        if (c == '.' || c == '-') {
            if(anteriorPontoOuHifen) throw invalid_argument("Ponto ou hifen nao podem ser consecutivos.");
            anteriorPontoOuHifen = true;
        } else if (isalnum(c)) {
            anteriorPontoOuHifen = false;
        } else {
            throw invalid_argument("Caractere invalido na parte local do email.");
        }
    }

    // Validação Domínio
    // Partes separadas por ponto. Não hifen inicio/fim.
    if(dominio.empty()) throw invalid_argument("Dominio vazio.");

    if(dominio.front() == '-') throw invalid_argument("Dominio nao pode iniciar com hifen.");
    if(dominio.back() == '-') throw invalid_argument("Dominio nao pode terminar com hifen.");

    // O domínio deve ter pelo menos um ponto separando partes? O PDF diz "composto por uma ou mais partes separadas por ponto".
    // Se for só "com", é uma parte. Se for "com.br", duas.
    // Mas não pode iniciar ou terminar com ponto.

    if(dominio.front() == '.' || dominio.back() == '.')
        throw invalid_argument("Dominio nao pode iniciar ou terminar com ponto.");

    anteriorPontoOuHifen = false;
    for(char c : dominio) {
        if (c == '.') {
            if(anteriorPontoOuHifen) throw invalid_argument("Pontos nao podem ser consecutivos no dominio.");
            anteriorPontoOuHifen = true;
        } else if (c == '-') {
             // Hifen no meio é ok, mas hifen seguido de ponto? "a-.b"?
             // PDF: "não pode iniciar ou terminar com hifen".
        } else if (!isalnum(c)) {
             throw invalid_argument("Caractere invalido no dominio.");
        }

        if (c != '.') anteriorPontoOuHifen = false;
    }
}

void EMAIL::setValor(const string& novoValor) {
    validar(novoValor);
    this->email = novoValor;
}

// ============================================================================
// CLASSE RAMAL
// ============================================================================

void Ramal::validar(unsigned short ramal) {
    if(ramal > 50) { // Como é unsigned, < 0 não precisa checar
        throw invalid_argument("Ramal deve estar entre 0 e 50.");
    }
}

void Ramal::setValor(unsigned short novoValor) {
    validar(novoValor);
    this->ramal = novoValor;
}
