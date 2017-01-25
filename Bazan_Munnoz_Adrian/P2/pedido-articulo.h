// -*-c++-*-
#ifndef PEDIDOARTICULO_H_
#define PEDIDOARTICULO_H_

#include <map>
#include "articulo.h"
#include "pedido.h"
#include <ostream>
#include <iostream>


class Pedido;

struct OrdenaPedidos{
bool operator()(const Pedido* a,const Pedido* b)const;
};

struct OrdenaArticulos{
bool operator()(const Articulo* a,const Articulo* b)const{return a->referencia()<b->referencia();}
};

class LineaPedido{
	public:
	explicit LineaPedido(double pr,unsigned can=1):precio_(pr),cant_(can){}
	double precio_venta()const;
	unsigned cantidad()const;
	
	private:
	double precio_;
	unsigned cant_;
};

class Pedido_Articulo{
	public:
	typedef std::map<Articulo*, LineaPedido,OrdenaArticulos> ItemsPedido;
	typedef std::map<Pedido*,LineaPedido, OrdenaPedidos> Pedidos;
	void pedir(Pedido& ped,Articulo& art,double pr,unsigned cant=1);
	void pedir(Articulo& art,Pedido& ped,double pr,unsigned cant=1);
	ItemsPedido& detalle(Pedido& ped);
	Pedidos& ventas(Articulo&);
	std::ostream& mostrarDetallePedidos(std::ostream& os);
	std::ostream& mostrarVentasArticulos(std::ostream& os);

	private: 
	std::map<Pedido*, ItemsPedido, OrdenaPedidos>	pedart_;
	std::map<Articulo*,Pedidos, OrdenaArticulos> artped_;

};



//Linea de pedido
inline double LineaPedido::precio_venta()const{return precio_;}
inline unsigned LineaPedido::cantidad()const{return cant_;}
std::ostream& operator<<(std::ostream& os,const LineaPedido& lped);

//Pedido_Articulo
std::ostream& operator<<(std::ostream& os,const Pedido_Articulo::ItemsPedido& ip);
std::ostream& operator<<(std::ostream& os,const Pedido_Articulo::Pedidos& ped);


#endif
