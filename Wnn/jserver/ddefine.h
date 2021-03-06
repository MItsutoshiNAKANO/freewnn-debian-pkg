/*
 *  $Id: ddefine.h,v 1.7 2003/05/11 18:29:19 hiroo Exp $
 */

/*
 * FreeWnn is a network-extensible Kana-to-Kanji conversion system.
 * This file is part of FreeWnn.
 * 
 * Copyright Kyoto University Research Institute for Mathematical Sciences
 *                 1987, 1988, 1989, 1990, 1991, 1992
 * Copyright OMRON Corporation. 1987, 1988, 1989, 1990, 1991, 1992, 1999
 * Copyright ASTEC, Inc. 1987, 1988, 1989, 1990, 1991, 1992
 * Copyright FreeWnn Project 1999, 2000, 2003
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

/************************
 * define of daemon
 ************************/

#ifndef JSERVER_DDEFINE_H
#define JSERVER_DDEFINE_H 1

#include <ctype.h>

#define SIZE_JISHOTABLE 1000
#define SIZE_JISHOHEAP 2000

#define KANGO_HINSI_MX  256     /* 幹語の品詞数の最大数 */
#define KANGO_VECT_L (KANGO_HINSI_MX+8*4-1)/(8*4)       /* 幹語接続ベクタの長さ */
#define FZKVECT_L       5       /* 付属語ベクタの長さ */
#define VECT_L  KANGO_VECT_L + FZKVECT_L        /* 接続ベクタの長さ */

struct fzkkouho
{                               /* used in reffering to fuzokugo jouhou 
                                   fuzokugo jouhou is stored using this struct */
  int offset;
  int vector[KANGO_VECT_L];     /* 幹語終端ベクタ */
};

/* macro C(i , j)  is useful for finding a pointer which points out 
   the first jishoentry whose yomi starts at i and endes at j
   which returns NULL if there is no entry which matches this
*/

#define C(i,j)  (j > maxj[i] ? (struct jdata *)NULL : *(jmtp[i] + (j - i)))


/* #define      FZKIBNO 10 */
#define FZKIBNO 5

/* 付属語解析結果 */
struct ICHBNP
{
  struct ICHBNP *next_p;
  struct fzkkouho fzkib[FZKIBNO];       /* vec の解析結果 */
  struct fzkkouho fzkib1[FZKIBNO];      /* vec1 の解析結果 */
};
/* 実は、fzkib1->offset は、ごみが入っている */

#define SV_KOSUU        3

#define UJIS_A          0xa3c1  /* Ａ */
#define UJIS_Z          0xa3da  /* Ｚ */
#define UJIS_a          0xa3e1  /* ａ */
#define UJIS_z          0xa3fa  /* ｚ */
#ifdef CHINESE
#define UJIS_comma      0xa3ac  /* ， */
#define S_PAREN         0xa1ae  /* ‘ */
#define E_PAREN         0xa1bf  /* 】 */
#else
# ifdef KOREAN
#define UJIS_comma      0xa3ac  /* ， */
#define S_PAREN         0xa1ae  /* ‘ */
#define E_PAREN         0xa1bd  /* 】 */
# else
#define UJIS_comma      0xa1a4  /* ， */
#define S_PAREN         0xa1c6  /* ‘ */
#define E_PAREN         0xa1db  /* 】 */
# endif
#endif /* CHINESE */
/*
#define isdigit(x)      ((unsigned)((x) - '0') <= ('9' - '0'))
#define isalpha(x)      ((unsigned)((x) - 'A') <= ('Z' - 'A') || \
                            (unsigned)((x) - 'a') <= ('z' - 'a'))
#define isalnum(x)      (isalpha(x) || isdigit(x))
*/
#ifdef  isspace
#       undef   isspace         /* ctype.h の isspace() は使わない */
#endif
#define isspace(x)      (((x) == ' ') || ((x) == 0x09))
#define isjspace(x)     ((x) == 0xa1a1)
#define isparen_s(x)    (/* (x) == '\"' || */ (x) == '`' || \
/* 開括弧 */             (x) == '(' || (x) == '<' || \
                         (x) == '[' || (x) == '{')
#define isparen_e(x)    ((x) == '\"' || (x) == '\'' || \
/* 閉括弧 */             (x) == ')' || (x) == '>' || \
                         (x) == ']' || (x) == '}')

#define isjdigit(x)     ((unsigned)((x) - S_NUM) <= (E_NUM - S_NUM))
#define isjalpha(x)     ((unsigned)((x) - UJIS_A) <= (UJIS_Z - UJIS_A) || \
                         (unsigned)((x) - UJIS_a) <= (UJIS_z - UJIS_a))
#define isjalnum(x)     (isjalpha(x) || isjdigit(x))
#define isjhira(x)      ((unsigned)((x) - S_HIRA) <= (E_HIRA - S_HIRA))
#define isjkata(x)      ((unsigned)((x) - S_KATA) <= (E_KATA - S_KATA))
#define isj1bytekana(x) ((unsigned)((x) - S_HANKATA) <= (E_HANKATA - S_HANKATA))
# define S_KANJI        0xb0a1  /* 16区 */
# define E_KANJI        0xfefe  /* 94区 */
#ifdef  CHINESE
# define S_HANJI        0x20a1  /* 16区 */
# define E_HANJI        0x7efe  /* 94区 */
#define isjkanji(x)     (((unsigned)((x) - S_KANJI) <= (E_KANJI - S_KANJI)) || \
                         ((unsigned)((x) - S_HANJI) <= (E_HANJI - S_HANJI)))
#define isjparen(x)     ((unsigned)((x) - S_PAREN) <= (E_PAREN - S_PAREN) || \
                         (x)==0xa3a8 || (x)==0xa3a9 ||  \
                         (x)==0xa3bc || (x)==0xa3be || \
                         (x)==0xa3db || (x)==0xa3dd || \
                         (x)==0xa3fb || (x)==0xa3fd )
                        /*  for (  )  <  >  [  ]  { } */
#define isjparen_s(x)   (((unsigned)((x) - S_PAREN) <= (E_PAREN - S_PAREN)) && \
                             (((x) & 0x01) == 0) || \
                         (x)==0xa3a8 || (x)==0xa3bc || \
                         (x)==0xa3db || (x)==0xa3fb )

#define isjparen_e(x)   (((unsigned)((x) - S_PAREN) <= (E_PAREN - S_PAREN)) && \
                             (((x) & 0x01) == 1) || \
                         (x)==0xa3a9 || (x)==0xa3be || \
                         (x)==0xa3dd || (x)==0xa3fd )
#else
# ifdef KOREAN
#define S_HANJA 0xcaa1          /* 福 */
#define E_HANJA 0xfdfe          /* �� */
#define isjkanji(x)     ((unsigned)((x) - S_HANJA) <= (E_HANJA - S_HANJA))
#define isjparen(x)     ((unsigned)((x) - S_PAREN) <= (E_PAREN - S_PAREN) || \
                         (x)==0xa3a8 || (x) ==0xa3a9 || \
                         (x)==0xa3bc || (x) ==0xa3be || \
                         (x)==0xa3db || (x) ==0xa3dd || \
                         (x)==0xa3fb || (x) ==0xa3fc )
#define isjparen_s(x)   (((unsigned)((x) - S_PAREN) <= (E_PAREN - S_PAREN)) && \
                            (((x) & 0x01) == 0) || \
                         (x)==0xa3a8 || (x)==0xa3bc || \
                         (x)==0xa3db || (x)==0xa3fb)
#define isjparen_e(x)   (((unsigned)((x) - S_PAREN) <= (E_PAREN - S_PAREN)) && \
                            (((x) & 0x01) == 1) || \
                         (x) ==0xa3a9 || (x) ==0xa3be || \
                         (x) ==0xa3dd || (x) ==0xa3fc )
#define ishangul(x)     ((unsigned)((x) - S_HANGUL) <= (E_HANGUL - S_HANGUL))
# else /* JAPANESE */
#define isjkanji(x)     ((unsigned)((x) - S_KANJI) <= (E_KANJI - S_KANJI))
#define isjparen(x)     ((unsigned)((x) - S_PAREN) <= (E_PAREN - S_PAREN))
#define isjparen_s(x)   (isjparen(x) && (((x) & 0x01) == 0))
#define isjparen_e(x)   (isjparen(x) && ((x) & 0x01))
# endif /* KOREAN */
#endif /* CHINESE */

#define UJIS_DKT        0xa1ab  /* ゛ */
#define UJIS_HDK        0xa1ac  /* ゜ */

#define BAR_CODE(x)     ((x) == BAR)
#define TOKU(x) (((x) == UJIS_DKT) || ((x) == UJIS_HDK))

#define TOKUSYU(x)      (TOKU(x) || isjkata(x) || isj1bytekana(x))
        /* this resembles macro before */

#define kuten(x)        (((x)==KUTEN_NUM)? True:False)
#define touten(x)       (((x)==TOUTEN_NUM)? True:False)

struct SYO_BNSETSU
{
  struct SYO_BNSETSU *lnk_br;   /* 他の小文節へのポインタ */
  struct SYO_BNSETSU *parent;   /* 一つ前の小文節へのポインタ */
  short j_c;                    /* 幹語 top index */
  short i_jc;                   /* 幹語 end index */
  short bend_m;                 /* 小文節 end char index */
  int v_jc;                     /* この文節の評価値 */
  int son_v;                    /* この小文節までの評価値の合計 */
  struct jdata *jentptr;        /* 辞書データへのポインタ */
  int t_jc;                     /* 品詞、頻度情報のインデックス */
  int kangovect;                /* 接続ベクトルテーブルのインデックス */
  int hinsi_fk;                 /* 幹語の品詞No.(複合品詞を含む) */
  short kbcnt;                  /* 大文節中で何小文節目か */
  short reference;              /* この小文節のリファレンス数 */
  short status;                 /* 前の文節と接続できるか */
  short status_bkwd;            /* 後の文節とと接続できるか */
};

struct BZD
{
  struct BZD *lnk_br;           /* 他の大文節候補 */
  struct BZD *lnk_son;          /* 次の大文節への pointer */
  short j_c;                    /* 幹語 top index */
  short bend_m;                 /* この大文節の end char index */
  int v_jc;                     /* この大文節の評価値 */
  int son_v;                    /* 次の大文節の評価値 */
  struct SYO_BNSETSU *sbn;      /* 先頭の小文節 */
  short sbn_cnt;                /* この大文節を構成する小文節の数 */
  short kbcnt;                  /* この大文節の前に何文節解析したか  */
};

struct JKT_SONE
{
  struct JKT_SONE *lnk_br;      /* 他の小文節へのポインタ */
  short i_jc;                   /* 幹語 end index */
  short v_jc;                   /* この文節の評価値 */
  struct jdata *jentptr;        /* 辞書データへのポインタ */
  int t_jc;                     /* 品詞、頻度情報のインデックス */
  int hinsi_fk;                 /* 幹語の品詞No.(複合品詞を含む) */
  short status_bkwd;            /* 後の文節とと接続できるか */
};

struct JKT_SBN
{
  struct JKT_SBN *lnk_br;       /* 他の小文節へのポインタ */
  struct JKT_SBN *parent;       /* 一つ前の小文節へのポインタ */
  short j_c;                    /* 幹語 top index */
  short bend_m;                 /* 小文節 end char index */
  struct JKT_SONE *sbn;         /* 他の小文節へのポインタ */
  int kangovect;                /* 接続ベクトルテーブルのインデックス */
  short kbcnt;                  /* 大文節中で何小文節目か  */
  short reference;              /* この小文節のリファレンス数 */
  short status;                 /* 前の文節と接続できるか */
};

struct JKT_DBN
{
  struct JKT_DBN *lnk_br;       /* 他の小文節へのポインタ */
  short j_c;                    /* 幹語 top index */
  short bend_m;                 /* 小文節 end char index */
  struct JKT_SBN *sbn;          /* 他の小文節へのポインタ */
  int v_jc;                     /* 最大評価の評価値 */
  short sbn_cnt;                /* この大文節を構成する小文節の数 */
};

struct DSD_SBN
{
  short bun_m;                  /* 候補文節の end char index */
  short bun_jc;                 /* 候補文節の top char index */
  short i_jc;                   /* 候補文節の自立語 end char index */
  struct jdata *jentptr;        /* 候補文節の辞書 entry pointer */
  int t_jc;                     /* 候補自立語の品詞 & 頻度 index */
  int hinsi;                    /* 品詞 */
  int kangovect;                /* 接続ベクトルテーブルのインデックス */
  int v_jc;                     /* 小文節の評価値 */
  short status;                 /* 前の文節と接続できるか */
  short status_bkwd;            /* 後の文節とと接続できるか */
};

struct DSD_DBN
{
  short bun_m;                  /* 候補文節の end char index */
  short bun_jc;                 /* 候補文節の top char index */
  struct DSD_SBN *sbn;          /* 小文節解析結果へのポインタ */
  short sbncnt;                 /* 小文節数 (次候補の場合は、次候補数)
                                   DSD_SBNは、*sbn から sbncnt だけある */
  int v_jc;                     /* 大文節の評価値 */
};

#ifdef  nodef                   /* move to jslib.h */
/* 疑似文節の直前に選択した候補 */
#define HIRAGANA        -1      /* ひらがな */  /* 読みのまま */
#define KATAKANA        -11     /* カタカナ */
/* 数字 */
#define NUM_HAN         -2      /* 半角数字 */  /* 読みのまま */
#define NUM_ZEN         -12     /* 全角数字 */  /* １２３ */
#define NUM_KAN         -13     /* 漢数字 */    /* 一二三 */
#define NUM_KANSUUJI    -15     /* 漢数字 */    /* 百二十三 */
#define NUM_KANOLD      -16     /* 漢数字 */    /* 壱百弐拾参 */
#define NUM_HANCAN      -17     /* 半角数字 */  /* 1,234 */
#define NUM_ZENCAN      -18     /* 全角数字 */  /* １，２３４ */
/* 英数 */
#define ALP_HAN         -4      /* 半角 */      /* 読みのまま */
#define ALP_ZEN         -30     /* 全角 */
/* 記号 */
#define KIG_HAN         -5      /* 半角 */      /* 読みのまま */
#define KIG_JIS         -40     /* 全角(JIS) */
#define KIG_ASC         -41     /* 全角(ASC) */
#endif

#define YES             1
#define NO              0
#define UN_KNOWN        -1

#define NOTHING         0

#endif /* JSERVER_DDEFINE_H */
