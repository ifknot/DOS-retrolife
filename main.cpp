//#include "retrolib/dos/dos_segmented_memory_block.h"
//#include "retrolib/gfx/hga/test_hga.h"
//#include "retrolib/file/test_file_utilities.h"
//#include "retrolib/file/test_file_streams.h"
//#include "retrolib/memory/test_array.h"
//#include "retrolib/memory/test_data_vector.h"
//#include "retrolib/gfx/test_point_vector_2d.h"
//#include "retrolib/memory/test_memory_unions.h"
//#include "retrolib/automata/test_count_neighbours.h"

#include "gamelife/dosgol.h"

int main(int argc, char* argv[]) {
//int main() {

    return dosgol::run(argc, argv);

}