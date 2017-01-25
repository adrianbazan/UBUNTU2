// -*-c++-*-

#ifndef FECHA_H_
#define FECHA_H_
#include <iostream>
#include <ostream>
#include <istream>
#include <cstring>


class Fecha
{
	public:
		static const int AnnoMinimo=1902;
		static const int AnnoMaximo=2037;
		
		
		friend std::istream& operator >>(std::istream&, Fecha& f);
		explicit Fecha(int d = 0,int m = 0,int a = 0);//evitamos la conversion implicita de entero a fecha
		Fecha(const Fecha& f):dia_(f.dia_),mes_(f.mes_),ano_(f.ano_){}
		Fecha(const char* f);
		//metodos observadores
		int dia() const;
		int mes() const;
		int anno() const;
			
		class Invalida
		{
		    char p_q[100];  
			public:
			Invalida(const char* error);
			const char* por_que() const;
                     
		};
		
		
		Fecha& operator =(const Fecha& a);//Asignacion de fechas
		Fecha& operator +=(int n);
		Fecha& operator -=(int n);
		Fecha& operator ++();//Preincremento
		Fecha operator ++(int);//Postincremento
		Fecha& operator --();//Predecremento
		Fecha operator --(int);//Postdecremento
		//Resta de fechas
		long operator -(const Fecha& a)const;
		
		
		
		
		/*operator const char*()const//conversion implicita de cadena
		{
			return cadena();
		}*/
		const char* cadena() const;
		const char* diaEscrito(int dia)const;
		const char* mesEscrito(int mes)const;
			
	private:
		int dia_, mes_ , ano_;
		bool comprobar_dia(int d,int m, int a);
 		void copiarDeChar(const char* f);

};

Fecha operator+(const Fecha& a, int b);//suma entero
Fecha operator-(const Fecha& a, int b);//Resta entero
bool operator ==(const Fecha& a,const Fecha& b);
bool operator <(const Fecha& a,const Fecha& b);
bool operator !=(const Fecha& a,const Fecha& b);
bool operator >(const Fecha& a,const Fecha& b);
bool operator <=(const Fecha& a,const Fecha& b);
bool operator >=(const Fecha& a,const Fecha& b);
std::ostream& operator <<(std::ostream& os, const Fecha& f);//insercion


inline int Fecha::dia()const{return dia_;}
inline int Fecha::mes()const{return mes_;}
inline int Fecha::anno()const{return ano_;}

#endif
