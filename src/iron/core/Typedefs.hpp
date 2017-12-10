#pragma once

// Threading
namespace iron {

typedef boost::shared_mutex        Mutex;
typedef boost::shared_lock<Mutex>  ReadLock;
typedef boost::unique_lock<Mutex>  WriteLock;

} /* iron */
