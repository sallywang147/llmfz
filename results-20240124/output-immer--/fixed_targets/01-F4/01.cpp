#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <tuple>
#include <vector>

#include "fuzzer/FuzzedDataProvider.h"
#include "immer/detail/rbts/rbts.hpp"
#include "immer/detail/rbts/slice_right_mut_visitor.hpp"
#include "immer/memory_policy.hpp"
#include "immer/refcount/unsafe_refcount_policy.hpp"

namespace immer {
namespace detail {
namespace rbts {

using memory_policy_t = immer::memory_policy<
    immer::heap_policy<immer::cpp_heap>,
    immer::unsafe_refcount_policy,
    immer::no_lock_policy,
    immer::no_transience_policy,
    false,
    true>;

struct node
{
    using memory_policy = memory_policy_t;
    using heap_policy   = typename memory_policy::heap_policy;
    using refcount     = typename memory_policy::refcount;
    using lock_policy   = typename memory_policy::lock_policy;
    using transience    = typename memory_policy::transience;

    static constexpr auto bits = 2u;

    struct regular_pos
    {
        node* node_;
        size_t idx_;

        regular_pos(node* n, size_t i) : node_{n}, idx_{i} {}
    };

    struct regular_sub_pos
    {
        node* node_;
        size_t idx_;
        size_t end_;

        regular_sub_pos(node* n, size_t i, size_t e) : node_{n}, idx_{i}, end_{e} {}
    };

    static constexpr auto empty_size = 2u;

    node()
        : size_{empty_size}
    {}

    node(std::initializer_list<node*> l)
        : size_{l.size()}
    {
        for (auto e : l)
            children_[size_++] = e;
    }

    node(node&& n)
        : size_{n.size_}
    {
        std::swap(children_, n.children_);
    }

    node& operator=(node&& n)
    {
        if (this != &n) {
            size_ = n.size_;
            std::swap(children_, n.children_);
        }
        return *this;
    }

    node* clone() const
    {
        auto n = new node;
        for (size_t i = 0; i < size_; ++i)
            n->children_[i] = children_[i]->clone();
        return n;
    }

    size_t size() const { return size_; }

    node* get(size_t idx) const
    {
        return children_[idx];
    }

    node* set(size_t idx, node* v) const
    {
        auto n = clone();
        n->children_[idx] = v;
        return n;
    }

    node* push_back(node* v) const
    {
        if (size_ == empty_size) {
            auto n = new node;
            n->children_[0] = children_[0];
            n->children_[1] = v;
            return n;
        } else {
            auto n = clone();
            n->children_[size_++] = v;
            return n;
        }
    }

    node* assoc(size_t idx, node* v) const
    {
        if (idx < size_) {
            return set(idx, v);
        } else if (idx == size_) {
            return push_back(v);
        } else {
            IMMER_UNREACHABLE;
        }
    }

    node* take(size_t n) const
    {
        if (n == size_)
            return clone();
        else if (n < size_) {
            auto m = new node;
            for (size_t i = 0; i < n; ++i)
                m->children_[i] = children_[i];
            m->size_ = n;
            return m;
        } else {
            IMMER_UNREACHABLE;
        }
    }

    node* drop(size_t n) const
    {
        if (n == size_)
            return empty();
        else if (n < size_) {
            auto m = new node;
            for (size_t i = n; i < size_; ++i)
                m->children_[i - n] = children_[i];
            m->size_ = size_ - n;
            return m;
        } else {
            IMMER_UNREACHABLE;
        }
    }

    static node* empty()
    {
        static node r;
        return &r;
    }

private:
    size_t size_;
    node* children_[empty_size];
};

template <typename NodeT, typename VisitorT, bool Dir, bool Rev>
struct slice_right_mut_visitor
{
    using node_t = NodeT;
    using visitor_t = VisitorT;

    template <typename PosT>
    void visit_regular(std::tuple<PosT, typename node_t::regular_sub_pos*, size_t>& pos)
    {
        auto& [pos_, last, e] = pos;
        auto& n = pos_.node_;
        auto& l = *last;
        if (l.idx_ < l.end_) {
            if constexpr (Dir) {
                if constexpr (Rev) {
                    visit_regular(std::make_tuple(
                        node_t::regular_pos{n, l.end_ - 1}, &l, e));
                } else {
                    visit_regular(std::make_tuple(
                        node_t::regular_pos{n, l.idx_ + 1}, &l, e));
                }
            } else {
                if constexpr (Rev) {
                    visit_regular(std::make_tuple(
                        node_t::regular_pos{n, l.idx_}, &l, e));
                } else {
                    visit_regular(std::make_tuple(
                        node_t::regular_pos{n, l.end_ - 1}, &l, e));
                }
            }
        } else {
            if constexpr (Dir) {
                if constexpr (Rev) {
                    visitor_t::visit_inner(pos_);
                } else {
                    visitor_t::visit_inner(pos_);
                }
            } else {
                if constexpr (Rev) {
                    visitor_t::visit_inner(pos_);
                } else {
                    visitor_t::visit_inner(pos_);
                }
            }
        }
    }
};

} // namespace rbts
} // namespace detail
} // namespace immer

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  using namespace immer::detail::rbts;

  auto n = node::empty();
  for (size_t i = 0; i < stream.ConsumeIntegralInRange<size_t>(0, 1000); ++i) {
    n = n->push_back(node::empty());
  }

  auto pos = std::make_tuple(node::regular_pos{n, 0},
                             nullptr,
                             stream.ConsumeIntegralInRange<size_t>(0, n->size()));
  auto last = node::regular_sub_pos{n, 0, 0};
  auto e = stream.ConsumeIntegralInRange<size_t>(0, n->size());

  slice_right_mut_visitor<node, slice_right_mut_visitor<node, void, true, true>, true, true>::visit_regular<node::regular_pos>(pos, &last, e);

  return 0;
}