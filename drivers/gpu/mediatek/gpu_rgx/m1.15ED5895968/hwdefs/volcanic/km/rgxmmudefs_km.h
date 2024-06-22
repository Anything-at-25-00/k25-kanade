/*************************************************************************/ /*!
@Title          Hardware definition file rgxmmudefs_km.h
@Brief          The file contains auto-generated hardware definitions without
                BVNC-specific compile time conditionals.
@Copyright      Copyright (c) Imagination Technologies Ltd. All Rights Reserved
@License        Dual MIT/GPLv2

The contents of this file are subject to the MIT license as set out below.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

Alternatively, the contents of this file may be used under the terms of
the GNU General Public License Version 2 ("GPL") in which case the provisions
of GPL are applicable instead of those above.

If you wish to allow use of your version of this file only under the terms of
GPL, and not to allow others to use your version of this file under the terms
of the MIT license, indicate your decision by deleting the provisions above
and replace them with the notice and other provisions required by GPL as set
out in the file called "GPL-COPYING" included in this distribution. If you do
not delete the provisions above, a recipient may use your version of this file
under the terms of either the MIT license or GPL.

This License is also included in this distribution in the file called
"MIT-COPYING".

EXCEPT AS OTHERWISE STATED IN A NEGOTIATED AGREEMENT: (A) THE SOFTWARE IS
PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT; AND (B) IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/ /**************************************************************************/

/*               ****   Autogenerated C -- do not edit    ****               */

/*
 *      rogue_bif.def
 */


#ifndef RGXMMUDEFS_KM_H
#define RGXMMUDEFS_KM_H

#include "img_types.h"
#include "img_defs.h"


#define RGXMMUDEFS_KM_REVISION 0

#define OSID_CTXT_MAPPING_REGISTERS_CONSTANTS_OSID_CTXT_MAPPING_NUM_ENTRIES_VALUE (0x00000010U)


#define OSID_CTXT_MAPPING_REGISTERS_CONSTANTS_OSID_CTXT_MAPPING_PER_OS_SHIFT_VALUE (0x00000004U)


#define OSID_CTXT_MAPPING_REGISTERS_CONSTANTS_OSID_CTXT_MAPPING_PER_OS_MASK_VALUE (0x00000007U)


#define RGX_BIF_DM_ENCODING_VERTEX                        (0x00000000U)
#define RGX_BIF_DM_ENCODING_PIXEL                         (0x00000001U)
#define RGX_BIF_DM_ENCODING_COMPUTE                       (0x00000002U)
#define RGX_BIF_DM_ENCODING_TLA                           (0x00000003U)
#define RGX_BIF_DM_ENCODING_PB_VCE                        (0x00000004U)
#define RGX_BIF_DM_ENCODING_PB_TE                         (0x00000005U)
#define RGX_BIF_DM_ENCODING_META                          (0x00000007U)
#define RGX_BIF_DM_ENCODING_HOST                          (0x00000008U)
#define RGX_BIF_DM_ENCODING_PM_ALIST                      (0x00000009U)


#define RGX_MMUCTRL_VADDR_PC_INDEX_SHIFT                  (30U)
#define RGX_MMUCTRL_VADDR_PC_INDEX_CLRMSK                 (IMG_UINT64_C(0xFFFFFF003FFFFFFF))
#define RGX_MMUCTRL_VADDR_PD_INDEX_SHIFT                  (21U)
#define RGX_MMUCTRL_VADDR_PD_INDEX_CLRMSK                 (IMG_UINT64_C(0xFFFFFFFFC01FFFFF))
#define RGX_MMUCTRL_VADDR_PT_INDEX_SHIFT                  (12U)
#define RGX_MMUCTRL_VADDR_PT_INDEX_CLRMSK                 (IMG_UINT64_C(0xFFFFFFFFFFE00FFF))


#define RGX_MMUCTRL_ENTRIES_PC_VALUE                      (0x00000400U)


#define RGX_MMUCTRL_ENTRIES_PD_VALUE                      (0x00000200U)


#define RGX_MMUCTRL_ENTRIES_PT_VALUE                      (0x00000200U)


#define RGX_MMUCTRL_ENTRY_SIZE_PC_VALUE                   (0x00000020U)


#define RGX_MMUCTRL_ENTRY_SIZE_PD_VALUE                   (0x00000040U)


#define RGX_MMUCTRL_ENTRY_SIZE_PT_VALUE                   (0x00000040U)


#define RGX_MMUCTRL_PAGE_SIZE_MASK                        (0x00000007U)
#define RGX_MMUCTRL_PAGE_SIZE_4KB                         (0x00000000U)
#define RGX_MMUCTRL_PAGE_SIZE_16KB                        (0x00000001U)
#define RGX_MMUCTRL_PAGE_SIZE_64KB                        (0x00000002U)
#define RGX_MMUCTRL_PAGE_SIZE_256KB                       (0x00000003U)
#define RGX_MMUCTRL_PAGE_SIZE_1MB                         (0x00000004U)
#define RGX_MMUCTRL_PAGE_SIZE_2MB                         (0x00000005U)


#define RGX_MMUCTRL_PAGE_4KB_RANGE_SHIFT                  (12U)
#define RGX_MMUCTRL_PAGE_4KB_RANGE_CLRMSK                 (IMG_UINT64_C(0xFFFFFF0000000FFF))


#define RGX_MMUCTRL_PAGE_16KB_RANGE_SHIFT                 (14U)
#define RGX_MMUCTRL_PAGE_16KB_RANGE_CLRMSK                (IMG_UINT64_C(0xFFFFFF0000003FFF))


#define RGX_MMUCTRL_PAGE_64KB_RANGE_SHIFT                 (16U)
#define RGX_MMUCTRL_PAGE_64KB_RANGE_CLRMSK                (IMG_UINT64_C(0xFFFFFF000000FFFF))


#define RGX_MMUCTRL_PAGE_256KB_RANGE_SHIFT                (18U)
#define RGX_MMUCTRL_PAGE_256KB_RANGE_CLRMSK               (IMG_UINT64_C(0xFFFFFF000003FFFF))


#define RGX_MMUCTRL_PAGE_1MB_RANGE_SHIFT                  (20U)
#define RGX_MMUCTRL_PAGE_1MB_RANGE_CLRMSK                 (IMG_UINT64_C(0xFFFFFF00000FFFFF))


#define RGX_MMUCTRL_PAGE_2MB_RANGE_SHIFT                  (21U)
#define RGX_MMUCTRL_PAGE_2MB_RANGE_CLRMSK                 (IMG_UINT64_C(0xFFFFFF00001FFFFF))


#define RGX_MMUCTRL_PT_BASE_4KB_RANGE_SHIFT               (12U)
#define RGX_MMUCTRL_PT_BASE_4KB_RANGE_CLRMSK              (IMG_UINT64_C(0xFFFFFF0000000FFF))


#define RGX_MMUCTRL_PT_BASE_16KB_RANGE_SHIFT              (10U)
#define RGX_MMUCTRL_PT_BASE_16KB_RANGE_CLRMSK             (IMG_UINT64_C(0xFFFFFF00000003FF))


#define RGX_MMUCTRL_PT_BASE_64KB_RANGE_SHIFT              (8U)
#define RGX_MMUCTRL_PT_BASE_64KB_RANGE_CLRMSK             (IMG_UINT64_C(0xFFFFFF00000000FF))


#define RGX_MMUCTRL_PT_BASE_256KB_RANGE_SHIFT             (6U)
#define RGX_MMUCTRL_PT_BASE_256KB_RANGE_CLRMSK            (IMG_UINT64_C(0xFFFFFF000000003F))


#define RGX_MMUCTRL_PT_BASE_1MB_RANGE_SHIFT               (5U)
#define RGX_MMUCTRL_PT_BASE_1MB_RANGE_CLRMSK              (IMG_UINT64_C(0xFFFFFF000000001F))


#define RGX_MMUCTRL_PT_BASE_2MB_RANGE_SHIFT               (5U)
#define RGX_MMUCTRL_PT_BASE_2MB_RANGE_CLRMSK              (IMG_UINT64_C(0xFFFFFF000000001F))


#define RGX_MMUCTRL_AXCACHE_MASK                          (0x0000000FU)
/*
Device Non-bufferable */
#define RGX_MMUCTRL_AXCACHE_DEVNONBUFF                    (0x00000000U)
/*
Device Bufferable */
#define RGX_MMUCTRL_AXCACHE_DEVBUFF                       (0x00000001U)
/*
Normal Non-cacheable Non-bufferable */
#define RGX_MMUCTRL_AXCACHE_NORMNONBUFF                   (0x00000002U)
/*
Normal Non-cacheable Bufferable */
#define RGX_MMUCTRL_AXCACHE_NORMBUFF                      (0x00000003U)
/*
Write-through No-allocate*/
#define RGX_MMUCTRL_AXCACHE_WTNOALLOC                     (0x00000006U)
/*
Write-back No-allocate*/
#define RGX_MMUCTRL_AXCACHE_WBNOALLOC                     (0x00000007U)
/*
Write-through Read-Allocate */
#define RGX_MMUCTRL_AXCACHE_WTRALLOC                      (0x00000008U)
/*
Write-back Read-Allocate */
#define RGX_MMUCTRL_AXCACHE_WBRALLOC                      (0x00000009U)
/*
Write-through Write-Allocate */
#define RGX_MMUCTRL_AXCACHE_WTWALLOC                      (0x0000000aU)
/*
Write-back Write-Allocate */
#define RGX_MMUCTRL_AXCACHE_WBWALLOC                      (0x0000000bU)
/*
Write-through Read/Write-Allocate */
#define RGX_MMUCTRL_AXCACHE_WTRWALLOC                     (0x0000000eU)
/*
Write-back Read/Write-Allocate */
#define RGX_MMUCTRL_AXCACHE_WBRWALLOC                     (0x0000000fU)


#define RGX_MMUCTRL_PT_DATA_PM_META_PROTECT_SHIFT         (62U)
#define RGX_MMUCTRL_PT_DATA_PM_META_PROTECT_CLRMSK        (IMG_UINT64_C(0xBFFFFFFFFFFFFFFF))
#define RGX_MMUCTRL_PT_DATA_PM_META_PROTECT_EN            (IMG_UINT64_C(0x4000000000000000))
#define RGX_MMUCTRL_PT_DATA_AXCACHE_SHIFT                 (58U)
#define RGX_MMUCTRL_PT_DATA_AXCACHE_CLRMSK                (IMG_UINT64_C(0xC3FFFFFFFFFFFFFF))
#define RGX_MMUCTRL_PT_DATA_AXCACHE_DEVNONBUFF            (IMG_UINT64_C(0x0000000000000000))
#define RGX_MMUCTRL_PT_DATA_AXCACHE_DEVBUFF               (IMG_UINT64_C(0x0400000000000000))
#define RGX_MMUCTRL_PT_DATA_AXCACHE_NORMNONBUFF           (IMG_UINT64_C(0x0800000000000000))
#define RGX_MMUCTRL_PT_DATA_AXCACHE_NORMBUFF              (IMG_UINT64_C(0x0c00000000000000))
#define RGX_MMUCTRL_PT_DATA_AXCACHE_WTNOALLOC             (IMG_UINT64_C(0x1800000000000000))
#define RGX_MMUCTRL_PT_DATA_AXCACHE_WBNOALLOC             (IMG_UINT64_C(0x1c00000000000000))
#define RGX_MMUCTRL_PT_DATA_AXCACHE_WTRALLOC              (IMG_UINT64_C(0x2000000000000000))
#define RGX_MMUCTRL_PT_DATA_AXCACHE_WBRALLOC              (IMG_UINT64_C(0x2400000000000000))
#define RGX_MMUCTRL_PT_DATA_AXCACHE_WTWALLOC              (IMG_UINT64_C(0x2800000000000000))
#define RGX_MMUCTRL_PT_DATA_AXCACHE_WBWALLOC              (IMG_UINT64_C(0x2c00000000000000))
#define RGX_MMUCTRL_PT_DATA_AXCACHE_WTRWALLOC             (IMG_UINT64_C(0x3800000000000000))
#define RGX_MMUCTRL_PT_DATA_AXCACHE_WBRWALLOC             (IMG_UINT64_C(0x3c00000000000000))
#define RGX_MMUCTRL_PT_DATA_VP_PAGE_HI_SHIFT              (40U)
#define RGX_MMUCTRL_PT_DATA_VP_PAGE_HI_CLRMSK             (IMG_UINT64_C(0xFC0000FFFFFFFFFF))
#define RGX_MMUCTRL_PT_DATA_PAGE_SHIFT                    (12U)
#define RGX_MMUCTRL_PT_DATA_PAGE_CLRMSK                   (IMG_UINT64_C(0xFFFFFF0000000FFF))
#define RGX_MMUCTRL_PT_DATA_VP_PAGE_LO_SHIFT              (6U)
#define RGX_MMUCTRL_PT_DATA_VP_PAGE_LO_CLRMSK             (IMG_UINT64_C(0xFFFFFFFFFFFFF03F))
#define RGX_MMUCTRL_PT_DATA_ENTRY_PENDING_SHIFT           (5U)
#define RGX_MMUCTRL_PT_DATA_ENTRY_PENDING_CLRMSK          (IMG_UINT64_C(0xFFFFFFFFFFFFFFDF))
#define RGX_MMUCTRL_PT_DATA_ENTRY_PENDING_EN              (IMG_UINT64_C(0x0000000000000020))
#define RGX_MMUCTRL_PT_DATA_PM_SRC_SHIFT                  (4U)
#define RGX_MMUCTRL_PT_DATA_PM_SRC_CLRMSK                 (IMG_UINT64_C(0xFFFFFFFFFFFFFFEF))
#define RGX_MMUCTRL_PT_DATA_PM_SRC_EN                     (IMG_UINT64_C(0x0000000000000010))
#define RGX_MMUCTRL_PT_DATA_CC_SHIFT                      (2U)
#define RGX_MMUCTRL_PT_DATA_CC_CLRMSK                     (IMG_UINT64_C(0xFFFFFFFFFFFFFFFB))
#define RGX_MMUCTRL_PT_DATA_CC_EN                         (IMG_UINT64_C(0x0000000000000004))
#define RGX_MMUCTRL_PT_DATA_READ_ONLY_SHIFT               (1U)
#define RGX_MMUCTRL_PT_DATA_READ_ONLY_CLRMSK              (IMG_UINT64_C(0xFFFFFFFFFFFFFFFD))
#define RGX_MMUCTRL_PT_DATA_READ_ONLY_EN                  (IMG_UINT64_C(0x0000000000000002))
#define RGX_MMUCTRL_PT_DATA_VALID_SHIFT                   (0U)
#define RGX_MMUCTRL_PT_DATA_VALID_CLRMSK                  (IMG_UINT64_C(0xFFFFFFFFFFFFFFFE))
#define RGX_MMUCTRL_PT_DATA_VALID_EN                      (IMG_UINT64_C(0x0000000000000001))


#define RGX_MMUCTRL_PD_DATA_ENTRY_PENDING_SHIFT           (40U)
#define RGX_MMUCTRL_PD_DATA_ENTRY_PENDING_CLRMSK          (IMG_UINT64_C(0xFFFFFEFFFFFFFFFF))
#define RGX_MMUCTRL_PD_DATA_ENTRY_PENDING_EN              (IMG_UINT64_C(0x0000010000000000))
#define RGX_MMUCTRL_PD_DATA_PT_BASE_SHIFT                 (5U)
#define RGX_MMUCTRL_PD_DATA_PT_BASE_CLRMSK                (IMG_UINT64_C(0xFFFFFF000000001F))
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_SHIFT               (1U)
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_CLRMSK              (IMG_UINT64_C(0xFFFFFFFFFFFFFFF1))
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_4KB                 (IMG_UINT64_C(0x0000000000000000))
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_16KB                (IMG_UINT64_C(0x0000000000000002))
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_64KB                (IMG_UINT64_C(0x0000000000000004))
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_256KB               (IMG_UINT64_C(0x0000000000000006))
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_1MB                 (IMG_UINT64_C(0x0000000000000008))
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_2MB                 (IMG_UINT64_C(0x000000000000000a))
#define RGX_MMUCTRL_PD_DATA_VALID_SHIFT                   (0U)
#define RGX_MMUCTRL_PD_DATA_VALID_CLRMSK                  (IMG_UINT64_C(0xFFFFFFFFFFFFFFFE))
#define RGX_MMUCTRL_PD_DATA_VALID_EN                      (IMG_UINT64_C(0x0000000000000001))


#define RGX_MMUCTRL_PC_DATA_PD_BASE_SHIFT                 (4U)
#define RGX_MMUCTRL_PC_DATA_PD_BASE_CLRMSK                (0x0000000FU)
#define RGX_MMUCTRL_PC_DATA_PD_BASE_ALIGNSHIFT            (12U)
#define RGX_MMUCTRL_PC_DATA_PD_BASE_ALIGNSIZE             (4096U)
#define RGX_MMUCTRL_PC_DATA_ENTRY_PENDING_SHIFT           (1U)
#define RGX_MMUCTRL_PC_DATA_ENTRY_PENDING_CLRMSK          (0xFFFFFFFDU)
#define RGX_MMUCTRL_PC_DATA_ENTRY_PENDING_EN              (0x00000002U)
#define RGX_MMUCTRL_PC_DATA_VALID_SHIFT                   (0U)
#define RGX_MMUCTRL_PC_DATA_VALID_CLRMSK                  (0xFFFFFFFEU)
#define RGX_MMUCTRL_PC_DATA_VALID_EN                      (0x00000001U)


#endif /* RGXMMUDEFS_KM_H */
/*****************************************************************************
 End of file (rgxmmudefs_km.h)
*****************************************************************************/
