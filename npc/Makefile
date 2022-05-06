all:
	@echo "Write this Makefile by your self."

sim: waveform.vcd
	gtkwave waveform.vcd
waveform.vcd: ./obj_dir/Valu
	./obj_dir/Valu
./obj_dir/Valu: ./obj_dir/Valu.mk
	make -C obj_dir -f Valu.mk Valu
./obj_dir/Valu.mk: ./csrc/sim_main.cpp ./vsrc/alu.v
	verilator -Wall --trace -cc ./vsrc/alu.v --exe ./csrc/sim_main.cpp


	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."

include ../Makefile
