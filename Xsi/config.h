/* config.h.  Generated automatically by configure.  */
/*
 *   $Id: config.h.in $
 */

/*
 * FreeWnn is a network-extensible Kana-to-Kanji conversion system.
 * This file is part of FreeWnn.
 * 
 * Copyright Kyoto University Research Institute for Mathematical Sciences
 *                 1987, 1988, 1989, 1990, 1991, 1992
 * Copyright OMRON Corporation. 1987, 1988, 1989, 1990, 1991, 1992, 1999
 * Copyright ASTEC, Inc. 1987, 1988, 1989, 1990, 1991, 1992
 * Copyright FreeWnn Project 1999, 2000
 * 
 * Maintainer:  FreeWnn Project   <freewnn@tomo.gr.jp>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#define HAVE_UNISTD_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_MKDIR 1

/* *_t が定義されているか? (定義されていればここでは undef になる) */
/* #undef time_t */
/* #undef socklen_t */


/*
 *   drand48() があるかどうかを調べる。あれば srand48() もあるはずなので
 *   HAVE_SRAND48 は作らず、これで兼用させる。
 */    
#define HAVE_DRAND48 1

/*
 *   RAND_MAX が定義されていればこれも定義される。ちなみにこれは rand() が
 *   返す値の最大値である。
 */
#define HAVE_RAND_MAX 1

/*
 *   perror() が定義されていればこれも定義される。
 */
#define HAVE_PERROR 1
