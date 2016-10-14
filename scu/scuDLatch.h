/**
@file scuDLatch.h Latch definitions
@brief Definition of diferent kinds of latch register
@author Ronald Sulbaran
@date December 2012
@mail ronalanto03@gmail.com
*/


# ifndef SCU_DLATCH_H
# define SCU_DLATCH_H


# include<systemc.h>
# include<scuDefines.h>

# ifndef SCU_DEFINES_H
# error make sure you have scuDefines.h file in your scu system
# endif

SCU_BEGIN_NAMESPACE


/**
@class DLatchClockedEnableReset
@brief clocked Latch with enable and reset input.
when reset input equal to 1 and clock input equal to 1 DLatchClockedEnableReset change it's state to 0 and other inputs doesnt matter.
when enable input equal to 0 and clock equal to 1
z_out keep the state and when enable input equal to 1 and clock input equal to 1 z_out change to x_in.

@author Ronald Sulbaran
@date December 2012
@mail ronalanto03@gmail.com

*/

template < typename dataType ,bool zero=false>
///dataType is de DataType of the latch
///if zero=true => this is a Zero Latch
///if zero=false => this is a normal latch

class DLatchClockedEnableReset:public sc_module{
	public:

		///Clock port for sincronization
		sc_in_clk clk_in;
		///enable input port
		sc_in<bool> en_in;
		///reset input port, make d=0
		sc_in<bool> reset_in;
		///input data port
		sc_in< dataType > x_in;
		///output data port
		sc_out< dataType > z_out;
		
		///constructor
		SC_CTOR(DLatchClockedEnableReset):\
		SCU_INIT_PORT_NAME(clk_in),SCU_INIT_PORT_NAME(en_in),SCU_INIT_PORT_NAME(reset_in),SCU_INIT_PORT_NAME(x_in),SCU_INIT_PORT_NAME(z_out)\
		{
			d=0;
			SC_METHOD(operation)
				sensitive<<x_in<<en_in<<clk_in.pos()<<reset_in;

		}


		///provide information to report errors
		virtual const char* kind() const{
			return "DLatchClockedEnableReset";
		}

	private:
		///keep the state of the latch
		dataType d;

		///SC_METHOD that make write and read when clock input equal to 1.
		void operation(){
			if(not zero and en_in.read())
				d=x_in.read();

			else if(zero)
				d=0;

			if(reset_in.read())
				d=0;

			z_out.write(d);
		}



};
//end class DLatchClockedEnableReset



/**
@class DLatchClockedEnable
@brief clocked Latch with enable input.
when enable input equal to 0 and clock equal to 1
z_out keep the state and when enable input equal to 1 and clock input equal to 1 z_out change to x_in.

@author Ronald Sulbaran
@date December 2012
@mail ronalanto03@gmail.com
*/

template < typename dataType ,bool zero=false>
///dataType is de DataType of the latch
///if zero=true => this is a Zero Latch
///if zero=false => this is a normal latch

class DLatchClockedEnable:public sc_module{
	public:

		///Clock port for sincronization
		sc_in_clk clk_in;
		///enable input port
		sc_in<bool> en_in;
		///data input port
		sc_in< dataType > x_in;
		///data output port
		sc_out< dataType > z_out;
		
		///construtor
		SC_CTOR(DLatchClockedEnable):\
		SCU_INIT_PORT_NAME(clk_in),SCU_INIT_PORT_NAME(en_in),SCU_INIT_PORT_NAME(x_in),SCU_INIT_PORT_NAME(z_out)\
		{
			d=0;
			SC_METHOD(operation)
				sensitive<<x_in<<en_in<<clk_in.pos();

		}


		///provide information to report errors
		virtual const char* kind() const{
			return "DLatchClockedEnable";
		}

	private:

		///keep the state of the latch		
		dataType d;

		
		///SC_METHOD that make write and read when clock input equal to 1.
		void operation(){
			if(not zero and en_in.read())
				d=x_in.read();

			else if(zero)
				d=0;

			z_out.write(d);
		}



};
//end class DLatchClockedEnable




/**
@class DLatchClockedReset
@brief clocked Latch with reset input.
when reset input equal to 1 and clock input equal to 1 DLatchClockedReset change it's state to 0 and x_in input doesnt matter.
when reset input equal to 0 and clock input equal to 1 z_out change to x_in.

@author Ronald Sulbaran
@date December 2012
@mail ronalanto03@gmail.com
*/


template < typename dataType ,bool zero=false>
///dataType is de DataType of the latch
///if zero=true => this is a Zero Latch
///if zero=false => this is a normal latch

class DLatchClockedReset:public sc_module{
	public:

		///Clock port for sincronization
		sc_in_clk clk_in;
		///reset input port
		sc_in<bool> reset_in;
		///data input port
		sc_in< dataType > x_in;
		///data  output port
		sc_out< dataType > z_out;

		///constructor
		SC_CTOR(DLatchClockedReset):\
		SCU_INIT_PORT_NAME(clk_in),SCU_INIT_PORT_NAME(reset_in),SCU_INIT_PORT_NAME(x_in),SCU_INIT_PORT_NAME(z_out)\
		{
			d=0;
			SC_METHOD(operation)
				sensitive<<x_in<<reset_in<<clk_in.pos();

		}


		///provide information to report errors
		virtual const char* kind() const{
			return "DLatchClockedReset";
		}

	private:

		///keep the state of the latch		
		dataType d;

		
		///SC_METHOD that make write and read when clock input equal to 1.
		void operation(){
			if(not zero)
				d=x_in.read();

			else if(zero)
				d=0;
			if(reset_in.read())
				d=0;
			z_out.write(d);
		}



};
//end class DLatchClockedReset


/**
@class DLatchClocked
@brief clocked Latch,when clk_in=1 z_out has x_in value.
*/

template < typename dataType ,bool zero=false>
///dataType is de DataType of the latch
///if zero=true => this is a Zero Latch
///if zero=false => this is a normal latch

class DLatchClocked:public sc_module{
	public:

		sc_in_clk clk_in;
		sc_in< dataType > x_in;
		sc_out< dataType > z_out;
		
		SC_CTOR(DLatchClocked):\
		SCU_INIT_PORT_NAME(clk_in),SCU_INIT_PORT_NAME(x_in),SCU_INIT_PORT_NAME(z_out)\
		{
			d=0;
			SC_METHOD(operation)
				sensitive<<x_in<<clk_in.pos();

		}



		virtual const char* kind() const{
			return "DLatchClocked";
		}

	private:
		dataType d;

		void operation(){
			if(not zero)
				d=x_in.read();

			else if(zero)
				d=0;

			z_out.write(d);
		}



};
//end class DLatchClocked




/**
@class DLatchEnableReset
@brief Latch with enable and reset input, when enable=0 and clk_in=1 z_out keep the state and when
enable=1 and clk_in=1 z_out change to x_in.
*/

template < typename dataType ,bool zero=false>
///dataType is de DataType of the latch
///if zero=true => this is a Zero Latch
///if zero=false => this is a normal latch

class DLatchEnableReset:public sc_module{
	public:

		///enble input
		sc_in<bool> en_in;
		///reset input, make d=0
		sc_in<bool> reset_in;
		///input data
		sc_in< dataType > x_in;
		///output data
		sc_out< dataType > z_out;

		///constructor
		SC_CTOR(DLatchEnableReset):\
		SCU_INIT_PORT_NAME(en_in),SCU_INIT_PORT_NAME(reset_in),SCU_INIT_PORT_NAME(x_in),SCU_INIT_PORT_NAME(z_out)\
		{
			d=0;
			SC_METHOD(operation)
				sensitive<<x_in<<en_in<<reset_in;

		}



		virtual const char* kind() const{
			return "DLatchEnableReset";
		}

	private:
		dataType d;

		void operation(){
			if(not zero and en_in.read())
				d=x_in.read();

			else if(zero)
				d=0;

			if(reset_in.read())
				d=0;

			z_out.write(d);
		}



};
//end class DLatchEnableReset




/**
@class DLatchEnable
@brief Latch with enable input, when enable=0 and clk_in=1 z_out keep the state and when
enable=1 and clk_in=1 z_out change to x_in.
*/

template < typename dataType ,bool zero=false>
///dataType is de DataType of the latch
///if zero=true => this is a Zero Latch
///if zero=false => this is a normal latch

class DLatchEnable:public sc_module{
	public:

		sc_in<bool> en_in;
		sc_in< dataType > x_in;
		sc_out< dataType > z_out;
		
		SC_CTOR(DLatchEnable):\
		SCU_INIT_PORT_NAME(en_in),SCU_INIT_PORT_NAME(x_in),SCU_INIT_PORT_NAME(z_out)\
		{
			d=0;
			SC_METHOD(operation)
				sensitive<<x_in<<en_in;

		}



		virtual const char* kind() const{
			return "DLatchEnable";
		}

	private:
		dataType d;

		void operation(){
			if(not zero and en_in.read())
				d=x_in.read();

			else if(zero)
				d=0;

			z_out.write(d);
		}



};
//end class DLatchEnable





/**
@class DLatchReset
@brief Latch with reset input, when reset=0 and clk_in=1 z_out has x_in value,
when reset=1 and clk_in=1 z_out change 0.
*/

template < typename dataType ,bool zero=false>
///dataType is de DataType of the latch
///if zero=true => this is a Zero Latch
///if zero=false => this is a normal latch

class DLatchReset:public sc_module{
	public:

		sc_in<bool> reset_in;
		sc_in< dataType > x_in;
		sc_out< dataType > z_out;
		
		SC_CTOR(DLatchReset):\
		SCU_INIT_PORT_NAME(reset_in),SCU_INIT_PORT_NAME(x_in),SCU_INIT_PORT_NAME(z_out)\
		{
			d=0;
			SC_METHOD(operation)
				sensitive<<x_in<<reset_in;

		}



		virtual const char* kind() const{
			return "DLatchReset";
		}

	private:
		dataType d;

		void operation(){
			if(not zero)
				d=x_in.read();

			else if(zero)
				d=0;
			if(reset_in.read())
				d=0;
			z_out.write(d);
		}



};
//end class DLatchReset




/**
@class DLatch
@brief Latch, z_out take the value of x_in anytime .
*/

template < typename dataType ,bool zero=false>
///dataType is de DataType of the latch
///if zero=true => this is a Zero Latch
///if zero=false => this is a normal latch

class DLatch:public sc_module{
	public:

		sc_in< dataType > x_in;
		sc_out< dataType > z_out;
		
		SC_CTOR(DLatch):\
		SCU_INIT_PORT_NAME(x_in),SCU_INIT_PORT_NAME(z_out)\
		{
			d=0;
			SC_METHOD(operation)
				sensitive<<x_in;

		}



		virtual const char* kind() const{
			return "DLatch";
		}

	private:
		dataType d;

		void operation(){
			if(not zero)
				d=x_in.read();

			else if(zero)
				d=0;

			z_out.write(d);
		}



};

//end class DLatch

SCU_END_NAMESPACE


# endif
