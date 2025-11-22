#include "dominios.hpp"
#include <stdexcept>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

void Numero::validar(int valor) {
    if(valor < 1 || valor > 999) {
        throw invalid_argument("Numero invalido. O valor deve estar entre 001 e 999.");
    }
}

void Numero::setValor(int novoValor) {
    validar(novoValor);
    this->valor = novoValor;
}

void Senha::validar(string valor) {
    const int TAMANHO = 5;

    if(valor.length() != TAMANHO) {
        throw invalid_argument("Senha deve conter 5 caracteres.");
    }

    int temDigito = 0;
    int temMaiuscula = 0;
    int temMinuscula = 0;
    int temEspecial = 0;

    const string CARACTERES_ESPECIAIS = "!\"#$%&?";

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

void Senha::setValor(string novoValor) {
    validar(novoValor);
    this->valor = novoValor;
}

void Endereco::validar(string valor) {
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

void Endereco::setValor(string novoValor) {
    validar(novoValor);
    this->valor = novoValor;
}

// ----------------- Marcel -----------------------
void Dinheiro::validar(string valor) {
    size_t posVirgula = valor.find(',');

    if (posVirgula == string::npos) {
        throw invalid_argument("Formato invalido. Deve conter virgula separando centavos.\n");
    }
    if (valor.find(',', posVirgula + 1) != string::npos) {
        throw invalid_argument("Formato invalido. Deve conter apenas uma virgula.\n");
    }

    string parteCentavos = valor.substr(posVirgula + 1);
    if (parteCentavos.length() != 2) {
        throw invalid_argument("Formato invalido. Deve conter exatamente 2 digitos para centavos.\n");
    }
    if (!isdigit(parteCentavos[0]) || !isdigit(parteCentavos[1])) {
        throw invalid_argument("Centavos devem ser digitos numericos.\n");
    }
  
    string parteReais = valor.substr(0, posVirgula);
    if (parteReais.empty()) {
        throw invalid_argument("Formato invalido. Parte dos reais esta vazia.\n");
    }

    string strValorNumerico;
    int digitosDesdeUltimoPonto = 0;

    for (int i = parteReais.length() - 1; i >= 0; i--) {
        char c = parteReais[i];

        if (isdigit(c)) {
            strValorNumerico = c + strValorNumerico;
            digitosDesdeUltimoPonto++;
        } else if (c == '.') {
            if (i == 0) {
                throw invalid_argument("Ponto nao pode ser o primeiro caractere.\n");
            }
            if (digitosDesdeUltimoPonto != 3) {
                throw invalid_argument("Ponto de milhar mal posicionado. Deve separar 3 digitos.\n");
            }
            digitosDesdeUltimoPonto = 0;
        } else {
            throw invalid_argument("Caractere invalido na parte dos reais. Use apenas digitos e '.'\n");
        }
    }

    strValorNumerico += parteCentavos;

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

void Dinheiro::setValor(string novoValor) {
    validar(novoValor);
    
    string strCentavos;
    for (char c : novoValor) {
        if (isdigit(c)) {
            strCentavos += c;
        }
    }
    this->valor = stoi(strCentavos); 
}

string Dinheiro::getValor() const {
    string s = to_string(this->valor);

    while (s.length() < 3) {
        s = "0" + s;
    }

    string centavos = s.substr(s.length() - 2);
    string reais = s.substr(0, s.length() - 2);

    string reaisFormatado;
    int contador = 0;
    for (int i = reais.length() - 1; i >= 0; i--) {
        reaisFormatado = reais[i] + reaisFormatado;
        contador++;
        if (contador == 3 && i > 0) {
            reaisFormatado = "." + reaisFormatado;
            contador = 0;
        }
    }

    return reaisFormatado + "," + centavos;
}

void Cartao::validar(string valor){
    if(valor.size()!=16)
        throw invalid_argument("O numero do cartao deve conter exatamente 16 digitos (0-9)\n");
    else{
        short int contador=0;
        for(int i=0; i<valor.size(); i++){
            if(!isdigit(valor[i]))
                throw invalid_argument("O cartao deve conter apenas digitos (0-9).\n");
        }
        for(int i=14; i>=0; i--){
            short int numero = valor[i]-'0';
            if(i%2==1)
                contador+=numero;
            
            else if((2*(numero))>9){
                short int digito=(2*numero)-9;
                contador+=digito;
            }
            else
                contador+=2*numero;
        }
        short int init=valor[15]-'0';
        if((10-(contador%10))%10!=init)
            throw invalid_argument("Numero nao respeita o algoritmo de Luhn.\n");
    }
}

void Cartao::setValor(string valor){
    validar(valor);
    this->valor = valor;
}

void Nome::validar(string valor){
    if(5>valor.size() || valor.size()>20)
        throw invalid_argument("Nome deve conter entre 5 e 20 caracteres.\n");
    else if(valor[valor.size()-1] == ' ')
        throw invalid_argument("Ultimo caractere nao deve ser espaco em branco.\n");
    else if(valor[0]>'Z' || valor[0]<'A')
        throw invalid_argument("Primeiro caractere deve ser letra maiuscula.\n");
    else{
        bool teve_espaco=false;
        for(int i=0; i<valor.size(); i++){
            char c = valor[i];
            if(teve_espaco){
                teve_espaco=false;
                if(c<'A' || c>'Z'){
                    if('a'<=c && c <= 'z')
                        throw invalid_argument("O primeiro caractere de cada termo deve ser letra maiuscula (A-Z).\n");
                    else if(c==' ')
                        throw invalid_argument("Espaco em branco deve ser seguido por letra.\n");
                    else
                        throw invalid_argument("Nome deve conter apenas letras maiusuculas (A-Z), minusculas (a-z) e espacos em branco.\n");
                }
            }
            else{
                if(c==' '){
                    teve_espaco=true;
                    continue;
                }
                else if(('A'<=c && c<='Z') || ('a'<=c && c<='z')) continue;
                else
                    throw invalid_argument("Nome deve conter apenas letras maiusuculas (A-Z), minusculas (a-z) e espacos em branco.\n");
            }
        }
    }
}

void Nome::setValor(string valor){
    validar(valor);
    this->valor=valor;
}

// -------------------- Duda ----------------------

void Capacidade::validar(unsigned short capacidade) const {
    if (capacidade < LIMITE_INFERIOR)
        throw out_of_range("Erro: capacidade menor que o limite mínimo permitido de 1 pessoa");

    if (capacidade > LIMITE_SUPERIOR)
        throw out_of_range("Erro: capacidade maior que o limite máximo permitido de 4 pessoas");
}

void Capacidade::setCapacidade(unsigned short capacidade) {
    validar(capacidade);
    this->capacidade = capacidade;
}

string Data::letraMaiuscula(const string &mes) const {
    string mesPadrao = mes;
    for (int i = 0; i < (unsigned short)mesPadrao.size(); i++) {
        mesPadrao[i] = toupper(mesPadrao[i]);
    }
    return mesPadrao;
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
    int indiceMes = mesParaIndice(mes);

    switch (indiceMes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: //meses impares
            return 31;
        case 4: case 6: case 9: case 11: //meses
            return 30;
        case 2:
            return ehBissexto(ano) ? 29 : 28;
        default:
            return 0;
    }
}

bool Data::mesValido(const string &mes) const {
    if (mes.size() != 3) return false;

    string m = letraMaiuscula(mes);
    static const string mesesValidos[] = {
        "JAN", "FEV", "MAR", "ABR", "MAI", "JUN",
        "JUL", "AGO", "SET", "OUT", "NOV", "DEZ"
    };

    for (const string &mesValido : mesesValidos) {
        if (m == mesValido) {
            return true;
        }
    }
    return false;
}

void Data::validar(unsigned short dia, const string &mes, unsigned short ano) const {
    if (ano < ANO_MIN || ano > ANO_MAX)
        throw out_of_range("Ano fora do intervalo permitido (2000–2999).");

    if (!mesValido(mes))
        throw invalid_argument("Mês inválido. Use abreviações de três letras em maiúsculo (ex: JAN, FEV).");

    unsigned short limite = diasNoMes(mes, ano);
    if (dia < 1 || dia > limite)
        throw out_of_range("Dia fora do intervalo permitido para o mês informado.");
}

void Data::setValor(unsigned short dia, const string &mes, unsigned short ano) {
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

    return true;
}

void Telefone::setTelefone(const string &telefone) {
    validar(telefone);
    this->telefone = telefone;
}

// ------------------ Gustavo ----------------------
void Codigo::validar(std::string& codigo) {
    
    if(codigo.length() != 10) {
        throw std::invalid_argument("Tamanho inválido");
        
    }

    for(char x : codigo) {
        if(!((x >='a' && x<='z') || (x >= '0') && (x<='9'))) {
            throw std::invalid_argument("O código deve ter apenas letras e números");
        }
    }
}


void Codigo::setCodigo(std::string& codigo) {   
    validar(codigo);
    this->codigo = codigo;

}

    Codigo::Codigo(std::string& codigo) {
        setCodigo(codigo);
    }

void EMAIL::validar(std::string& email) {
    
    //dividir pra verificar parte local e dominio
    size_t arroba = email.find("@");

    if(arroba == std::string::npos) {
        throw std::invalid_argument("Email deve ter @");
    }

    std::string parte_local = email.substr(0, arroba);
    std::string dominio = email.substr(arroba+1);

    if(parte_local.length()> MAX_PARTE_LOCAL) throw std::invalid_argument("Parte local excedeu o limite");
    if(dominio.length()> MAX_DOMINIO) throw std::invalid_argument("Dominio excedeu o limite");
    

    bool ultimoEspecial = true;
    
    for(char& c : parte_local) {
        c = std::tolower(static_cast<unsigned char>(c));

        if(!(c>= 'a' && c<= 'z' || c>='0' && c<='9' || c== '.' || c=='-')) throw std::invalid_argument("Email pode conter apenas letras, numeros, ponto ou hifen.");

        if(c=='.' || c=='-') {
            if(ultimoEspecial) throw std::invalid_argument("Email não pode começar com caracter especial nem ter sequência de caracter especial");
            ultimoEspecial = true;
        } else ultimoEspecial = false;
    }

    if(parte_local[parte_local.length()-1] == '.' || parte_local[parte_local.length()-1]=='-') {
        throw std::invalid_argument("Parte local não pode terminar com hifen ou ponto");
    }

    ultimoEspecial = true;
    for(char& c : dominio) {
        c = std::tolower(static_cast<unsigned char>(c));

        if(!(c>= 'a' && c<= 'z' || c>='0' && c<='9' || c== '.' || c=='-')) throw std::invalid_argument("Email pode conter apenas letras, numeros, ponto ou hifen.");

        if(c=='.' || c=='-') {
            if(ultimoEspecial) throw std::invalid_argument("Email não pode começar com caracter especial nem ter sequência de caracter especial");
            ultimoEspecial = true;
        } else ultimoEspecial = false;
    }
    if(dominio[dominio.length()-1] == '.' || dominio[dominio.length()-1]=='-') {
        throw std::invalid_argument("Dominio não pode terminar com hifen ou ponto");
    }

    email = parte_local + '@' + dominio;
}

void EMAIL::setEmail(std::string& email) {
    validar(email);
    this->email = email;

}

EMAIL::EMAIL(std::string& email) {
    setEmail(email);
}

void Ramal::validar(int& ramal) {
    if(ramal < 0 || ramal > 50) throw std::invalid_argument("Ramal deve estar entre 0 e 50");

}

void Ramal::setRamal(int& ramal) {
    validar(ramal);
    this->ramal = ramal;
}

Ramal::Ramal(int& ramal) {
    setRamal(ramal);
}