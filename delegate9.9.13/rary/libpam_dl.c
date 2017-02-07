/*////////////////////////////////////////////////////////////////////////
Copyright (c) 2006 National Institute of Advanced Industrial Science and Technology (AIST)

Permission to use this material for noncommercial and/or evaluation
purpose, copy this material for your own use, and distribute the copies
via publicly accessible on-line media, without fee, is hereby granted
provided that the above copyright notice and this permission notice
appear in all copies.
AIST MAKES NO REPRESENTATIONS ABOUT THE ACCURACY OR SUITABILITY OF THIS
MATERIAL FOR ANY PURPOSE.  IT IS PROVIDED "AS IS", WITHOUT ANY EXPRESS
OR IMPLIED WARRANTIES.
/////////////////////////////////////////////////////////////////////////
Content-Type:	program/C; charset=US-ASCII
Program:	libpam.c (PAM as an optional dynamic library)
Author:		Yutaka Sato <ysato@delegate.org>
Description:

History:
	061009	created
//////////////////////////////////////////////////////////////////////#*/
#include <stdio.h>
#include <stdlib.h>
#include "ystring.h"
#include "log.h"

/*BEGIN_STAB(pam)*/
#include <stdio.h> /*DLST*/
#define PCStr(s) const char *s /*DLST*/
#define ISDLIB /*DLST*/
/*DLST*/ typedef struct {const char*name; void*addr; const char*opt;} DLMap;
/*DLST*/ extern DLMap dlmap_pam[];
/*DLST*/ void *dgdlsym(DLMap*,const char *sym);
#define mydlsym(s) dgdlsym(dlmap_pam,s)
#line 27
#if defined(__cplusplus)
extern "C" {
#endif
typedef int (*iiFUNCP)(int,...);
struct pam_conv {
        iiFUNCP conv;
        void   *appdata_ptr;
};
int pam_start(const char *s,const char *u,const struct pam_conv *c,void**h);
/*DLST*/ int pam_start(const char *s,const char *u,const struct pam_conv *c,void**h);
/*DLST*/ int (*pam_start_PTR_)(const char *s,const char *u,const struct pam_conv *c,void**h);
#define pam_start (*pam_start_PTR_) /*DLST*/
#line 36
int pam_end(void *ph,int ps);
/*DLST*/ int pam_end(void *ph,int ps);
/*DLST*/ int (*pam_end_PTR_)(void *ph,int ps);
#define pam_end (*pam_end_PTR_) /*DLST*/
#line 37
int pam_authenticate(void *ph,int flags);
/*DLST*/ int pam_authenticate(void *ph,int flags);
/*DLST*/ int (*pam_authenticate_PTR_)(void *ph,int flags);
#define pam_authenticate (*pam_authenticate_PTR_) /*DLST*/
#line 38
#if defined(__cplusplus)
}
#endif
/*END_STAB*/

int dl_library(const char *libname,DLMap *dlmap,const char *mode);
static int paminit = 0;
static int PAMinit(){
	int code;

	if( paminit )
		return paminit;

	code = dl_library("pam",dlmap_pam,"");
	paminit = code == 0 ? 1 : -1;
	return paminit;
}
int PAM_start(const char *s,const char *u,const struct pam_conv *c,void**h){
	int code;
	if( PAMinit() <= 0 )
		return -1;
	code = pam_start(s,u,c,h);
	return code;
}
int PAM_end(void *ph,int ps){
	int code;
	if( PAMinit() <= 0 )
		return -1;
	code = pam_end(ph,ps);
	return code;
}
int PAM_authenticate(void *ph,int flags){
	int code;
	if( PAMinit() <= 0 )
		return -1;
	code = pam_authenticate(ph,flags);
	return code;
}
/*DLST*/ DLMap dlmap_pam[] = {
/*DLST*/ {"#pam"}, /*handle*/
/*DLST*/ {"pam_start",&pam_start_PTR_},
/*DLST*/ {"pam_end",&pam_end_PTR_},
/*DLST*/ {"pam_authenticate",&pam_authenticate_PTR_},
/*DLST*/ 0};
