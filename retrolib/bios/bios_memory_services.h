/*****************************************************************//**
 * \file   bios_memory_tools.h
 * \brief  
 * 
 * \author ifkno
 * \date   September 2021
 *********************************************************************/
//#pragma once

#ifndef BIOS_MEMORY_TOOLS_H
#define BIOS_MEMORY_TOOLS_H

#include <stdint.h> 

#include "bios_memory_services_constants.h"

#define ENABLE_EBDA // enable Extended BIOS Data Area services

namespace bios {

	/**
	 * \brief Detecting Low Memory INT 12h - get memory size. 
	 * 
	 * "Low memory" is the available RAM below 1MB, and usually below 640KB. 
	 * The INT 0x12 call will return AX = total number of KB. 
	 * The AX value measures from 0, up to the bottom of the EBDA 
	 * 
	 * \note Do not use the first 0x500 bytes of the space either - i.e. the IVT or BDA.
	 * \note This call returns the contents of the word at 0040h:0013h.
	 * \note This function is supposed to be always present, and may not modify the carry flag. 
	 * If an emulator doesn't support it, the carry flag will be set, indicating error.
	 * 
	 * \return kilobytes of contiguous memory starting at absolute address 00000h
	 * 0 indicates error 
	 */
	inline uint16_t get_low_memory_size() {
		uint16_t kbytes = 0;
		__asm {
			.8086
			push	ax
				
			clc					; Clear carry flag
			int		0x12		; Switch to the BIOS(= request low memory size)
			jc		ERR			; The carry flag is set if it failed
			mov		kbytes, ax

ERR:		pop		ax
		}
		return kbytes;
	}

	/**
	 * .
	 * 
	 * \return the segment address of the top of free low memory area
	 */
	inline uint16_t get_ram_segment_top() {
		return (get_low_memory_size() * 0x40) ;
	}

#ifdef ENABLE_EBDA 

	/**
	 * Some BIOSes store additional data in the last 1 KB of conventional memory. 
	 * In general this so-called Extended BIOS Data Area will be used to hold data 
	 * for a mouse port, hard disk parameters and disk track buffers. 
	 * The EBDA segment is normally stored in the BIOS Data Area at 0040:000Eh, 
	 * a location that was originally used to store the port number for parallel port 4. 
	 * This pointer is typically set to 9FC0h, 
	 * representing a 1 KB memory area just below the top of conventional memory. 
	 * A few systems may reserve 2 KB or even 4 KB for the EBDA.
	 * 
	 * \return 
	 */
	inline uint16_t get_ebda_segment() {
		uint16_t ebda;
		__asm {
			.8086
			push	ax

			mov		ax, RAM_SEGMENT_BDA
			mov		es, ax
			mov		ax, [es:PORT_ADDRESS_LPT4]	; get the segment of the EBDA
			mov		ebda, ax

			pop		ax
		}
		return ebda;
	}

	/**
	 * offset 00h - Size of Extended BIOS Data Area	1 byte	1 = 1024 bytes; 2 = 2048 bytes.
	 * 
	 * \return size in bytes of the EBDA 
	 */
	inline uint8_t get_ebda_size() {
		uint8_t size = 0;
		__asm {
			.8086
			push	ax

			mov		ax, RAM_SEGMENT_BDA
			mov		es, ax
			mov		ax, [es:PORT_ADDRESS_LPT4]	; get the segment of the EBDA
			mov		es, ax						; es now points to EBDA
			mov		al, [es:0h]					; number of bytes allocated to EBDA in Kbytes
			mov		size, al

			pop		ax
		}
		return size;
	}

#endif

}

#endif