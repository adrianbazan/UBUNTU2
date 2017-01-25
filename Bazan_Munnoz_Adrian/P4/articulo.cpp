#include "articulo.h"

Articulo::Articulo(const Autores& aut,Cadena ref,Cadena tit,Fecha fech_pub,double precio):ref_(ref),tit_(tit),fech_pub_(fech_pub),precio_(precio)
{
	if(aut.empty())
		throw Autores_vacios();
	else
		autores_=aut;
}

void Libro::imp_esp(std::ostream& os)const{
	os << "\n\t" << n_pag_ << " págs., " << stock_ << " unidades.";
}

void Cederron::imp_esp(std::ostream& os)const{
os << "\n\t" << tam_ << " MB, " << stock_ << " unidades.";
}

void LibroDigital::imp_esp(std::ostream& os)const{
	os << "\n\t" << "A la venta hasta el " << f_expir_ <<".";
}

std::ostream& operator <<(std::ostream& os,const Articulo& art){
	os << "[" << art.referencia() <<"] "<<'"' << art.titulo() <<'"'<<", de ";
	
	for(auto i=art.autores().begin();i!=art.autores().end();i++){
		os << (*i)->apellidos();
		if(std::next(i,1)!=art.autores().end())
			os << ", ";
	 }
	
	os << ". " <<art.f_publi().anno()<<". "<<std::fixed <<std::setprecision(2) << art.precio()<< " €";
	
	art.imp_esp(os); 
	 
	return os;
	}
