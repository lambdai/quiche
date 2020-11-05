// Copyright (c) 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/third_party/quiche/src/quic/test_tools/qpack/qpack_test_utils.h"

#include <limits>
#include "net/third_party/quiche/src/quic/platform/api/quic_bug_tracker.h"

namespace quic {
namespace test {

FragmentSizeGenerator FragmentModeToFragmentSizeGenerator(
    FragmentMode fragment_mode) {
  switch (fragment_mode) {
    case FragmentMode::kSingleChunk:
      return []() { return std::numeric_limits<size_t>::max(); };
    case FragmentMode::kOctetByOctet:
      return []() { return 1; };
  }
  QUIC_BUG << "Unknown FragmentMode " << static_cast<int>(fragment_mode);
  return []() { return 0; };
}

}  // namespace test
}  // namespace quic
