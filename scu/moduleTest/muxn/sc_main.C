#include<scuMux.h>
#include<test_bench.h>
#define n 8
#define nb 3
int sc_main(int argc,char *argv[]){

	sc_time delay(0,SC_NS);
	sc_time period(10,SC_NS);
	sc_clock clk("clock",period,0.5,delay,true);

	scu::Mux< n,nb > mux("mux");

	sc_signal<sc_uint<nb> > out_sg;
	sc_signal<sc_int<32> > inputs_sg[n];
	sc_signal<sc_int<32> > z_sg;

	Test_Bench<n,nb> ts("TestBench");


	ts.clk_in(clk);

	for(int i=0; i<n; ++i){
		ts.x_out[i](inputs_sg[i]);
		mux.x_in[i](inputs_sg[i]);
	}

	mux.ctrl_in(out_sg);
	ts.ctrl_out(out_sg);
	mux.z_out(z_sg);
	ts.z_in(z_sg);

	sc_start();
	return 0;
}
