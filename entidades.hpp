#ifndef ENTIDADES_HPP_INCLUDED
#define ENTIDADES_HPP_INCLUDED

#include "dominios.hpp"
#include <stdexcept>
#include <string>
#include <cctype>

using namespace std;

/**
 * @class Pessoa
 * @brief Entidade base que representa uma Pessoa no sistema.
 * 
 * @details Esta classe define os atributos comuns a Gerentes e Hóspedes.
 * A chave primária(PK) do resgistro é o EMAIL.
 */

class Pessoa {
    private:
        Nome nome;
        EMAIL email;
    public:
        /**
         * @brief Atribui o Nome da Pessoa.
         * @param novoNome Objeto Domínio Nome, validado para conter entre 5 e 20
         * caracteres e formatação correta.
         */
        void setNome(const Nome& novoNome);

        /**
         * @brief Atribui o EMAIL da Pessoa.
         * @param novoEmail Objeto Domínio EMAIL, validado seguindo o padrão
         * parte-local@domínio.
         */
        void setEmail(const EMAIL& novoEmail);

        /**
         * @brief Retorna o Nome da Pessoa.
         * @return O objeto Domínio Nome.
         */
        Nome getNome() const;

        /**
         * @brief Retorna o EMAIL da Pessoa.
         * @return O objeto Domínio EMAIL.
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
 * @brief Entidade que representa o Gerente do sistema.
 * 
 * @details Herda de Pessoa e adiciona atributos de acesso: Ramal e Senha.
 */
class Gerente : public Pessoa {
    private:
        Ramal ramal;
        Senha senha;
    public:
        /**
         * @brief Atribui o Ramal de contato do Gerente.
         * @param novoRamal Objeto Domínio Ramal, validado para conter
         * um valor entre 00 e 50.
         */
        void setRamal(const Ramal& novoRamal);

        /**
         * @brief Atribui a Senha de acesso do Gerente.
         * @param novaSenha Objeto Domínio Senha, validado para conter 5 caracteres
         * com composição mista e sem repetição sequencial.
         */
        void setSenha(const Senha& novaSenha);

        /**
         * @brief Retorna o Ramal do Gerente.
         * @return O objeto Domínio Ramal.
         */
        Ramal getRamal() const;

        /**
         * @brief Retorna a Senha do Gerente.
         * @return O objeto Domínio Senha.
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
 * @class Hóspede
 * @brief Entidade que representa um Hóspede que fará reservas.
 * 
 * @details Herda de Pessoa e adiciona atributos necessários para o registro e
 * pagamento: Endereço e Cartão.
 */
class Hospede : public Pessoa {
    private:
        Endereco endereco;
        Cartao cartao;
    public:
        /**
         * @brief Atribui o Endereço do Hóspede.
         * @param novoEndereco Objeto Domínio Endereco, validado para conter entre
         * 5 e 30 caracteres com regras de sequẽncia específicas.
         */
        void setEndereco(const Endereco& novoEndereco);

        /**
         * @brief Atribui o Cartão do Hóspede.
         * @param novoCartao Objeto Domínio Cartao, validado para conter 16
         * dígitos e seguir o Algoritmo de Luhn.
         */
        void setCartao(const Cartao& novoCartao);

        /**
         * @brief Retorna o Endereço do Hóspede.
         * @return O objeto Domínio Endereco.
         */
        Endereco getEndereco() const;

        /**
         * @brief Retorna o Cartão do Hóspede.
         * @return O objeto Domínio Cartao.
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

/**
 * @class Hotel
 * @brief Entidade que representa um Hotel geenciado pelo sistema.
 * 
 * @details Contém os dados de identificação e localização do hotel.
 * A chave primária(PK) do resgistro é o Codigo.
 */
class Hotel {
    private:
        Nome nome;
        Endereco endereco;
        Telefone telefone;
        Codigo codigo;
    public:
        /**
         * @brief Atribui o Nome do Hotel.
         * @param novoNome Objeto Domínio Nome.
         */
        void setNome(const Nome& novoNome);

        /**
         * @brief Atribui o Endereço do Hotel.
         * @param novoEndereco Objeto Domínio Endereco.
         */
        void setEndereco(const Endereco& novoEndereco);

        /**
         * @brief Atribui o Telefone do Hotel.
         * @param novoTelefone Objeto Domínio Telefone, validado no formato
         * +DDDDDDDDDDDDDD.
         */
        void setTelefone(const Telefone& novoTelefone);

        /**
         * @brief Atribui o Código do Hotel.
         * @param novoCodigo Objeto Domínio Codigo, validado para conter 10
         * caracteres alfanuméricos.
         */
        void setCodigo(const Codigo& novoCodigo);

        /**
         * @brief Retorna o Nome do Hotel.
         * @return O objeto Domínio Nome.
         */
        Nome getNome() const;

        /**
         * @brief Retorna o Endereço do Hotel.
         * @return O objeto Domínio Endereco.
         */
        Endereco getEndereco() const;

        /**
         * @brief Retorna o Telefone do Hotel.
         * @return O objeto Domínio Telefone.
         */
        Telefone getTelefone() const;

        /**
         * @brief Retorna o Código (PK) do Hotel.
         * @return O objeto Domínio Codigo.
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
 * @brief Entidade que representa um Quarto específico dentro de um Hotel.
 *
 * @details Contém as características e a diária do quarto.
 * O Número é a chave primária (PK) no contexto do Hotel.
 */
class Quarto {
    private:
        Numero numero;
        Capacidade capacidade;
        Dinheiro diaria;
        Ramal ramal;
    public:
        /**
         * @brief Atribui o Número do Quarto.
         * @param novoNumero Objeto Domínio Numero, validado entre 001 e 999.
         */
        void setNumero(const Numero& novoNumero);

        /**
         * @brief Atribui a Capacidade máxima de pessoas do Quarto.
         * @param novaCapacidade Objeto Domínio Capacidade,
         * validado para 1, 2, 3 ou 4.
         */
        void setCapacidade(const Capacidade& novaCapacidade);

        /**
         * @brief Atribui o valor da Diária do Quarto.
         * @param novaDiaria Objeto Domínio Dinheiro.
         */
        void setDiaria(const Dinheiro& novaDiaria);

        /**
         * @brief Atribui o Ramal interno do Quarto.
         * @param novoRamal Objeto Domínio Ramal.
         */
        void setRamal(const Ramal& novoRamal);

        /**
         * @brief Retorna o Número do Quarto.
         * @return O objeto Domínio Numero.
         */
        Numero getNumero() const;

        /**
         * @brief Retorna a Capacidade do Quarto.
         * @return O objeto Domínio Capacidade.
         */
        Capacidade getCapacidade() const;

        /**
         * @brief Retorna o valor da Diária do Quarto.
         * @return O objeto Domínio Dinheiro.
         */
        Dinheiro getDiaria() const;

        /**
         * @brief Retorna o Ramal do Quarto.
         * @return O objeto Domínio Ramal.
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
 * @brief Entidade que representa uma Reserva de Quarto.
 *
 * @details Contém os detalhes de datas e valores da reserva.
 * Código é a chave primária (PK).
 */
class Reserva {
    private:
        Data chegada;
        Data partida;
        Dinheiro valor;
        Codigo codigo;
    public:
        /**
         * @brief Atribui a Data de Chegada da Reserva.
         * @param novaChegada Objeto Domínio Data, validada com dia-mês-ano correto,
         * incluindo anos bissextos.
         */
        void setChegada(const Data& novaChegada);

        /**
         * @brief Atribui a Data de Partida da Reserva.
         * @param novaPartida Objeto Domínio Data.
         */
        void setPartida(const Data& novaPartida);

        /**
         * @brief Atribui o Valor total da Reserva.
         * @param novoValor Objeto Domínio Dinheiro.
         */
        void setValor(const Dinheiro& novoValor);

        /**
         * @brief Atribui o Código da Reserva.
         * @param novoCodigo Objeto Domínio Codigo.
         */
        void setCodigo(const Codigo& novoCodigo);

        /**
         * @brief Retorna a Data de Chegada da Reserva.
         * @return O objeto Domínio Data.
         */
        Data getChegada() const;

        /**
         * @brief Retorna a Data de Partida da Reserva.
         * @return O objeto Domínio Data.
         */
        Data getPartida() const;

        /**
         * @brief Retorna o Valor total da Reserva.
         * @return O objeto Domínio Dinheiro.
         */
        Dinheiro getValor() const;

        /**
         * @brief Retorna o Código da Reserva.
         * @return O objeto Domínio Codigo.
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
