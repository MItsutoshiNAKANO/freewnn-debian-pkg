#
#   $Id: makerule.mk.in $
#

#
# FreeWnn is a network-extensible Kana-to-Kanji conversion system.
# This file is part of FreeWnn.
# 
# Copyright Kyoto University Research Institute for Mathematical Sciences
#                 1987, 1988, 1989, 1990, 1991, 1992
# Copyright OMRON Corporation. 1987, 1988, 1989, 1990, 1991, 1992, 1999
# Copyright ASTEC, Inc. 1987, 1988, 1989, 1990, 1991, 1992
# Copyright FreeWnn Project 1999, 2000
# 
# Maintainer:  FreeWnn Project   <freewnn@tomo.gr.jp>
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

all::

            SHELL = /bin/sh

              TOP = /home/ukai/tmp/wnn/freewnn-1.1.0+1.1.1-a016/Xsi
      CURRENT_DIR = `pwd`

           DEPEND = gccmakedep
        MKDIRHIER = mkdir -p


           MANDIR = /usr/share/man/man$(MANSUFFIX)
        LIBMANDIR = /usr/share/man/man$(LIBMANSUFFIX)

        MANSUFFIX = 1
     LIBMANSUFFIX = 3

   COMPRESSMANCMD = :


               AR = ar cq
               CC = gcc
               AS = as

              CPP = /lib/cpp

     INSTALLFLAGS = -c
               LD = ld
             LINT = lint
      LINTLIBFLAG = -C
         LINTOPTS = -axz
               LN = $ln -s
             MAKE = make
               MV = mv -f
               CP = cp

           RANLIB = ranlib
  RANLIBINSTFLAGS =

               RM = rm -f
              TBL = tbl

             TAGS = ctags

   PARALLELMFLAGS =


     INSTPGMFLAGS = -s
     INSTBINFLAGS = -m 0755
     INSTUIDFLAGS = -m 4755
     INSTLIBFLAGS = -m 0644
     INSTINCFLAGS = -m 0444
     INSTMANFLAGS = -m 0444
     INSTDATFLAGS = -m 0444

      CDEBUGFLAGS = -O2 -fno-strength-reduce
        CCOPTIONS = -Dlinux -D_POSIX_SOURCE -D_BSD_SOURCE

ALLDEFINES = $(INCLUDES) -DFUNCPROTO=15 -DNARROWPROTO $(DEFINES)
CFLAGS = $(CDEBUGFLAGS) $(CCOPTIONS) $(ALLDEFINES)
LINTFLAGS = $(LINTOPTS) -DLINT $(ALLDEFINES) $(DEPEND_DEFINES)
LDOPTIONS = $(CDEBUGFLAGS) $(CCOPTIONS)

           CCLINK = $(CC)






#
# OMRON INPUT MATHOD MAKE ENV
#

       WNNOWNER = root

          IMTOP = $(TOP)

         prefix = /usr
    exec_prefix = ${prefix}
         PREFIX = /usr
      WNNWNNDIR = ${PREFIX}/lib/wnn
      WNNBINDIR = ${PREFIX}/bin
      WNNINCDIR = ${prefix}/include
      WNNLIBDIR = ${exec_prefix}/lib
    WNNTERM_LIB = -ltermcap

  PUBDICPLUSSRC = $(IMTOP)/PubdicPlus
  WNNCONSDICSRC = $(IMTOP)/Wnn-consortium/dic

         WNNTOP = $(IMTOP)/Wnn
       JWNNLANG = ja_JP
     JWNNWNNDIR = $(WNNWNNDIR)/$(JWNNLANG)
     JWNNBINDIR = $(WNNBINDIR)/Wnn4
     JWNNINCDIR = $(WNNINCDIR)/wnn
     JWNNDICDIR = $(JWNNWNNDIR)/dic
  JWNNPUBDICDIR = $(JWNNDICDIR)/pubdic
JWNNWNNCONSDICDIR = $(JWNNDICDIR)/wnncons
  JWNNFZKSRCDIR = $(JWNNDICDIR)/src
     WNNCONVSRC = $(WNNTOP)/conv
      WNNETCSRC = $(WNNTOP)/etc
  WNNINCLUDESRC = $(WNNTOP)/include
       WNNJDSRC = $(WNNTOP)/jd
     WNNJLIBSRC = $(WNNTOP)/jlib
   WNNJLIBV3SRC = $(WNNTOP)/jlib.V3
  WNNJSERVERSRC = $(WNNTOP)/jserver
    WNNJUTILSRC = $(WNNTOP)/jutil
       WNNLDSRC = $(WNNTOP)/ld
WNNPUBDICPLUSSRC = $(WNNTOP)/pubdicplus
WNNWNNCONSSRC = $(WNNTOP)/wnncons
WNNWNNCONSDICSRC = $(WNNWNNCONSSRC)/dic
   WNNROMKANSRC = $(WNNTOP)/romkan
      WNNUUMSRC = $(WNNTOP)/uum
   WNNCNVFILEDIR = $(WNNJDSRC)/./bsd
    WNNINCLUDES = -I$(WNNINCLUDESRC) -I$(WNNROMKANMSRC)
     WNNDEFINES = -DLIBDIR=\"$(WNNWNNDIR)\"
        WNNJLIB = $(WNNJLIBSRC)/libwnn.a
     WNNCONVLIB = $(WNNCONVSRC)/libconvkey.a

        CWNNTOP = $(IMTOP)/cWnn
       CWNNLANG = zh_CN
     CWNNWNNDIR = $(WNNWNNDIR)/$(CWNNLANG)
     CWNNINCDIR = $(WNNINCDIR)/cwnn
     CWNNBINDIR = $(WNNBINDIR)/cWnn4
     CWNNDICDIR = $(CWNNWNNDIR)/dic
  CWNNSYSDICDIR = $(CWNNDICDIR)/sys
      CWNNCDSRC = $(CWNNTOP)/cd
    CWNNCDICSRC = $(CWNNTOP)/cdic
    CWNNCONVSRC = $(CWNNTOP)/conv
     CWNNETCSRC = $(CWNNTOP)/etc
 CWNNINCLUDESRC = $(CWNNTOP)/include
    CWNNJLIBSRC = $(CWNNTOP)/jlib
 CWNNJSERVERSRC = $(CWNNTOP)/jserver
   CWNNJUTILSRC = $(CWNNTOP)/jutil
  CWNNROMKANSRC = $(CWNNTOP)/romkan
     CWNNUUMSRC = $(CWNNTOP)/uum
 CWNNCNVFILEDIR = $(CWNNCDSRC)/./bsd
   CWNNINCLUDES = -I$(CWNNINCLUDESRC) -I$(CWNNROMKANMSRC)
    CWNNDEFINES = -DLIBDIR=\"$(WNNWNNDIR)\"
       CWNNJLIB = $(CWNNJLIBSRC)/libcwnn.a
    CWNNCONVLIB = $(CWNNCONVSRC)/libconvkey.a

        KWNNTOP = $(IMTOP)/kWnn
       KWNNLANG = ko_KR
     KWNNWNNDIR = $(WNNWNNDIR)/$(KWNNLANG)
     KWNNINCDIR = $(WNNINCDIR)/kwnn
     KWNNBINDIR = $(WNNBINDIR)/kWnn4
     KWNNDICDIR = $(KWNNWNNDIR)/dic
  KWNNSYSDICDIR = $(KWNNDICDIR)/sys
      KWNNKDSRC = $(KWNNTOP)/kd
    KWNNKDICSRC = $(KWNNTOP)/kdic
    KWNNCONVSRC = $(KWNNTOP)/conv
     KWNNETCSRC = $(KWNNTOP)/etc
 KWNNINCLUDESRC = $(KWNNTOP)/include
    KWNNJLIBSRC = $(KWNNTOP)/jlib
 KWNNJSERVERSRC = $(KWNNTOP)/jserver
   KWNNJUTILSRC = $(KWNNTOP)/jutil
  KWNNROMKANSRC = $(KWNNTOP)/romkan
     KWNNUUMSRC = $(KWNNTOP)/uum
 KWNNCNVFILEDIR = $(KWNNCDSRC)/./bsd
   KWNNINCLUDES = -I$(KWNNINCLUDESRC) -I$(KWNNROMKANMSRC)
    KWNNDEFINES = -DLIBDIR=\"$(WNNWNNDIR)\"
       KWNNJLIB = $(KWNNJLIBSRC)/libkwnn.a
    KWNNCONVLIB = $(KWNNCONVSRC)/libconvkey.a

       TWNNLANG = zh_TW
     TWNNWNNDIR = $(WNNWNNDIR)/$(TWNNLANG)
     TWNNDICDIR = $(TWNNWNNDIR)/dic
  TWNNSYSDICDIR = $(TWNNDICDIR)/sys
      TWNNTDSRC = $(CWNNTOP)/td
    TWNNTDICSRC = $(CWNNTOP)/tdic

       LWNNLANG = lt_LN
     LWNNWNNDIR = $(WNNWNNDIR)/$(LWNNLANG)

     WNNLANGDEF = -DJAPANESE
    CWNNLANGDEF = -DCHINESE
    TWNNLANGDEF = -DTAIWANESE
    KWNNLANGDEF = -DKOREAN
    LWNNLANGDEF = -DLATIN
     ALLLANGDEF = $(WNNLANGDEF) $(CWNNLANGDEF) $(KWNNLANGDEF) $(LWNNLANGDEF)

       XWNMOTOP = $(IMTOP)/Xwnmo
       XWNMOSRC = $(XWNMOTOP)/xwnmo
      XJUTILSRC = $(XWNMOTOP)/xjutil
 XWNMOROMKANSRC = $(XWNMOTOP)/romkan
   XWNMOJLIBSRC = $(XWNMOTOP)/jlib
     XWNMOJDSRC = $(XWNMOTOP)/jd
XWNMOROMKANMSRC = $(XWNMOTOP)/romkan_m

  XWNMOXLIBINC  = -I$(XWNMOTOP)/X11R6/include

  XWNMOINCLUDES = -I$(XWNMOROMKANMSRC) -I$(WNNINCLUDESRC) $(XWNMOXLIBINC)
      XWNMOJLIB = $(XWNMOJLIBSRC)/libwnn_m.a
 XWNMOLIBRARIES = $(XWNMOJLIB)

       XWNMODEF = -DBC_X11R5




# ----------------------------------------------------------------------

all::
	@cont=0; \
	for flag in ${MAKEFLAGS} ''; do \
	case "$$flag" in *=*) ;; *[ik]*) cont=1;; esac; done; \
	SUBDIRS="$(SUBDIRS)" ;\
	for i in $$SUBDIRS ;\
	do \
	echo "making" all "in $(CURRENT_DIR)/$$i..."; \
	(cd $$i && $(MAKE) $(MFLAGS) $(PARALLELMFLAGS) \
	'CDEBUGFLAGS=$(CDEBUGFLAGS)' all) \
	|| if [ $$cont -eq 0 ]; then exit 1; fi; \
	done

install::
	@cont=0; \
	for flag in ${MAKEFLAGS} ''; do \
	case "$$flag" in *=*) ;; *[ik]*) cont=1;; esac; done; \
	SUBDIRS="$(SUBDIRS)" ;\
	for i in $$SUBDIRS ;\
	do \
	echo "installing" all "in $(CURRENT_DIR)/$$i..."; \
	(cd $$i && $(MAKE) $(MFLAGS) $(PARALLELMFLAGS) \
	'CDEBUGFLAGS=$(CDEBUGFLAGS)' install) \
	|| if [ $$cont -eq 0 ]; then exit 1; fi; \
	done

install.man::
	@cont=0; \
	for flag in ${MAKEFLAGS} ''; do \
	case "$$flag" in *=*) ;; *[ik]*) cont=1;; esac; done; \
	SUBDIRS="$(SUBDIRS)" ;\
	for i in $$SUBDIRS ;\
	do \
	echo "installing man pages" "in $(CURRENT_DIR)/$$i..."; \
	(cd $$i && $(MAKE) $(MFLAGS) $(PARALLELMFLAGS) \
	'CDEBUGFLAGS=$(CDEBUGFLAGS)' install.man) \
	|| if [ $$cont -eq 0 ]; then exit 1; fi; \
	done

depend::
	@cont=0; \
	@for flag in ${MAKEFLAGS} ''; do \
	case "$$flag" in *=*) ;; *[ik]*) cont=1;; esac; done; \
	SUBDIRS="$(SUBDIRS)" ;\
	for i in $$SUBDIRS ;\
	do \
	echo "depending" "in $(CURRENT_DIR)/$$i..."; \
	(cd $$i && $(MAKE) $(MFLAGS) $(PARALLELMFLAGS) \
	 depend) \
	|| if [ $$cont -eq 0 ]; then exit 1; fi; \
	done

clean::
	SUBDIRS="$(SUBDIRS)" ;\
	for i in $$SUBDIRS ;\
	do \
	echo "cleaning" "in $(CURRENT_DIR)/$$i..."; \
	(cd $$i && $(MAKE) $(MFLAGS) $(PARALLELMFLAGS) \
	 clean) \
	done

depend:: .depend

.depend::
	$(RM) $@
	$(DEPEND) -f- -- $(ALLDEFINES) $(DEPEND_DEFINES) -- $(SRCS) > $@

# ----------------------------------------------------------------------
# common rules for all Makefiles - do not edit


emptyrule::

clean::
	$(RM) *.CKP *.ln *.BAK *.bak *.o core errs ,* *~ *.a .emacs_* tags TAGS make.log MakeOut *.core "#"*


tags::
	$(TAGS) -w *.[ch]
	$(TAGS) -xw *.[ch] > TAGS

man_keywords::

# ----------------------------------------------------------------------
# empty rules for directories that do not have SUBDIRS - do not edit

install::
	@echo "install in $(CURRENT_DIR) done"

install.man::
	@echo "install.man in $(CURRENT_DIR) done"

install.linkkit::
	@echo "install.linkkit in $(CURRENT_DIR) done"

Makefiles::

includes::

depend::

# ----------------------------------------------------------------------
# dependencies generated by makedepend

# dependencies are in .depend
