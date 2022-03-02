// Copyright 2021 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "common/quiche_mem_slice_storage.h"

#include "quic/core/quic_utils.h"

namespace quiche {

QuicheMemSliceStorage::QuicheMemSliceStorage(
    const struct iovec* iov, int iov_count,
    quic::QuicBufferAllocator* allocator,
    const quic::QuicByteCount max_slice_len) {
  if (iov == nullptr) {
    return;
  }
  quic::QuicByteCount write_len = 0;
  for (int i = 0; i < iov_count; ++i) {
    write_len += iov[i].iov_len;
  }
  QUICHE_DCHECK_LT(0u, write_len);

  size_t io_offset = 0;
  while (write_len > 0) {
    size_t slice_len = std::min(write_len, max_slice_len);
    quic::QuicBuffer buffer(allocator, slice_len);
    quic::QuicUtils::CopyToBuffer(iov, iov_count, io_offset, slice_len,
                                  buffer.data());
    storage_.push_back(QuicheMemSlice(std::move(buffer)));
    write_len -= slice_len;
    io_offset += slice_len;
  }
}

}  // namespace quiche