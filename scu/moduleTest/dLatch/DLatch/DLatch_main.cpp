#include<scuDLatch.h>
#include<test_bench.h>
int sc_main(int argc,char *argv[]){

	sc_time delay(0,SC_NS);
	sc_time period(10,SC_NS);
	sc_clock clk("clock",period,0.5,delay,true);
	sc_trace_file * tf;
	tf = sc_create_vcd_trace_file("tf");

	scu::DLatch< sc_int<32> > d_latch("d_latch");

	sc_signal< sc_int<32> > x_sg;
	sc_signal< sc_int<32> > z_sg;

	sc_trace(tf, x_sg,"x_sg");
	sc_trace(tf, z_sg,"z_sg");
	sc_trace(tf, clk,"clk");

	Test_Bench< sc_int<32> > ts("TestBench");


	ts.clk_in(clk);

	d_latch.x_in(x_sg);
	ts.x_out(x_sg);

	d_latch.z_out(z_sg);
	ts.z_in(z_sg);


	sc_start();
	sc_close_vcd_trace_file(tf);

	return 0;
}
