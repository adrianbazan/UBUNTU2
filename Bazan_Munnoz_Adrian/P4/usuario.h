// -*-c++-*-
#ifndef USUARIO_H_
#define USUARIO_H_
#include "cadena.h"
#include "tarjeta.h"
#include "articulo.h"
#include <unistd.h>
#include <map>
#include <set>
#include <iostream>
#include <ostream>
class Tarjeta;
class Numero;
#ifndef CLAVE_H_
#define CLAVE_H_
class Clave{
	
	public:
		Clave(const char* clav);
		inline const Cadena& clave()const{return clave_;}
		bool verifica(const char* clav)const;
		enum Razon {CORTA,ERROR_CRYPT};
		class Incorrecta{
			public:	
				
				Incorrecta(Razon a):razon_(a){}
				inline Razon razon()const{return razon_;}
			private:
				Razon razon_;
		};
	
	private:
		Cadena clave_;
	};
#endif
class Usuario{
	public:
	typedef std::map<Numero,Tarjeta*> Tarjetas;
	typedef std::map<Articulo*,unsigned> Articulos;
	
	 
	Usuario(const Cadena& iden,const Cadena& nom,const Cadena& apell,const Cadena& dir,const Clave& contra);
	Usuario(const Usuario& usuario)= delete;
	Usuario& operator =(const Usuario& usuario)=delete;
	const Cadena& id()const;
	const Cadena& nombre()const;
	const Cadena& apellidos()const;
	const Cadena& direccion()const;
	const Tarjetas& tarjetas()const;
	void es_titular_de(Tarjeta& tar);
	void no_es_titular_de(Tarjeta& tar);
	void compra(Articulo& art, unsigned cant=1);
	size_t n_articulos()const;
	const Articulos& compra()const;
	
	~Usuario();
	friend std::ostream& operator <<(std::ostream& os,const Usuario& usuario);
	friend std::ostream& mostrar_carro(std::ostream& os,const Usuario& usuario);
	
	

	class Id_duplicado{
		
		public:
		Id_duplicado(const Cadena& ide):ide_(ide){}
		const Cadena& idd()const{return ide_;}	
		private:
		Cadena ide_;
	};
	
	private:

	typedef Tarjetas::iterator it_tar;
	typedef Articulos::iterator it_art;
	Cadena iden_,nom_,apell_,dir_;
	Clave contra_;
	Articulos arts_;
	Tarjetas tarjs_;
};
inline const Cadena& Usuario::id()const {return iden_;}
inline 	const Cadena& Usuario::nombre()const {return nom_;}
inline 	const Cadena& Usuario::apellidos()const {return apell_;}
inline	const Cadena& Usuario::direccion()const {return dir_;}
#endif
