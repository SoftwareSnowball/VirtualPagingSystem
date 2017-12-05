#ifndef MAIN_MEMORY_H_
#define MAIN_MEMORY_H_

#include <memory>

#include "..\..\utils\parameters.h"


namespace vmm {
namespace memory {

	class MainMemory {
	public:
		MainMemory(const vmm_parameters::SimulationParameters* parameters);

	private:
		//metadata
		const vmm_parameters::SimulationParameters* parameters_;

		//actual main memory
		std::unique_ptr<Byte> memory_;


	};

} //end of namespace memory
} //end of namespace vmm

#endif