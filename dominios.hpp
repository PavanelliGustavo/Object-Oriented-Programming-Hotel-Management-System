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
 */
class Numero {
    private:
        int valor;
        void validar(int valor);
    public:
        /**
         * @brief Define o número do quarto.
         * @param novoValor Inteiro entre 1 e 999.
         * @throw std::invalid_argument Se o valor estiver fora do intervalo.
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
 * @details A senha deve seguir as seguintes regras:
 * - Exatamente 5 caracteres.
 * - Caracteres permitidos: a-z, A-Z, 0-9, ! " # $ % & ?.
 * - Deve conter pelo menos uma letra minúscula, uma maiúscula, um dígito e um caractere especial.
 * - Não permite caracteres repetidos de tipos sequenciais (ex: letra seguida de letra).
 */
class Senha {
    private:
        string valor;
        void validar(const string& valor);
    public:
        /**
         * @brief Define a senha.
         * @param novoValor String contendo a senha.
         * @throw std::invalid_argument Se a senha não atender aos critérios de complexidade.
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
 * - Letras, dígitos, vírgula, ponto e espaço.
 * - Restrições de posição para pontuação e espaços.
 */
class Endereco {
    private:
        string valor;
        void validar(const string& valor);
    public:
        void setValor(const string& novoValor);
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
 * - O armazenamento interno é realizado em inteiros (centavos) para evitar erros de arredondamento de ponto flutuante.
 */
class Dinheiro {
    private:
        long long valor; // Armazena em centavos para precisão
        void validar(long long valor);
    public:
        /**
         * @brief Define o valor monetário.
         * @details Recebe um valor double que será convertido para centavos internamente.
         * @param valor Valor em double (ex: 100.50).
         * @throw std::invalid_argument Se fora do intervalo 0.00 a 1,000,000.00.
         */
        void setValor(double valor);

        /**
         * @brief Retorna o valor monetário.
         * @return double Valor em formato de ponto flutuante.
         */
        double getValor() const;
};

/**
 * @class Cartao
 * @brief Domínio para representar um número de cartão de crédito.
 *
 * @details Regras de formato:
 * - Exatamente 16 dígitos.
 * - Validação através do algoritmo de Luhn para verificação do dígito verificador.
 */
class Cartao {
    private:
        string valor;
        void validar(const string& valor);
    public:
        /**
         * @brief Define o número do cartão.
         * @param valor String contendo os 16 dígitos.
         * @throw std::invalid_argument Se não tiver 16 dígitos ou falhar no teste de Luhn.
         */
        void setValor(const string& valor);

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
 * - Pode conter letras (a-z, A-Z), dígitos (0-9), vírgula, ponto ou espaço.
 * - Regras estritas de pontuação (vírgula não seguida de ponto, etc).
 * - Primeiro caracter deve ser letra maiúscula (para nomes próprios tipicamente, embora o PDF permita dígitos na regra geral, a convenção de classes costuma forçar capitalização).
 */
class Nome {
    private:
        string valor;
        void validar(const string& valor);
    public:
        /**
         * @brief Define o nome.
         * @param valor String do nome.
         * @throw std::invalid_argument Se o formato for inválido.
         */
        void setValor(const string& valor);

        string getValor() const;
};

inline string Nome::getValor() const {
    return this->valor;
}

/**
 * @class Capacidade
 * @brief Gerencia a capacidade máxima de pessoas em um quarto.
 *
 * @details Valores permitidos: 1, 2, 3 ou 4.
 */
class Capacidade {
    private:
        unsigned short capacidade;
        void validar(unsigned short capacidade) const;
    public:
        /**
         * @brief Define a capacidade.
         * @param capacidade Valor entre 1 e 4.
         * @throw std::invalid_argument Se fora do intervalo.
         */
        void setValor(unsigned short capacidade);
        unsigned short getValor() const;
};

inline unsigned short Capacidade::getValor() const {
    return capacidade;
}

/**
 * @class Data
 * @brief Representa uma data (DD-MMM-AAAA).
 *
 * @details Valida dias (1-31), meses (JAN, FEV...) e anos (2000-2999),
 * considerando anos bissextos.
 */
class Data {
    private:
        unsigned short dia;
        string mes;
        unsigned short ano;

        static const int ANO_MIN = 2000;
        static const int ANO_MAX = 2999;

        string letraMaiuscula(const string &s) const;
        unsigned short mesParaIndice(const string &mes) const;
        bool ehBissexto(unsigned short ano) const;
        unsigned short diasNoMes(const string &mes, unsigned short ano) const;
        bool mesValido(const string &mes) const;

        void validar(unsigned short dia, const string &mes, unsigned short ano) const;
        // Métodos auxiliares de validação devem ser privados ou estar apenas no .cpp

    public:
        /**
         * @brief Define a data.
         * @param dia Dia (1-31).
         * @param mes Mês (formato de 3 letras maiúsculas: JAN, FEV...).
         * @param ano Ano (2000-2999).
         * @throw std::invalid_argument Se a data for inválida (ex: 30 de FEV).
         */
        void setValor(unsigned short dia, const string &mes, unsigned short ano);

        unsigned short getDia() const;
        string getMes() const;
        unsigned short getAno() const;
};

inline unsigned short Data::getDia() const { return dia; }
inline string Data::getMes() const { return mes; }
inline unsigned short Data::getAno() const { return ano; }

/**
 * @class Telefone
 * @brief Define o número de telefone.
 *
 * @details Formato: +DDDDDDDDDDDDDD (sinal de mais seguido de 14 dígitos, totalizando 15 caracteres de acordo com padrão comum, ou conforme especificado na tabela).
 * Observação: A tabela do PDF diz "+DDDDDDDDDDDDDD" (15 caracters total ou + seguido de D's). Vamos assumir a validação exata da string.
 */
class Telefone {
    private:
        string telefone;
        void validar(const string &telefone);
    public:
        void setValor(const string &telefone);
        string getValor() const;
};

inline string Telefone::getValor() const {
    return telefone;
}

/**
 * @class Codigo
 * @brief Domínio para códigos de identificação (PK).
 *
 * @details Regras de formato:
 * - Exatamente 10 caracteres.
 * - Cada caractere deve ser letra (a-z) ou dígito (0-9).
 */
class Codigo {
    private:
        string codigo;
        static const int TAMANHO = 10;
        void validar(const string& codigo);
    public:
        /**
         * @brief Define o código único.
         * @param codigo String de 10 caracteres alfanuméricos.
         * @throw std::invalid_argument Se tamanho ou conteúdo forem inválidos.
         */
        void setValor(const string& codigo);

        string getValor() const;
};

inline string Codigo::getValor() const {
    return codigo;
}

/**
 * @class EMAIL
 * @brief Domínio para endereços de e-mail.
 *
 * @details Formato: parte-local@domínio.
 * - Parte local: até 64 chars, letras, dígitos, ponto, hífen. Não pode iniciar/terminar com ponto/hífen.
 * - Domínio: até 255 chars, partes separadas por ponto, sem hífens no início/fim.
 */
class EMAIL {
    private:
        string email;
        static const int MAX_PARTE_LOCAL = 64;
        static const int MAX_DOMINIO = 255;
        void validar(const string& email);
    public:
        /**
         * @brief Define o endereço de email.
         * @param email String no formato local@dominio.
         * @throw std::invalid_argument Se o formato estiver incorreto.
         */
        void setValor(const string& email);

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
        void validar(unsigned short ramal);
    public:
        /**
         * @brief Define o número do ramal.
         * @param ramal Inteiro entre 0 e 50.
         * @throw std::invalid_argument Se fora do intervalo.
         */
        void setValor(unsigned short ramal);

        unsigned short getValor() const;
};

inline unsigned short Ramal::getValor() const {
    return ramal;
}

#endif // DOMINIOS_HPP_INCLUDED
