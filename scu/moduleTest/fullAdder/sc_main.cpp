#include<scuFullAdder.h>
#include<test_bench.h>

int sc_main(int argc,char *argv[]){

	sc_time delay(0,SC_NS);
	sc_time period(10,SC_NS);
	sc_clock clk("clock",period,0.5,delay,true);

	scu::FullAdder fullAdder("fullAdder");

	sc_signal<bool> x_sg,y_sg,z_sg,c_in_sg,c_out_sg;
	Test_Bench ts("TestBench");


	ts.clk_in(clk);

	ts.x_out(x_sg);
	fullAdder.x_in(x_sg);

	ts.y_out(y_sg);
	fullAdder.y_in(y_sg);

	ts.c_out(c_in_sg);
	fullAdder.c_in(c_in_sg);

	ts.c_in(c_out_sg);
	fullAdder.c_out(c_out_sg);

	ts.z_in(z_sg);
	fullAdder.z_out(z_sg);

	sc_start();
	return 0;
}
