#include "downpour.h"

#define SELF_TYPE drizzle_query_st

static VALUE get_result(VALUE self)
{
  read_self_ptr();

  VALUE cached_result = rb_iv_get(self, "@result");
  if(cached_result != Qnil)
    return cached_result;

  drizzle_result_st *result = drizzle_query_result(self_ptr);
  VALUE ret = rb_iv_set(self, "@result", downpour_result_constructor(result, rb_iv_get(self, "@connection")));
  return ret;
}

VALUE downpour_query_constructor(drizzle_query_st *self_ptr, VALUE status, VALUE connection)
{
  VALUE query = Data_Wrap_Struct(DrizzleQuery, NULL, drizzle_query_free, self_ptr);
  rb_iv_set(query, "@status", status);
  rb_iv_set(query, "@connection", connection);
  return query;
}

void init_drizzle_query()
{
  DrizzleQuery = drizzle_gem_create_class_with_private_constructor("Query", rb_cObject);
  rb_define_method(DrizzleQuery, "result", get_result, 0);
}
