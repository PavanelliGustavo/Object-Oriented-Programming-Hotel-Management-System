#include "testes.hpp"
#include <iostream>

using namespace std;

// ====================================================================
// 0. DEFINIÇÕES DE CONSTANTES (PARA OS TESTES FALTANTES)
// ====================================================================

// Domínio Senha (já definido no .hpp)
const string TUSenha::VALOR_VALIDO_SENHA = "A1!b#";
const string TUSenha::VALOR_INVALIDO_SENHA = "AA1!#"; 

// Domínio Endereco
const string TUEndereco::VALOR_VALIDO_ENDERECO = "Rua Teste 101, Bairro X";
const string TUEndereco::VALOR_INVALIDO_ENDERECO = " Comeca com espaco"; // Invalido: começa com espaço

// Entidade Pessoa (Valores de setup)
const string VALOR_VALIDO_NOME = "Maria Silva";
const string VALOR_VALIDO_EMAIL = "maria.silva@teste.com";


// ====================================================================
// 1. IMPLEMENTAÇÃO: TESTE DE UNIDADE DO DOMÍNIO NUMERO (TUNumero)
// ====================================================================

void TUNumero::setUp() {
    dominio = new Numero();
    estado = SUCESSO;
}

void TUNumero::tearDown() {
    delete dominio;
}

void TUNumero::testarCenarioValorValido() {
    try {
        dominio->setValor(VALOR_VALIDO);
        if (dominio->getValor() != VALOR_VALIDO) {
            estado = FALHA;
            cerr << "ERRO: TUNumero (Valido): getValor nao retornou o valor esperado." << endl;
        }
    } catch (const invalid_argument& excecao) {
        estado = FALHA;
        cerr << "ERRO: TUNumero (Valido): Excecao lancada indevidamente: " << excecao.what() << endl;
    }
}

void TUNumero::testarCenarioValorInvalido() {
    try {
        dominio->setValor(VALOR_INVALIDO);
        estado = FALHA;
        cerr << "ERRO: TUNumero (Invalido): Excecao nao lancada para valor invalido." << endl;
    } catch (const invalid_argument& excecao) {
        // Sucesso: Exceção de argumento inválido lançada.
    } catch (...) {
        estado = FALHA;
        cerr << "ERRO: TUNumero (Invalido): Excecao de tipo inesperado lancada." << endl;
    }
}

int TUNumero::run() {
    setUp();
    testarCenarioValorValido();
    testarCenarioValorInvalido();
    tearDown();
    return estado;
}


// ====================================================================
// 2. IMPLEMENTAÇÃO: TESTE DE UNIDADE DO DOMÍNIO SENHA (TUSenha)
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

        if (dominio->getValor() != VALOR_VALIDO_SENHA) {
            estado = FALHA;
            cerr << "ERRO: TUSenha (Valido): getValor nao retornou o valor esperado." << endl;
        }
    } catch (const invalid_argument& excecao) {
        estado = FALHA;
        cerr << "ERRO: TUSenha (Valido): Excecao lancada indevidamente: " << excecao.what() << endl;
    }
}

void TUSenha::testarCenarioValorInvalido() {
    try {
        dominio->setValor(VALOR_INVALIDO_SENHA);
        estado = FALHA;
        cerr << "ERRO: TUSenha (Invalido): Excecao nao lancada para valor invalido." << endl;
    } catch (const invalid_argument& excecao) {
        // Sucesso
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
// 3. IMPLEMENTAÇÃO: TESTE DE UNIDADE DO DOMÍNIO ENDERECO (TUEndereco)
// ====================================================================

void TUEndereco::setUp() {
    dominio = new Endereco();
    estado = SUCESSO;
}

void TUEndereco::tearDown() {
    delete dominio;
}

void TUEndereco::testarCenarioValorValido() {
    try {
        dominio->setValor(VALOR_VALIDO_ENDERECO);
        if (dominio->getValor() != VALOR_VALIDO_ENDERECO) {
            estado = FALHA;
            cerr << "ERRO: TUEndereco (Valido): getValor nao retornou o valor esperado." << endl;
        }
    } catch (const invalid_argument& excecao) {
        estado = FALHA;
        cerr << "ERRO: TUEndereco (Valido): Excecao lancada indevidamente: " << excecao.what() << endl;
    }
}

void TUEndereco::testarCenarioValorInvalido() {
    try {
        dominio->setValor(VALOR_INVALIDO_ENDERECO);
        estado = FALHA;
        cerr << "ERRO: TUEndereco (Invalido): Excecao nao lancada para valor invalido." << endl;
    } catch (const invalid_argument& excecao) {
        // Sucesso
    } catch (...) {
        estado = FALHA;
        cerr << "ERRO: TUEndereco (Invalido): Excecao de tipo inesperado lancada." << endl;
    }
}

int TUEndereco::run() {
    setUp();
    testarCenarioValorValido();
    testarCenarioValorInvalido();
    tearDown();
    return estado;
}


// ====================================================================
// 4. IMPLEMENTAÇÃO: TESTE DE UNIDADE DA ENTIDADE PESSOA (TUPessoa)
// ====================================================================

void TUPessoa::setUp() {
    entidade = new Pessoa();
    estado = SUCESSO;
}

void TUPessoa::tearDown() {
    delete entidade;
}

void TUPessoa::testarCenarioSucesso() {
    // 1. Cria objetos Domínio
    try {
        Nome nomeValido;
        nomeValido.setValor(VALOR_VALIDO_NOME); // Assume que este nome é válido

        EMAIL emailValido;
        emailValido.setValor(VALOR_VALIDO_EMAIL); // Assume que este email é válido

        // 2. Atribui os Domínios à Entidade
        entidade->setNome(nomeValido);
        entidade->setEmail(emailValido);

        // 3. Verifica a recuperação
        if (entidade->getNome().getValor() != VALOR_VALIDO_NOME) {
            estado = FALHA;
            cerr << "ERRO: TUPessoa: Atribuicao/Recuperacao de Nome falhou." << endl;
        }

        if (entidade->getEmail().getValor() != VALOR_VALIDO_EMAIL) {
            estado = FALHA;
            cerr << "ERRO: TUPessoa: Atribuicao/Recuperacao de EMAIL falhou." << endl;
        }

    } catch (const invalid_argument& e) {
        estado = FALHA;
        cerr << "ERRO: TUPessoa: Falha na validacao do Dominio durante o setup: " << e.what() << endl;
    }
}

int TUPessoa::run() {
    setUp();
    testarCenarioSucesso();
    tearDown();
    return estado;
}


// ====================================================================
// 5. IMPLEMENTAÇÃO: TESTE DE UNIDADE DA ENTIDADE GERENTE (TUGerente)
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
        // Validação de atributos herdados (Pessoa)
        EMAIL emailValido;
        emailValido.setValor("gerente.teste@uni.br");
        entidade->setEmail(emailValido); 
        
        // Validação de atributos próprios (Gerente)
        Senha senhaValida;
        senhaValida.setValor(TUSenha::VALOR_VALIDO_SENHA);

        Ramal ramalValido;
        ramalValido.setValor(30);

        // 2. Atribui os Domínios à Entidade
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
