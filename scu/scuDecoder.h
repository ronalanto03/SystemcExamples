/**
@file dLatch.h Definition of Generic Decoders
@brief Definition of UseFull Generic Decoders for fast development
@author Ronald Sulbaran
@date December 2012
@mail ronalanto03@gmail.com
*/

# ifndef DECODER_H
# define DECODER_H
# include<systemc.h>
# include<cstdlib>
# include<scuDefines.h>

using namespace std;

SCU_BEGIN_NAMESPACE


/**
@class Decoder
@brief Generic decoder with a control input and an array of outputs between (2^(n_in-1))+1 and 2^n_in
*/
template < int n_in=1,int n_out=2 >
class Decoder:public sc_module{
	public:

		///control port
		sc_in< sc_uint<n_in> > x_in;
		///array of outputs
		sc_out< bool > z_out[n_out];
		
		///constructor
		SC_CTOR(Decoder){

			SC_METHOD(decode)
				sensitive<<x_in;

			if(n_in<=0 and n_out<=0)
				SCU_REPORT_FATAL(\
				"the number of inputs and outputs must be positive( >0 )"\
				);

			else if(n_in<=0)
				SCU_REPORT_FATAL(\
				"the number of inputs must be positive( >0 )"\
				);

			else if(n_out<=0)
				SCU_REPORT_FATAL(\
				"the number of outputs must be positive( >0 )"\
				);


			if(n_out<pow(2,n_in-1)+1 or n_out>pow(2,n_in)){
				SCU_REPORT_FATAL(
				("Invalid Number of outputs,you have "+scu::intToString(n_in)+\
				" bits of input and "+scu::intToString(n_out)+\
				" outputs,  and the number of outputs must be between "+\
				scu::intToString(pow(2,n_in-1)+1)+" and "+scu::intToString(pow(2,n_in)))\
				);
			}


		}

		///provide information to report errors
		virtual const char* kind() const{
			return "Decoder";
		}

	private:

		///SC_METHOD that decode
		void decode(){

			bool tmp_out;
			sc_uint<n_in> tmp;

			for(int i=0; i<n_out; ++i){
				tmp_out=true;

				for( int j=0;j<n_in; ++j ){
					tmp=i;
					if(tmp[j])
						tmp_out&=x_in.read().operator[](j);
					else
						tmp_out&=!x_in.read().operator[](j);
				}

				z_out[i].write(tmp_out);

			}

		}



};



/**
@class DecoderEnable
@brief Generic decoder with a control input, an enable input and an array of outputs between (2^(n_in-1))+1 and 2^n_in.
when enable input is equal to 1 the output is normal, when the enable input is equal to 0, every output is 0.
*/
template < int n_in=1,int n_out=2 >
class DecoderEnable:public sc_module{
	public:

		///enable input
		sc_in<bool> en_in;
		///control port
		sc_in< sc_uint<n_in> > x_in;
		///array of outputs
		sc_out< bool > z_out[n_out];
		
		///constructor
		SC_CTOR(DecoderEnable){

			SC_METHOD(decode)
				sensitive<<x_in<<en_in;

			if(n_in<=0 and n_out<=0)
				SCU_REPORT_FATAL(\
				"the number of inputs and outputs must be positive( >0 )"\
				);

			else if(n_in<=0)
				SCU_REPORT_FATAL(\
				"the number of inputs must be positive( >0 )"\
				);

			else if(n_out<=0)
				SCU_REPORT_FATAL(\
				"the number of outputs must be positive( >0 )"\
				);


			if(n_out<pow(2,n_in-1)+1 or n_out>pow(2,n_in)){
				SCU_REPORT_FATAL(
				("Invalid Number of outputs,you have "+scu::intToString(n_in)+\
				" bits of input and "+scu::intToString(n_out)+\
				" outputs,  and the number of outputs must be between "+\
				scu::intToString(pow(2,n_in-1)+1)+" and "+scu::intToString(pow(2,n_in)))\
				);
			}


		}

		///provide information to report errors
		virtual const char* kind() const{
			return "DecoderEnable";
		}

	private:

		///SC_METHOD that decode
		void decode(){

			bool tmp_out;
			sc_uint<n_in> tmp;

			for(int i=0; i<n_out; ++i){
				tmp_out=true;

				for( int j=0;j<n_in; ++j ){
					tmp=i;
					if(tmp[j])
						tmp_out&=x_in.read().operator[](j) and en_in.read();
					else
						tmp_out&=!x_in.read().operator[](j) and en_in.read();
				}

				z_out[i].write(tmp_out);

			}

		}



};

SCU_END_NAMESPACE

#endif
