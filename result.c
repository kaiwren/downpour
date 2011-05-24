#include "drizzle.h"

#define SELF_TYPE drizzle_result_st

static VALUE buffer(VALUE self)
{
  read_self_ptr();

  CHECK_OK(drizzle_result_buffer(self_ptr));
}

static VALUE row_count(VALUE self)
{
  buffer(self);
  read_self_ptr();
  return UINT2NUM(drizzle_result_row_count(self_ptr));
}

static VALUE next_row(VALUE self)
{
  buffer(self);
  read_self_ptr();
  return drizzle_gem_to_string_array(drizzle_row_next(self_ptr));
}

void init_drizzle_result()
{
  DrizzleResult = drizzle_gem_create_class_with_private_constructor("Result", rb_cObject);
  rb_define_method(DrizzleResult, "row_count", row_count, 0);
  rb_define_method(DrizzleResult, "buffer", buffer, 0);
  rb_define_method(DrizzleResult, "next_row", next_row, 0);
}
