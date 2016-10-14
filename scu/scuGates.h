/**
@file scuGates.h
@brief Description of gates of n inputs.
@author Ronald Sulbaran
@date December 2012
@mail ronalanto03@gmail.com
*/

#ifndef SCU_GATES_H
#define SCU_GATES_H

# include<systemc.h>
# include<scuDefines.h>

# ifndef SCU_DEFINES_H
# error make sure you have scuDefines.h file in your scu system
# endif
using namespace std;
SCU_BEGIN_NAMESPACE

/**
@class Or
@brief Or gate of n inputs
*/

template< int n >
class Or: public sc_module{

	public:

		///array of input ports
		sc_in< bool > x_in[n];

		///output port
		sc_out< bool > z_out;

		///constructor
		SC_CTOR(Or){

			if(n<2)
				SCU_REPORT_FATAL("must  have more than one input");

			SC_METHOD(operation)
			for(int i=0; i< n; ++i)
				sensitive<<x_in[i];
	
		}

		///provide information to report errors
		virtual const char * kind()const{
			return "Or";
		}

	private:

		///SC_METHOD that make the or operation
		void operation(){

			bool __z_out=false;

			for( int i=0; i<n; ++i)
				__z_out|=x_in[i].read();

			z_out.write(__z_out);

		}
};
//end class Or


/**
@class And
@brief And gate of n inputs
*/
template< int n=2 >
class And: public sc_module{

	public:

		///array of input ports
		sc_in< bool > x_in[n];

		///output port
		sc_out< bool > z_out;

		///constructor
		SC_CTOR(And){

			if(n<2)
				SCU_REPORT_FATAL("must  have more than one input");

			SC_METHOD(operation)
			for(int i=0; i< n; ++i)
				sensitive<<x_in[i];
	
		}

		///provide informaion to report errors
		virtual const char * kind()const{
			return "And";
		}

	private:

		///SC_METHOD that make the and operation
		void operation(){

			bool __z_out=true;

			for( int i=0; i<n; ++i)
				__z_out&=x_in[i].read();

			z_out.write(__z_out);

		}
};
//end class And



/**
@class Xor
@brief Xor gate of n inputs
*/
template< int n=2 >
class Xor: public sc_module{

	public:

		///array of input ports
		sc_in< bool > x_in[n];

		///output port
		sc_out< bool > z_out;

		///constructor
		SC_CTOR(Xor){

			if(n<2)
				SCU_REPORT_FATAL("must  have more than one input");

			SC_METHOD(operation)
			for(int i=0; i< n; ++i)
				sensitive<<x_in[i];
	
		}

		///provide information to report errors
		virtual const char * kind()const{
			return "Xor";
		}

	private:

		///SC_METHOD that make the xor operation
		void operation(){

			bool __z_out=false;

			for( int i=0; i<n; ++i)
				__z_out^=x_in[i].read();

			z_out.write(__z_out);

		}
};
//end class Xor



/**
@class Nand
@brief Nand gate of n inputs
*/
template< int n=2 >
class Nand: public sc_module{

	public:

		///array port of inputs
		sc_in< bool > x_in[n];

		///output port
		sc_out< bool > z_out;

		///constructor
		SC_CTOR(Nand){

			if(n<2)
				SCU_REPORT_FATAL("must  have more than one input");

			SC_METHOD(operation)
			for(int i=0; i< n; ++i)
				sensitive<<x_in[i];
	
		}


		///provide information to report errors
		virtual const char * kind()const{
			return "Nand";
		}


	private:

		///SC_METHOD that make the operation
		void operation(){

			bool __z_out=true;

			for( int i=0; i<n; ++i)
				__z_out&=x_in[i].read();

			z_out.write(not __z_out);

		}
};
//end class Nand




/**
@class Or
@brief Or gate of n inputs
*/
template< int n=2 >
class Nor: public sc_module{

	public:

		///array port of inputs
		sc_in< bool > x_in[n];

		///output port
		sc_out< bool > z_out;

		///constructor
		SC_CTOR(Nor){

			if(n<2)
				SCU_REPORT_FATAL("must  have more than one input");

			SC_METHOD(operation)
			for(int i=0; i< n; ++i)
				sensitive<<x_in[i];
	
		}

		///provide information to report errors
		virtual const char * kind()const{
			return "Nor";
		}

	private:

		///SC_METHOD that make the nor operation
		void operation(){

			bool __z_out=false;

			for( int i=0; i<n; ++i)
				__z_out|=x_in[i].read();

			z_out.write(not __z_out);

		}
};
//end class Nor




/**
@class NotXor
@brief Not Xor gate of n inputs
*/
template< int n=2 >
class NotXor: public sc_module{

	public:

		///array port of inputs
		sc_in< bool > x_in[n];

		///output port
		sc_out< bool > z_out;

		///constructor
		SC_CTOR(NotXor){

			if(n<2)
				SCU_REPORT_FATAL("must  have more than one input");

			SC_METHOD(operation)
			for(int i=0; i< n; ++i)
				sensitive<<x_in[i];
	
		}

		///provide information to report errors
		virtual const char * kind()const{
			return "NotXor";
		}

	private:

		///SC_METHOD that make the not xor operation
		void operation(){

			bool __z_out=false;

			for( int i=0; i<n; ++i)
				__z_out^=x_in[i].read();

			z_out.write(not __z_out);

		}
};
//end class NotXor

/**
@class Not
@brief Not gate of n inputs
*/
class Not: public sc_module{

	public:

		///input port
		sc_in< bool > x_in;

		///output port
		sc_out< bool > z_out;

		///constructor
		SC_CTOR(Not){

			SC_METHOD(operation)
				sensitive<<x_in;
	
		}

		///provide information to report errors
		virtual const char * kind()const{
			return "Not";
		}


	private:

		///SC_METHOD that make the not operation
		void operation(){

			z_out.write(not x_in.read());

		}
};
//end class Not



SCU_END_NAMESPACE


#endif
