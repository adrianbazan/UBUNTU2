#include "cadena.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

const size_t Cadena::npos(-1);

Cadena::~Cadena()
{
	if(tam_ != 0)
	{	
		delete[] cad_;
		tam_ = 0;
	}	
}

Cadena::Cadena(unsigned t, char car):tam_(t)
{
	cad_ = new char[tam_ + 1];
	
	for(int i = 0; i<tam_; i++)
	{
		cad_[i] = car;
		cad_[tam_] = 0;
	}
}

Cadena::Cadena(const Cadena& cad):tam_(cad.tam_)
{
	cad_ = new char[tam_ + 1];
	
	strcpy(cad_, cad.cad_);	
}
//HACER *****************
/*Cadena::Cadena(const Cadena& cad, unsigned pos_ini , size_t longitud):tam_(longitud)
{
	if(pos_ini>tam_ || pos_ini+longitud>tam_ || longitud<0 || pos_ini>0)
	{
		throw std::out_of_range("Fuera de rango");
	}
	else
	{
		
		//if(longitud == npos || longitud > tam_ - pos_ini)
		
		cad_= new char[tam_];
		
		strncpy(cad_,cad.cad_+pos_ini,longitud);
		
		cad_[tam_] = 0;
	}
}*/
//Ctor de Subcadena
Cadena::Cadena(const Cadena& cad, unsigned pos_ini, size_t longitud):tam_(longitud)
{
	if(pos_ini>cad.length())
	{
		throw std::out_of_range("Fuera de rango");
	}
	
    if(longitud == npos || longitud > cad.length()+pos_ini)
    {
        tam_ = cad.length()-pos_ini;
        cad_ = new char[tam_];
        /*for(unsigned int j=0; j<tam_; j++)
            cad_[j] = cad[j+pos_ini];cambio esto por strcpy*/
        strcpy(cad_,cad.cad_+pos_ini) ;   
        cad_[tam_] = 0; //'\0';
    }
    else
    {
        if(longitud>0)
        {
			tam_ = longitud;
			cad_ = new char[tam_];
			/*for(unsigned int j=0; j<tam_; j++)
				cad_[j] = cad[j+pos_ini];*/
			strncpy(cad_,cad.cad_+pos_ini,longitud);
			cad_[tam_] = 0; //'\0';
		}
        else if(longitud == 0)
        {
			
			tam_=0; 
			cad_= new char[tam_];
		}
    }
    
}

	
Cadena::Cadena(Cadena&& cad)
{
	cad_ = cad.cad_;
	cad.cad_ = new char[1];
	cad.cad_[0] = 0;

	tam_ = cad.tam_;

	cad.tam_ = 0;
}

Cadena& Cadena::operator =(Cadena&& cad)
{
	if(this != &cad)
	{	
		delete[] cad_;
		cad_ = cad.cad_;
		cad.cad_ = new char[1];
		cad.cad_[0] = 0;
		tam_ = cad.tam_;
		cad.tam_ = 0;
	}

	return *this;
}

Cadena::Cadena(const char* cad)
{
	tam_ = strlen(cad);
	cad_ = new char[tam_ + 1];	
	strcpy(cad_,cad);
	cad_[tam_] = 0;
}

//PROBAR
Cadena::Cadena(const char* cad, unsigned n)
{
	tam_ = n;
	cad_ = new char[tam_ + 1];	
	strncpy(cad_,cad,n);
	cad_[tam_] = 0;
}

Cadena& Cadena::operator =(const Cadena& cad)
{
	if(this != &cad)
	{
		if(tam_!=cad.tam_)
		{
			delete cad_;
			tam_ = cad.tam_;
			cad_ = new char[tam_ + 1];
		}
		strcpy(cad_,cad.cad_);	
	}
	return *this;
}

Cadena& Cadena::operator =(const char* cad)
{
	tam_ = strlen(cad);
	delete cad_;
	cad_ = new char[tam_ + 1];	
	strcpy(cad_,cad);
	cad_[tam_] = 0;
	return *this;
}

const char* Cadena::c_str() const
{
	return cad_;
}

unsigned Cadena::length()
{
	return tam_;
}

unsigned Cadena::length()const
{
	return tam_;
}

Cadena& Cadena::operator +=(const Cadena& cad)
{
	tam_ += cad.tam_;
	char* aux = new char[tam_ + 1];
	strcpy(aux,cad_);
	strcat(aux,cad.cad_);
	delete[] cad_;
	cad_ = aux;
	aux = 0;
	return *this;
}

Cadena operator +(const Cadena& cad1,const Cadena& cad2)
{
	Cadena a(cad1);
	a += cad2;
	return a;
	
}

bool operator ==(const Cadena& cad1,const Cadena& cad2)
{
	return (strcmp(cad1.c_str(),cad2.c_str()) == 0);
}

bool operator !=(const Cadena& cad1,const Cadena& cad2)
{
	return !(cad1 == cad2);
}

bool operator <(const Cadena& cad1,const Cadena& cad2)
{
	return (strcmp(cad1.c_str(),cad2.c_str()) < 0);
}

bool operator >(const Cadena& cad1,const Cadena& cad2)
{
	return cad2 < cad1;
}

bool operator <=(const Cadena& cad1,const Cadena& cad2)
{
	return !(cad1 > cad2);
}

bool operator >=(const Cadena& cad1,const Cadena& cad2)
{
	return !(cad1 < cad2);
}

char Cadena::operator [](unsigned n) const 
{
	return *(cad_ + n);
}

char& Cadena::operator [](unsigned n)
{
	return *(cad_ + n);
}

char& Cadena::at(unsigned n)
{
	if(n >= tam_)
	{
		throw std::out_of_range("Fuera de rango");
	}
	
	return *(cad_ + n);
}

char Cadena::at(unsigned n)const
{
	if(n >= tam_)
		throw std::out_of_range("Fuera de rango");
	
	return *(cad_ + n);
}

Cadena& Cadena::substr(unsigned i,unsigned tam)
{
	
	if(i >= tam_)
		throw std::out_of_range("Fuera de rango");
	if(tam+i < tam || i+tam >= tam_)
		throw std::out_of_range("No hay tantos caracteres");
	
	Cadena* aux = new Cadena(tam);
	strncpy(aux->cad_,cad_ + i,tam);

	return *aux;
}

Cadena& Cadena::substr(unsigned i,unsigned tam)const
{
	
	if(i >= tam_)
	{	
		throw std::out_of_range("Fuera de rango");
	}
	if(tam+i < i || i+tam >= tam_)
	{
		throw std::out_of_range("No hay tantos caracteres");
	}
	
	Cadena* aux = new Cadena(tam);
	strncpy(aux->cad_,cad_ + i,tam);

	return *aux;
}

std::ostream& operator <<(std::ostream& os,const Cadena& cad)
{
	os<<cad.c_str();
	return os;
}

std::istream& operator >>(std::istream& is,Cadena& cad)
{
	
	int tipo;
	char cadena[32];
	strcpy(cadena,"");
	int i = 0;
	char c;
	
	c = is.peek();
	tipo = is.get();
	
	while(isspace(tipo) && tipo!=-1)
	{
		tipo = is.get();
	}

	while(!isspace(tipo) && tipo!=-1){
		c = tipo;
		cadena[i] = c;
		tipo = is.get();
		i++;

	}
	cadena[i] = 0;
	if(isspace(tipo))
		is.putback(tipo);
		
	cad = cadena;
	
	return is;
}
