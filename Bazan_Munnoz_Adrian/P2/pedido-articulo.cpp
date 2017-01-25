#include "pedido-articulo.h"

std::ostream& operator <<(std::ostream& os,const LineaPedido& lped){
	os << std::fixed <<std::setprecision(2) << lped.precio_venta()<< " €"<<"	"<<lped.cantidad();
	return os;
}

void Pedido_Articulo::pedir(Pedido& ped,Articulo& art,double pr,unsigned cant)
{
	pedart_[&ped].insert(std::make_pair(&art,LineaPedido(pr,cant)));
	artped_[&art].insert(std::make_pair(&ped,LineaPedido(pr,cant)));
}

void Pedido_Articulo::pedir(Articulo& art,Pedido& ped,double pr,unsigned cant){pedir(ped,art,pr,cant);}

Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& ped){
	return pedart_[&ped];
}

Pedido_Articulo::Pedidos& Pedido_Articulo::ventas(Articulo& art){
	return artped_[&art];
}

std::ostream& operator <<(std::ostream& os,const Pedido_Articulo::ItemsPedido& itped){
double tot=0;
	for(auto i = itped.begin(); i != itped.end(); ++i)
	{		
		os << std::fixed << std::setprecision(2) << i->second.precio_venta() << " €	"; 
		os << i->second.cantidad() << "	"; 
		os << "[" << i->first->referencia() << "]	" << i->first->titulo() << std::endl;

		tot =  tot + i->second.precio_venta() * i->second.cantidad();
	}
	
	os << "===================================================" << std::endl;
	 os << "Total: 	" << std::fixed << std::setprecision(2) << tot << " €" << std::endl;

	return os;
}

std::ostream& operator<< (std::ostream& os,const Pedido_Articulo::Pedidos& ped){
	double tot=0;
	unsigned ctot=0;
	
	for(auto i=ped.begin(); i!=ped.end(); ++i)
	{
		os << std::fixed << std::setprecision(2) << (i->second).precio_venta() << " €	";
		os << (i->second).cantidad() << "	";
		os << (i->first)->fecha() << std::endl;
		
		tot = tot + i->second.precio_venta() * i->second.cantidad();
		ctot = ctot + i->second.cantidad();
	}
	os << "===================================================" << std::endl;
	os << "Total: "<< std::fixed << std::setprecision(2) << tot << " €	" << ctot << std::endl;
	
	return os;
}
bool OrdenaPedidos::operator()(const Pedido* a,const Pedido* b)const{return a->numero()<b->numero();}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os){
	double tot=0;
	
	for(auto i=pedart_.begin(); i!=pedart_.end(); ++i)
	{		
		os << "PVP	" << "Cantidad	" << "Fecha de venta	" << std::endl;
		os << "===================================================" << std::endl;
		os << detalle(*i->first) << std::endl;
		tot +=i->first->total();
	}
	os << "Total: " << std::fixed << std::setprecision(2) << tot << " €"<< std::endl;
	return os;
	
	}
std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os){
	for(auto i =artped_.begin(); i!=artped_.end(); i++)
	{
		os << "Ventas de " << "[" << i->first->referencia() << "] " << '"' << (i->first)->titulo();
		os << '"' << " " << "[Pedidos: " << i->second.size() << "] " << std::endl;
		os << "===================================================" << std::endl;
		os << "PVP	" << "Cantidad	" << "Fecha de venta	" << std::endl;
		os << "===================================================" << std::endl;
		os << ventas(*i->first) << std::endl;
	}

	return os;
	}
