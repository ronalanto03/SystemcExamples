#ifndef TEST_BENCH_H
#define TEST_BENCH_H

#include<systemc.h>
#include<ctime>

class Test_Bench: public sc_module{
	public:
		sc_in_clk clk_in;

		sc_out<bool> x_out;
		sc_out<bool> y_out;
		sc_out<bool> c_out;
		sc_in<bool> z_in;
		sc_in<bool> c_in;

		SC_CTOR(Test_Bench){
			srand(time(NULL));

			SC_THREAD(test)
				sensitive<<clk_in.pos();
				dont_initialize();

		}



	void test(){

		cout<<"x_in\ty_in\tc_in\tz_out\tc_out";
		cout<<"\n\n";
		for(int j=0; j<6; ++j	){
			x_out.write(rand()%2);
			y_out.write(rand()%2);
			c_out.write(rand()%2);
			wait();
			print();

		}
		sc_stop();
	}


	void print(){
		cout<<x_out<<"\t"<<y_out<<"\t"<<c_out<<"\t"<<z_in<<"\t"<<c_in<<endl;
	}


};

#endif
