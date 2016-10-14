#ifndef TEST_BENCH_H
#define TEST_BENCH_H

#include<systemc.h>
#include<ctime>

template <int n>
class Test_Bench: public sc_module{
	public:
		sc_in_clk clk_in;

		sc_out< bool> x_out[n];

		sc_in<bool> z_in;


		SC_CTOR(Test_Bench){
			srand(time(NULL));

			SC_THREAD(test)
				sensitive<<clk_in.pos();
				dont_initialize();

		}



	void test(){

		for(int i=0; i<n; ++i)
			cout<<"x"<<i<<"\t";
			cout<<"z\n\n";
		for(int j=0; j<6; ++j	){
			for(int i=0; i<n; ++i)
				x_out[i].write(rand()%2);
			wait();
			print();

		}
		sc_stop();
	}


	void print(){
		for(int i=0; i<n; ++i)
			cout<<x_out[i].read()<<"\t";

		cout<<z_in.read()<<endl;
	}


};

#endif
