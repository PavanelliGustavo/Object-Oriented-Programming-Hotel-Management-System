#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

#include <stdexcept>
#include <string>
#include <cctype>
#include <iostream>

using namespace std;

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

        /**
         * @brief Atribui um novo valor ao número do quarto, garantindo a validade.
         *
         * @param novoValor O valor inteiro (entre 1 e 999) a ser atribuído.
         * @throw std::invalid_argument Exceção  lançada caso o valor esteja fora do intervalo permitido (1 a 999).
         */

        void setValor(int novoValor);

        /**
         * @brief Retorna o valor atual do número do quarto.
         *
         * @return O número do quarto armazenado (int).
         */

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
        void validar(string valor);
    public:

        /**
         * @brief Atribui um novo valor de senha, validando o formato.
         *
         * @param novoValor A string contendo os 5 caracteres da senha a ser validada.
         * @throw std::invalid_argument Exceção lançada se o formato da senha for inválido (tamanho, composição ou sequência incorreta).
         */

        void setValor(string novoValor);

        /**
         * @brief Retorna o valor atualda senha armazenada.
         *
         * @return A senha (string).
         */

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
        void validar(string valor);
    public:

        /**
         * @brief Atribui um novo valor de endereço, validando o formato.
         *
         * @param novoEndereco A string contendo o endereço a ser validado.
         * @throw std::invalid_argument Exceção lançada se o formato do endereço for inválido (e.g., tamanho, caractere não permitido ou sequência incorreta).
         */

        void setValor(string novoValor);

        /**
         * @brief Retorna o valor atual do endereço armazenado.
         *
         * @return O endereço (string).
         */

        string getValor() const;
};

inline string Endereco::getValor() const {
    return valor;
}

// ---------------------- Marcel --------------------
class Dinheiro{
    private:
        int valor;
        void validar(string valor);
    public:
        void setValor(string valor);
        string getValor() const;
};

class Cartao{
    private:
        string valor;
        void validar(string valor);
    public:
        void setValor(string valor);
        string getValor() const;
};

inline string Cartao::getValor() const{
    return this->valor;
}

class Nome{
    private:
        string valor;
        void validar(string valor);
    public:
    void setValor(string Valor);
    string getValor() const;
};

inline string Nome::getValor() const{
    return this->valor;
}

// ------------------- Duda ------------------
/**
 * @class Capacida
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
   void setCapacidade(unsigned short capacidade);;

    /**
     * @brief Retorna a capacidade atual do quarto.
     * @details o Metodo retorna o valor armazenado no atributo capacidade
     * sem realizar validações ou modificações.
     * @return Valor da capacidade.
     */
    unsigned short getCapacidade() const;
};

inline unsigned short Capacidade::getCapacidade() const {
    return capacidade;
}

/**
* @class Data
* @brief Representa uma data formada por dia, mês e ano
* @details A classe valida e armazena uma data, garantindo o formato do dia (1 a 31),
* do mês ( no formato de texto com as trẽs primeiraas letras do mês maíusculas
* e o ano (entre 2000 e 2999)  estejam  da forma correta.
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

    /**
     * @brief Define uma nova data (dia, mês e ano), validando o formato.
     * @details Este método verifica se o ano está dentro dos limites de 2000 a 2999
     * e se o mês é uma abreviação válida (ex: JAN,FEV,MAR),se estiver em minusculo ele
     * armazena em maisculo de qualquer forma.
     * Em seguida, verifica se o dia está dentro do intervalo permitido
     * para o mês e ano especificados, incluindo a validação de anos bissextos.
     *
     * @param dia O valor do dia (entre 1 e o máximo para o mês/ano).
     * @param mes A abreviação de três letras do mês, (ex: JAN, FEV, DEZ).
     * @param ano O ano (entre 2000 e 2999).
     *
     * @throws out_of_range Se o ano ou o dia estiverem fora dos limites válidos.
     * @throws invalid_argument Se o formato do mês for inválido.
     *
     */
    void setValor(unsigned short dia, const std::string &mes, unsigned short ano);

    /**
     * @brief Retorna o dia da data.
     * @details Fornece acesso ao valor do dia armazenado na instância.
     * @return O valor do dia.
     */
    unsigned short getDia() const;
    /**
     * @brief Retorna o mês da data.
     * @details Fornece acesso ao mês da data, que está sempre no formato de
     * 3 letras maiúsculas (ex: "JAN").
     * @return O mês da data em formato de 3 letras maiúsculas.
     */
    string getMes() const;
    /**
     * @brief Retorna o ano da data.
     * @details Fornece acesso ao valor do ano armazenado.
     * @return O valor do ano.
     */
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
    /**
     * @brief Define um número de telefone, validando o formato.
     * @details Este método verifica se o telefone está no formato válido
     * (+DDDDDDDDDDDDDDDD), ou seja, iniciando com o caractere '+' seguido de 15 dígitos numéricos.
     * Caso o valor esteja vazio, tenha tamanho incorreto, não comece com '+'
     * ou contenha caracteres que não sejam dígitos, uma exceção é lançada.
     *
     * @param telefone O número de telefone a ser definido (ex: "+5511999999999").
     * @throws invalid_argument Se o formato do telefone for inválido.
     */
    void setTelefone(const string &telefone);

    /**
     * @brief Retorna o telefone do hotel.
     * @return O número de telefone no formato válido.
     */
    string getTelefone() const;
};

inline string Telefone::getTelefone() const {
    return telefone;
}

//---------------- Gustavo --------------------
class Codigo {
    private:
        std::string codigo;
        static const int TAMANHO = 10;
        void validar(std::string& codigo);

    public:
        void setCodigo(std::string& codigo);
        std::string getCodigo() const;
        Codigo(std::string& codigo);
};

inline std::string Codigo::getCodigo() const {
    return codigo;
}

class EMAIL {
    private:
        std::string email;
        static const int MAX_PARTE_LOCAL = 64;
        static const int MAX_DOMINIO = 255;
        void validar(std::string& email);

    public:
        void setEmail(std::string& email);
        std::string getEmail() const;
        EMAIL(std::string& email);
};

inline std::string EMAIL::getEmail() const {
    return email;
}

class Ramal {
    private:
        char ramal;
        void validar(int& ramal);
    public:
        void setRamal(int& ramal);
        char getRamal() const;
        Ramal(int& ramal);
};

inline char Ramal::getRamal() const {
    return ramal;
}

#endif // DOMINIOS_HPP_INCLUDED
