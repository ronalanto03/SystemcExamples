#include<scuDecoder.h>
#include<test_bench.h>
#define n 4
#define n_out 16
int sc_main(int argc,char *argv[]){

	sc_time delay(0,SC_NS);
	sc_time period(10,SC_NS);
	sc_clock clk("clock",period,0.5,delay,true);

	scu::Decoder< n,n_out > decoder("decoder");

	sc_signal<sc_uint<n> > out_sg;
	sc_signal<bool> inputs_sg[n_out];

	Test_Bench<n,n_out> ts("TestBench");


	ts.clk_in(clk);

	for(int i=0; i<n_out; ++i){
		ts.z_in[i](inputs_sg[i]);
		decoder.z_out[i](inputs_sg[i]);
	}

	decoder.x_in(out_sg);
	ts.x_out(out_sg);

	sc_start();
	return 0;
}
