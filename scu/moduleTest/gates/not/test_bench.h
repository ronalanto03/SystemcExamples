#ifndef TEST_BENCH_H
#define TEST_BENCH_H

#include<systemc.h>
#include<ctime>

class Test_Bench: public sc_module{
	public:
		sc_in_clk clk_in;

		sc_out< bool> x_out;

		sc_in<bool> z_in;


		SC_CTOR(Test_Bench){
			srand(time(NULL));

			SC_THREAD(test)
				sensitive<<clk_in.pos();
				dont_initialize();

		}



	void test(){

			cout<<"x"<<"\t";
			cout<<"z\n\n";
		for(int j=0; j<6; ++j	){
				x_out.write(rand()%2);
			wait();
			print();

		}
		sc_stop();
	}


	void print(){
			cout<<x_out.read()<<"\t";

		cout<<z_in.read()<<endl;
	}


};

#endif
