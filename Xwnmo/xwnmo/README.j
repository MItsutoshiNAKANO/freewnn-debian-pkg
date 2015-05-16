/*
 * $Id: README.j,v 1.2.2.1 1999/02/08 08:08:35 yamasita Exp $
 */

/*
 * FreeWnn is a network-extensible Kana-to-Kanji conversion system.
 * This file is part of FreeWnn.
 * 
 * Copyright Kyoto University Research Institute for Mathematical Sciences
 *                 1987, 1988, 1989, 1990, 1991, 1992
 * Copyright OMRON Corporation. 1987, 1988, 1989, 1990, 1991, 1992, 1999
 * Copyright ASTEC, Inc. 1987, 1988, 1989, 1990, 1991, 1992
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
 */
	XWNMO - �ء�����ץåȡ��ޥ͡�����

���Υǥ��쥯�ȥ�ˤϡ�XWNMO�Υ�����������ޤ���

XWNMO�ϡ�XIM�饤�֥����Ф��ơ�¿������ϴĶ����󶡤��륤��ץåȡ��ޥ͡�����
�Ǥ���

XWNMO�ϡ��ʲ��Υ���ץåȥ�������򥵥ݡ��Ȥ��Ƥ��ޤ���

	(XIMPreeditArea | XIMStatusArea)		: Off-The-Spot
	(XIMPreeditPosition | XIMStatusArea)		: Over-The-Spot
	(XIMPreeditNothing | XIMStatusNothing )		: Root
	(XIMPreeditCallbacks | XIMStatusArea )		: On-The-Spot
	(XIMPreeditArea | XIMStatusCallbacks )		: On-The-Spot
	(XIMPreeditPosition | XIMStatusCallbacks )	: On-The-Spot
	(XIMPreeditCallbacks | XIMStatusCallbacks )	: On-The-Spot

�ʤ���On-The-Spot�Υ���ץåȥ�������ϡ�����ѥ�����Υǥե������
����Ǥ��ޤ���[XWNMO �κ����]�򻲾Ȳ�������

XWNMO�ϡ���ݲ��б������ף����Ѵ��˻��Ѥ��ޤ���
XWNMO�ϡ����饤�����(�饤�֥��)�θ���˽��äơ��Ѵ������Ф����򤷤ޤ���
�ޤ��������ʥߥå����Ѵ������Ф��ѹ����뤳�Ȥ��Ǥ��ޤ���
XWNMO�ϡ�ʣ���Υ��饤����ȡ�ʣ���Υ����Ф򥵥ݡ��ȤǤ��ޤ���

�ޥ˥奢��򥤥󥹥ȡ��뤹���硢�ǥե���ȤϱѸ�Υޥ˥奢��Ǥ���
�⤷�����ܸ�Υޥ˥奢��(EUC)��ɽ���Ǥ��륷���ƥ�ʤ顢Imakefile ��
LOCALMAN �� "man.en" ���� "man.ja" ���ѹ����Ʋ�������

[XWNMO �κ����]

    ����: Xsi ���ȼ��� Project.tmpl ����äƤ���Τǡ�xmkmf �ϻ��ѤǤ��ޤ���

    �ޤ���X11R5 �Υ�����ʬ��ᥤ�����Ʋ�������
    ���ˡ�XWNMO��XJUTIL������ӡ���ݲ��б�Wnn��ᥤ�����뤿��ˡ��ʲ���
    ���ޥ�ɤ�¹Ԥ��Ʋ�������

	% cd contrib/im/Xsi
	% make World

    XWNMO��XJUTIL������ӡ���ݲ��б�Wnn�򥤥󥹥ȡ��뤹��ˤϡ�

	% make install

    XWNMO�ϡ�����ѥ�����ˤ����Ĥ��Υǥե��������äƤ��ޤ��������ϡ�
    Imakefile �˽񤫤�Ƥ��ꡢ�ǥե���ȤǤϡ����٤Ƥ��ǥե����󤵤�Ƥ��ޤ���
    �⤷���ɤ줫�򳰤����ϡ�����ѥ������ˡ�Imakefile ��Ŭ�����ѹ�����
    ����������
    �ʲ��Υǥե���������Ǥ��ޤ���

	USING_XJUTIL	: XJUTIL(����桼�ƥ���ƥ��ޥ͡�����)�����
	CALLBACKS	: On-The-Spot ����ץåȥ�������򥵥ݡ���
	SPOT		: SpotLocation Extended Protocol �򥵥ݡ���
	XJPLIB		: XJp�Υץ��ȥ���(���ߥ�˥�������󥭥å���ʬ)��
			  ���ݡ���
	XJPLIB_DIRECT	: XJp�Υץ��ȥ���(�����쥯�ȥ��󥿥ե�������ʬ)��
			  ���ݡ���
    
    ���줾��ξܺ�:
      USING_XJUTIL:
	  �����ǥե����󤹤�ȡ�XWNMO�ϡ�XJUTIL ����桼�ƥ���ƥ��ޥ͡�����
	  ��ư�������餻�ޤ�������ˤ�ꡢ������Ф��뤵�ޤ��ޤʥ��ڥ졼�����
	  ���Ǥ��ޤ���(��Ͽ���������������ʤ�)
	  XJUTIL�ξܺ٤ϡ�xjutil/README �򻲾Ȳ�������
    
      CALLBACKS:
	  �����ǥե����󤹤�ȡ�XWNMO�ϡ� On-The-Spot ����ץåȥ��������
	  ���ݡ��Ȥ��ޤ�������ץåȥ��������:
		(XIMPreeditCallbacks | XIMStatusArea )
		(XIMPreeditArea | XIMStatusCallbacks )
		(XIMPreeditPosition | XIMStatusCallbacks )
		(XIMPreeditCallbacks | XIMStatusCallbacks )
      
      SPOT:
	  �����ǥե����󤹤�ȡ�XWNMO�ϡ�SpotLocation ��ĥ�ץ��ȥ����
	  ���ݡ��Ȥ��ޤ������Υץ��ȥ����Ȥ������ݥåȤΰ�ư���Ǥ��ޤ���
	  SpotLocation ��ĥ�ץ��ȥ���ξܺ٤ϡ�SEP_README ���뤤�ϡ�xwnmo
	  �Υޥ˥奢��� SEP ��ʬ�򻲾Ȳ�������

      XJPLIB:
	  �����ǥե����󤹤�ȡ�XWNMO�ϡ�XJp �ץ��ȥ���Υ��ߥ�˥��������
	  ���å���ʬ�򥵥ݡ��Ȥ��ޤ���XJp �Υ��ߥ�˥�������󥭥åȥ饤�֥��
	  �����ѤǤ��ޤ���(XJp_open()��XJp_begin() �ʤ�)

      XJPLIB_DIRECT:
	  �����ǥե����󤹤�ȡ�XWNMO�ϡ�XJp �ץ��ȥ���Υ����쥯��
	  ���󥿥ե�������ʬ�򥵥ݡ��Ȥ��ޤ���XJp �� �����쥯�ȥ��󥿥ե�����
	  �����ѤǤ��ޤ���(XLookupKanjiString())
	  �����ǥե����󤹤���ϡ�XJPLIB ��ɬ���ǥե����󤷤Ʋ�������

[XWNMO �λȤ���]

    XWNMO ��ư�������ˡ��Ѵ������ФǤ��롢jserver �� cserver ��ư����
    ��������jserver �ϡ����ܸ��Ѵ������Фǡ�cserver �ϡ������Ѵ������ФǤ���

    XWNMO ��ư����ˤ�

	% xwnmo

    XML ��ǥե����󤷡�������ʬ�򥳥�ѥ��뤹��ȡ����ץꥱ�������ϡ�
    ʣ������Ķ������ѤǤ��ޤ���xwnmo �Υޥ˥奢��� XML ��ʬ�򻲾Ȳ�������
