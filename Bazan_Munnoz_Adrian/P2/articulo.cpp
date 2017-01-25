#include "articulo.h"

std::ostream& operator <<(std::ostream& os,const Articulo& art){
	os << "[" << art.referencia() <<"] "<<'"' << art.titulo() <<'"'<<", "<< art.f_publi().anno()
	<<". "<<std::fixed <<std::setprecision(2) << art.precio()<< " €";  
	return os;
	}
