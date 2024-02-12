 #include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/model/document_comparator.h"
#include "Firestore/core/src/model/field_path.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/types.h"
#include "Firestore/core/src/query/query.h"
#include "Firestore/core/src/query/query_builder.h"
#include "Firestore/core/src/query/query_comparators.h"

using firebase::firestore::core::OrderBy;
using firebase::firestore::core::Query;
using firebase::firestore::core::QueryComparator;
using firebase::firestore::core::QueryDirection;
using firebase::firestore::core::QuerySnapshot;
using firebase::firestore::core::ResourcePath;
using firebase::firestore::model::DocumentComparator;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::FieldPath;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::Type;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};

  // Test Query::Comparator(DocumentComparator*, Query*) const.
  try {
    Query query;
    DocumentComparator comparator;
    query.Comparator(&comparator, &query);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Comparator(DocumentComparator*) const.
  try {
    Query query;
    DocumentComparator comparator;
    query.Comparator(&comparator);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Comparator() const.
  try {
    Query query;
    query.Comparator();
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::KeyComparator() const.
  try {
    Query query;
    query.KeyComparator();
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::DocumentKeyComparator() const.
  try {
    Query query;
    query.DocumentKeyComparator();
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::OrderBy(const FieldPath&, QueryDirection) const.
  try {
    Query query;
    query.OrderBy(FieldPath::FromDotSeparatedString("foo.bar"),
                  QueryDirection::Ascending);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::OrderBy(const FieldPath&, QueryDirection, bool) const.
  try {
    Query query;
    query.OrderBy(FieldPath::FromDotSeparatedString("foo.bar"),
                  QueryDirection::Ascending, false);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::OrderBy(const std::vector<OrderBy>&) const.
  try {
    std::vector<OrderBy> order_by;
    order_by.push_back(OrderBy(FieldPath::FromDotSeparatedString("foo.bar"),
                               QueryDirection::Ascending, false));
    Query query;
    query.OrderBy(order_by);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::OrderBy(const FieldPath&) const.
  try {
    Query query;
    query.OrderBy(FieldPath::FromDotSeparatedString("foo.bar"));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::OrderBy(const FieldPath&, bool) const.
  try {
    Query query;
    query.OrderBy(FieldPath::FromDotSeparatedString("foo.bar"), false);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::OrderBy(const std::vector<FieldPath>&) const.
  try {
    std::vector<FieldPath> field_path;
    field_path.push_back(FieldPath::FromDotSeparatedString("foo.bar"));
    Query query;
    query.OrderBy(field_path);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&) const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&)
  // const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&) const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5), FieldValue::Integer(6));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&)
  // const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5), FieldValue::Integer(6),
                  FieldValue::Integer(7));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&) const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5), FieldValue::Integer(6),
                  FieldValue::Integer(7), FieldValue::Integer(8));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5), FieldValue::Integer(6),
                  FieldValue::Integer(7), FieldValue::Integer(8),
                  FieldValue::Integer(9));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5), FieldValue::Integer(6),
                  FieldValue::Integer(7), FieldValue::Integer(8),
                  FieldValue::Integer(9), FieldValue::Integer(10));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&)
  // const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5), FieldValue::Integer(6),
                  FieldValue::Integer(7), FieldValue::Integer(8),
                  FieldValue::Integer(9), FieldValue::Integer(10),
                  FieldValue::Integer(11));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&) const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5), FieldValue::Integer(6),
                  FieldValue::Integer(7), FieldValue::Integer(8),
                  FieldValue::Integer(9), FieldValue::Integer(10),
                  FieldValue::Integer(11), FieldValue::Integer(12));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5), FieldValue::Integer(6),
                  FieldValue::Integer(7), FieldValue::Integer(8),
                  FieldValue::Integer(9), FieldValue::Integer(10),
                  FieldValue::Integer(11), FieldValue::Integer(12),
                  FieldValue::Integer(13));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5), FieldValue::Integer(6),
                  FieldValue::Integer(7), FieldValue::Integer(8),
                  FieldValue::Integer(9), FieldValue::Integer(10),
                  FieldValue::Integer(11), FieldValue::Integer(12),
                  FieldValue::Integer(13), FieldValue::Integer(14));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&)
  // const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5), FieldValue::Integer(6),
                  FieldValue::Integer(7), FieldValue::Integer(8),
                  FieldValue::Integer(9), FieldValue::Integer(10),
                  FieldValue::Integer(11), FieldValue::Integer(12),
                  FieldValue::Integer(13), FieldValue::Integer(14),
                  FieldValue::Integer(15));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&) const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5), FieldValue::Integer(6),
                  FieldValue::Integer(7), FieldValue::Integer(8),
                  FieldValue::Integer(9), FieldValue::Integer(10),
                  FieldValue::Integer(11), FieldValue::Integer(12),
                  FieldValue::Integer(13), FieldValue::Integer(14),
                  FieldValue::Integer(15), FieldValue::Integer(16));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5), FieldValue::Integer(6),
                  FieldValue::Integer(7), FieldValue::Integer(8),
                  FieldValue::Integer(9), FieldValue::Integer(10),
                  FieldValue::Integer(11), FieldValue::Integer(12),
                  FieldValue::Integer(13), FieldValue::Integer(14),
                  FieldValue::Integer(15), FieldValue::Integer(16),
                  FieldValue::Integer(17));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5), FieldValue::Integer(6),
                  FieldValue::Integer(7), FieldValue::Integer(8),
                  FieldValue::Integer(9), FieldValue::Integer(10),
                  FieldValue::Integer(11), FieldValue::Integer(12),
                  FieldValue::Integer(13), FieldValue::Integer(14),
                  FieldValue::Integer(15), FieldValue::Integer(16),
                  FieldValue::Integer(17), FieldValue::Integer(18));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&)
  // const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5), FieldValue::Integer(6),
                  FieldValue::Integer(7), FieldValue::Integer(8),
                  FieldValue::Integer(9), FieldValue::Integer(10),
                  FieldValue::Integer(11), FieldValue::Integer(12),
                  FieldValue::Integer(13), FieldValue::Integer(14),
                  FieldValue::Integer(15), FieldValue::Integer(16),
                  FieldValue::Integer(17), FieldValue::Integer(18),
                  FieldValue::Integer(19));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::StartAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&) const.
  try {
    Query query;
    query.StartAt(FieldValue::Integer(1), FieldValue::Integer(2),
                  FieldValue::Integer(3), FieldValue::Integer(4),
                  FieldValue::Integer(5), FieldValue::Integer(6),
                  FieldValue::Integer(7), FieldValue::Integer(8),
                  FieldValue::Integer(9), FieldValue::Integer(10),
                  FieldValue::Integer(11), FieldValue::Integer(12),
                  FieldValue::Integer(13), FieldValue::Integer(14),
                  FieldValue::Integer(15), FieldValue::Integer(16),
                  FieldValue::Integer(17), FieldValue::Integer(18),
                  FieldValue::Integer(19), FieldValue::Integer(20));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&) const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&)
  // const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&) const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5), FieldValue::Integer(6));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&)
  // const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5), FieldValue::Integer(6),
                FieldValue::Integer(7));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&) const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5), FieldValue::Integer(6),
                FieldValue::Integer(7), FieldValue::Integer(8));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5), FieldValue::Integer(6),
                FieldValue::Integer(7), FieldValue::Integer(8),
                FieldValue::Integer(9));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5), FieldValue::Integer(6),
                FieldValue::Integer(7), FieldValue::Integer(8),
                FieldValue::Integer(9), FieldValue::Integer(10));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&)
  // const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5), FieldValue::Integer(6),
                FieldValue::Integer(7), FieldValue::Integer(8),
                FieldValue::Integer(9), FieldValue::Integer(10),
                FieldValue::Integer(11));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&) const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5), FieldValue::Integer(6),
                FieldValue::Integer(7), FieldValue::Integer(8),
                FieldValue::Integer(9), FieldValue::Integer(10),
                FieldValue::Integer(11), FieldValue::Integer(12));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5), FieldValue::Integer(6),
                FieldValue::Integer(7), FieldValue::Integer(8),
                FieldValue::Integer(9), FieldValue::Integer(10),
                FieldValue::Integer(11), FieldValue::Integer(12),
                FieldValue::Integer(13));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5), FieldValue::Integer(6),
                FieldValue::Integer(7), FieldValue::Integer(8),
                FieldValue::Integer(9), FieldValue::Integer(10),
                FieldValue::Integer(11), FieldValue::Integer(12),
                FieldValue::Integer(13), FieldValue::Integer(14));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&)
  // const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5), FieldValue::Integer(6),
                FieldValue::Integer(7), FieldValue::Integer(8),
                FieldValue::Integer(9), FieldValue::Integer(10),
                FieldValue::Integer(11), FieldValue::Integer(12),
                FieldValue::Integer(13), FieldValue::Integer(14),
                FieldValue::Integer(15));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&) const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5), FieldValue::Integer(6),
                FieldValue::Integer(7), FieldValue::Integer(8),
                FieldValue::Integer(9), FieldValue::Integer(10),
                FieldValue::Integer(11), FieldValue::Integer(12),
                FieldValue::Integer(13), FieldValue::Integer(14),
                FieldValue::Integer(15), FieldValue::Integer(16));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5), FieldValue::Integer(6),
                FieldValue::Integer(7), FieldValue::Integer(8),
                FieldValue::Integer(9), FieldValue::Integer(10),
                FieldValue::Integer(11), FieldValue::Integer(12),
                FieldValue::Integer(13), FieldValue::Integer(14),
                FieldValue::Integer(15), FieldValue::Integer(16),
                FieldValue::Integer(17));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&) const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5), FieldValue::Integer(6),
                FieldValue::Integer(7), FieldValue::Integer(8),
                FieldValue::Integer(9), FieldValue::Integer(10),
                FieldValue::Integer(11), FieldValue::Integer(12),
                FieldValue::Integer(13), FieldValue::Integer(14),
                FieldValue::Integer(15), FieldValue::Integer(16),
                FieldValue::Integer(17), FieldValue::Integer(18));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&)
  // const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5), FieldValue::Integer(6),
                FieldValue::Integer(7), FieldValue::Integer(8),
                FieldValue::Integer(9), FieldValue::Integer(10),
                FieldValue::Integer(11), FieldValue::Integer(12),
                FieldValue::Integer(13), FieldValue::Integer(14),
                FieldValue::Integer(15), FieldValue::Integer(16),
                FieldValue::Integer(17), FieldValue::Integer(18),
                FieldValue::Integer(19));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::EndAt(const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&, const FieldValue&, const FieldValue&, const FieldValue&,
  // const FieldValue&) const.
  try {
    Query query;
    query.EndAt(FieldValue::Integer(1), FieldValue::Integer(2),
                FieldValue::Integer(3), FieldValue::Integer(4),
                FieldValue::Integer(5), FieldValue::Integer(6),
                FieldValue::Integer(7), FieldValue::Integer(8),
                FieldValue::Integer(9), FieldValue::Integer(10),
                FieldValue::Integer(11), FieldValue::Integer(12),
                FieldValue::Integer(13), FieldValue::Integer(14),
                FieldValue::Integer(15), FieldValue::Integer(16),
                FieldValue::Integer(17), FieldValue::Integer(18),
                FieldValue::Integer(19), FieldValue::Integer(20));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Where(const FieldPath&, const FieldValue&, const FieldValue&)
  // const.
  try {
    Query query;
    query.Where(FieldPath::FromDotSeparatedString("foo.bar"),
                FieldValue::Integer(1), FieldValue::Integer(2));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Where(const FieldPath&, const FieldValue&) const.
  try {
    Query query;
    query.Where(FieldPath::FromDotSeparatedString("foo.bar"),
                FieldValue::Integer(1));