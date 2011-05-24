#include "ruby.h"
#include <libdrizzle/drizzle.h>

VALUE Drizzle;

void Init_drizzle();

static VALUE version(VALUE self)
{
  return rb_str_new2(drizzle_version());
}

static VALUE initialize(VALUE self)
{
  rb_raise(rb_eNameError, "private method `new' called for %s:Class. Please use create instead", rb_class2name(CLASS_OF(self)));
}

static VALUE create(VALUE self)
{
  drizzle_st *ptr = drizzle_create(NULL);
  return Data_Wrap_Struct(Drizzle, NULL, drizzle_free, ptr);
}

static VALUE clone(VALUE self)
{
  drizzle_st *ptr;
  Data_Get_Struct(self, drizzle_st, ptr);
  drizzle_st *cloned = drizzle_clone(NULL, ptr);
  return Data_Wrap_Struct(Drizzle, NULL, drizzle_free, cloned);
}

void Init_drizzle()
{
  Drizzle = rb_define_class("Drizzle", rb_cObject);
  rb_define_method(Drizzle, "initialize", initialize, 0);
  rb_define_singleton_method(Drizzle, "version", version, 0);
  rb_define_singleton_method(Drizzle, "create", create, 0);
  rb_define_method(Drizzle, "clone", clone, 0);
}
