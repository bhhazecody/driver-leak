#pragma once
#include "framework.h"

namespace driver
{
    typedef void (*winapi_t)(void*);
    static winapi_t winapi = {};
    static int32_t  process_id = {};

    struct communication_t 
    {
        int32_t  process_id;
        uint64_t address;
        uint64_t buffer;
        size_t   size;
    };

    void init(int32_t id, HMODULE lib)
    {
        process_id = id;
        winapi = reinterpret_cast<winapi_t>(GetProcAddress(lib, "NtUserUnregisterBadMemoryNotification"));
    }

    void read(uint64_t address, uint64_t* buffer, size_t size)
    {
        communication_t comm;
        comm.address = address;
        comm.process_id = process_id;
        comm.size = size;

        winapi(&comm);

        *buffer = comm.buffer;
    }

    void write(uint64_t address, uint64_t buffer, size_t size) 
    {
        communication_t comm;
        comm.address = address;
        comm.buffer = buffer;
        comm.process_id = process_id;
        comm.size = size;

        winapi(&comm);
    }
}