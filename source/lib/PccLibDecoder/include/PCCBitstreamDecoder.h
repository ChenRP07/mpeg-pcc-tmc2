/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2017, ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PCCBitstreamDecoder_h
#define PCCBitstreamDecoder_h

#include "PCCCommon.h"
#include "PCCDecoderParameters.h"
#include "PCCCodec.h"
#include "PCCMath.h"
#include "ArithmeticCodec.h"
#include "PCCMetadata.h"
#include "PCCPatch.h"

namespace pcc {

class PCCBitstream;
class PCCContext;
class Arithmetic_Codec;

class PCCBitstreamDecoder {
 public:
  PCCBitstreamDecoder();
  ~PCCBitstreamDecoder();

  int decode( PCCBitstream &bitstream , PCCContext &context );

private:
  int  readMetadata( PCCMetadata &metadata, PCCBitstream &bitstream);
  int  decompressMetadata( PCCMetadata &metadata,
                           o3dgc::Arithmetic_Codec &arithmeticDecoder);
  int  decompressMetadata( PCCMetadata &metadata,
                           o3dgc::Arithmetic_Codec &arithmeticDecoder,
                           o3dgc::Static_Bit_Model &bModelMaxDepth0,
                           o3dgc::Adaptive_Bit_Model &bModelMaxDepthDD);
  int  decompressHeader( PCCContext &context, PCCBitstream &bitstream );

  void decompressOccupancyMap( PCCContext &context,  PCCBitstream& bitstream );
  void decompressOccupancyMap( PCCContext &context, PCCFrameContext& frame, PCCBitstream &bitstream,
                               PCCFrameContext& preFrame, size_t frameIndex );

  void readMissedPointsGeometryNumber( PCCContext& context, PCCBitstream &bitstream);
  void readMissedPointsTextureNumber( PCCContext& context, PCCBitstream &bitstream);

  void decompressPatchMetaDataM42195( PCCContext& context,
                                      PCCFrameContext& frame,
                                      PCCFrameContext& preFrame,
                                      PCCBitstream &bitstream ,
                                      o3dgc::Arithmetic_Codec &arithmeticDecoder,
                                      o3dgc::Static_Bit_Model &bModel0,
                                      uint32_t &compressedBitstreamSize,
                                      size_t occupancyPrecision,
                                      uint8_t enable_flexible_patch_flag);

  void decompressOneLayerData( PCCContext&                 context,
                               PCCFrameContext&            frame,
                               PCCPatch&                   patch,
                               o3dgc::Arithmetic_Codec&    arithmeticDecoder,
                               o3dgc::Adaptive_Bit_Model&  occupiedModel,
                               o3dgc::Adaptive_Bit_Model&  interpolateModel,
                               o3dgc::Adaptive_Data_Model& neighborModel,
                               o3dgc::Adaptive_Data_Model& minD1Model,
                               o3dgc::Adaptive_Bit_Model&  fillingModel );

  uint32_t DecodeUInt32( const uint32_t bitCount,
                         o3dgc::Arithmetic_Codec &arithmeticDecoder,
                         o3dgc::Static_Bit_Model &bModel0 );
};


}; //~namespace

#endif /* PCCBitstreamDecoder_h */