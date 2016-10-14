#include<scuGates.h>
#include<test_bench.h>
#define n 2

int sc_main(int argc,char *argv[]){

	sc_time delay(0,SC_NS);
	sc_time period(10,SC_NS);
	sc_clock clk("clock",period,0.5,delay,true);

	scu::Xor< n > xor1("xor1");	

	sc_signal<bool> xor_inputs_sg[n],out_sg;
	Test_Bench<n> ts("TestBench");


	ts.clk_in(clk);

	for(int i=0; i<n; ++i){
		ts.x_out[i](xor_inputs_sg[i]);
		xor1.x_in[i](xor_inputs_sg[i]);
	}

	ts.z_in(out_sg);
	xor1.z_out(out_sg);

	sc_start();
	return 0;
}
