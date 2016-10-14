/**
@file scuDLatch.h Latch definitions
@brief Definition of diferent kinds of latch register
@author Ronald Sulbaran
@date December 2012
@mail ronalanto03@gmail.com
*/


# ifndef SCU_REGISTER_H
# define SCU_REGISTER_H


# include<systemc.h>
# include<scuDefines.h>

# ifndef SCU_DEFINES_H
# error make sure you have scuDefines.h file in your scu system
# endif

SCU_BEGIN_NAMESPACE


/**
@class RegisterEnableReset
@brief clocked Register with enable and reset input.
this register read when clock input is equal to 1 and write when clock input is equal to 0.

when reset input equal to 1 and clock input equal to 0 RegisterEnableReset change it's state to 0 and other inputs doesnt matter.
when enable input equal to 0 and clock equal to 0 RegisterEnableReset keep the state
 and when enable input is equal to 1 and clock input is equal to 0 RegegisterEnableReset change to x_in.

@author Ronald Sulbaran
@mail ronalanto03@gmail.com
@date December 2012
*/

template < typename dataType ,bool zero=false>
///dataType is de DataType of the latch
///if zero=true => this is a Zero Latch
///if zero=false => this is a normal latch

class RegisterEnableReset:public sc_module{
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
		SC_CTOR(RegisterEnableReset):\
		SCU_INIT_PORT_NAME(clk_in),SCU_INIT_PORT_NAME(en_in),SCU_INIT_PORT_NAME(reset_in),SCU_INIT_PORT_NAME(x_in),SCU_INIT_PORT_NAME(z_out)\
		{
			d=0;

			SC_METHOD(readOperation)
				sensitive<<clk_in.pos();

			SC_METHOD(writeOperation)
				sensitive<<clk_in.neg()<<en_in<<reset_in<<x_in;

		}


		///provide information to report errors
		virtual const char* kind() const{
			return "RegisterEnableReset";
		}

	private:
		///keep the state of the latch
		dataType d;

		///SC_METHOD that read when clock input equal to 1.
		void readOperation(){
				z_out.write(d);
		}

		///SC_METHOD that write when clock input equal to 0.
		void writeOperation(){
			if(reset_in.read())
				d=0;
			else if(not zero and en_in.read())
				d=x_in.read();
			else if(zero)
				d=0;
		}




};
//end class RegisterEnableReset



/**
@class RegisterEnable
@brief clocked Register with enable input.
when enable input equal to 0 and clock equal to 1
z_out keep the state and when enable input equal to 1 and clock input equal to 1 z_out change to x_in.

@author Ronald Sulbaran
@mail ronalanto03@gmail.com
@date December 2012
*/


///dataType is de DataType of the latch
///if zero=true => this is a Zero Latch
///if zero=false => this is a normal latch
template < typename dataType ,bool zero=false>

class RegisterEnable:public sc_module{
	public:

		///Clock port for sincronization
		sc_in_clk clk_in;
		///enable input port
		sc_in<bool> en_in;
		///input data port
		sc_in< dataType > x_in;
		///output data port
		sc_out< dataType > z_out;
		
		///constructor
		SC_CTOR(RegisterEnable):\
		SCU_INIT_PORT_NAME(clk_in),SCU_INIT_PORT_NAME(en_in),SCU_INIT_PORT_NAME(x_in),SCU_INIT_PORT_NAME(z_out)\
		{
			d=0;

			SC_METHOD(readOperation)
				sensitive<<clk_in.pos();

			SC_METHOD(writeOperation)
				sensitive<<clk_in.neg()<<en_in<<x_in;

		}


		///provide information to report errors
		virtual const char* kind() const{
			return "RegisterEnable";
		}

	private:
		///keep the state of the latch
		dataType d;

		///SC_METHOD that read when clock input equal to 1.
		void readOperation(){
				z_out.write(d);
		}

		///SC_METHOD that write when clock input equal to 0.
		void writeOperation(){
			if(not zero and en_in.read())
				d=x_in.read();
			else if(zero)
				d=0;
		}




};
//end class RegisterEnableReset




/**
@class RegisterReset
@brief clocked reset with reset input.
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

class RegisterReset:public sc_module{
	public:

		///Clock port for sincronization
		sc_in_clk clk_in;
		///enable input port
		sc_in<bool> reset_in;
		///input data port
		sc_in< dataType > x_in;
		///output data port
		sc_out< dataType > z_out;
		
		///constructor
		SC_CTOR(RegisterReset):\
		SCU_INIT_PORT_NAME(clk_in),SCU_INIT_PORT_NAME(reset_in),SCU_INIT_PORT_NAME(x_in),SCU_INIT_PORT_NAME(z_out)\
		{
			d=0;

			SC_METHOD(readOperation)
				sensitive<<clk_in.pos();

			SC_METHOD(writeOperation)
				sensitive<<clk_in.neg()<<reset_in<<x_in;

		}


		///provide information to report errors
		virtual const char* kind() const{
			return "RegisterReset";
		}

	private:
		///keep the state of the latch
		dataType d;

		///SC_METHOD that read when clock input equal to 1.
		void readOperation(){
				z_out.write(d);
		}

		///SC_METHOD that write when clock input equal to 0.
		void writeOperation(){
			if(reset_in.read())
				d=0;
			else if(not zero)
				d=x_in.read();
			else if(zero)
				d=0;
		}




};
//end class RegisterReset


/**
@class DLatchClocked
@brief clocked Latch,when clk_in=1 z_out has x_in value.
*/

template < typename dataType ,bool zero=false>
///dataType is the DataType of the latch
///if zero=true => this is a Zero Latch
///if zero=false => this is a normal latch

class Register:public sc_module{
	public:

		///Clock port for sincronization
		sc_in_clk clk_in;
		///input data port
		sc_in< dataType > x_in;
		///output data port
		sc_out< dataType > z_out;
		
		///constructor
		SC_CTOR(Register):\
		SCU_INIT_PORT_NAME(clk_in),SCU_INIT_PORT_NAME(x_in),SCU_INIT_PORT_NAME(z_out)\
		{
			d=0;

			SC_METHOD(readOperation)
				sensitive<<clk_in.pos();

			SC_METHOD(writeOperation)
				sensitive<<clk_in.neg()<<x_in;

		}


		///provide information to report errors
		virtual const char* kind() const{
			return "Register";
		}

	private:
		///keep the state of the latch
		dataType d;

		///SC_METHOD that read when clock input equal to 1.
		void readOperation(){
				z_out.write(d);
		}

		///SC_METHOD that write when clock input equal to 0.
		void writeOperation(){
			if(not zero)
				d=x_in.read();
			else if(zero)
				d=0;
		}




};

//end class Register

SCU_END_NAMESPACE


# endif
