#include <iostream>
#include <fstream>

//#include "retrolib/bios/bios_video_services.h"
//#include "retrolib/bios/test_keyboard.h"

//#include "retrolib/dos/dos_segmented_memory_block.h"

//#include "retrolib/file/test_file_utilities.h"
//#include "retrolib/file/test_file_streams.h"
 
//#include "retrolib/memory/test_memory_unions.h"
//#include "retrolib/memory/test_array.h"
//#include "retrolib/memory/test_data_vector.h"

// GFX
//		MDA
#include "retrolib/gfx/mda/mode7/test_mode7.h"
//		HGA
//#include "retrolib/gfx/test_point_vector_2d.h"
//#include "retrolib/gfx/test_glyph.h"
//#include "retrolib/gfx/hga/hga_read_lightpen_registers.h"
//#include "retrolib/gfx/hga/test_hga.h"
//#include "retrolib/gfx/hga/test_write_glyph.h"
//		CGA
//		EGA
//		MCGA
//		VGA
// #include "retrolib/gfx/vga/test_vga.h"

//#include "retrolib/automata/test_count_neighbours.h"

//#include "gamelife/dosgol.h"

//int main(int argc, char* argv[]) {
int main() {

	test_mode7::run();

}