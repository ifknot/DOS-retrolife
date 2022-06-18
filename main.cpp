#include <iostream>

#include "retrolib/bios/bios_video_services.h"
#include "retrolib/gfx/hga/hga_read_lightpen_registers.h"

//#include "retrolib/dos/dos_segmented_memory_block.h"

//#include "retrolib/file/test_file_utilities.h"
//#include "retrolib/file/test_file_streams.h"
 
//#include "retrolib/memory/test_memory_unions.h"
//#include "retrolib/memory/test_array.h"
//#include "retrolib/memory/test_data_vector.h"

//#include "retrolib/gfx/test_point_vector_2d.h"
//#include "retrolib/gfx/test_glyph.h"
//#include "retrolib/gfx/hga/test_hga.h"
//#include "retrolib/gfx/hga/test_write_glyph.h"

//#include "retrolib/automata/test_count_neighbours.h"

//#include "gamelife/dosgol.h"


//int main(int argc, char* argv[]) {
int main() {

	std::cout
		<< bios::video_adapter_names[bios::detect_video_adapter_type()] << '\n'
		<< "light pen registers = " << hga::read_light_pen_registers() << '\n'
	;
	bios::print_VDDA();

	//test_write_glyph::run();

}