// -*-c++-*-
#ifndef USUARIOPEDIDO_H_
#define USUARIOPEDIDO_H_

#include "usuario.h"
#include "pedido.h"
#include <map>
#include <set>
class Pedido;
class Usuario_Pedido{

public:
	typedef std::set<Pedido*> Pedidos;
	//Mirar usuario con const
	void asocia(Usuario& user,Pedido& ped);
	void asocia(Pedido& ped,Usuario& user);
	Pedidos pedidos(Usuario& user);
	Usuario* cliente(Pedido& pedi);

private:

	std::map<Usuario*,Pedidos> usu_pedi;
	std::map<Pedido*,Usuario*> pedi_usu;

};
inline void Usuario_Pedido::asocia(Usuario& user,Pedido& ped)
{
usu_pedi[&user].insert(&ped);
//pedi-usu[&ped]=&user;//Preguntar
pedi_usu.insert(std::make_pair(&ped,&user));
}
inline void Usuario_Pedido::asocia(Pedido& ped,Usuario& user){asocia(user,ped);}

inline Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario& user)
{return usu_pedi[&user];}

inline Usuario* Usuario_Pedido::cliente(Pedido& pedi)
{return pedi_usu[&pedi];}



#endif
