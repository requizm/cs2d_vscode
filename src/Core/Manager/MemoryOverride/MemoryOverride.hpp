#ifndef MEMORYOVERRIDE_H
#define MEMORYOVERRIDE_H

#include <iostream>
#if defined(WIN32) && defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>


inline void *operator new(std ::size_t count)
{
    auto ptr = malloc(count);
    TracyAlloc(ptr, count);
    return ptr;
}

inline void operator delete(void* ptr) noexcept
{
TracyFree (ptr);
free(ptr);
}
#endif

#endif // MEMORYOVERRIDE_H