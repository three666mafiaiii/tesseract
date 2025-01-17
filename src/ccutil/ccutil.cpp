// Copyright 2008 Google Inc. All Rights Reserved.
// Author: scharron@google.com (Samuel Charron)
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ccutil.h"

namespace tesseract {
CCUtil::CCUtil() :
  params_(),
  INT_INIT_MEMBER(ambigs_debug_level, 0, "Debug level for unichar ambiguities",
                  &params_),
  BOOL_MEMBER(use_definite_ambigs_for_classifier, false, "Use definite"
              " ambiguities when running character classifier", &params_),
  BOOL_MEMBER(use_ambigs_for_adaption, false, "Use ambigs for deciding"
              " whether to adapt to a character", &params_) {
}

// Destructor.
// It is defined here, so the compiler can create a single vtable
// instead of weak vtables in every compilation unit.
CCUtil::~CCUtil() = default;

CCUtilMutex::CCUtilMutex() {
#ifdef _WIN32
  mutex_ = CreateMutex(0, FALSE, 0);
#else
  pthread_mutex_init(&mutex_, nullptr);
#endif
}

void CCUtilMutex::Lock() {
#ifdef _WIN32
  WaitForSingleObject(mutex_, INFINITE);
#else
  pthread_mutex_lock(&mutex_);
#endif
}

void CCUtilMutex::Unlock() {
#ifdef _WIN32
  ReleaseMutex(mutex_);
#else
  pthread_mutex_unlock(&mutex_);
#endif
}

} // namespace tesseract
