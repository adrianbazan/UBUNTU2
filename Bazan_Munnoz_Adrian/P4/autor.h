// -*-c++-*-
#ifndef AUTOR_H_
#define AUTOR_H_
#include "cadena.h"

class Autor{

public:
Autor(const Cadena& nom,const Cadena& apell,const Cadena& dir):nom_(nom),apell_(apell),dir_(dir){}
Cadena nombre()const;
Cadena apellidos()const;
Cadena direccion()const;

private:

Cadena nom_,apell_,dir_;

};
inline Cadena Autor::nombre()const{return nom_;}
inline Cadena Autor::apellidos()const{return apell_;}
inline Cadena Autor::direccion()const{return dir_;}
#endif
