#include "../registry.hpp"

#include "FN_types.hpp"
#include "FN_functions.hpp"

#include "RNA_access.h"

namespace FN {
namespace DataFlowNodes {

using BLI::float3;
using BLI::rgba_f;

static void LOAD_float(PointerRNA *rna, Tuple &tuple, uint index)
{
  float value = RNA_float_get(rna, "value");
  tuple.set<float>(index, value);
}

static void LOAD_vector(PointerRNA *rna, Tuple &tuple, uint index)
{
  float3 vector;
  RNA_float_get_array(rna, "value", vector);
  tuple.set<float3>(index, vector);
}

static void LOAD_integer(PointerRNA *rna, Tuple &tuple, uint index)
{
  int value = RNA_int_get(rna, "value");
  tuple.set<int32_t>(index, value);
}

static void LOAD_boolean(PointerRNA *rna, Tuple &tuple, uint index)
{
  bool value = RNA_boolean_get(rna, "value");
  tuple.set<bool>(index, value);
}

static void LOAD_object(PointerRNA *rna, Tuple &tuple, uint index)
{
  Object *value = (Object *)RNA_pointer_get(rna, "value").id.data;
  tuple.set<Object *>(index, value);
}

static void LOAD_color(PointerRNA *rna, Tuple &tuple, uint index)
{
  rgba_f color;
  RNA_float_get_array(rna, "value", color);
  tuple.set<rgba_f>(index, color);
}

template<typename T> static void LOAD_empty_list(PointerRNA *UNUSED(rna), Tuple &tuple, uint index)
{
  auto list = Types::SharedList<T>::New();
  tuple.move_in(index, list);
}

void register_socket_loaders(SocketLoaderRegistry &registry)
{
  registry.loader("Float", LOAD_float);
  registry.loader("Vector", LOAD_vector);
  registry.loader("Integer", LOAD_integer);
  registry.loader("Boolean", LOAD_boolean);
  registry.loader("Object", LOAD_object);
  registry.loader("Color", LOAD_color);
  registry.loader("Float List", LOAD_empty_list<float>);
  registry.loader("Vector List", LOAD_empty_list<float3>);
  registry.loader("Integer List", LOAD_empty_list<int32_t>);
  registry.loader("Boolean List", LOAD_empty_list<bool>);
  registry.loader("Object List", LOAD_empty_list<Object *>);
  registry.loader("Color List", LOAD_empty_list<rgba_f>);
}

}  // namespace DataFlowNodes
}  // namespace FN