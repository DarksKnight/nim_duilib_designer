// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is used for debugging assertion support.  The Lock class
// is functionally a wrapper around the LockImpl class, so the only
// real intelligence in the class is in the debugging logic.

#if !defined(NDEBUG)

#include "include/base/cef_lock.h"
#include "include/base/cef_logging.h"

namespace base {

CefLock::CefLock() : lock_() {
}

CefLock::~CefLock() {
  DCHECK(owning_thread_ref_.is_null());
}

void CefLock::AssertAcquired() const {
  DCHECK(owning_thread_ref_ == PlatformThread::CurrentRef());
}

void CefLock::CheckHeldAndUnmark() {
  DCHECK(owning_thread_ref_ == PlatformThread::CurrentRef());
  owning_thread_ref_ = PlatformThreadRef();
}

void CefLock::CheckUnheldAndMark() {
  // Hitting this DCHECK means that your code is trying to re-enter a lock that
  // is already held. The Chromium Lock implementation is not reentrant.
  // See "Why can the holder of a Lock not reacquire it?" at
  // http://www.chromium.org/developers/lock-and-condition-variable for more
  // information.
  DCHECK(owning_thread_ref_.is_null());
  owning_thread_ref_ = PlatformThread::CurrentRef();
}

}  // namespace base

#endif  // NDEBUG
