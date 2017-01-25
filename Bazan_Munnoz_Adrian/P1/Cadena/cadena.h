//-*-c++-*-
#ifndef CADENA_H_
#define CADENA_H_
#include <ostream>
#include <istream>


class Cadena
{
	public:
	
		static const size_t npos;
		
		typedef char* iterator;
		typedef const char* const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		
		//constructres
	    explicit Cadena(unsigned t=0,char car=' ');
		Cadena(const Cadena& cad);//d) copia de otra cadena
		
		//HACER constructor por copia de otra subcadena*********************
		Cadena(const Cadena& cad, unsigned pos_ini , size_t longitud = npos);
		//Cadena(const Cadena& cad, int pos_ini , size_t longitud = npos);
		
		
		
		
		Cadena(Cadena&& cad);
		/*//Conversion implicita de cadena
		operator const char*()const
		{
			return cad_;
		}*/
		
		Cadena(const char* cad);
		//HACER constructor de n caracteres de cadena de bajo nivel 
		Cadena(const char* cad, unsigned n);
		
		//asignacion de cadenas
		Cadena& operator =(const Cadena& cad);
		Cadena& operator =(Cadena&& cad);
		Cadena& operator =(const char* cad);
		
		const char* c_str() const;
		
		//concatenacion de cadenas +=
		Cadena& operator +=(const Cadena& cad);
		
		//sobrecarga operador corchetes y at
		char operator [](unsigned n)const;
		char& operator [](unsigned n);
		char& at(unsigned n);
		char at(unsigned n)const;
		
		//funcion substr
		Cadena& substr(unsigned i,unsigned tam);
		Cadena& substr(unsigned i,unsigned tam)const;
		
		//funcion observadora legth
		unsigned length();
		unsigned length()const;
		
		//borrar cadena
		~Cadena();
		
		inline iterator begin() noexcept {return cad_;}
		inline iterator begin()const noexcept {return cad_;}
		
		inline  const_iterator cbegin()const noexcept {return cad_;}
	
		inline iterator end() noexcept {return cad_+tam_;}
		inline iterator end()const noexcept {return cad_+tam_;}
		
		inline const_iterator const cend()const noexcept {return cad_+tam_;}
		
		inline reverse_iterator rbegin() noexcept{ return reverse_iterator(end());}
		inline reverse_iterator rbegin()const noexcept{ return reverse_iterator(end());}
		
		inline const_reverse_iterator crbegin()const noexcept { return reverse_iterator(end());}
		
		inline reverse_iterator rend() noexcept{ return reverse_iterator(begin());}
		inline reverse_iterator rend()const noexcept { return reverse_iterator(begin());}
		
		inline const_reverse_iterator crend()const noexcept{ return reverse_iterator(begin());}
		
	private:
		char* cad_;
		unsigned tam_;	
		
};

std::istream& operator >>(std::istream& is,Cadena& cad);
std::ostream& operator <<(std::ostream& os,const Cadena& cad);

Cadena operator +(const Cadena& cad1,const Cadena& cad2);//suma cadenas
bool operator ==(const Cadena& cad1,const Cadena& cad2);//comparacion cadenas =
bool operator !=(const Cadena& cad1,const Cadena& cad2);//comparacion cadenas !=
bool operator <(const Cadena& cad1,const Cadena& cad2);//comparacion cadenas <
bool operator >(const Cadena& cad1,const Cadena& cad2);//comparacion cadenas >
bool operator <=(const Cadena& cad1,const Cadena& cad2);//comparacion cadenas <=
bool operator >=(const Cadena& cad1,const Cadena& cad2);//comparacion cadenas >=

#endif

