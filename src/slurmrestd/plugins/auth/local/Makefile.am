# Makefile for auth/local plugin

AUTOMAKE_OPTIONS = foreign
CLEANFILES = *.bino

PLUGIN_FLAGS = -module -avoid-version --export-dynamic

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/src/common $(JSON_CPPFLAGS)

pkglib_LTLIBRARIES = rest_auth_local.la

rest_auth_local_la_SOURCES = local.c

rest_auth_local_la_DEPENDENCIES = $(LIB_SLURM_BUILD)
rest_auth_local_la_LDFLAGS = $(PLUGIN_FLAGS)
rest_auth_local_la_LIBADD = $(libslurmfull_la_LIBADD)
