#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

/**
 * @class Numero
 * @brief Domínio para representar o Número do Quarto em um Hotel.
 *
 * @details Esta classe armazena um valor inteiro que representa o número do quarto.
 * O formato válido, de acordo com as regras de negócio, deve ser um valor entre 1 e 999 (001 a 999).
 * A classe garante a validade do seu valor interno através do método validar.
 */
class Numero {
    private:
        int valor;
        /**
         * @brief Valida o número do quarto.
         * @param valor Inteiro a ser validado.
         * @throw std::invalid_argument Se o valor estiver fora do intervalo [1, 999].
         */
        void validar(int valor);
    public:
        /**
         * @brief Define o número do quarto.
         * @param novoValor Inteiro entre 1 e 999.
         * @throw std::invalid_argument Se o valor for inválido.
         */
        void setValor(int novoValor);

        /**
         * @brief Retorna o número do quarto.
         * @return int Valor do número.
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
 * @details A senha deve seguir regras estritas de segurança:
 * - Exatamente 5 caracteres.
 * - Caracteres permitidos: a-z, A-Z, 0-9, ! " # $ % & ?.
 * - Deve conter pelo menos uma letra minúscula, uma maiúscula, um dígito e um caractere especial.
 * - Não permite caracteres repetidos de tipos sequenciais (ex: letra seguida de letra).
 */
class Senha {
    private:
        string valor;
        /**
         * @brief Valida a senha conforme as regras de complexidade.
         * @param valor String da senha.
         * @throw std::invalid_argument Se a senha não atender aos critérios.
         */
        void validar(const string& valor);
    public:
        /**
         * @brief Define a senha.
         * @param novoValor String contendo a senha.
         * @throw std::invalid_argument Se a senha for inválida.
         */
        void setValor(const string& novoValor);

        /**
         * @brief Retorna a senha armazenada.
         * @return string Senha.
         */
        string getValor() const;
};

inline string Senha::getValor() const {
    return valor;
}

/**
 * @class Endereco
 * @brief Domínio para armazenar e validar o Endereço.
 *
 * @details Regras de formato:
 * - 5 a 30 caracteres.
 * - Caracteres: Letras, dígitos, vírgula, ponto e espaço.
 * - Restrições de posição para pontuação e espaços (ex: não começar com espaço).
 */
class Endereco {
    private:
        string valor;
        /**
         * @brief Valida o formato do endereço.
         * @param valor String do endereço.
         * @throw std::invalid_argument Se o formato for inválido.
         */
        void validar(const string& valor);
    public:
        /**
         * @brief Define o endereço.
         * @param novoValor String do endereço.
         * @throw std::invalid_argument Se o valor for inválido.
         */
        void setValor(const string& novoValor);

        /**
         * @brief Retorna o endereço armazenado.
         * @return string Endereço.
         */
        string getValor() const;
};

inline string Endereco::getValor() const {
    return valor;
}

/**
 * @class Dinheiro
 * @brief Domínio para representar valores monetários.
 *
 * @details Regras de negócio:
 * - Valor entre 0,01 e 1.000.000,00.
 * - O armazenamento interno é realizado em inteiros (centavos - long long) para evitar erros de arredondamento típicos de ponto flutuante.
 */
class Dinheiro {
    private:
        long long valor; // Armazena em centavos para precisão
        /**
         * @brief Valida se o valor em centavos está dentro do limite permitido.
         * @param valor Valor em centavos.
         * @throw std::invalid_argument Se fora do intervalo.
         */
        void validar(long long valor);
    public:
        /**
         * @brief Define o valor monetário a partir de um double.
         * @details Converte o valor double para centavos internamente.
         * @param valor Valor em double (ex: 100.50).
         * @throw std::invalid_argument Se fora do intervalo permitido.
         */
        void setValor(double valor);

        /**
         * @brief Retorna o valor monetário convertido para double.
         * @return double Valor formatado em reais.
         */
        double getValor() const;
};

/**
 * @class Cartao
 * @brief Domínio para representar um número de cartão de crédito.
 *
 * @details Regras de formato:
 * - Exatamente 16 dígitos numéricos.
 * - Validação através do algoritmo de Luhn para verificação do dígito verificador.
 */
class Cartao {
    private:
        string valor;
        /**
         * @brief Valida o número do cartão usando o algoritmo de Luhn.
         * @param valor String com 16 dígitos.
         * @throw std::invalid_argument Se inválido ou falhar no teste de Luhn.
         */
        void validar(const string& valor);
    public:
        /**
         * @brief Define o número do cartão.
         * @param valor String contendo os 16 dígitos.
         * @throw std::invalid_argument Se o formato for inválido.
         */
        void setValor(const string& valor);

        /**
         * @brief Retorna o número do cartão.
         * @return string Número do cartão.
         */
        string getValor() const;
};

inline string Cartao::getValor() const {
    return this->valor;
}

/**
 * @class Nome
 * @brief Domínio para nomes de pessoas ou hotéis.
 *
 * @details Regras de formato:
 * - Texto com 5 a 30 caracteres.
 * - Primeira letra maiúscula.
 * - Regras estritas de pontuação e espaçamento.
 */
class Nome {
    private:
        string valor;
        /**
         * @brief Valida o nome conforme regras de formatação.
         * @param valor String do nome.
         * @throw std::invalid_argument Se o formato for inválido.
         */
        void validar(const string& valor);
    public:
        /**
         * @brief Define o nome.
         * @param valor String do nome.
         * @throw std::invalid_argument Se o formato for inválido.
         */
        void setValor(const string& valor);

        /**
         * @brief Retorna o nome armazenado.
         * @return string Nome.
         */
        string getValor() const;
};

inline string Nome::getValor() const {
    return this->valor;
}

/**
 * @class Capacidade
 * @brief Gerencia a capacidade máxima de pessoas em um quarto.
 *
 * @details Valores permitidos: 1, 2, 3 ou 4 pessoas.
 */
class Capacidade {
    private:
        unsigned short capacidade;
        /**
         * @brief Valida se a capacidade está entre 1 e 4.
         * @param capacidade Valor a ser validado.
         * @throw std::invalid_argument Se fora do intervalo.
         */
        void validar(unsigned short capacidade) const;
    public:
        /**
         * @brief Define a capacidade.
         * @param capacidade Valor entre 1 e 4.
         * @throw std::invalid_argument Se fora do intervalo.
         */
        void setValor(unsigned short capacidade);

        /**
         * @brief Retorna a capacidade.
         * @return unsigned short Valor da capacidade.
         */
        unsigned short getValor() const;
};

inline unsigned short Capacidade::getValor() const {
    return capacidade;
}

/**
 * @class Data
 * @brief Representa uma data no formato DD-MMM-AAAA.
 *
 * @details Valida dias (1-31), meses (JAN, FEV...) e anos (2000-2999),
 * considerando anos bissextos e a quantidade de dias de cada mês.
 */
class Data {
    private:
        unsigned short dia;
        string mes;
        unsigned short ano;

        static const int ANO_MIN = 2000;
        static const int ANO_MAX = 2999;

        // Métodos auxiliares de validação (internos)
        string letraMaiuscula(const string &s) const;
        unsigned short mesParaIndice(const string &mes) const;
        bool ehBissexto(unsigned short ano) const;
        unsigned short diasNoMes(const string &mes, unsigned short ano) const;
        bool mesValido(const string &mes) const;

        /**
         * @brief Valida a data completa (dia, mês e ano).
         * @param dia Dia do mês.
         * @param mes Mês em formato texto (3 letras).
         * @param ano Ano com 4 dígitos.
         * @throw std::invalid_argument ou std::out_of_range Se a data for inválida.
         */
        void validar(unsigned short dia, const string &mes, unsigned short ano) const;

    public:
        /**
         * @brief Define a data.
         * @param dia Dia (1-31).
         * @param mes Mês (JAN, FEV, etc).
         * @param ano Ano (2000-2999).
         * @throw std::invalid_argument Se a data for inválida.
         */
        void setValor(unsigned short dia, const string &mes, unsigned short ano);

        /**
         * @brief Retorna o dia.
         * @return unsigned short Dia.
         */
        unsigned short getDia() const;

        /**
         * @brief Retorna o mês.
         * @return string Mês (3 letras maiúsculas).
         */
        string getMes() const;

        /**
         * @brief Retorna o ano.
         * @return unsigned short Ano.
         */
        unsigned short getAno() const;
};

inline unsigned short Data::getDia() const { return dia; }
inline string Data::getMes() const { return mes; }
inline unsigned short Data::getAno() const { return ano; }

/**
 * @class Telefone
 * @brief Define o número de telefone.
 *
 * @details Formato esperado: +DDDDDDDDDDDDDD (15 dígitos após o sinal de +).
 */
class Telefone {
    private:
        string telefone;
        /**
         * @brief Valida o formato do telefone.
         * @param telefone String do telefone.
         * @throw std::invalid_argument Se o formato for inválido.
         */
        void validar(const string &telefone);
    public:
        /**
         * @brief Define o número de telefone.
         * @param telefone String no formato +DD...
         * @throw std::invalid_argument Se inválido.
         */
        void setValor(const string &telefone);

        /**
         * @brief Retorna o telefone.
         * @return string Telefone.
         */
        string getValor() const;
};

inline string Telefone::getValor() const {
    return telefone;
}

/**
 * @class Codigo
 * @brief Domínio para códigos de identificação únicos (PK).
 *
 * @details Regras de formato:
 * - Exatamente 10 caracteres alfanuméricos (letras e números).
 */
class Codigo {
    private:
        string codigo;
        static const int TAMANHO = 10;
        /**
         * @brief Valida o código.
         * @param codigo String do código.
         * @throw std::invalid_argument Se tamanho ou conteúdo forem inválidos.
         */
        void validar(const string& codigo);
    public:
        /**
         * @brief Define o código.
         * @param codigo String de 10 caracteres.
         * @throw std::invalid_argument Se inválido.
         */
        void setValor(const string& codigo);

        /**
         * @brief Retorna o código.
         * @return string Código.
         */
        string getValor() const;
};

inline string Codigo::getValor() const {
    return codigo;
}

/**
 * @class EMAIL
 * @brief Domínio para endereços de e-mail.
 *
 * @details Formato padrão: parte-local@domínio.
 * Valida caracteres permitidos, posição de pontos e hífens, e tamanho máximo.
 */
class EMAIL {
    private:
        string email;
        static const int MAX_PARTE_LOCAL = 64;
        static const int MAX_DOMINIO = 255;
        /**
         * @brief Valida o email.
         * @param email String do email.
         * @throw std::invalid_argument Se o formato for inválido.
         */
        void validar(const string& email);
    public:
        /**
         * @brief Define o email.
         * @param email String do email.
         * @throw std::invalid_argument Se inválido.
         */
        void setValor(const string& email);

        /**
         * @brief Retorna o email.
         * @return string Email.
         */
        string getValor() const;
};

inline string EMAIL::getValor() const {
    return email;
}

/**
 * @class Ramal
 * @brief Domínio para ramais telefônicos internos.
 *
 * @details Intervalo válido: 0 a 50.
 */
class Ramal {
    private:
        unsigned short ramal;
        /**
         * @brief Valida o número do ramal.
         * @param ramal Valor a ser validado.
         * @throw std::invalid_argument Se fora do intervalo [0, 50].
         */
        void validar(unsigned short ramal);
    public:
        /**
         * @brief Define o número do ramal.
         * @param ramal Inteiro entre 0 e 50.
         * @throw std::invalid_argument Se inválido.
         */
        void setValor(unsigned short ramal);

        /**
         * @brief Retorna o ramal.
         * @return unsigned short Ramal.
         */
        unsigned short getValor() const;
};

inline unsigned short Ramal::getValor() const {
    return ramal;
}

#endif // DOMINIOS_HPP_INCLUDED
