/*
 * $Id: json.h,v 1.6 2006/01/26 02:16:28 mclark Exp $
 *
 * Copyright (c) 2004, 2005 Metaparadigm Pte. Ltd.
 * Michael Clark <michael@metaparadigm.com>
 * Copyright (c) 2009 Hewlett-Packard Development Company, L.P.
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See COPYING for details.
 *
 */

#ifndef _json_h_
#define _json_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "json_config.h"
#include "json_inttypes.h"
#include "json_bits.h"
#include "json_debug.h"
#include "json_linkhash.h"
#include "json_arraylist.h"
#include "json_util.h"
#include "json_object.h"
#include "json_tokener.h"
#include "json_object_iterator.h"
#include "json_c_version.h"
#include "json_printbuf.h"

#ifdef __cplusplus
}
#endif



#ifdef __cplusplus

//(A)::AFEW 2014-08-19
// for only c++ application

json_type    jsoncpp_t(struct json_object *jso);								// call json_object_get_type

json_object* jsoncpp_root(const char* str_buf);									// call json_tokener_parse(str_buf);

int          jsoncpp_release(json_object** jso);								// release all object

json_object* jsoncpp_o(json_object* jso											// get the sub object with key
						, const char* k0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						);

int          jsoncpp_b(json_object* jso, const char* key);						// get the boolean value
int          jsoncpp_b(json_object* jso
						, const char* k0, const char* k1
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						);
int          jsoncpp_b(json_object* jso, int _idx
						, const char* k0, const char* k1
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						);


int          jsoncpp_i(json_object* jso, const char* key);						// get the int32 value
int          jsoncpp_i(json_object* jso
						, const char* k0, const char* k1
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						);
int          jsoncpp_i(json_object* jso, int _idx
						, const char* k0, const char* k1
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						);


double       jsoncpp_d(json_object* jso, const char* key);						// get the double value
double       jsoncpp_d(json_object* jso
						, const char* k0, const char* k1
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						);
double       jsoncpp_d(json_object* jso, int _idx
						, const char* k0, const char* k1
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						);


float        jsoncpp_f(json_object* jso, const char* key);						// get the double value
float        jsoncpp_f(json_object* jso
						, const char* k0, const char* k1
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						);
float        jsoncpp_f(json_object* jso, int _idx
						, const char* k0, const char* k1
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						);


const char*  jsoncpp_s(json_object* jso, const char* key);						// get the string value
const char*  jsoncpp_s(json_object* jso
						, const char* k0, const char* k1
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						);
const char*  jsoncpp_s(json_object* jso, int _idx
						, const char* k0, const char* k1
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						, const char* =0, const char* =0
						);

#endif

#endif
