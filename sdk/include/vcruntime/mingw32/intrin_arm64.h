/*
	Compatibility <intrin.h> header for GCC -- GCC equivalents of intrinsic
	Microsoft Visual C++ functions. Originally developed for the ReactOS
	(<https://reactos.org/>) and TinyKrnl (<http://www.tinykrnl.org/>)
	projects.

	Copyright (c) 2006 KJK::Hyperion <hackbunny@reactos.com>

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE.
*/

#ifndef KJK_INTRIN_ARM64_H_
#define KJK_INTRIN_ARM64_H_

#ifndef __GNUC__
#error Unsupported compiler
#endif

#define _ReturnAddress() (__builtin_return_address(0))
#define _ReadWriteBarrier() __sync_synchronize()

__INTRIN_INLINE unsigned char _BitScanForward64(unsigned long * const Index, const unsigned long Mask)
{
	return 0;
}

__INTRIN_INLINE unsigned char _BitScanReverse64(unsigned long * const Index, const unsigned long Mask)
{
    return 0;
}

__INTRIN_INLINE unsigned char _interlockedbittestandset64(long long * a, const long b)
{
	return 0;
}

__INTRIN_INLINE unsigned char _interlockedbittestandreset64(long long * a, const long b)
{
	return 0;
}

__INTRIN_INLINE void * _InterlockedCompareExchangePointer(void * volatile * const Destination, void * const Exchange, void * const Comperand)
{
    return 0;
}

__INTRIN_INLINE void * _InterlockedExchangePointer(void * volatile * const Target, void * const Value)
{
    return 0;
}

__INTRIN_INLINE long _InterlockedExchangeAdd(volatile long * const dest, const long add)
{
    return 0;
}

#endif
/* EOF */
