Shadow Workload Generator v1.0
==============================

This framework can create a shadow workload (aka clone) given an x86_64 binary as input. The shadow workload demonstrates similar memory access pattern as the original workload while pruning all the non-memory instructions. The output of this framework is a C++ source code that can be compiled with GNU C or clang (not tested on icc).

Building the framework
----------------------

Run make from the root directory. Successful build should create the obj-intel64/MAPProfiler.so file.


Running the framework
---------------------

The tool itself is a target for Intel PIN, and should be invoked as follows:

	$ ./pin/pin -t obj-intel64/MAPProfiler.so -func <function_to_be_profiled> -out <output_code_file>		\
		-top <top_filtering_percentage> -step <sample_size> -maxinst <maximum_inst_to_profile>			\
		-- <target_binary> <target_binary_arguments>
		
Where,

	function_to_be_profiled:	The user can limit the profiling to a specific function. If specified,
					the shadow workload only mimics that particular function. Requires the
					target_binary to be compiled with debug flag. (default: main)
								
	output_code_file:		Name of the generated shadow workload code file. It can be compiled with
					a C compiler to get the shadow workload binary. (default: genCode.cpp)
								
	top_filtering_percentage:	During top rank filtering stage, this specified amount of memory accesses
					will be kept at minimum. (default: 95)
								
	sample_size:			Sample size or batch size of the code fragments in number of memory
					instructions. (default: -1, which means only a single code fragment)
								
	maxinst:			Maximum number of instructions to profile. This includes all instructions,
					not just memory instructions. (default: -1, no limit)
								
	target_binary:			The original workload binary.
	
	target_binary_arguments:	Command line arguments for the target binary, if any.
	
	
Example
-------

	$ cd examples/scatter_gather
	$ make
	$ cd ../../
	$ ./pin/pin -t obj-intel64/MAPProfiler.so -out shadow.cpp -top 97 -step 1000000 -maxinst 5000000000	\
		-- ./examples/scatter_gather/scatter_gather
	
This will clone the scatter_gather benchmark with a batch size of 1 million memory instructions, upto a maximum of
5 billion instructions. The generated clone have the file name shadow.cpp. It can be compiled as follows:

	$ g++ genCode.cpp -o shadow -mavx
	
The -mavx flag is necessary since the clone can contain AVX/AVX2/AVX512 load/store instructions.



