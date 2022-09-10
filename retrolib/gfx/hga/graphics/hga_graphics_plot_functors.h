/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      6.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_GRAPHICS_PLOT_FUNCTORS_H
#define HGA_GRAPHICS_PLOT_FUNCTORS_H

#include "hga_graphics_is_plot_point.h"
#include "hga_graphics_plot_multi_point.h"

namespace hga {

	namespace graphics {

		namespace screen_bound {


			struct is_plot_point_functor {

				inline bool operator()(uint32_t point, uint8_t buffer = 0) {
					return is_plot_point(point, buffer);
				}

			};

			struct plot_multi_point_functor {

				inline void operator()(const uint32_t* point_data, uint16_t size, uint8_t buffer = 0) {
					plot_multi_point(point_data, size, buffer);
				}

			};

		}

		namespace toroid_bound {



		}

	}

}

#endif