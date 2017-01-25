// -*-c++-*-
#ifndef ARTICULO_H_
#define ARTICULO_H_
#include <iostream>
#include <ostream>
#include "fecha.h"
#include "cadena.h"
#include <iomanip>
#include <set>
#include "autor.h"

class Articulo{
	
	public:
	typedef std::set<Autor*> Autores;
	Articulo(const Autores& aut,Cadena ref,Cadena tit,Fecha fech_pub,double precio);
	const Cadena& referencia() const;
	const Cadena& titulo() const;
	const Fecha& f_publi() const;
	double precio() const;
	double& precio();
	const Autores& autores()const;
	Autores& autores();
	virtual void imp_esp(std::ostream& os)const=0;
	
	class Autores_vacios{
		public:
			Autores_vacios(){}
	};

	protected:
		Autores autores_;
		Cadena ref_,tit_;
		Fecha fech_pub_;
		double precio_;
		
};
inline const Cadena& Articulo::referencia() const{return ref_;}
inline const Cadena& Articulo::titulo() const {return tit_;}
inline const Fecha& Articulo::f_publi() const {return fech_pub_;}
inline double Articulo::precio() const {return precio_;}
inline double& Articulo::precio() {return precio_;}
inline const Articulo::Autores& Articulo::autores()const{return autores_;}
inline Articulo::Autores& Articulo::autores(){return autores_;}
std::ostream& operator <<(std::ostream& os,const Articulo& art);

class ArticuloAlmacenable:public Articulo{
public:
	ArticuloAlmacenable(const Articulo::Autores& aut,Cadena ref,Cadena tit,Fecha fech_pub,double precio,size_t st):Articulo(aut,ref,tit,fech_pub,precio),stock_(st){}
	virtual size_t stock() const;
	virtual size_t& stock();
protected:
	size_t stock_;
};
inline size_t ArticuloAlmacenable::stock() const {return stock_;}
inline size_t& ArticuloAlmacenable::stock() {return stock_;}

class Libro: public ArticuloAlmacenable{

public:
	Libro(const Articulo::Autores& aut,Cadena ref,Cadena tit,Fecha fech_pub,double precio,unsigned n_p,size_t st):ArticuloAlmacenable(aut,ref,tit,fech_pub,precio,st),n_pag_(n_p){}
	unsigned n_pag()const;
	void imp_esp(std::ostream& os)const;
private:
	unsigned n_pag_;

};

inline unsigned Libro::n_pag()const{return n_pag_;}

class Cederron: public ArticuloAlmacenable{

public:
	Cederron(const Articulo::Autores& aut,Cadena ref,Cadena tit,Fecha fech_pub,double precio,unsigned t,size_t st):ArticuloAlmacenable(aut,ref,tit,fech_pub,precio,st),tam_(t){}
	unsigned tam()const;
	void imp_esp(std::ostream& os)const;
private:
	unsigned tam_;

};

inline unsigned Cederron::tam()const{return tam_;}

class LibroDigital:public Articulo{

public:
	LibroDigital(const Articulo::Autores& aut,Cadena ref,Cadena tit,Fecha fech_pub,double precio,Fecha f_ex):Articulo(aut,ref,tit,fech_pub,precio),f_expir_(f_ex){}
	Fecha f_expir()const;
	void imp_esp(std::ostream& os)const;
private:
Fecha f_expir_;

};

inline Fecha LibroDigital::f_expir()const{return f_expir_;}











#endif
