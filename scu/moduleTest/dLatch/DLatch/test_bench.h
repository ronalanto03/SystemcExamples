#ifndef TEST_BENCH_H
#define TEST_BENCH_H

#include<systemc.h>
#include<ctime>

template < typename dataType >
class Test_Bench: public sc_module{
	public:
		sc_in_clk clk_in;

		sc_out< dataType > x_out;
		sc_in< dataType > z_in;


		SC_CTOR(Test_Bench){
			srand(time(NULL));

			SC_THREAD(test)
				sensitive<<clk_in.pos();
				dont_initialize();

		}



	void test(){
		cout<<"x_out\tz_in";
		cout<<endl<<endl;
		for(int i=0; i<10; ++i){
			x_out.write(rand());
			wait();
			print();

		}
		sc_stop();
	}


	void print(){
		cout<<x_out.read()<<"\t"<<z_in.read();
		cout<<endl;
	}


};

#endif
