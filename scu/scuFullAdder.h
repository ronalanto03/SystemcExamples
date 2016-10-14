/**
@file scuFullAdder.h
@brief Full Adder in low level
@author Ronald Sulbarán
@mail ronalanto03@gmail.com
@date 11/6/2011
*/


#ifndef SCU_FULLADDER_H
#define SCU_FULLADDER_H
#include<systemc.h>
#include<scuGates.h>

SCU_BEGIN_NAMESPACE

/*
@class FullAdder
@brief Full Adder.
z_out=x_in xor y_in xor c_in.
c_out= (x_in and (y_in or c_in)) or (y_in and c_in).
*/

class FullAdder:public sc_module{

	public:

		///first operand input
		sc_in<bool> x_in;
		///second operand input
		sc_in<bool> y_in;
		///carry input
		sc_in<bool> c_in;
		///result port
		sc_out<bool> z_out;
		///carry output
		sc_out<bool> c_out;

		///constructor
		SC_CTOR(FullAdder):SCU_INIT_PORT_NAME(x_in),SCU_INIT_PORT_NAME(y_in),SCU_INIT_PORT_NAME(c_in),\
		SCU_INIT_PORT_NAME(z_out),SCU_INIT_PORT_NAME(c_out)\
		{

			xor0=new Xor<2>("xor0");
			xor1=new Xor<2>("xor1");

			and0=new And<2>("and0");
			and1=new And<2>("and1");


			or0=new Or<2>("or0");
			or1=new Or<2>("or1");


			xor0->x_in[0](x_in);
			xor0->x_in[1](y_in);
			xor0->z_out(xor1_to_xor2);

			xor1->x_in[0](xor1_to_xor2);
			xor1->x_in[1](c_in);
			xor1->z_out(z_out);

			or0->x_in[0](y_in);
			or0->x_in[1](c_in);
			or0->z_out(or0_to_and0);


			and0->x_in[0](x_in);
			and0->x_in[1](or0_to_and0);
			and0->z_out(and0_to_or1);


			and1->x_in[0](y_in);
			and1->x_in[1](c_in);
			and1->z_out(and1_to_or1);

			or1->x_in[0](and0_to_or1);
			or1->x_in[1](and1_to_or1);
			or1->z_out(c_out);


}

~FullAdder(){

	delete xor0;
	delete xor1;
	delete and0;
	delete and1;
	delete or0;
	delete or1;

}

	private:

		Xor<2> *xor0,*xor1;
		And<2> * and0,*and1;
		Or<2> *or0,*or1;

		sc_signal<bool> or0_to_and0;
		sc_signal<bool> and0_to_or1;
		sc_signal<bool> and1_to_or1;
		sc_signal<bool> xor1_to_xor2;

};
//end class FullAdder

SCU_END_NAMESPACE

#endif
