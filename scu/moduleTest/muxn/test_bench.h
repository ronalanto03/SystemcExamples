#ifndef TEST_BENCH_H
#define TEST_BENCH_H

#include<systemc.h>
#include<ctime>

template < int n_in=2,int nb_in=1, typename dataType=sc_int<32> >
class Test_Bench: public sc_module{
	public:
		sc_in_clk clk_in;

		sc_out< dataType > x_out[n_in];
		sc_out< sc_uint<nb_in> > ctrl_out;
		sc_in<dataType> z_in;


		SC_CTOR(Test_Bench){
			srand(time(NULL));

			SC_THREAD(test)
				sensitive<<clk_in.pos();
				dont_initialize();

		}



	void test(){
		cout<<"x_in";
		for(int i=0;i<n_in; ++i)
			cout<<"\tZ"<<i;
			cout<<"\toutput";
		cout<<endl<<endl;
		for(int i=0; i<n_in; ++i){
			ctrl_out.write(i);
			for(int j=0; j<n_in; ++j)
				x_out[j].write(rand()%650);
			wait();
			print();

		}
		sc_stop();
	}


	void print(){
		cout<<ctrl_out.read()<<"\t";
		for(int i=0; i<n_in; ++i)
			cout<<x_out[i].read()<<"\t";
		cout<<z_in.read();
		cout<<endl;
	}


};

#endif
