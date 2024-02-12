 #include <cstdint>
#include <vector>
#include <string>

#define exprtk_enable_range_runtime_checks
#include "exprtk.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
   typedef exprtk::details::expression_node<float> expression_node_t;
   typedef exprtk::details::vec_binop_vecvec_node<float, exprtk::details::div_op<float> > vec_binop_vecvec_node_t;
   typedef exprtk::details::node_allocator<vec_binop_vecvec_node_t> node_allocator_t;

   std::vector<expression_node_t*> nodes;
   nodes.reserve(1024);

   std::vector<vec_binop_vecvec_node_t*> vec_binop_vecvec_nodes;
   vec_binop_vecvec_nodes.reserve(1024);

   std::vector<int*> ints;
   ints.reserve(1024);

   std::vector<std::string> strings;
   strings.reserve(1024);

   std::vector<std::vector<float>> vec_floats;
   vec_floats.reserve(1024);

   FuzzedDataProvider provider(data, size);

   while (provider.remaining_bytes() > 0)
   {
      const uint8_t type = provider.ConsumeIntegral<uint8_t>();

      switch (type)
      {
         case 0:
         {
            nodes.push_back(new expression_node_t(provider.ConsumeIntegral<float>()));
            break;
         }
         case 1:
         {
            vec_binop_vecvec_nodes.push_back(new vec_binop_vecvec_node_t(provider.ConsumeIntegral<float>()));
            break;
         }
         case 2:
         {
            ints.push_back(new int(provider.ConsumeIntegral<int>()));
            break;
         }
         case 3:
         {
            const std::string str = provider.ConsumeRemainingBytesAsString();
            strings.push_back(str);
            break;
         }
         case 4:
         {
            const size_t size = provider.ConsumeIntegral<size_t>();
            std::vector<float> vec(size);
            for (size_t i = 0; i < size; ++i)
            {
               vec[i] = provider.ConsumeIntegral<float>();
            }
            vec_floats.push_back(vec);
            break;
         }
         default:
         {
            break;
         }
      }
   }

   node_allocator_t allocator;

   for (size_t i = 0; i < vec_binop_vecvec_nodes.size(); ++i)
   {
      allocator.allocate_rrr<vec_binop_vecvec_node_t, exprtk::details::operator_type const, expression_node_t*, expression_node_t*>(nullptr, nullptr, &nodes[i], &nodes[i]);
   }

   for (auto node : nodes)
   {
      delete node;
   }
   for (auto node : vec_binop_vecvec_nodes)
   {
      delete node;
   }
   for (auto int_ptr : ints)
   {
      delete int_ptr;
   }

   return 0;
}