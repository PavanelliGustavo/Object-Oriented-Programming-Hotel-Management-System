#ifndef TESTES_HPP_INCLUDED
#define TESTES_HPP_INCLUDED

#include "dominios.hpp"
#include "entidades.hpp"
#include <stdexcept>

// Constantes de resultado global para os testes
const static int SUCESSO = 0;
const static int FALHA = -1;

// ====================================================================
// 1. TESTE DE UNIDADE DE DOMÍNIO (TUNumero já existe)
// ====================================================================

/**
 * @class TUDominio
 * @brief Classe base abstrata para testes de unidade de Domínios.
 */
class TUDominio {
private:
    virtual void testarCenarioValorValido() = 0;
    virtual void testarCenarioValorInvalido() = 0;

public:
    virtual int run() = 0;
    virtual ~TUDominio() {}
};


// ... A classe TUNumero e suas declarações iriam aqui ...


/**
 * @class TUSenha
 * @brief Teste de Unidade específico para o Domínio Senha.
 * @details Verifica tamanho, composição mista e regras de sequência (letra/dígito).
 */
class TUSenha : public TUDominio {
private:
    // Senha válida: 5 caracteres, mista, sem repetição de tipo. Ex: A1!b#
    const static string VALOR_VALIDO_SENHA;
    // Senha inválida: Falha na sequência (Duas letras seguidas). Ex: Aa1!#
    const static string VALOR_INVALIDO_SENHA;

    Senha* dominio;
    int estado;

    void setUp();
    void tearDown();
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();

public:
    int run();
};


// ====================================================================
// 2. TESTE DE UNIDADE DE ENTIDADE (TUPessoa já existe)
// ====================================================================

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
