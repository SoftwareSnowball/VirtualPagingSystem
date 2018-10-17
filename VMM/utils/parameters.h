#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#include "types.h"

namespace vmm_parameters {

class SimulationParameters {
public:
	SimulationParameters() {
		SetDefaultValues();
	};
	~SimulationParameters() = default;

	void SetDefaultValues() {
		page_table_size_bits_ = 8;
		page_size_bits_ = 8;
		frame_size_bits_ = 8;

		page_table_size_ = 1 << page_table_size_bits_;
		page_size_ = 1 << page_size_bits_;
		frame_size_ = 1 << page_size_bits_;
		backingstore_size_ = 0; //unknown. Needs to be provided by FileIO
								//This isn't used to limit the programs behavior anyway.

		num_tlb_entries_ = 16;
		number_of_frames_ = 256;
		physical_memory_size_ = (2 << frame_size_) * number_of_frames_;

		tlb_use_fifo_ = false;
	};

	SizePow2 page_table_size_bits_;
	SizePow2 page_size_bits_;
	SizePow2 frame_size_bits_;
	Size page_table_size_;
	Size page_size_;
	Size frame_size_;
	Size backingstore_size_;
	unsigned int num_tlb_entries_;
	unsigned int number_of_frames_;
	unsigned int physical_memory_size_;

	bool tlb_use_fifo_;

};


} //end of namespace vmm_parameters


#endif
