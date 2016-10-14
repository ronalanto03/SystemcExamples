#include<scuRegister.h>
#include<test_bench.h>
int sc_main(int argc,char *argv[]){

	sc_time delay(0,SC_NS);
	sc_time period(10,SC_NS);
	sc_clock clk("clock",period,0.5,delay,true);
	sc_trace_file * tf;
	tf = sc_create_vcd_trace_file("tf");

	scu::RegisterEnableReset< sc_int<32>  > register1("register1");

	sc_signal< sc_int<32> > x_sg;
	sc_signal< sc_int<32> > z_sg;
	sc_signal< bool > en_sg,reset_sg;

	sc_trace(tf, x_sg,"x_sg");
	sc_trace(tf, z_sg,"z_sg");
	sc_trace(tf, en_sg,"en_sg");
	sc_trace(tf, clk,"clk");
	sc_trace(tf, reset_sg,"reset_sg");

	Test_Bench< sc_int<32> > ts("TestBench");


	ts.clk_in(clk);
	register1.clk_in(clk);
	register1.x_in(x_sg);
	ts.x_out(x_sg);

	register1.z_out(z_sg);
	ts.z_in(z_sg);

	register1.en_in(en_sg);
	ts.en_out(en_sg);

	register1.reset_in(reset_sg);
	ts.reset_out(reset_sg);

	sc_start();
	sc_close_vcd_trace_file(tf);

	return 0;
}
