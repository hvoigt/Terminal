/*++
Copyright (c) Microsoft Corporation

Module Name:
- RowCellIterator.hpp

Abstract:
- Read-only view into cells already in the input buffer.
- This is done for performance reasons (avoid heap allocs and copies).

Author:
- Michael Niksa (MiNiksa) 12-Oct-2018

--*/

#pragma once

#include "CharRow.hpp"
#include "OutputCellView.hpp"

class RowCellIterator final
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = OutputCellView;
    using difference_type = ptrdiff_t;
    using pointer = OutputCellView*;
    using reference = OutputCellView&;

    RowCellIterator(const ROW& row, const size_t start, const size_t length);
    ~RowCellIterator() = default;

    RowCellIterator& operator=(const RowCellIterator& it) = default;

    operator bool() const noexcept;

    bool operator==(const RowCellIterator& it) const noexcept;
    bool operator!=(const RowCellIterator& it) const noexcept;

    RowCellIterator& operator+=(const ptrdiff_t& movement);
    RowCellIterator& operator++();
    RowCellIterator operator++(int);
    RowCellIterator operator+(const ptrdiff_t& movement);

    const OutputCellView& operator*() const;
    const OutputCellView* operator->() const;

private:
    const ROW& _row;
    const size_t _start;
    const size_t _length;

    size_t _pos;
    OutputCellView _view;

    void _RefreshView();
    static OutputCellView s_GenerateView(const ROW& row, const size_t pos);
};
