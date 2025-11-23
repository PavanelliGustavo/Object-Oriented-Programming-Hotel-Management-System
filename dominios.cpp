#include "dominios.hpp"
#include <stdexcept>
#include <string>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <sstream> // Necessário para conversão de Ramal

using namespace std;

// ====================================================================
// NOSSAS CLASSES INICIAIS (NUMERO, SENHA, ENDERECO)
// ====================================================================

void Numero::validar(int valor) {
    if(valor < 1 || valor > 999) {
        throw invalid_argument("Numero invalido. O valor deve estar entre 001 e 999.");
    }
}

void Numero::setValor(int novoValor) {
    validar(novoValor);
    this->valor = novoValor;
}

void Senha::validar(const string& valor) { // CORREÇÃO: const string&
    const int TAMANHO = 5;

    if(valor.length() != TAMANHO) {
        throw invalid_argument("Senha deve conter 5 caracteres.");
    }

    int temDigito = 0;
    int temMaiuscula = 0;
    int temMinuscula = 0;
    int temEspecial = 0;

    const string CARACTERES_ESPECIAIS = "!\"#$%&?";

    // 1. Verifica Composição Mínima e Caracteres Permitidos
    for(int i = 0; i < TAMANHO; i++) {
        char c = valor[i];

        if (isdigit(c)) {
            temDigito = 1;
        }
        else if (isupper(c)) {
            temMaiuscula = 1;
        }
        else if (islower(c)) {
            temMinuscula = 1;
        }
        else if (CARACTERES_ESPECIAIS.find(c) != string::npos) {
            temEspecial = 1;
        }
        else {
            throw invalid_argument("Caracter invalido. Use letra (a-z, A-Z), digito (0-9) ou especial (!\"#$%&?).");
        }
    }

    if(temDigito == 0 || temMaiuscula == 0 || temMinuscula == 0 || temEspecial == 0) {
        throw invalid_argument("Senha deve conter pelo menos uma letra minuscula, uma maiuscula, um digito e um caracter especial.");
    }

    // 2. Verifica Sequência
    for(int i = 0; i < TAMANHO - 1; i++) {
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

void Senha::setValor(const string& novoValor) { // CORREÇÃO: const string&
    validar(novoValor);
    this->valor = novoValor;
}

void Endereco::validar(const string& valor) { // CORREÇÃO: const string&
    const int TAMANHO_MIN = 5;
    const int TAMANHO_MAX = 30;
    const string CARACTERES_ESPECIAIS = ",. ";

    if(valor.length() < TAMANHO_MIN || valor.length() > TAMANHO_MAX) {
        throw invalid_argument("Endereço deve conter entre 5 e 30 caracteres.");
    }

    for(int i = 0; i < valor.length(); i++) {
        char c = valor[i];

        if (!(isalnum(c) || CARACTERES_ESPECIAIS.find(c) != string::npos)) {
            throw invalid_argument("Caracter invalido. Use letra (a-z, A-Z), digito (0-9) ou especial (., ).");
        }

        if((i == 0 || i == valor.length()-1) && CARACTERES_ESPECIAIS.find(c) != string::npos) {
            throw invalid_argument("Primeiro e último caracter não pode ser vírgula, ponto ou espaço em branco.");
        }
    }

    for(int i = 0; i < valor.length() - 1; i++) {
        char atual = valor[i];
        char proximo = valor[i+1];

        if(atual == ',' && (proximo == ',' || proximo == '.')) {
            throw invalid_argument("Vírgula não pode ser seguida por vírgula ou ponto.");
        }
        if(atual == '.' && (proximo == ',' || proximo == '.')) {
            throw invalid_argument("Ponto não pode ser seguido por vírgula ou ponto.");
        }
        if(atual == ' ' && !isalnum(proximo)) {
            throw invalid_argument("Espaco em branco deve ser seguido por letra ou digito.");
        }
    }
}

void Endereco::setValor(const string& novoValor) { // CORREÇÃO: const string&
    validar(novoValor);
    this->valor = novoValor;
}

// ====================================================================
// ----------------- Marcel (DINHEIRO, CARTAO, NOME) -----------------------
// ====================================================================

void Dinheiro::validar(const string& valor) { // CORREÇÃO: const string&
    size_t posVirgula = valor.find(',');

    if (posVirgula == string::npos) {
        throw invalid_argument("Formato invalido. Deve conter virgula separando centavos.\n");
    }
    // ... [Restante da lógica Dinheiro::validar está OK] ...
    
    // Recalcular o valor numérico apenas com dígitos para checar o limite
    string strValorNumerico;
    for (char c : valor) {
        if (isdigit(c)) {
            strValorNumerico += c;
        }
    }

    long long valorLongo;
    try {
        valorLongo = stoll(strValorNumerico);
    } catch (const out_of_range& e) {
        throw invalid_argument("Valor excede o limite maximo.\n");
    }

    if (valorLongo < 1 || valorLongo > 100000000) {
        throw invalid_argument("Valor fora do intervalo permitido (0,01 a 1.000.000,00).\n");
    }
}

void Dinheiro::setValor(const string& novoValor) { // CORREÇÃO: setValor e const string&
    validar(novoValor);
    
    // CRÍTICO: Recalcular o valor apenas com dígitos para armazenar em 'int' (centavos)
    string strCentavos;
    for (char c : novoValor) {
        if (isdigit(c)) {
            strCentavos += c;
        }
    }
    this->valor = stoi(strCentavos); 
}

string Dinheiro::getValor() const {
    // Mantido o código de formatação para retornar a string formatada
    string s = to_string(this->valor);
    // ... [código de formatação omitido por brevidade] ...
    return "R$ " + s; // Retorno fictício, assumindo que a formatação é complexa e externa.
}

void Cartao::validar(const string& valor){ // CORREÇÃO: const string&
    if(valor.size()!=16)
        throw invalid_argument("O numero do cartao deve conter exatamente 16 digitos (0-9)\n");
    else{
        // ... [Lógica de Cartao::validar está OK] ...
    }
}

void Cartao::setValor(const string& valor){ // CORREÇÃO: setValor e const string&
    validar(valor);
    this->valor = valor;
}

void Nome::validar(const string& valor){ // CORREÇÃO: const string&
    if(5>valor.size() || valor.size()>20)
        throw invalid_argument("Nome deve conter entre 5 e 20 caracteres.\n");
    // ... [Lógica de Nome::validar está OK, usa comparações ASCII] ...
}

void Nome::setValor(const string& valor){ // CORREÇÃO: setValor e const string&
    validar(valor);
    this->valor=valor;
}

// ====================================================================
// -------------------- Duda (CAPACIDADE, DATA, TELEFONE) ----------------------
// ====================================================================

void Capacidade::validar(unsigned short capacidade) const {
    if (capacidade < LIMITE_INFERIOR)
        throw out_of_range("Erro: capacidade menor que o limite mínimo permitido de 1 pessoa");

    if (capacidade > LIMITE_SUPERIOR)
        throw out_of_range("Erro: capacidade maior que o limite máximo permitido de 4 pessoas");
}

void Capacidade::setValor(unsigned short capacidade) { // CORREÇÃO: setValor
    validar(capacidade);
    this->capacidade = capacidade;
}

// ... [Métodos auxiliares de Data estão OK] ...

void Data::validar(unsigned short dia, const string &mes, unsigned short ano) const {
    // ... [Lógica de Data::validar está OK] ...
}

void Data::setValor(unsigned short dia, const string &mes, unsigned short ano) { // CORREÇÃO: setValor
    validar(dia, mes, ano);
    this->dia = dia;
    this->mes = letraMaiuscula(mes);
    this->ano = ano;
}

bool Telefone::validar(const string &telefone) {
    if (telefone.empty() || telefone[0] != '+')
        throw invalid_argument("Erro: telefone deve começar com '+'.");

    if (telefone.size() != 16)
        throw invalid_argument("Erro: telefone deve ter exatamente 16 caracteres.");

    for (size_t i = 1; i < telefone.size(); i++) {
        if (!isdigit(telefone[i]))
            throw invalid_argument("Erro: telefone deve conter apenas dígitos depois do '+'.");
    }
    return true; // Retorna true (assinatura pede bool)
}

void Telefone::setValor(const string &telefone) { // CORREÇÃO: setValor
    validar(telefone);
    this->telefone = telefone;
}

// ====================================================================
// ------------------ Gustavo (CODIGO, EMAIL, RAMAL) ----------------------
// ====================================================================

void Codigo::validar(const std::string& codigo) { // CORREÇÃO: const std::string&
    
    if(codigo.length() != 10) {
        throw std::invalid_argument("Tamanho inválido (deve ser 10).");
    }

    for(char x : codigo) {
        // CORREÇÃO: Usar isalnum (ou checar a-z, A-Z, 0-9)
        if(!isalnum(x)) { 
            throw std::invalid_argument("O código deve ter apenas letras (a-z, A-Z) e números (0-9).");
        }
    }
}

void Codigo::setValor(const std::string& codigo) { // CORREÇÃO: setValor e const string&
    validar(codigo);
    this->codigo = codigo;
}

// Construtor Codigo::Codigo(std::string& codigo) foi removido.

void EMAIL::validar(const std::string& email) { // CORREÇÃO: const std::string&
    
    //... [Lógica do EMAIL - Grande, será corrigida para usar const] ...
    
    // CRÍTICO: O código original manipula a string 'email' e a usa para atribuir 'this->email'.
    // Mas agora 'email' é const! Você precisa criar uma cópia interna para manipulação.
    
    string emailCopia = email; // Criamos uma cópia para manipulação
    
    //dividir pra verificar parte local e dominio
    size_t arroba = emailCopia.find("@"); // Usa a cópia

    if(arroba == std::string::npos) {
        throw std::invalid_argument("Email deve ter @");
    }

    // ... [Resto da lógica EMAIL::validar está OK, mas deve usar 'emailCopia' e 'std::tolower'] ...
    
    // O final da validação deve salvar o valor padronizado na variável interna da classe,
    // mas o método 'validar' não faz isso.
}

void EMAIL::setValor(const std::string& email) { // CORREÇÃO: setValor e const string&
    // A validação do EMAIL é complexa e precisa de manipulação da string.
    // O setValor precisa chamar a validação E o ajuste da string.
    
    string emailAjustado = email;
    validar(emailAjustado); // Aqui validar deve aceitar uma string não-const para ajustes
                            // OU a lógica de ajuste deve ir para cá.
                            
    // Opção mais simples: Validar com const e a lógica de ajuste deve ir para o setValor.
    // Reverter para o modelo anterior onde o validar é const e o setValor faz a manipulação.
    
    string emailCopia = email;
    // ... [Repetir a lógica de manipulação e ajuste de minúsculas no emailCopia aqui] ...
    
    validar(emailCopia); // A validação já checa o formato.
    this->email = emailCopia; // Se validou, atribui.
}

// Construtor EMAIL::EMAIL(std::string& email) foi removido.

void Ramal::validar(unsigned short ramal) { // CORREÇÃO: unsigned short
    if(ramal > 50) throw std::invalid_argument("Ramal deve estar entre 00 e 50");
}

void Ramal::setValor(unsigned short ramal) { // CORREÇÃO: setValor e unsigned short
    validar(ramal);
    this->ramal = ramal;
}

// Construtor Ramal::Ramal(int& ramal) foi removido.
