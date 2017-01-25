#include "tarjeta.h"
#include "usuario.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <algorithm>

Tarjeta::Tarjeta(const Numero& num,const Usuario& user,Fecha fech):num_(num),fecha_(fech),titular_(&user){
  Fecha f;
  
  if(fech < f){
    Tarjeta::Caducada c(fech);
    throw c;
  }
  titular_facial_=user.nombre()+" "+user.apellidos();
  const_cast<Usuario*>(titular_)->es_titular_de(*this);
  

}

void Tarjeta::anular_titular(){
	const_cast<Usuario*>(titular_)->no_es_titular_de(*this);
	titular_=0;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& t){
  return os << t.numero() << std::endl << t.titular_facial() << std::endl <<
    "Caduca: "    <<std::setfill('0') << std::setw(2) << t.caducidad().mes()<<"/"<< std::setfill('0') << 
    std::setw(2) <<t.caducidad().anno()%100;
}

Tarjeta::~Tarjeta(){
	if(titular()){
		const_cast<Usuario*>(titular_)->no_es_titular_de(*this);
	}
}



bool luhn(const Cadena& numero, size_t n);

bool operator <(const Numero& a, const Numero& b){
  return a.num_<b.num_;
}

Numero::Numero(const Cadena& numero){
  Cadena::iterator ite;
  
  Cadena tem(numero);
  
  ite=std::find_if(tem.begin(),tem.end(),[](char c){return isalpha(c);});
  
   if(ite!=tem.end()){
		Razon b=Razon::DIGITOS;
		Incorrecto a(b);
		throw a;
		  }
  
  auto i=std::remove_if(tem.begin(),tem.end(),[](char c){return isspace(c);});
  int k=0;
  char* aux=new char[tem.length()+1];
  for(auto j=tem.begin();j!=i;j++,k++)
	aux[k]=*j;
	
	aux[k]=0;	
    num_=aux;  
    delete[] aux;
  
  if(num_.length()<13 || num_.length()>19){
    Razon b=Razon::LONGITUD;
    Incorrecto a(b);
    throw a;
  }

  if(!luhn(num_,num_.length())){
	Razon b=Razon::NO_VALIDO;
	Incorrecto a(b);
	throw a;
  }
}

Numero::operator const char*()const{
  return num_.c_str();
}
