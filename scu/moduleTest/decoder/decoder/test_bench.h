#ifndef TEST_BENCH_H
#define TEST_BENCH_H

#include<systemc.h>
#include<ctime>

template <int n=1,int n_out=2>
class Test_Bench: public sc_module{
	public:
		sc_in_clk clk_in;

		sc_out< sc_uint<n> > x_out;

		sc_in<bool> z_in[n_out];


		SC_CTOR(Test_Bench){
			srand(time(NULL));

			SC_THREAD(test)
				sensitive<<clk_in.pos();
				dont_initialize();

		}



	void test(){
		cout<<"x_in";
		for(int i=0;i<n_out; ++i)
			cout<<"\tZ"<<i;
		cout<<endl<<endl;
		for(int i=0; i<n_out; ++i){
			x_out.write(i);
			wait();
			print();

		}
		sc_stop();
	}


	void print(){
		cout<<x_out.read()<<"\t";
		for(int i=0; i<n_out; ++i)
			cout<<z_in[i].read()<<"\t";
		cout<<endl;
	}


};

#endif
