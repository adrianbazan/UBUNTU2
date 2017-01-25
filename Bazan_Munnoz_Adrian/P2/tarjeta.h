// -*-c++-*-
#ifndef TARJETA_H_
#define TARJETA_H_
#include <ostream>
#include "fecha.h"
#include "cadena.h"
#include "usuario.h"

class Usuario;

#ifndef NUMERO_H_
#define NUMERO_H_

class Numero{
	public:
	Numero(const Cadena& numero);
	operator const char*()const;
	friend bool operator <(const Numero& a, const Numero& b);
	enum Razon {LONGITUD,DIGITOS,NO_VALIDO};
	class Incorrecto{
				public:	
				
				Incorrecto(Razon a):razon_(a){}
				Razon razon()const{return razon_;}
			private:
				Razon razon_;	
	
	};
	
	private:
	Cadena num_;
};


#endif

class Tarjeta{

public:

	Tarjeta(const Numero& num,const Usuario& user,Fecha fech);
	Numero numero()const {return num_;}
	const Fecha& caducidad()const;
	const Cadena& titular_facial()const;
	const Usuario* titular()const;
	Tarjeta(const Tarjeta& num)=delete;
	Tarjeta& operator=(const Tarjeta& num)=delete;
	void anular_titular();
	
	~Tarjeta();


	class Caducada{
		public:
			Caducada(Fecha f):f_(f){}
			const Fecha& cuando()const {return f_;}
		private:
			Fecha f_;
	};

	private:
	Numero num_;
	Usuario const *titular_;
	Fecha fecha_;
	Cadena titular_facial_;
	
};

inline const Fecha& Tarjeta::caducidad()const {return fecha_;}
	inline const Cadena& Tarjeta::titular_facial()const {return titular_facial_;}
	inline const Usuario* Tarjeta::titular()const {return titular_;}
inline bool operator <(const Tarjeta& a,const Tarjeta& b){
return a.numero()<b.numero();}
std::ostream& operator <<(std::ostream& os, const Tarjeta& t);

#endif
