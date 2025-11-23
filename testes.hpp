#ifndef TESTES_HPP_INCLUDED
#define TESTES_HPP_INCLUDED

#include "dominios.hpp"
#include "entidades.hpp"
#include <stdexcept>
#include <string> // Necessário para as constantes de string

// Constantes de resultado global para os testes
const static int SUCESSO = 0;
const static int FALHA = -1;

// ====================================================================
// 1. TESTE DE UNIDADE DE DOMÍNIO
// ====================================================================

/**
 * @class TUDominio
 * @brief Classe base abstrata para testes de unidade de Domínios.
 * @details Define o contrato para todos os testes de domínio: verificar um valor
 * válido e um valor inválido.
 */
class TUDominio {
private:
    virtual void testarCenarioValorValido() = 0;
    virtual void testarCenarioValorInvalido() = 0;

public:
    virtual int run() = 0;
    virtual ~TUDominio() {}
};


/**
 * @class TUNumero
 * @brief Teste de Unidade específico para o Domínio Numero (001 a 999).
 */
class TUNumero : public TUDominio {
private:
    const static int VALOR_VALIDO = 42;
    const static int VALOR_INVALIDO = 1000;

    Numero* dominio;
    int estado;

    void setUp();
    void tearDown();
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();

public:
    int run();
};


/**
 * @class TUSenha
 * @brief Teste de Unidade específico para o Domínio Senha.
 * @details Verifica tamanho, composição mista e regras de sequência (letra/dígito).
 */
class TUSenha : public TUDominio {
private:
    Senha* dominio;
    int estado;

    void setUp();
    void tearDown();
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();

public:
    // Senha válida: 5 caracteres, mista, sem repetição de tipo. Ex: A1!b#
    const static string VALOR_VALIDO_SENHA;
    // Senha inválida: Falha na sequência (Duas letras seguidas). Ex: AA1!#
    const static string VALOR_INVALIDO_SENHA;
    int run();
};


/**
 * @class TUEndereco
 * @brief Teste de Unidade específico para o Domínio Endereco.
 * @details Verifica o comprimento (5-30) e as restrições de sequência e caracteres.
 */
class TUEndereco : public TUDominio {
private:
    // Exemplo: Rua Apto 101. (5 a 30 caracteres, sem especial no início/fim)
    const static string VALOR_VALIDO_ENDERECO;
    // Exemplo: Começa com espaço, o que é inválido.
    const static string VALOR_INVALIDO_ENDERECO;

    Endereco* dominio;
    int estado;

    void setUp();
    void tearDown();
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();

public:
    int run();
};


// ====================================================================
// 2. TESTE DE UNIDADE DE ENTIDADE
// ====================================================================

/**
 * @class TUPessoa
 * @brief Teste de Unidade específico para a Entidade Pessoa.
 * @details Verifica a correta atribuição e recuperação dos Domínios Nome e EMAIL.
 */
class TUPessoa {
private:
    const static int ESTADO_INICIAL = 0;

    Pessoa* entidade;
    int estado;

    void setUp();
    void tearDown();
    void testarCenarioSucesso();

public:
    int run();
};


/**
 * @class TUGerente
 * @brief Teste de Unidade específico para a Entidade Gerente.
 * @details Verifica a correta atribuição e recuperação de Senha e Ramal (atributos derivados).
 */
class TUGerente {
private:
    const static int ESTADO_INICIAL = 0;

    Gerente* entidade;
    int estado;

    void setUp();
    void tearDown();
    void testarCenarioSucesso();

public:
    int run();
};

#endif // TESTES_HPP_INCLUDED
