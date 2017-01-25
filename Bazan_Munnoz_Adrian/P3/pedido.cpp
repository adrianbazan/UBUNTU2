#include "pedido.h"
int Pedido::cant_ped_=0;

Pedido::Pedido(Usuario_Pedido& u_p,Pedido_Articulo& p_a,Usuario& user,const Tarjeta& tarj,Fecha fech)
:importe_(0),nPedido_(cant_ped_+1),tarjeta_(&tarj),fecha_ped_(fech)
{
	
	if(user.n_articulos()==0)
		throw Vacio(user);
	if(&user!=tarj.titular())
		throw Impostor(user);
	if(fecha_ped_>tarj.caducidad()){
		Tarjeta::Caducada a(tarj.caducidad());
		throw a;
	}
		
	Usuario::Articulos arts=user.compra();
	auto pri=arts.end();
	bool art_sin=false;
	
	for(auto i=arts.begin();i!=arts.end() && !art_sin;i++){
		if(i->first->stock()<i->second){
			art_sin=true;
			pri=i;
		}
	}
	
	for(auto i=arts.begin();i!=arts.end();i++){
		if(!art_sin){
			i->first->stock()-=i->second;
			p_a.pedir(*this,*i->first,i->first->precio(),i->second);
			importe_+=i->first->precio()* i->second;
		}
		user.compra(*i->first,0);
	}
	
	if(art_sin)
		throw SinStock(*pri->first);
	else
		cant_ped_++;
		
	u_p.asocia(user,*this);
	
}

std::ostream& operator <<(std::ostream& os,const Pedido& ped){
	os << "Núm. pedido: " << ped.numero() << std::endl;
	os << "Fecha:		" << ped.fecha() << std::endl;
	os << "Pagado con:	" << ped.tarjeta()->numero() << std::endl;
	os << "Importe:		" << std::fixed << std::setprecision(2) << ped.total() << " €" << std::endl;
	return os;
	
	
	return os;
}
