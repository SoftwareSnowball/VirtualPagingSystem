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

		inline void SetDefaultValues() {
			number_pages_ = 256;
			number_frames_ = 256;
		};

		int number_pages_;
		int number_frames_;

	private:


	};



} //end of namespace vmm_parameters


#endif
