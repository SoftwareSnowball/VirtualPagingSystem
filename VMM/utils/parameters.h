#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#include "types.h"
//Yes I included a header file in a header file. I do not enjoy the "guess which header file this header
//file depends on" game.

namespace vmm_parameters {

	class SimulationParameters {
	public:
		SimulationParameters() {
			SetDefaultValues();
		};
		~SimulationParameters() = default;

		void SetDefaultValues() {
			page_table_size_bits = 8;
			page_size_bits = 8;
			frame_size_bits = 8;

			page_size_ = 1 << page_size_bits;
			frame_size_ = 1 << page_size_bits;

			num_tlb_entries_ = 16;
			number_of_frames_ = 256;
			physical_memory_size_ = (2 << frame_size_) * number_of_frames_;
		};

		SizePow2 page_table_size_bits;
		SizePow2 page_size_bits;
		SizePow2 frame_size_bits;
		Size page_size_;
		Size frame_size_;
		unsigned int num_tlb_entries_;
		unsigned int number_of_frames_;
		unsigned int physical_memory_size_;

	};


} //end of namespace vmm_parameters


#endif
