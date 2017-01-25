#include "usuario.h"
#include <cstring>
#include <iomanip>

static std::set<Cadena> ids;
typedef std::set<Cadena>::iterator it_ids;
Usuario::Usuario(const Cadena& iden,const Cadena& nom,const Cadena& apell,const Cadena& dir,const Clave& contra)
:iden_(iden),nom_(nom),apell_(apell),dir_(dir),contra_(contra){
	
	std::pair<it_ids,bool> in;
	
	in=ids.insert(iden_);
	
	if(in.second == false){
	Usuario::Id_duplicado dupli(iden_);
	throw dupli;
	}	
}



std::ostream& operator <<(std::ostream& os,const Usuario& usuario){
	os << usuario.id() << " [" << usuario.contra_.clave() << "] " << usuario.nombre() <<
	 " " << usuario.apellidos() << std::endl << usuario.direccion() << std::endl <<
	 "Tarjetas: " << std::endl;
	 
	 for(auto i=usuario.tarjs_.begin();i!=usuario.tarjs_.end();i++)
	 os << "<"<<*i->second <<">"<< std::endl;
	 
	 
	 return os;
}

const Usuario::Tarjetas& Usuario::tarjetas()const{
	
	return tarjs_;
}

void Usuario::es_titular_de(Tarjeta& tar){
	tarjs_.insert(std::make_pair(tar.numero(),&tar));
}
void Usuario::no_es_titular_de(Tarjeta& tar){
	if(tar.titular())
		tarjs_.erase(tar.numero());
	else
		tar.anular_titular();
}

Usuario::~Usuario(){
	for(auto i =tarjs_.begin();i!=tarjs_.end();i++){
	i->second->anular_titular();
	tarjs_.erase(i,i);
	}
	
	ids.erase(iden_);
}

void Usuario::compra(Articulo& art, unsigned cant){
	
	if(cant==0){
		arts_.erase(&art);
	}else{
		if(arts_.find(&art)->first)
		arts_.erase(&art);
		
		arts_.insert(std::make_pair(&art,cant));
	}
	
}

size_t Usuario::n_articulos()const{
	
	return arts_.size();
	
}

const Usuario::Articulos& Usuario::compra()const {
	return arts_;
}

std::ostream& mostrar_carro(std::ostream& os,const Usuario& usuario){
	os <<std::endl << "Carrito de la compra de " << usuario.id() << " [Artículos: "<<usuario.n_articulos() <<"]" << std::endl
	<<"Cant. Artículo" <<std::endl << std::setfill('=')<< std::setw(60) <<std::endl;
	
	for(auto i=usuario.arts_.begin();i!=usuario.arts_.end();i++){
	 os << "[" << (i->first)->referencia() <<"] "<<'"' << (i->first)->titulo() <<'"'<<", "<< (i->first)->f_publi().anno()
		<<". "<<std::fixed <<std::setprecision(2) << (i->first)->precio()<< " €";
	}
	return os;
}

Clave::Clave(const char* clav){
  if(strlen(clav)<5){
    Razon b=Clave::Razon::CORTA;
    Clave::Incorrecta a(b);
    throw a;
  }
   
  clave_=crypt(clav,"cx");
   
  if(clave_==""){
    Razon b=Clave::Razon::ERROR_CRYPT;
    Clave::Incorrecta a(b);
    throw a;
  }
}

bool Clave::verifica(const char* clav)const{
  return clave_==crypt(clav,"cx");   
}
