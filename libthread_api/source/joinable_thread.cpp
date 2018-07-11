#include "joinable_thread.h"
#include "cancellation_guard.h"

#include <cassert>

using sys::joinable_thread;

joinable_thread::~joinable_thread()
{ interrupt(); }

void joinable_thread::interrupt()
{
    if(!impl_.joinable()) return;

    token_.cancel();
    impl_.join();
}

joinable_thread::id joinable_thread::get_id() const noexcept
{   return impl_.get_id(); }

unsigned int joinable_thread::hardware_concurrency() noexcept
{   return std::thread::hardware_concurrency(); }

joinable_thread::native_handle_type joinable_thread::native_handle()
{   return impl_.native_handle(); }
