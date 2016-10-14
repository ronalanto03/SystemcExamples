#include<scuGates.h>
#include<test_bench.h>
#define n 2

int sc_main(int argc,char *argv[]){

	sc_time delay(0,SC_NS);
	sc_time period(10,SC_NS);
	sc_clock clk("clock",period,0.5,delay,true);

	scu::And< n > and1("and1");	

	sc_signal<bool> and_inputs_sg[n],out_sg;
	Test_Bench<n> ts("TestBench");


	ts.clk_in(clk);

	for(int i=0; i<n; ++i){
		ts.x_out[i](and_inputs_sg[i]);
		and1.x_in[i](and_inputs_sg[i]);
	}

	ts.z_in(out_sg);
	and1.z_out(out_sg);

	sc_start();
	return 0;
}
