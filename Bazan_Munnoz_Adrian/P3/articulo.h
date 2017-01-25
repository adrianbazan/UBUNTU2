// -*-c++-*-
#ifndef ARTICULO_H_
#define ARTICULO_H_
#include <iostream>
#include <ostream>
#include "fecha.h"
#include "cadena.h"
#include <iomanip>

class Articulo{
	
	public:
	Articulo(Cadena ref,Cadena tit,Fecha fech_pub,double precio,int stock):ref_(ref),tit_(tit),fech_pub_(fech_pub),precio_(precio),stock_(stock){}
	inline const Cadena& referencia() const{return ref_;}
	inline const Cadena& titulo() const {return tit_;}
	inline const Fecha& f_publi() const {return fech_pub_;}
	inline double precio() const {return precio_;}
	inline double& precio() {return precio_;}
	inline size_t stock() const {return stock_;}
	inline size_t& stock() {return stock_;}
	
	private:
		Cadena ref_,tit_;
		Fecha fech_pub_;
		double precio_;
		size_t stock_;
	
	
};

std::ostream& operator <<(std::ostream& os,const Articulo& art);


#endif
