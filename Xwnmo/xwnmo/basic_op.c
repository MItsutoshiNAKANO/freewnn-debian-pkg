/*
 * $Id: basic_op.c,v 1.2 2001/06/14 18:16:14 ura Exp $
 */

/*
 * FreeWnn is a network-extensible Kana-to-Kanji conversion system.
 * This file is part of FreeWnn.
 * 
 * Copyright Kyoto University Research Institute for Mathematical Sciences
 *                 1987, 1988, 1989, 1990, 1991, 1992
 * Copyright OMRON Corporation. 1987, 1988, 1989, 1990, 1991, 1992, 1999
 * Copyright ASTEC, Inc. 1987, 1988, 1989, 1990, 1991, 1992
 * Copyright 1991, 1992 by Massachusetts Institute of Technology
 *
 * Author: OMRON SOFTWARE Co., Ltd. <freewnn@rd.kyoto.omronsoft.co.jp>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs; see the file COPYING.  If not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Commentary:
 *
 * Change log:
 *
 * Last modified date: 8,Feb.1999
 *
 * Code:
 *
 */
/*      Version 4.0
 */
#include <stdio.h>
#include "commonhd.h"
#include "sdefine.h"
#ifdef  XJUTIL
#include "xjutil.h"
#include "sxheader.h"
#include "xext.h"
#else /* XJUTIL */
#include "xim.h"
#include "sheader.h"
#include "ext.h"
#endif /* XJUTIL */
#include "rk_spclval.h"
#include "rk_fundecl.h"

/*
 * The buflen is a length of buffer. The mode is status of reverse and
 * under-line. Input a initial strings in the buffer.
 */

int
redraw_nisemono ()
{
  call_t_redraw_move (c_b->t_c_p, c_b->t_c_p, c_b->maxlen, 2, 1);
  check_scroll ();
  return (0);
}

#ifdef  XJUTIL
int
buffer_in ()
{
  unsigned int c;
  int ret;
  unsigned int romkan;
  int ignored = 0;
  int in;
  unsigned int *output;

  while (1)
    {
      in = keyin ();
      output = romkan_henkan (in);
      conv_ltr_to_ieuc (output);
      if (input_func)
        (*input_func) (output, output);
      for (; *output != EOLTTR; output++)
        {
          c = ((romkan = *output) & 0x0000ffff);
          if (isSPCL (romkan))
            {
              if (romkan == REDRAW)
                {
                  (*c_b->redraw_fun) ();
                  continue;
                }
              else if (romkan == CHMSIG)
                {               /* mode changed */
                  if (redraw_when_chmsig_func)
                    (*redraw_when_chmsig_func) ();
                  disp_mode ();
                  continue;
                }
              else if (romkan == NISEBP)
                {               /* error */
                  ring_bell ();
                  continue;
                }
              else
                {
                  continue;     /* if (romkan == EOLTTR) */
                }
            }
          if (ignored)
            {
              if (isNISE (romkan))
                {
                  if (c == rubout_code)
                    {
                      --ignored;
                    }
                  else
                    {
                      ++ignored;
                    }
                }
              else
                {
                  ignored = 0;
                }
              continue;
            }
          if (isNISE (romkan) && (ESCAPE_CHAR (c) || NOT_NORMAL_CHAR (c)) && c != rubout_code)
            {
              ++ignored;
              continue;
            }

          if (c < TBL_SIZE && c_b->key_table[c])
            {
              if (c_b->rk_clear_tbl[c])
                romkan_clear ();
              ret = (*c_b->key_table[c]) (c, romkan);
            }
          else if (c >= 0x80 && c <= 0x9f)
            {
              ret = 0;
              ring_bell ();
            }
          else if (!(ESCAPE_CHAR (c)) || c == 0x09)
            {                   /* TAB is not ESCAPE char */
              if (c_b->maxlen < c_b->buflen)
                {
                  if (c_b->key_in_fun)
                    {
                      ret = (*c_b->key_in_fun) (c, romkan);
                    }
                  else
                    {
                      ret = insert_char (c);
                      call_t_redraw_move (c_b->t_c_p + 1, c_b->t_c_p, c_b->maxlen, 0, 1);
                      check_scroll ();
                      kk_cursor_normal ();
                    }
                }
              else
                {
                  romkan_clear ();
                  ret = 0;
                }
            }
          else
            {
              if (c_b->ctrl_code_fun)
                {
                  ret = (*c_b->ctrl_code_fun) (c, romkan);
                }
              else
                {
                  ret = 0;
                  ring_bell ();
                }
            }
          if (ret == 1)
            {
              return (0);
            }
          else if (ret == -1)
            {
              return (-1);
            }
        }
    }
}

int
kana_in (mode, buffer, buflen)
     int mode;
     w_char *buffer;
     int buflen;
{
  ClientBuf c_b1, *c_btmp;

  c_btmp = c_b;
  c_b = &c_b1;
  c_b->buffer = buffer;
  c_b->hanten = mode;
  c_b->maxlen = Strlen (buffer);
  c_b->t_c_p = c_b->maxlen;
  c_b->buflen = buflen;
  c_b->t_m_start = -2;
  c_b->key_table = main_table[6];
  c_b->rk_clear_tbl = romkan_clear_tbl[6];
  c_b->key_in_fun = (int (*)()) NULL;
  c_b->redraw_fun = redraw_nisemono;
  c_b->ctrl_code_fun = (int (*)()) NULL;
  kill_buffer_offset = 0;

  init_screen ();
  if (buffer_in () == -1)
    {
      xjutil->sel_ret = -1;
      c_b = c_btmp;
      return (-1);
    }
  if (xjutil->sel_ret == -2)
    {
      xjutil->sel_ret = -1;
      c_b = c_btmp;
      return (-1);
    }
  c_b->buffer[c_b->maxlen] = 0;
  c_b = c_btmp;
  return (0);
}

#ifdef nodef
int
kana_in_w_char_msg (mode, buffer, buflen)
     int mode;
     w_char *buffer;
     int buflen;
{
  static ClientBuf c_b1, *c_btmp;
  c_btmp = c_b;
  c_b = &c_b1;
  if ((c_b->buffer = (w_char *) Malloc (buflen * 2)) == NULL)
    {
      print_msg_getc ("Error occured in malloc.");
      return (-1);
    }
  c_b->t_m_start = 0;
  Strcpy (c_b->buffer, buffer);

  c_b->hanten = mode;
  c_b->maxlen = Strlen (c_b->buffer);
  c_b->t_c_p = c_b->maxlen;
  c_b->buflen = buflen;
  c_b->redraw_fun = redraw_nisemono;
  c_b->key_table = main_table[6];
  c_b->rk_clear_tbl = romkan_clear_tbl[6];
  c_b->key_in_fun = NULL;
  c_b->ctrl_code_fun = NULL;
  kill_buffer_offset = 0;

  init_screen ();
  if (buffer_in () == -1)
    {
      Free (c_b->buffer);
      c_b = c_btmp;
      return (-1);
    }
  Free (c_b->buffer);
  Strncpy (buffer, c_b->buffer, c_b->maxlen);
  buffer[c_b->maxlen] = 0;
  c_b = c_btmp;
  return (0);
}
#endif
#else /* XJUTIL */

int
buffer_in (in)
     int in;
{
  unsigned int c;
  int ret;
  unsigned int romkan;
  unsigned int *output;

  if (if_unget_buf ())
    {
      output = get_unget_buf ();
    }
  else
    {
      if (c_c->func_stack_count >= 0 && c_c->command_func_stack[c_c->func_stack_count] != 0)
        {
          ret = (*c_c->command_func_stack[c_c->func_stack_count]) (in);
          return (-1);
        }
      else
        {
          ignored = 0;
          output = romkan_henkan (in);
        }
    }
  conv_ltr_to_ieuc (output);
  if (input_func)
    (*input_func) (output, output);
  for (; *output != EOLTTR; output++)
    {
      c = ((romkan = *output) & 0x0000ffff);
      if (isSPCL (romkan))
        {
          if (romkan == REDRAW)
            {
              (*c_b->redraw_fun) ();
              continue;
            }
          else if (romkan == CHMSIG)
            {                   /* mode changed */
              if (redraw_when_chmsig_func)
                (*redraw_when_chmsig_func) ();
              disp_mode ();
              continue;
            }
          else if (romkan == NISEBP)
            {                   /* error */
              ring_bell ();
              continue;
            }
          else if (romkan == SENDCH)
            {
              c = ((romkan = *++output) & 0x0000ffff);
              romkan_clear ();
              send_string (c);
              return (0);
            }
          else
            {
              continue;
            }
        }
      if (ignored)
        {
          if (isNISE (romkan))
            {
              if (c == rubout_code)
                {
                  --ignored;
                }
              else
                {
                  ++ignored;
                }
            }
          else
            {
              ignored = 0;
            }
          continue;
        }
      if (isNISE (romkan) && (ESCAPE_CHAR (c) || NOT_NORMAL_CHAR (c)) && c != rubout_code)
        {
          ++ignored;
          continue;
        }

      if (c < TBL_SIZE && c_b->key_table[c])
        {
          if (c_b->rk_clear_tbl[c])
            romkan_clear ();
          ret = (*c_b->key_table[c]) (c, romkan);
/*
        }else if(c >= 0x80 && c <= 0x9f){
            ret = return_it(c, romkan);
*/
        }
      else if (!(c >= 0x80 && c <= 0x9f) && (!(ESCAPE_CHAR (c)) || c == 0x09))
        {                       /* TAB is not ESCAPE char */
          if (c_b->maxlen < c_b->buflen)
            {
              if (c_b->key_in_fun)
                {
                  ret = (*c_b->key_in_fun) (c, romkan);
                }
              else
                {
                  ret = insert_char (c);
                  call_t_redraw_move (c_b->t_c_p + 1, c_b->t_c_p, c_b->maxlen, 0, 1);
                  check_scroll ();
                  kk_cursor_normal ();
                  if (henkan_on_kuten && c_b->t_c_p == c_b->maxlen)
                    henkan_if_maru (c);
                }
            }
          else
            {
              romkan_clear ();
              ret = 0;
            }
        }
      else
        {
          if (c_b->ctrl_code_fun)
            {
              ret = (*c_b->ctrl_code_fun) (c, romkan);
            }
          else
            {
              ret = 0;
              ring_bell ();
            }
        }
      if (ret == 1)
        {
          return (0);
        }
      else if (ret == -1)
        {
          return (-1);
        }
      continue;
    }
  return (-1);
}
#endif /* XJUTIL */

int
delete_char1 ()
{
  if (c_b->t_c_p < c_b->maxlen)
    {
      Strncpy (c_b->buffer + c_b->t_c_p, c_b->buffer + c_b->t_c_p + 1, c_b->maxlen - c_b->t_c_p - 1);
      c_b->maxlen -= 1;
    }
  return (0);
}

int
t_delete_char ()
{
  delete_char1 ();
/*    kk_cursor_invisible(); */
  call_t_redraw_move (c_b->t_c_p, c_b->t_c_p, c_b->maxlen, 2, 1);
  check_scroll ();
/*    kk_cursor_normal(); */
  return (0);
}

int
t_rubout (c, romkan)
     int c, romkan;
{
  if (c_b->t_c_p != 0)
    {
      backward ();
      t_delete_char ();
    }
  return (0);
}


#ifdef  XJUTIL
int
kuten ()
{
  input_a_char_from_function (in_kuten);
  return (0);
}

int
jis ()
{
  input_a_char_from_function (in_jis);
  return (0);
}

int
input_a_char_from_function (fun)
     int (*fun) ();
{
  int c, in = 0;
  int ret = -1;

  for (;;)
    {
      if ((c = (*fun) (in)) != BUFFER_IN_CONT)
        {
          if (c == -1)
            return (ret);
          if (c_b->key_in_fun)
            {
              ret = (*c_b->key_in_fun) (c, c);
            }
          else
            {
              ret = insert_char (c);
              t_redraw_move (c_b->t_c_p + 1, c_b->t_c_p, c_b->maxlen, 0);
            }
          break;
        }
      in = keyin ();
    }
  return (ret);
}

#else /* XJUTIL */

int
kuten (in)
     int in;
{
  static WnnClientRec *c_c_sv = 0;
  int ret = -1;
#ifdef  CALLBACKS
  int c;
  static int save_c;
#endif /* CALLBACKS */

#ifdef  CALLBACKS
  if (IsPreeditCallbacks (cur_x) && cur_x->cb_redraw_needed)
    {
      if (c_b->key_in_fun)
        {
          ret = (*c_b->key_in_fun) (save_c, save_c);
        }
      else
        {
          ret = insert_char (save_c);
          t_redraw_move (c_b->t_c_p + 1, c_b->t_c_p, c_b->maxlen, 0);
          check_scroll ();
        }
      c_c_sv = 0;
      pop_func (c_c);
      cur_x->cb_redraw_needed = 0;
      return (0);
    }
#endif /* CALLBACKS */
  if (c_c_sv != 0 && c_c != c_c_sv)
    {
      ring_bell ();
      return (0);
    }
  if (c_c_sv == 0)
    {
      c_c_sv = c_c;
      push_func (c_c, kuten);
    }
#ifdef  CALLBACKS
  if ((c = in_kuten (in)) == BUFFER_IN_CONT)
    {
      return (BUFFER_IN_CONT);
    }
  else if (c != -1)
    {
      if (IsPreeditCallbacks (cur_x))
        {
          cur_x->cb_redraw_needed = 1;
          SendCBRedraw ();
          save_c = c;
          return (BUFFER_IN_CONT);
        }
      if (c_b->key_in_fun)
        {
          ret = (*c_b->key_in_fun) (c, c);
        }
      else
        {
          ret = insert_char (c);
          t_redraw_move (c_b->t_c_p + 1, c_b->t_c_p, c_b->maxlen, 0);
          check_scroll ();
        }
    }
#else /* CALLBACKS */
  if ((ret = input_a_char_from_function (in_kuten, in)) == BUFFER_IN_CONT)
    {
      return (BUFFER_IN_CONT);
    }
#endif /* CALLBACKS */
  c_c_sv = 0;
  pop_func (c_c);
  return (ret);
}

int
jis (in)
     int in;
{
  static WnnClientRec *c_c_sv = 0;
  int ret = -1;
#ifdef  CALLBACKS
  int c;
  static int save_c;
#endif /* CALLBACKS */

#ifdef  CALLBACKS
  if (IsPreeditCallbacks (cur_x) && cur_x->cb_redraw_needed)
    {
      if (c_b->key_in_fun)
        {
          ret = (*c_b->key_in_fun) (save_c, save_c);
        }
      else
        {
          ret = insert_char (save_c);
          t_redraw_move (c_b->t_c_p + 1, c_b->t_c_p, c_b->maxlen, 0);
          check_scroll ();
        }
      c_c_sv = 0;
      pop_func (c_c);
      cur_x->cb_redraw_needed = 0;
      return (0);
    }
#endif /* CALLBACKS */
  if (c_c_sv != 0 && c_c != c_c_sv)
    {
      ring_bell ();
      return (0);
    }
  if (c_c_sv == 0)
    {
      c_c_sv = c_c;
      push_func (c_c, jis);
    }
#ifdef  CALLBACKS
  if ((c = in_jis (in)) == BUFFER_IN_CONT)
    {
      return (BUFFER_IN_CONT);
    }
  else if (c != -1)
    {
      if (IsPreeditCallbacks (cur_x))
        {
          cur_x->cb_redraw_needed = 1;
          SendCBRedraw ();
          save_c = c;
          return (BUFFER_IN_CONT);
        }
      if (c_b->key_in_fun)
        {
          ret = (*c_b->key_in_fun) (c, c);
        }
      else
        {
          ret = insert_char (c);
          t_redraw_move (c_b->t_c_p + 1, c_b->t_c_p, c_b->maxlen, 0);
          check_scroll ();
        }
    }
#else /* CALLBACKS */
  if ((ret = input_a_char_from_function (in_jis, in)) == BUFFER_IN_CONT)
    {
      return (BUFFER_IN_CONT);
    }
#endif /* CALLBACKS */
  c_c_sv = 0;
  pop_func (c_c);
  return (ret);
}

#ifndef CALLBACKS
int
input_a_char_from_function (fun, in)
     int (*fun) ();
     int in;
{
  int c;
  int ret = -1;

  if ((c = (*fun) (in)) != -1)
    {
      if (c == BUFFER_IN_CONT)
        {
          return (BUFFER_IN_CONT);
        }
      if (c_b->key_in_fun)
        {
          ret = (*c_b->key_in_fun) (c, c);
        }
      else
        {
          ret = insert_char (c);
          t_redraw_move (c_b->t_c_p + 1, c_b->t_c_p, c_b->maxlen, 0);
          check_scroll ();
        }
    }
  return (ret);
}
#endif /* !CALLBACKS */
#endif /* !XJUTIL */

int
t_kill ()
{
  kill_buffer_offset = MIN_VAL (c_b->maxlen - c_b->t_c_p, maxchg);
  Strncpy (kill_buffer, c_b->buffer + c_b->t_c_p, kill_buffer_offset);
  c_b->maxlen = c_b->t_c_p;
  t_redraw_move (c_b->t_c_p, c_b->t_c_p, c_b->maxlen, 1);
  check_scroll ();
  return (0);
}

int
t_yank ()
{
  if (kill_buffer_offset <= c_b->buflen - c_b->t_c_p)
    {
      Strncpy (c_b->buffer + c_b->t_c_p + kill_buffer_offset, c_b->buffer + c_b->t_c_p, c_b->maxlen - c_b->t_c_p);
      Strncpy (c_b->buffer + c_b->t_c_p, kill_buffer, kill_buffer_offset);
      c_b->maxlen += kill_buffer_offset;
      call_t_redraw_move (c_b->t_c_p + kill_buffer_offset, c_b->t_c_p, c_b->maxlen, 0, 1);
      check_scroll ();
    }
  return (0);
}

int
t_ret ()
{
  return (1);
}

int
t_quit ()
{
  return (-1);
}

int
c_top ()
{
  (*c_top_func) ();
  return (0);
}

int
c_end ()
{
  (*c_end_func) ();
  return (0);
}

int
c_end_nobi ()
{
  (*c_end_nobi_func) ();
  return (0);
}

int
t_jmp_backward ()
{
  int k;
  for (k = 1; k < touroku_bnst_cnt; k++)
    {
      if (touroku_bnst[k] >= c_b->t_c_p)
        {
          if (touroku_bnst[k - 1] >= c_b->t_m_start)
            {
              call_t_redraw_move_1 (touroku_bnst[k - 1], touroku_bnst[k - 1], c_b->maxlen, 0, 1, 0, 3);
            }
          else
            {
              c_top ();
            }
          return (0);
        }
    }
  backward ();
  return (0);
}

int
t_jmp_forward ()
{
  int k;

  for (k = 1; k < touroku_bnst_cnt; k++)
    {
      if (touroku_bnst[k] > c_b->t_c_p)
        {
          call_t_redraw_move_1 (touroku_bnst[k], c_b->t_c_p, c_b->maxlen, 0, 1, 0, 3);
          return (0);
        }
    }
  forward_char ();
  return (0);
}

int
forward_char ()
{
  if (c_b->t_c_p < c_b->maxlen)
    {
      call_t_redraw_move_2 (c_b->t_c_p + 1, c_b->t_c_p, c_b->t_m_start, c_b->t_c_p + 2, c_b->t_c_p + 1, 0, 1);
    }
  return (0);
}

int
forward ()
{
  if (c_b->t_c_p < c_b->maxlen)
    {
      t_move (c_b->t_c_p + 1);
    }
  return (0);
}

int
backward_char ()
{
  if (c_b->t_c_p >= 1 && c_b->t_c_p > c_b->t_m_start)
    {
      call_t_redraw_move_2 (c_b->t_c_p - 1, c_b->t_c_p - 1, c_b->t_m_start, c_b->t_c_p + 1, c_b->t_c_p, 0, 1);
    }
  return (0);
}

int
backward ()
{
  if (c_b->t_c_p >= 1 && c_b->t_c_p > c_b->t_m_start)
    {
      t_move (c_b->t_c_p - 1);
    }
  return (0);
}

int
insert_char (c)
     int c;
{
  if (c_b->maxlen < c_b->buflen)
    {
      Strncpy (c_b->buffer + c_b->t_c_p + 1, c_b->buffer + c_b->t_c_p, c_b->maxlen - c_b->t_c_p);
      c_b->maxlen += 1;
      c_b->buffer[c_b->t_c_p] = (w_char) (c & 0xffff);
    }
  return (0);
}

int
insert_string (string, len)
     w_char *string;
     int len;
{
  if (c_b->maxlen + len <= c_b->buflen)
    {
      Strncpy (c_b->buffer + c_b->t_c_p + len, c_b->buffer + c_b->t_c_p, c_b->maxlen - c_b->t_c_p);
      Strncpy (c_b->buffer + c_b->t_c_p, string, len);
      c_b->maxlen += len;
    }
  return (0);
}

#ifdef  XJUTIL
int
quote ()
{
  unsigned int c;
  c = keyin ();
  if (empty_modep () && c_b->key_in_fun)
    return ((*c_b->key_in_fun) (c, c));
  insert_char (c);
  t_redraw_move (c_b->t_c_p + 1, c_b->t_c_p, c_b->maxlen, 0);
  romkan_clear ();
  return (0);
}
#else /* XJUTIL */
int
quote (in)
     int in;
{
  static WnnClientRec *c_c_sv = 0;

  if (in == -99)
    {
      romkan_clear ();
      c_c_sv = 0;
      pop_func (c_c);
      return (0);
    }
  if (c_c_sv != 0 && c_c != c_c_sv)
    {
      ring_bell ();
      return (0);
    }
  if (c_c_sv == 0)
    {
      c_c_sv = c_c;
      push_func (c_c, quote);
      return (BUFFER_IN_CONT);
    }
  if (empty_modep ())
    {
      if (send_ascii_char)
        {
          c_c_sv = 0;
          pop_func (c_c);
          return (return_it_if_ascii (in, 0));
        }
      else
        {
          insert_char_and_change_to_insert_mode (in);
        }
    }
  else
    {
      insert_char (in);
      t_redraw_move (c_b->t_c_p + 1, c_b->t_c_p, c_b->maxlen, 0);
      check_scroll ();
    }
  romkan_clear ();
  c_c_sv = 0;
  pop_func (c_c);
  return (0);
}

int
reset_line ()
{
  if (empty_modep () == 0)
    {
      redraw_xj_all ();
    }
  return (0);
}
#endif /* XJUTIL */

void
redraw_line ()
{
  throw_col (0);
  disp_mode ();
  if (!empty_modep ())
    {
      t_print_l ();
    }
}
