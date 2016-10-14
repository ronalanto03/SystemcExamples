#include<scuGates.h>
#include<test_bench.h>

int sc_main(int argc,char *argv[]){

	sc_time delay(0,SC_NS);
	sc_time period(10,SC_NS);
	sc_clock clk("clock",period,0.5,delay,true);

	scu::Not not1("not1");	

	sc_signal<bool> x_sg,z_sg;
	Test_Bench ts("TestBench");


	ts.clk_in(clk);

	ts.x_out(x_sg);
	not1.x_in(x_sg);

	ts.z_in(z_sg);
	not1.z_out(z_sg);

	sc_start();
	return 0;
}
