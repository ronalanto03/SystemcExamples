#ifndef TEST_BENCH_H
#define TEST_BENCH_H

#include<systemc.h>
#include<ctime>

template < typename dataType >
class Test_Bench: public sc_module{
	public:
		sc_in_clk clk_in;

		sc_out<bool> en_out;
		sc_out< dataType > x_out;
		sc_in< dataType > z_in;


		SC_CTOR(Test_Bench){
			srand(time(NULL));

			SC_THREAD(test)
				sensitive<<clk_in.pos();
				dont_initialize();

		}



	void test(){
		cout<<"en_out\tx_out\tz_in";
		cout<<endl<<endl;
		for(int i=0; i<10; ++i){
			en_out.write(rand()%2);
			x_out.write(rand());
			wait();
			print();

		}
		sc_stop();
	}


	void print(){
		cout<<en_out.read()<<"\t"<<x_out.read()<<"\t"<<z_in.read();
		cout<<endl;
	}


};

#endif
