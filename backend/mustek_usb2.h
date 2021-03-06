/* sane - Scanner Access Now Easy.

   Copyright (C) 2000-2005 Mustek.
   Originally maintained by Mustek

   Copyright (C) 2001-2005 by Henning Meier-Geinitz.

   This file is part of the SANE package.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA 02111-1307, USA.

   As a special exception, the authors of SANE give permission for
   additional uses of the libraries contained in this release of SANE.

   The exception is that, if you link a SANE library with other files
   to produce an executable, this does not by itself cause the
   resulting executable to be covered by the GNU General Public
   License.  Your use of that executable is in no way restricted on
   account of linking the SANE library code into it.

   This exception does not, however, invalidate any other reasons why
   the executable file might be covered by the GNU General Public
   License.

   If you submit changes to SANE to the maintainers to be included in
   a subsequent release, you agree by submitting the changes that
   those changes may be distributed with this exception intact.

   If you write modifications of your own for SANE, it is your choice
   whether to permit this exception to apply to your modifications.
   If you do not wish that, delete this exception notice.

   This file implements a SANE backend for the Mustek BearPaw 2448 TA Pro 
   and similar USB2 scanners. */

#ifndef MUSTEK_USB2_H
#define MUSTEK_USB2_H

#include "mustek_usb2_high.h"


#define SCAN_BUFFER_SIZE (64 * 1024)
#define MAX_RESOLUTIONS 12
#define MAX_BUTTONS 5
#define DEF_LINEARTTHRESHOLD 128


enum
{
  OPT_NUM_OPTS = 0,
  OPT_MODE_GROUP,
  OPT_MODE,
  OPT_SOURCE,
  OPT_RESOLUTION,
  OPT_PREVIEW,

  OPT_ENHANCEMENT_GROUP,
  OPT_THRESHOLD,

  OPT_GEOMETRY_GROUP,
  OPT_TL_X,			/* top-left x */
  OPT_TL_Y,			/* top-left y */
  OPT_BR_X,			/* bottom-right x */
  OPT_BR_Y,			/* bottom-right y */

  OPT_SENSORS_GROUP,
  OPT_BUTTON_1,
  OPT_BUTTON_2,
  OPT_BUTTON_3,
  OPT_BUTTON_4,
  OPT_BUTTON_5,  

  /* must come last: */
  NUM_OPTIONS
};


typedef struct
{
  /** @name Identification */
  /*@{ */

  /** Device vendor string. */
  SANE_String_Const vendor_name;

  /** Device model name. */
  SANE_String_Const model_name;

  /** USB vendor and product ID */
  unsigned short vendor_id;
  unsigned short product_id;

  const Scanner_ModelParams * scanner_params;

  /** @name Scanner model parameters */
  /*@{ */
  SANE_Word dpi_values[MAX_RESOLUTIONS];	/* possible resolutions */
  SANE_Range x_range;		/* size of scan area in mm */
  SANE_Range y_range;
  SANE_Range x_range_ta;	/* size of scan area in TA mode in mm */
  SANE_Range y_range_ta;

  SANE_Bool isRGBInvert;	/* order of the CCD/CIS colors:
				   RGB if SANE_False, BGR otherwise */

  SANE_Int buttons;	/* number of buttons on the scanner */
  /* option names, titles, and descriptions for the buttons */
  SANE_String_Const button_name[MAX_BUTTONS];
  SANE_String_Const button_title[MAX_BUTTONS];
  SANE_String_Const button_desc[MAX_BUTTONS];
  /*@} */
} Scanner_Model;

typedef struct Scanner_Device
{
  struct Scanner_Device * next;

  const Scanner_Model * model;
  SANE_String name;
  SANE_Bool present;
} Scanner_Device;

typedef struct Scanner_Handle
{
  struct Scanner_Handle * next;

  const Scanner_Model * model;
  SANE_Option_Descriptor opt[NUM_OPTIONS];
  Option_Value val[NUM_OPTIONS];
  SANE_Parameters params;

  Scanner_State state;

  SANE_Bool bIsScanning;
  SANE_Bool bIsReading;
  SANE_Word read_rows;		/* number of image lines left to read */
  SANE_Byte * scan_buf;
  SANE_Byte * scan_buf_start;
  SANE_Int scan_buf_len;
} Scanner_Handle;

#endif
