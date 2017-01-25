
#include <iostream>
#include "fecha.h"
#include <ctime>
#include <stdlib.h>
//#include <cassert>

//const int Fecha::AnnoMinimo(1902);
//const int Fecha::AnnoMaximo(2037);

//invalida
Fecha::Invalida::Invalida(const char* error)
{
	strcpy(p_q,error);
}

const char* Fecha ::Invalida::por_que()const
{
	return p_q;
} 


//fecha

//Comprobacion fecha valida
bool Fecha::comprobar_dia(int d, int m, int a)
{
	bool valido = true;
	
	if(d<1)
	{
		valido = false;
	}
	else
	{
		switch(m)
		{
			case 1: case 3: case 5: case 7: case 8: case 10:case 12:
				if(d>31)
				{
					valido = false;	
				}break;
			case 4: case 6: case 9: case 11: 
				if(d>30)
				{
					valido = false;
				}break;
			case 2:
				if(a % 400 == 0 || (a % 4 == 0 && a % 100 != 0))
				{
					if(d>29)
					{
						valido = false;
					}
				}
				else
				{
					if(d>28)
					{
						valido = false;
					}
				}
		}
	}
	return valido;
}


Fecha::Fecha(int d , int m, int a)
{
	
	std::time_t tiempo_calendario = std::time(NULL);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
	
	if (a == 0)
	{
		ano_ = tiempo_descompuesto->tm_year + 1900; // tm_year: a~nos desde 1900
	}
	else 
	{
		if(a<AnnoMinimo || a>AnnoMaximo)
		{
			/*std::string cad="Año fuera de los límites";
    		char* mensaje=new char[cad.size()+1];
    		strcpy(mensaje,cad.c_str());*/
			Fecha::Invalida i("Año invalido");
			throw i;
		}
		else ano_ = a;
	}
	
	if (m == 0)
	{
		mes_ = tiempo_descompuesto->tm_mon + 1; // tm_mon: 0 (ene)..11 (dic)
	}
	else
	{
		if(m<1 || m>12)
		{
			/*std::string cad="Mes erroneo";
    		char* mensaje=new char[cad.size()+1];
    		strcpy(mensaje,cad.c_str());*/
    		
			Fecha::Invalida i("Mes invalido");
			throw i;
		}
		else mes_ = m;
	}
	
	if(d == 0)
	{
		dia_ = tiempo_descompuesto->tm_mday;
	}
	else
		if(!comprobar_dia(d,m,a))
		{
			/*std::string cad="Dia del mes erroneo";
    		char* mensaje=new char[cad.size()+1];
    		strcpy(mensaje,cad.c_str());*/
			Fecha::Invalida i("Dia invalido");
			throw i;
		}
		else dia_ = d;
}

Fecha& Fecha::operator =(const Fecha& a)
{
	dia_ = a.dia_;
	mes_ = a.mes_;
	ano_ = a.ano_;
	
	return *this;
}


Fecha& Fecha::operator +=(int n)
{
	 //std::time_t aux=std::time(0);
  //std::tm* tiempo=std::localtime(&aux);  
	tm tiempo = { 0, 0, 0, dia_ + n, mes_ - 1, ano_ - 1900, 0, 0, -1 };
	//tiempo->tm_year=ano_-1900;
 // tiempo->tm_mon=mes_-1;
  //tiempo->tm_mday=dia_+n;
	mktime(&tiempo);
  	
	if( tiempo.tm_year+1900<AnnoMinimo || tiempo.tm_year+1900>AnnoMaximo || tiempo.tm_mday<0)
	{
		/*std::string cad="Se ha pasado de los años";
    		char* mensaje=new char[cad.size()+1];
    		strcpy(mensaje,cad.c_str());*/
  		Fecha::Invalida i("Se ha pasado de los años");
		throw i;	
  	}
	
	dia_ = tiempo.tm_mday;
	mes_ = tiempo.tm_mon+1;
	ano_ = tiempo.tm_year+1900;
	return *this;
}

Fecha::Fecha(const char* f)
{
	copiarDeChar(f);
}

Fecha& Fecha::operator ++()
{
	*this += 1;
	return *this;
}

Fecha Fecha::operator ++(int)
{
	Fecha a;
	
	a = *this;
	*this += 1;
	return a;
}

Fecha& Fecha::operator --()
{
	*this += (-1);
	return *this;
}

Fecha Fecha::operator --(int)
{
	Fecha a;
	a = *this;
	*this += (-1);
	return a;
}

Fecha operator +(const Fecha& a, int b)
{
	Fecha c = a;
	c += b;
	return c;
}

Fecha operator -(const Fecha& a, int b)
{
	Fecha c = a;
	c += (-b);
	return c;
}

Fecha& Fecha::operator -=(int n)
{
	*this += (-n);
	return *this;
}

bool operator ==(const Fecha& a, const Fecha& b)
{
	bool iguales = true;
	if(a.dia() != b.dia() || a.mes() != b.mes() || a.anno() != b.anno())
	{
		iguales = false;
	}
	return iguales;
}

//comprobar si tengo que poner a donde b y al reves
bool operator <(const Fecha& a, const Fecha& b)
{
	bool menor = true;
	
	if(b.anno() < a.anno())
	{
		menor = false;
	}
	else
	        if(b.mes() < a.mes() && b.anno() == a.anno())
		{
			menor = false;
		}
		else 
		        if(b.dia() <= a.dia() && b.mes() == a.mes())
			{
				menor = false;
			}
	return menor;
}

bool operator !=(const Fecha& a, const Fecha& b)
{
	return !(a == b);
}

bool operator >(const Fecha& a, const Fecha& b)
{
	return b<a;
}

bool operator <=(const Fecha& a, const Fecha& b)
{
	return !(b<a);
}

bool operator >=(const Fecha& a, const Fecha& b)
{
	return !(a<b);
}


long Fecha::operator -(const Fecha& a)const
{
	tm c = {0,0,0,dia_,mes_-1,ano_-1900,0,0,-1};
	tm d = {0,0,0,a.dia(),a.mes()-1,a.anno()-1900,0,0,-1};
	return difftime(mktime(&c),mktime(&d))/86400;
	/*
	tm c;
	tm d;
	
	c.tm_year = ano_;
	c.tm_mon = mes_;
	c.tm_mday = dia_;
	
	d.tm_year = a.anno();
	d.tm_mon = a.mes();
	d.tm_mday = a.dia();
	
	
    long resultado = difftime(mktime(&c),mktime(&d))/86400;  


    return resultado;*/
}

const char* Fecha::cadena()const
{
        tm tiempo = { 0, 0, 0, dia_ , mes_ - 1, ano_ - 1900, 0, 0, -1 };
	char* fecha = new char[100];
	mktime(&tiempo);
	/*const char* dia=diaEscrito(tiempo.tm_wday);
 const char* mes=mesEscrito(mes_);

char d[2],a[4];
strcpy(fecha,"");
strcat(fecha,dia);
strcat(fecha," ");
//itoa(dia_,d,10);
//itoa(ano_,a,10);
strcat(fecha,d);
strcat(fecha," ");
strcat(fecha,mes);
strcat(fecha," ");
strcat(fecha,a);
strcat(fecha,"\0");
delete[] dia;
delete[] mes;*/
	
	sprintf(fecha,"%s %i de %s de %i",diaEscrito(tiempo.tm_wday),dia_,mesEscrito(mes_),ano_);

	return fecha;
	
}

const char* Fecha::diaEscrito(int dia) const
{
	char* diaEsc=new char[10];
	
	  switch(dia){
	case 1:strcpy(diaEsc,"lunes");
		break;
	case 2:strcpy(diaEsc,"martes");
		break;
	case 3:strcpy(diaEsc,"miércoles");
		break;
	case 4:strcpy(diaEsc,"jueves");
		break;
	case 5:strcpy(diaEsc,"viernes");
		break;
	case 6:strcpy(diaEsc,"sábado");
		break;
	case 0:strcpy(diaEsc,"domingo");
		break;
	}
	return diaEsc;
}

const char* Fecha::mesEscrito(int mes) const
{
	char* mesEsc=new char[10];
	
	switch(mes){
	case 1:strcpy(mesEsc,"enero");
		break;
	case 2:strcpy(mesEsc,"febrero");
		break;
	case 3:strcpy(mesEsc,"marzo");
		break;
	case 4:strcpy(mesEsc,"abril");
		break;
	case 5:strcpy(mesEsc,"mayo");
		break;
	case 6:strcpy(mesEsc,"junio");
		break;
	case 7:strcpy(mesEsc,"julio");
		break;
	case 8:strcpy(mesEsc,"agosto");
		break;
	case 9:strcpy(mesEsc,"septiembre");
		break;
	case 10:strcpy(mesEsc,"octubre");
		break;
	case 11:strcpy(mesEsc,"noviembre");
		break;
	case 12:strcpy(mesEsc,"diciembre");
		break;
	}
return mesEsc;
}

std::ostream& operator <<(std::ostream& os, const Fecha& f){
	/*tm tiempo = { 0, 0, 0, f.dia() , f.mes() - 1, f.anno() - 1900, 0, 0, -1 };
	mktime(&tiempo);
	return os << f.diaEscrito(tiempo.tm_wday) << " "<<f.dia() <<" de "<<f.mesEscrito(f.mes())<<" de " <<f.anno();
	*/
	os<<f.cadena();
	return os;
}

std::istream& operator >>(std::istream& i, Fecha& f){
	char* fec=new char[11];
	i.getline(fec,11);
	f.copiarDeChar(fec);
	delete[] fec;
	return i;
	
}

void Fecha::copiarDeChar(const char* f)
{
	std::time_t tiempo_calendario = std::time(NULL);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
	
	int d, m, a, formato;
		formato = sscanf(f,"%d/%d/%d",&d,&m,&a);
		if(formato != 3)
		{
			/*std::string cad="Formato erroneo";
	    		char* mensaje=new char[cad.size()+1];
	    		strcpy(mensaje,cad.c_str());*/
			Fecha::Invalida i("Formato erroneo");
			throw i;
		}
		if (a == 0)
		{
		ano_ = tiempo_descompuesto->tm_year + 1900; // tm_year: a~nos desde 1900
		}
		else 
			if(a<AnnoMinimo || a>AnnoMaximo){
				/*std::string cad="Año fuera de los límites";
					char* mensaje=new char[cad.size()+1];
					strcpy(mensaje,cad.c_str());*/
				Fecha::Invalida i("Año invalido");
				throw i;
			}
			else
				ano_ = a;
		
		if (m == 0)
		{
			mes_ = tiempo_descompuesto->tm_mon + 1; // tm_mon: 0 (ene)..11 (dic)
		}			
		else	
			if(m>12 || m<1)
			{
				/*std::string cad="Mes erroneo";
				char* mensaje=new char[cad.size()+1];
				strcpy(mensaje,cad.c_str());*/
				Fecha::Invalida i("Mes invalido");	
				throw i;
			}
			else
				mes_ = m;
    		
		if(d == 0)
		{
			dia_ = tiempo_descompuesto->tm_mday;
		}
		else	
			if(!comprobar_dia(d,m,a))
			{
				/*std::string cad="Dia del mes erroneo";
				char* mensaje=new char[cad.size()+1];
				Fecha::Invalida a(mensaje);*/
				Fecha::Invalida i("Dia invalido");
				throw i;
			}
			else	
				dia_ = d;
}	 

