// -*-c++-*-
#ifndef PEDIDO_H_
#define PEDIDO_H_

#include "usuario.h"
#include "pedido-articulo.h"
#include "fecha.h"
#include "usuario-pedido.h"
#include "tarjeta.h"
#include <ostream>
#include <iostream>

class Pedido_Articulo;

class Pedido{

public:

	Pedido(Usuario_Pedido& u_p,Pedido_Articulo& p_a,Usuario& user,const Tarjeta& tarj,Fecha fech=Fecha());
	int numero()const;
	const Tarjeta* tarjeta()const;
	Fecha fecha()const;
	double total()const;
	static int n_total_pedidos(){return cant_ped_;}
	
	class Vacio{
		public:
		Vacio(const Usuario& user):us_(&user){}
		const Usuario& usuario()const{return *us_;}
		
		private:
		Usuario const *us_;
	};

	class Impostor{
		public:
		Impostor(const Usuario& user):us_(&user){}
		const Usuario& usuario()const{return *us_;}
		
		private:
		Usuario const *us_;
	};

	class SinStock{
		public:
		SinStock(const Articulo& ar):ar_(&ar){}
		const Articulo& articulo()const{return *ar_;}
		
		private:
		Articulo const *ar_;
	};

private:
int nPedido_;
Tarjeta const *tarjeta_;
Fecha fecha_ped_;
double importe_;
static int cant_ped_;
};

std::ostream& operator <<(std::ostream& os,const Pedido& ped);
inline int Pedido::numero()const{return nPedido_;}
inline const Tarjeta* Pedido::tarjeta()const{return tarjeta_;}
inline Fecha Pedido::fecha()const{return fecha_ped_;}
inline double Pedido::total()const{return importe_;}

#endif
