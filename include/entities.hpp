#ifndef ENTIDADES_HPP_INCLUDED
#define ENTIDADES_HPP_INCLUDED

#include "domains.hpp"
#include <string>

using namespace std;

// ====================================================================
// HIERARQUIA DE PESSOAS
// ====================================================================

/**
 * @class Pessoa
 * @brief Entidade base que representa uma Pessoa genérica no sistema.
 *
 * @details Esta classe serve como base para as entidades especializadas Gerente e Hóspede.
 * Ela encapsula atributos comuns de identificação pessoal.
 *
 * A chave primária (PK) para identificação única de uma pessoa neste sistema é o EMAIL.
 */
class Pessoa {
    private:
        Nome nome;
        EMAIL email;
    public:
        /**
         * @brief Atribui o Nome da Pessoa.
         * @param novoNome Objeto da classe de domínio Nome validado.
         */
        void setNome(const Nome& novoNome);

        /**
         * @brief Atribui o EMAIL da Pessoa.
         * @details O Email atua como identificador único (Chave Primária).
         * @param novoEmail Objeto da classe de domínio EMAIL validado.
         */
        void setEmail(const EMAIL& novoEmail);

        /**
         * @brief Recupera o Nome da Pessoa.
         * @return Objeto Nome contendo o nome armazenado.
         */
        Nome getNome() const;

        /**
         * @brief Recupera o EMAIL da Pessoa.
         * @return Objeto EMAIL contendo o endereço de email armazenado.
         */
        EMAIL getEmail() const;
};

inline void Pessoa::setNome(const Nome& novoNome) {
    this->nome = novoNome;
}

inline Nome Pessoa::getNome() const {
    return nome;
}

inline void Pessoa::setEmail(const EMAIL& novoEmail) {
    this->email = novoEmail;
}

inline EMAIL Pessoa::getEmail() const {
    return email;
}

/**
 * @class Gerente
 * @brief Entidade que representa o usuário administrativo do sistema (Gerente).
 *
 * @details Herda de Pessoa e adiciona atributos específicos para controle de acesso
 * e comunicação interna do hotel.
 *
 * Atributos adicionais:
 * - Ramal: Para contato telefônico interno.
 * - Senha: Para autenticação no sistema.
 */
class Gerente : public Pessoa {
    private:
        Ramal ramal;
        Senha senha;
    public:
        /**
         * @brief Define o Ramal de contato do Gerente.
         * @param novoRamal Objeto da classe de domínio Ramal.
         */
        void setRamal(const Ramal& novoRamal);

        /**
         * @brief Define a Senha de acesso do Gerente.
         * @param novaSenha Objeto da classe de domínio Senha.
         */
        void setSenha(const Senha& novaSenha);

        /**
         * @brief Recupera o Ramal do Gerente.
         * @return Objeto Ramal.
         */
        Ramal getRamal() const;

        /**
         * @brief Recupera a Senha do Gerente.
         * @return Objeto Senha.
         */
        Senha getSenha() const;
};

inline void Gerente::setRamal(const Ramal& novoRamal) {
    this->ramal = novoRamal;
}

inline Ramal Gerente::getRamal() const {
    return ramal;
}

inline void Gerente::setSenha(const Senha& novaSenha) {
    this->senha = novaSenha;
}

inline Senha Gerente::getSenha() const{
    return senha;
}

/**
 * @class Hospede
 * @brief Entidade que representa um cliente (Hóspede) do hotel.
 *
 * @details Herda de Pessoa e adiciona atributos necessários para o processo de
 * reserva e faturamento.
 *
 * Atributos adicionais:
 * - Endereço: Localização residencial do hóspede.
 * - Cartão: Dados de pagamento.
 */
class Hospede : public Pessoa {
    private:
        Endereco endereco;
        Cartao cartao;
    public:
        /**
         * @brief Define o Endereço residencial do Hóspede.
         * @param novoEndereco Objeto da classe de domínio Endereco.
         */
        void setEndereco(const Endereco& novoEndereco);

        /**
         * @brief Define os dados do Cartão de Crédito do Hóspede.
         * @param novoCartao Objeto da classe de domínio Cartao.
         */
        void setCartao(const Cartao& novoCartao);

        /**
         * @brief Recupera o Endereço do Hóspede.
         * @return Objeto Endereco.
         */
        Endereco getEndereco() const;

        /**
         * @brief Recupera os dados do Cartão do Hóspede.
         * @return Objeto Cartao.
         */
        Cartao getCartao() const;
};

inline void Hospede::setEndereco(const Endereco& novoEndereco) {
    this->endereco = novoEndereco;
}

inline Endereco Hospede::getEndereco() const {
    return endereco;
}

inline void Hospede::setCartao(const Cartao& novoCartao) {
    this->cartao = novoCartao;
}

inline Cartao Hospede::getCartao() const {
    return cartao;
}

// ====================================================================
// ENTIDADES DE INFRAESTRUTURA
// ====================================================================

/**
 * @class Hotel
 * @brief Entidade que representa a unidade hoteleira gerenciada pelo sistema.
 *
 * @details Agrega as informações de identificação e contato do estabelecimento.
 * A chave primária (PK) é o Código do hotel.
 */
class Hotel {
    private:
        Nome nome;
        Endereco endereco;
        Telefone telefone;
        Codigo codigo;
    public:
        /**
         * @brief Define o Nome fantasia do Hotel.
         * @param novoNome Objeto da classe de domínio Nome.
         */
        void setNome(const Nome& novoNome);

        /**
         * @brief Define o Endereço físico do Hotel.
         * @param novoEndereco Objeto da classe de domínio Endereco.
         */
        void setEndereco(const Endereco& novoEndereco);

        /**
         * @brief Define o Telefone de contato do Hotel.
         * @param novoTelefone Objeto da classe de domínio Telefone.
         */
        void setTelefone(const Telefone& novoTelefone);

        /**
         * @brief Define o Código identificador único do Hotel.
         * @param novoCodigo Objeto da classe de domínio Codigo.
         */
        void setCodigo(const Codigo& novoCodigo);

        /**
         * @brief Recupera o Nome do Hotel.
         * @return Objeto Nome.
         */
        Nome getNome() const;

        /**
         * @brief Recupera o Endereço do Hotel.
         * @return Objeto Endereco.
         */
        Endereco getEndereco() const;

        /**
         * @brief Recupera o Telefone do Hotel.
         * @return Objeto Telefone.
         */
        Telefone getTelefone() const;

        /**
         * @brief Recupera o Código identificador do Hotel.
         * @return Objeto Codigo.
         */
        Codigo getCodigo() const;
};

inline void Hotel::setNome(const Nome& novoNome) {
    this->nome = novoNome;
}

inline Nome Hotel::getNome() const {
    return nome;
}

inline void Hotel::setEndereco(const Endereco& novoEndereco) {
    this->endereco = novoEndereco;
}

inline Endereco Hotel::getEndereco() const {
    return endereco;
}

inline void Hotel::setTelefone(const Telefone& novoTelefone) {
    this->telefone = novoTelefone;
}

inline Telefone Hotel::getTelefone() const {
    return telefone;
}

inline void Hotel::setCodigo(const Codigo& novoCodigo) {
    this->codigo = novoCodigo;
}

inline Codigo Hotel::getCodigo() const {
    return codigo;
}

/**
 * @class Quarto
 * @brief Entidade que representa uma unidade de acomodação (Quarto).
 *
 * @details Contém as características físicas e financeiras do quarto.
 * O Número é a chave primária (PK) no contexto de um hotel específico.
 */
class Quarto {
    private:
        Numero numero;
        Capacidade capacidade;
        Dinheiro diaria;
        Ramal ramal;
    public:
        /**
         * @brief Define o Número do Quarto.
         * @param novoNumero Objeto da classe de domínio Numero.
         */
        void setNumero(const Numero& novoNumero);

        /**
         * @brief Define a Capacidade máxima de hóspedes.
         * @param novaCapacidade Objeto da classe de domínio Capacidade.
         */
        void setCapacidade(const Capacidade& novaCapacidade);

        /**
         * @brief Define o valor da Diária cobrada.
         * @param novaDiaria Objeto da classe de domínio Dinheiro.
         */
        void setDiaria(const Dinheiro& novaDiaria);

        /**
         * @brief Define o Ramal telefônico do quarto.
         * @param novoRamal Objeto da classe de domínio Ramal.
         */
        void setRamal(const Ramal& novoRamal);

        /**
         * @brief Recupera o Número do Quarto.
         * @return Objeto Numero.
         */
        Numero getNumero() const;

        /**
         * @brief Recupera a Capacidade do Quarto.
         * @return Objeto Capacidade.
         */
        Capacidade getCapacidade() const;

        /**
         * @brief Recupera o valor da Diária.
         * @return Objeto Dinheiro.
         */
        Dinheiro getDiaria() const;

        /**
         * @brief Recupera o Ramal do Quarto.
         * @return Objeto Ramal.
         */
        Ramal getRamal() const;
};

inline void Quarto::setNumero(const Numero& novoNumero) {
    this->numero = novoNumero;
}

inline Numero Quarto::getNumero() const {
    return numero;
}

inline void Quarto::setCapacidade(const Capacidade& novaCapacidade) {
    this->capacidade = novaCapacidade;
}

inline Capacidade Quarto::getCapacidade() const {
    return capacidade;
}

inline void Quarto::setDiaria(const Dinheiro& novaDiaria) {
    this->diaria = novaDiaria;
}

inline Dinheiro Quarto::getDiaria() const {
    return diaria;
}

inline void Quarto::setRamal(const Ramal& novoRamal) {
    this->ramal = novoRamal;
}

inline Ramal Quarto::getRamal() const {
    return ramal;
}

/**
 * @class Reserva
 * @brief Entidade que representa o contrato de hospedagem (Reserva).
 *
 * @details Agrega as informações temporais e financeiras da estadia.
 * O Código é a chave primária (PK) única da reserva.
 */
class Reserva {
    private:
        Data chegada;
        Data partida;
        Dinheiro valor;
        Codigo codigo;
    public:
        /**
         * @brief Define a Data de Check-in (Chegada).
         * @param novaChegada Objeto da classe de domínio Data.
         */
        void setChegada(const Data& novaChegada);

        /**
         * @brief Define a Data de Check-out (Partida).
         * @param novaPartida Objeto da classe de domínio Data.
         */
        void setPartida(const Data& novaPartida);

        /**
         * @brief Define o Valor total da reserva.
         * @param novoValor Objeto da classe de domínio Dinheiro.
         */
        void setValor(const Dinheiro& novoValor);

        /**
         * @brief Define o Código identificador da reserva.
         * @param novoCodigo Objeto da classe de domínio Codigo.
         */
        void setCodigo(const Codigo& novoCodigo);

        /**
         * @brief Recupera a Data de Chegada.
         * @return Objeto Data.
         */
        Data getChegada() const;

        /**
         * @brief Recupera a Data de Partida.
         * @return Objeto Data.
         */
        Data getPartida() const;

        /**
         * @brief Recupera o Valor total.
         * @return Objeto Dinheiro.
         */
        Dinheiro getValor() const;

        /**
         * @brief Recupera o Código da reserva.
         * @return Objeto Codigo.
         */
        Codigo getCodigo() const;
};

inline void Reserva::setChegada(const Data& novaChegada) {
    this->chegada = novaChegada;
}

inline Data Reserva::getChegada() const {
    return chegada;
}

inline void Reserva::setPartida(const Data& novaPartida) {
    this->partida = novaPartida;
}

inline Data Reserva::getPartida() const {
    return partida;
}

inline void Reserva::setValor(const Dinheiro& novoValor) {
    this->valor = novoValor;
}

inline Dinheiro Reserva::getValor() const {
    return valor;
}

inline void Reserva::setCodigo(const Codigo& novoCodigo) {
    this->codigo = novoCodigo;
}

inline Codigo Reserva::getCodigo() const {
    return codigo;
}

#endif // ENTIDADES_HPP_INCLUDED
