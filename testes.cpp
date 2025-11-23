#include "testes.hpp"
#include <iostream>

using namespace std;

// Definições das constantes globais
const string TUSenha::VALOR_VALIDO_SENHA = "A1!b#";
const string TUSenha::VALOR_INVALIDO_SENHA = "AA1!#";
// Note: As constantes de TUNumero e TUPessoa também precisariam ser definidas aqui ou no .hpp.

// ... Implementação de TUNumero e TUPessoa (anteriormente fornecidas) ...


// ====================================================================
// 3. IMPLEMENTAÇÃO: TESTE DE UNIDADE DO DOMÍNIO SENHA (TUSenha)
// ====================================================================

void TUSenha::setUp() {
    dominio = new Senha();
    estado = SUCESSO;
}

void TUSenha::tearDown() {
    delete dominio;
}

void TUSenha::testarCenarioValorValido() {
    try {
        dominio->setValor(VALOR_VALIDO_SENHA);

        // Verifica se o valor atribuído é o mesmo recuperado
        if (dominio->getValor() != VALOR_VALIDO_SENHA) {
            estado = FALHA;
            cerr << "ERRO: TUSenha (Valido): getValor nao retornou o valor esperado." << endl;
        }
    } catch (const invalid_argument& excecao) {
        // Se lançar exceção para valor válido, falha
        estado = FALHA;
        cerr << "ERRO: TUSenha (Valido): Excecao lancada indevidamente: " << excecao.what() << endl;
    }
}

void TUSenha::testarCenarioValorInvalido() {
    try {
        // Tenta atribuir valor que viola a regra de sequência (AA)
        dominio->setValor(VALOR_INVALIDO_SENHA);

        // Se a exceção *não* for lançada, o teste falha
        estado = FALHA;
        cerr << "ERRO: TUSenha (Invalido): Excecao nao lancada para valor invalido." << endl;

    } catch (const invalid_argument& excecao) {
        // Se a exceção for lançada, o teste é um SUCESSO.
    } catch (...) {
        estado = FALHA;
        cerr << "ERRO: TUSenha (Invalido): Excecao de tipo inesperado lancada." << endl;
    }
}

int TUSenha::run() {
    setUp();
    testarCenarioValorValido();
    testarCenarioValorInvalido();
    tearDown();
    return estado;
}


// ====================================================================
// 4. IMPLEMENTAÇÃO: TESTE DE UNIDADE DA ENTIDADE GERENTE (TUGerente)
// ====================================================================

void TUGerente::setUp() {
    entidade = new Gerente();
    estado = SUCESSO;
}

void TUGerente::tearDown() {
    delete entidade;
}

void TUGerente::testarCenarioSucesso() {
    // 1. Cria objetos Domínio
    try {
        // Valores de Domínio a serem testados
        EMAIL emailValido;
        emailValido.setValor("gerente.teste@uni.br");

        Senha senhaValida;
        senhaValida.setValor(TUSenha::VALOR_VALIDO_SENHA);

        Ramal ramalValido;
        ramalValido.setValor(30);

        // 2. Atribui os Domínios à Entidade (incluindo os herdados de Pessoa)
        entidade->setEmail(emailValido);
        entidade->setSenha(senhaValida);
        entidade->setRamal(ramalValido);

        // 3. Verifica a recuperação dos atributos específicos
        if (entidade->getSenha().getValor() != TUSenha::VALOR_VALIDO_SENHA) {
            estado = FALHA;
            cerr << "ERRO: TUGerente: Atribuicao/Recuperacao de Senha falhou." << endl;
        }

        if (entidade->getRamal().getValor() != 30) {
            estado = FALHA;
            cerr << "ERRO: TUGerente: Atribuicao/Recuperacao de Ramal falhou." << endl;
        }

    } catch (const invalid_argument& e) {
        estado = FALHA;
        cerr << "ERRO: TUGerente: Falha na validacao do Dominio durante o setup: " << e.what() << endl;
    }
}

int TUGerente::run() {
    setUp();
    testarCenarioSucesso();
    tearDown();
    return estado;
}
