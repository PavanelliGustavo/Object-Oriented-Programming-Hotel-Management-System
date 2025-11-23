#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

#include <stdexcept>
#include <string>
#include <cctype>
#include <iostream>

using namespace std;

// ====================================================================
// NOSSAS CLASSES (NUMERO, SENHA, ENDERECO)
// Corrigidas para usar string como const ref (&) no set, por eficiencia.
// ====================================================================

/**
 * @class Numero
 * @brief Domínio para representar o Número do Quarto em um Hotel.
 *
 * @details Esta classe armazena um valor inteiro que representa o número do quarto.
 * O formato válido, de acordo com as regras de negócio, deve ser um valor entre 1 e 999 (001 a 999).
 * A classe garante a validade do seu valor interno.
 */
class Numero{
    private:
        int valor;
        void validar(int valor);
    public:
        // setValor e getValor já estão corretos.
        void setValor(int novoValor);
        int getValor() const;
};

inline int Numero::getValor() const {
    return valor;
}

/**
 * @class Senha
 * @brief Domínio para armazenar e validar a Senha do Gerente.
 *
 * @details A senha é composta por 5 caracteres e deve seguir as seguintes regras de formato:
 * - O comprimento deve ser exatamente 5 caracteres.
 * - O caractere pode ser letra (a-z ou A-Z), dígito (0-9) ou caractere especial (!"#$%&?).
 * - Deve existir pelo menos uma letra minúscula (a-z), uma letra maiúscula (A-Z), um dígito (0-9) e um caractere especial.
 * - Letra não pode ser seguida por letra.
 * - Dígito não pode ser seguido por dígito.
 */
class Senha{
    private:
        string valor;
        void validar(const string& valor); // CORREÇÃO: Usar const string& no método privado
    public:
        // setValor e getValor já estão corretos.
        void setValor(const string& novoValor); // CORREÇÃO: Usar const string& no setValor
        string getValor() const;
};

inline string Senha::getValor() const {
    return valor;
}

/**
 * @class Endereco
 * @brief Domínio para armazenar e validar o Endereço residencial ou de um Hotel.
 *
 * @details Esta classe armazena uma string que representa um endereço e deve seguir as seguintes regras de formato:
 * 1. Tamanho: Deve conter entre 5 e 30 caracteres.
 * 2. Caracteres Permitidos: Pode conter letras (a-z, A-Z), dígitos (0-9), vírgula (,), ponto final (.) e espaço em branco ( ).
 * 3. Restrições de Posição/Sequência:
 * - O primeiro e o último caractere não podem ser vírgula, ponto ou espaço em branco.
 * - Vírgula e ponto não podem ser seguidos por vírgula ou ponto.
 * - Espaço em branco deve ser seguido por letra ou dígito.
 */
class Endereco {
    private:
        string valor;
        void validar(const string& valor); // CORREÇÃO: Usar const string& no método privado
    public:
        void setValor(const string& novoValor); // CORREÇÃO: Usar const string& no setValor
        string getValor() const;
};

inline string Endereco::getValor() const {
    return valor;
}

// ====================================================================
// ---------------------- Marcel (DINHEIRO, CARTAO, NOME) --------------------
// ====================================================================

class Dinheiro{
    private:
        int valor; // CORREÇÃO: Tipo INT é necessário para armazenar em centavos.
        void validar(const string& valor); // CORREÇÃO: Usar const string&
    public:
        void setValor(const string& valor); // CORREÇÃO: Usar const string&
        string getValor() const; // CORREÇÃO: O get deve retornar o valor formatado (string) ou o valor inteiro (int)
                                 // Mantendo STRING temporariamente, mas o requisito favorece INT para operações internas.
};

class Cartao{
    private:
        string valor;
        void validar(const string& valor); // CORREÇÃO: Usar const string&
    public:
        void setValor(const string& valor); // CORREÇÃO: Usar const string& e padronizar nome do método
        string getValor() const;
};

inline string Cartao::getValor() const{
    return this->valor;
}

class Nome{
    private:
        string valor;
        void validar(const string& valor); // CORREÇÃO: Usar const string&
    public:
    void setValor(const string& valor); // CORREÇÃO: Usar const string& e padronizar nome do parâmetro
    string getValor() const;
};

inline string Nome::getValor() const{
    return this->valor;
}

// ====================================================================
// ------------------- Duda (CAPACIDADE, DATA, TELEFONE) ------------------
// ====================================================================

/**
 * @class Capacidade
 * @brief Gerencia a capacidade máxima de pessoas em um quarto.
 * @details A classe armazena um valor inteiro curto (unsigned short)
 * que determina a capacidade de pessoas em um quarto, podendo ser de 1 a 4.
 */
class Capacidade {
private:
    static const int LIMITE_INFERIOR = 1;
    static const int LIMITE_SUPERIOR = 4;
    unsigned short capacidade;
    void validar(unsigned short capacidade) const;

public:
    /**
     * @brief Define a capacidade máxima de pessoas no quarto.
     * @details O metodo valida se o valor short fornecido está dentro do intervalo
     * permitido (1 a 4). Se estiver fora, lança uma exceção e se for valido
     * atualiza o atributo capacidade.
     *
     * @param capacidade Novo valor da capacidade do quarto entre 1 a 4 pessoas.
     * @throws out_of_range Se o valor estiver fora dos limites, sendo menor que 1 ou maior que 4.
     */
   void setValor(unsigned short capacidade); // CORREÇÃO: Padronizar nome do método (setValor) e remover ; extra

    /**
     * @brief Retorna a capacidade atual do quarto.
     * @details o Metodo retorna o valor armazenado no atributo capacidade
     * sem realizar validações ou modificações.
     * @return Valor da capacidade.
     */
    unsigned short getValor() const; // CORREÇÃO: Padronizar nome do método (getValor)
};

inline unsigned short Capacidade::getValor() const { // CORREÇÃO: Padronizar nome do método
    return capacidade;
}

/**
* @class Data
* @brief Representa uma data formada por dia, mês e ano
* @details A classe valida e armazena uma data, garantindo o formato do dia (1 a 31),
* do mês ( no formato de texto com as trẽs primeiraas letras do mês maíusculas
* e o ano (entre 2000 e 2999) estejam da forma correta.
*/
class Data {
private:
    unsigned short dia;
    string mes;
    unsigned short ano;

    static const int ANO_MIN = 2000;
    static const int ANO_MAX = 2999;

    void validar(unsigned short dia, const std::string &mes, unsigned short ano) const;
    bool ehBissexto(unsigned short ano) const;
    unsigned short diasNoMes(const string &mes, unsigned short ano) const;
    unsigned short mesParaIndice(const string &mes) const;
    bool mesValido(const string &mes) const;
    string letraMaiuscula(const string &s) const;

public:
    // setValor já está correto.
    void setValor(unsigned short dia, const std::string &mes, unsigned short ano);

    // get* já estão corretos.
    unsigned short getDia() const;
    string getMes() const;
    unsigned short getAno() const;
};

inline unsigned short Data::getDia() const {
    return dia;
}

inline string Data::getMes() const {
    return mes;
}

inline unsigned short Data::getAno() const {
    return ano;
}

/**
 * @class Telefone
 * @brief Define o número de telefone do Hotel.
 * @details A classe define o número de telefone do hotel seguindo um padrão de
 * formato (+DDDDDDDDDDDDDDDD), com 16 caracteres no total.
 */
class Telefone {
private:
    string telefone;
    bool validar(const string &telefone);

public:
    void setValor(const string &telefone); // CORREÇÃO: Padronizar nome do método (setValor)

    string getValor() const; // CORREÇÃO: Padronizar nome do método (getValor)
};

inline string Telefone::getValor() const { // CORREÇÃO: Padronizar nome do método
    return telefone;
}

// ====================================================================
// ---------------- Gustavo (CODIGO, EMAIL, RAMAL) --------------------
// ====================================================================

class Codigo {
    private:
        std::string codigo;
        static const int TAMANHO = 10;
        void validar(const std::string& codigo); // CORREÇÃO: Passar por const reference

    public:
        void setValor(const std::string& codigo); // CORREÇÃO: Padronizar nome (setValor) e assinatura
        std::string getValor() const; // CORREÇÃO: Padronizar nome (getValor)
        // Construtor removido para evitar problemas com a Entidade.
};

inline std::string Codigo::getValor() const { // CORREÇÃO: Padronizar nome
    return codigo;
}

class EMAIL {
    private:
        std::string email;
        static const int MAX_PARTE_LOCAL = 64;
        static const int MAX_DOMINIO = 255;
        void validar(const std::string& email); // CORREÇÃO: Passar por const reference

    public:
        void setValor(const std::string& email); // CORREÇÃO: Padronizar nome (setValor) e assinatura
        std::string getValor() const; // CORREÇÃO: Padronizar nome (getValor)
        // Construtor removido.
};

inline std::string EMAIL::getValor() const { // CORREÇÃO: Padronizar nome
    return email;
}

class Ramal {
    private:
        unsigned short ramal; // CORREÇÃO: Mudar tipo para unsigned short
        void validar(unsigned short ramal); // CORREÇÃO: Mudar tipo de parâmetro
    public:
        void setValor(unsigned short ramal); // CORREÇÃO: Padronizar nome e tipo
        unsigned short getValor() const; // CORREÇÃO: Padronizar nome e tipo
        // Construtor removido.
};

inline unsigned short Ramal::getValor() const { // CORREÇÃO: Padronizar nome e tipo
    return ramal;
}

#endif // DOMINIOS_HPP_INCLUDED
