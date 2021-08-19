/*!
  @file cpuinfo.hpp
  CPU feature detection for SDL.

  @copyright (C) 2014-2016 Tristan Brindle <t.c.brindle@gmail.com>
  @copyright (C) 1997-2016 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#ifndef SDLXX_CPUINFO_HPP
#define SDLXX_CPUINFO_HPP

#include "SDL_cpuinfo.h"

#include "detail/wrapper.hpp"

namespace sdl {

/*!
 @defgroup CpuInfo CPU Feature Detection

 This category contains functions for gathering information about the
 processor's features.

 @{
 */

//! This function returns the number of CPU cores available.
inline int get_cpu_count() { return detail::c_call(::SDL_GetCPUCount); }

/*!
 This function returns the L1 cache line size of the CPU

 This is useful for determining multi-threaded structure padding
 or SIMD prefetch sizes.
 */
inline int get_cpu_cache_line_size() {
    return detail::c_call(::SDL_GetCPUCacheLineSize);
}

//! This function returns true if the CPU has the RDTSC instruction.
inline bool cpu_has_rdtsc() { return detail::c_call(::SDL_HasRDTSC); }

//! This function returns true if the CPU has AltiVec features.
inline bool cpu_has_altivec() { return detail::c_call(::SDL_HasAltiVec); }

//! This function returns true if the CPU has MMX features.
inline bool cpu_has_mmx() { return detail::c_call(::SDL_HasMMX); }

//! This function returns true if the CPU has 3DNow! features.
inline bool cpu_has_3dnow() { return detail::c_call(::SDL_Has3DNow); }

//! This function returns true if the CPU has SSE features.
inline bool cpu_has_sse() { return detail::c_call(::SDL_HasSSE); }

//! This function returns true if the CPU has SSE2 features.
inline bool cpu_has_sse2() { return detail::c_call(::SDL_HasSSE2); }

//! This function returns true if the CPU has SSE3 features.
inline bool cpu_has_sse3() { return detail::c_call(::SDL_HasSSE3); }

//! This function returns true if the CPU has SSE4.1 features.
inline bool cpu_has_sse41() { return detail::c_call(::SDL_HasSSE41); }

//! This function returns true if the CPU has SSE4.2 features.
inline bool cpu_has_sse42() { return detail::c_call(::SDL_HasSSE42); }

//! This function returns true if the CPU has AVX features.
inline bool cpu_has_avx() { return detail::c_call(::SDL_HasAVX); }

//! This function returns true if the CPU has AVX2 features.
inline bool cpu_has_avx2() { return detail::c_call(::SDL_HasAVX2); }

//! This function returns the amount of RAM configured in the system, in MB.
inline int get_system_ram() { return detail::c_call(::SDL_GetSystemRAM); }

} // end namespace sdl

#endif // SDLXX_CPUINFO_HPP
