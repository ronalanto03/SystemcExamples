/**
@file scuMux
@brief Definition of a generic multiplexer
@author Ronald Sulbaran
@date December 2012
@mail ronalanto03@gmail.com
*/


# ifndef SCU_MUX_H
# define SCU_MUX_H
# include<systemc.h>
# include<cstdlib>
# include"scuDefines.h"
using namespace std;

SCU_BEGIN_NAMESPACE

///n is the number of data inputs
///nb is the number of bits of control port
///dataType is the DataType of inputs and outputs of the Mux
template < int n=2,int nb=1, typename dataType=sc_int<32> >
class Mux:public sc_module{
	public:

		///array of input ports
		sc_in< dataType > x_in[n];
		///control input
		sc_in< sc_uint<nb> > ctrl_in;
		///output port
		sc_out<dataType> z_out;

		///constructor
		SC_CTOR(Mux){

			SC_METHOD(mux)
				sensitive<<ctrl_in;
				for( int i=0; i<n; ++i )
					sensitive<<x_in[i];

			if(n<=0 and nb<=0)
				SCU_REPORT_FATAL("the number of inputs and bits of control port must be positive( >0 )");

			else if(n<=0)
				SCU_REPORT_FATAL("the number of inputs must be positive( >0 )");

			else if(nb<=0)
				SCU_REPORT_FATAL("the number of bits of control port must be positive( >0 )");


			if( n<pow(2,nb-1)+1 or n>pow(2,nb) ){
				SCU_REPORT_FATAL(
				("Invalid Number of bits or inputs given to the template,you have "+scu::intToString(nb)+\
				" bits for the control input and "+scu::intToString(n)+\
				" inputs,  and the number of inputs must be between "+\
				scu::intToString(pow(2,nb-1)+1)+" and "+scu::intToString(pow(2,nb)))\
				);
			}
		}



		///provide information to report errors
		virtual const char* kind() const{
			return "Mux";
		}

	private:

		///SC_METHOD that mux the data
		void mux(){

			z_out.write(x_in[ctrl_in.read()]);
		}



};


SCU_END_NAMESPACE

#endif
