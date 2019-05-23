/***************************************************************************/
/*                                                                         */
/*  cf2ft.c                                                                */
/*                                                                         */
/*    FreeType Glue ClientComponent to Adobe's Interpreter (body).               */
/*                                                                         */
/*  Copyright 2013-2014 Adobe Systems Incorporated.                        */
/*                                                                         */
/*  This software, and all works of authorship, whether in source or       */
/*  object code form as indicated by the copyright notice(s) included      */
/*  herein (collectively, the "Work") is made available, and may only be   */
/*  used, modified, and distributed under the FreeType Project License,    */
/*  LICENSE.TXT.  Additionally, subject to the terms and conditions of the */
/*  FreeType Project License, each contributor to the Work hereby grants   */
/*  to any individual or legal entity exercising permissions granted by    */
/*  the FreeType Project License and this section (hereafter, "You" or     */
/*  "Your") a perpetual, worldwide, non-exclusive, no-charge,              */
/*  royalty-free, irrevocable (except as stated in this section) patent    */
/*  license to make, have made, use, offer to sell, sell, import, and      */
/*  otherwise transfer the Work, where such license applies only to those  */
/*  patent claims licensable by such contributor that are necessarily      */
/*  infringed by their contribution(s) alone or by combination of their    */
/*  contribution(s) with the Work to which such contribution(s) was        */
/*  submitted.  If You institute patent litigation against any entity      */
/*  (including a cross-claim or counterclaim in a lawsuit) alleging that   */
/*  the Work or a contribution incorporated within the Work constitutes    */
/*  direct or contributory patent infringement, then any patent licenses   */
/*  granted to You under this License for that Work shall terminate as of  */
/*  the date such litigation is filed.                                     */
/*                                                                         */
/*  By using, modifying, or distributing the Work you indicate that you    */
/*  have read and understood the terms and conditions of the               */
/*  FreeType Project License as well as those provided in this section,    */
/*  and you accept them fully.                                             */
/*                                                                         */
/***************************************************************************/


#include "cf2ft.h"
#include FT_INTERNAL_DEBUG_H

#include "cf2font.h"
#include "cf2error.h"


#define CF2_MAX_SIZE  cf2_intToFixed( 2000 )    /* max ppem */


  /*
   * This check should avoid most internal overflow cases.  Clients should
   * generally respond to `Glyph_Too_Big' by getting a glyph outline
   * at EM size, scaling it and filling it as a graphics operation.
   *
   */
  static FT_Error
  cf2_checkTransform( const CF2_Matrix*  transform,
                      CF2_Int            unitsPerEm )
  {
    CF2_Fixed  maxScale;


    FT_ASSERT( unitsPerEm > 0 );

    if ( transform->a <= 0 || transform->d <= 0 )
      return FT_THROW( Invalid_Size_Handle );

    FT_ASSERT( transform->b == 0 && transform->c == 0 );
    FT_ASSERT( transform->tx == 0 && transform->ty == 0 );

    if ( unitsPerEm > 0x7FFF )
      return FT_THROW( Glyph_Too_Big );

    maxScale = FT_DivFix( CF2_MAX_SIZE, cf2_intToFixed( unitsPerEm ) );

    if ( transform->a > maxScale || transform->d > maxScale )
      return FT_THROW( Glyph_Too_Big );

    return FT_Err_Ok;
  }


  static void
  cf2_setGlyphWidth( CF2_Outline  outline,
                     CF2_Fixed    width )
  {
    CFF_Decoder*  decoder = outline->decoder;


    FT_ASSERT( decoder );

    decoder->glyph_width = cf2_fixedToInt( width );
  }


  /* Clean up font instance. */
  static void
  cf2_free_instance( void*  ptr )
  {
    CF2_Font  font = (CF2_Font)ptr;


    if ( font )
    {
      FT_Memory  memory = font->memory;


      (void)memory;
    }
  }


  /********************************************/
  /*                                          */
  /* functions for handling client outline;   */
  /* FreeType uses coordinates in 26.6 format */
  /*                                          */
  /********************************************/

  static void
  cf2_builder_moveTo( CF2_OutlineCallbacks      callbacks,
                      const CF2_CallbackParams  params )
  {
    /* downcast the object pointer */
    CF2_Outline   outline = (CF2_Outline)callbacks;
    CFF_Builder*  builder;

    (void)params;        /* only used in debug mode */


    FT_ASSERT( outline && outline->decoder );
    FT_ASSERT( params->op == CF2_PathOpMoveTo );

    builder = &outline->decoder->builder;

    /* note: two successive moves simply close the contour twice */
    cff_builder_close_contour( builder );
    builder->path_begun = 0;
  }


  static void
  cf2_builder_lineTo( CF2_OutlineCallbacks      callbacks,
                      const CF2_CallbackParams  params )
  {
    FT_Error  error;

    /* downcast the object pointer */
    CF2_Outline   outline = (CF2_Outline)callbacks;
    CFF_Builder*  builder;


    FT_ASSERT( outline && outline->decoder );
    FT_ASSERT( params->op == CF2_PathOpLineTo );

    builder = &outline->decoder->builder;

    if ( !builder->path_begun )
    {
      /* record the move before the line; also check points and set */
      /* `path_begun'                                               */
      error = cff_builder_start_point( builder,
                                       params->pt0.x,
                                       params->pt0.y );
      if ( error )
      {
        if ( !*callbacks->error )
          *callbacks->error =  error;
        return;
      }
    }

    /* `cff_builder_add_point1' includes a check_points call for one point */
    error = cff_builder_add_point1( builder,
                                    params->pt1.x,
                                    params->pt1.y );
    if ( error )
    {
      if ( !*callbacks->error )
        *callbacks->error =  error;
      return;
    }
  }


  static void
  cf2_builder_cubeTo( CF2_OutlineCallbacks      callbacks,
                      const CF2_CallbackParams  params )
  {
    FT_Error  error;

    /* downcast the object pointer */
    CF2_Outline   outline = (CF2_Outline)callbacks;
    CFF_Builder*  builder;


    FT_ASSERT( outline && outline->decoder );
    FT_ASSERT( params->op == CF2_PathOpCubeTo );

    builder = &outline->decoder->builder;

    if ( !builder->path_begun )
    {
      /* record the move before the line; also check points and set */
      /* `path_begun'                                               */
      error = cff_builder_start_point( builder,
                                       params->pt0.x,
                                       params->pt0.y );
      if ( error )
      {
        if ( !*callbacks->error )
          *callbacks->error =  error;
        return;
      }
    }

    /* prepare room for 3 points: 2 off-curve, 1 on-curve */
    error = cff_check_points( builder, 3 );
    if ( error )
    {
      if ( !*callbacks->error )
        *callbacks->error =  error;
      return;
    }

    cff_builder_add_point( builder,
                           params->pt1.x,
                           params->pt1.y, 0 );
    cff_builder_add_point( builder,
                           params->pt2.x,
                           params->pt2.y, 0 );
    cff_builder_add_point( builder,
                           params->pt3.x,
                           params->pt3.y, 1 );
  }


  static void
  cf2_outline_init( CF2_Outline  outline,
                    FT_Memory    memory,
                    FT_Error*    error )
  {
    FT_MEM_ZERO( outline, sizeof ( CF2_OutlineRec ) );

    outline->root.memory = memory;
    outline->root.error  = error;

    outline->root.moveTo = cf2_builder_moveTo;
    outline->root.lineTo = cf2_builder_lineTo;
    outline->root.cubeTo = cf2_builder_cubeTo;
  }


  /* get scaling and hint flag from GlyphSlot */
  static void
  cf2_getScaleAndHintFlag( CFF_Decoder*  decoder,
                           CF2_Fixed*    x_scale,
                           CF2_Fixed*    y_scale,
                           FT_Bool*      hinted,
                           FT_Bool*      scaled )
  {
    FT_ASSERT( decoder && decoder->builder.glyph );

    /* note: FreeType scale includes a factor of 64 */
    *hinted = decoder->builder.glyph->hint;
    *scaled = decoder->builder.glyph->scaled;

    if ( *hinted )
    {
      *x_scale = ( decoder->builder.glyph->x_scale + 32 ) / 64;
      *y_scale = ( decoder->builder.glyph->y_scale + 32 ) / 64;
    }
    else
    {
      /* for unhinted outlines, `cff_slot_load' does the scaling, */
      /* thus render at `unity' scale                             */

      *x_scale = 0x0400;   /* 1/64 as 16.16 */
      *y_scale = 0x0400;
    }
  }


  /* get units per em from `FT_Face' */
  /* TODO: should handle font matrix concatenation? */
  static FT_UShort
  cf2_getUnitsPerEm( CFF_Decoder*  decoder )
  {
    FT_ASSERT( decoder && decoder->builder.face );
    FT_ASSERT( decoder->builder.face->root.units_per_EM );

    return decoder->builder.face->root.units_per_EM;
  }


  /* Main entry point: Render one glyph. */
  FT_LOCAL_DEF( FT_Error )
  cf2_decoder_parse_charstrings( CFF_Decoder*  decoder,
                                 FT_Byte*      charstring_base,
                                 FT_ULong      charstring_len )
  {
    FT_Memory  memory;
    FT_Error   error = FT_Err_Ok;
    CF2_Font   font;


    FT_ASSERT( decoder && decoder->cff );

    memory = decoder->builder.memory;

    /* CF2 data is saved here across glyphs */
    font = (CF2_Font)decoder->cff->cf2_instance.data;

    /* on first glyph, allocate instance structure */
    if ( decoder->cff->cf2_instance.data == NULL )
    {
      decoder->cff->cf2_instance.finalizer =
        (FT_Generic_Finalizer)cf2_free_instance;

      if ( FT_ALLOC( decoder->cff->cf2_instance.data,
                     sizeof ( CF2_FontRec ) ) )
        return FT_THROW( Out_Of_Memory );

      font = (CF2_Font)decoder->cff->cf2_instance.data;

      font->memory = memory;

      /* initialize a client outline, to be shared by each glyph rendered */
      cf2_outline_init( &font->outline, font->memory, &font->error );
    }

    /* save decoder; it is a stack variable and will be different on each */
    /* call                                                               */
    font->decoder         = decoder;
    font->outline.decoder = decoder;

    {
      /* build parameters for Adobe engine */

      CFF_Builder*  builder = &decoder->builder;
      CFF_Driver    driver  = (CFF_Driver)FT_FACE_DRIVER( builder->face );

      /* local error */
      FT_Error       error2 = FT_Err_Ok;
      CF2_BufferRec  buf;
      CF2_Matrix     transform;
      CF2_F16Dot16   glyphWidth;

      FT_Bool  hinted;
      FT_Bool  scaled;


      /* FreeType has already looked up the GID; convert to         */
      /* `RegionBuffer', assuming that the input has been validated */
      FT_ASSERT( charstring_base + charstring_len >= charstring_base );

      FT_ZERO( &buf );
      buf.start =
      buf.ptr   = charstring_base;
      buf.end   = charstring_base + charstring_len;

      FT_ZERO( &transform );

      cf2_getScaleAndHintFlag( decoder,
                               &transform.a,
                               &transform.d,
                               &hinted,
                               &scaled );

      font->renderingFlags = 0;
      if ( hinted )
        font->renderingFlags |= CF2_FlagsHinted;
      if ( scaled && !driver->no_stem_darkening )
        font->renderingFlags |= CF2_FlagsDarkened;

      font->darkenParams[0] = driver->darken_params[0];
      font->darkenParams[1] = driver->darken_params[1];
      font->darkenParams[2] = driver->darken_params[2];
      font->darkenParams[3] = driver->darken_params[3];
      font->darkenParams[4] = driver->darken_params[4];
      font->darkenParams[5] = driver->darken_params[5];
      font->darkenParams[6] = driver->darken_params[6];
      font->darkenParams[7] = driver->darken_params[7];

      /* now get an outline for this glyph;      */
      /* also get units per em to validate scale */
      font->unitsPerEm = (CF2_Int)cf2_getUnitsPerEm( decoder );

      if ( scaled )
      {
        error2 = cf2_checkTransform( &transform, font->unitsPerEm );
        if ( error2 )
          return error2;
      }

      error2 = cf2_getGlyphOutline( font, &buf, &transform, &glyphWidth );
      if ( error2 )
        return FT_ERR( Invalid_File_Format );

      cf2_setGlyphWidth( &font->outline, glyphWidth );

      return FT_Err_Ok;
    }
  }


  /* get pointer to current FreeType subfont (based on current glyphID) */
  FT_LOCAL_DEF( CFF_SubFont )
  cf2_getSubfont( CFF_Decoder*  decoder )
  {
    FT_ASSERT( decoder && decoder->current_subfont );

    return decoder->current_subfont;
  }


  /* get `y_ppem' from `CFF_Size' */
  FT_LOCAL_DEF( CF2_Fixed )
  cf2_getPpemY( CFF_Decoder*  decoder )
  {
    FT_ASSERT( decoder                          &&
               decoder->builder.face            &&
               decoder->builder.face->root.size );

    /*
     * Note that `y_ppem' can be zero if there wasn't a call to
     * `FT_Set_Char_Size' or something similar.  However, this isn't a
     * problem since we come to this place in the code only if
     * FT_LOAD_NO_SCALE is set (the other case gets caught by
     * `cf2_checkTransform').  The ppem value is needed to compute the stem
     * darkening, which is disabled for getting the unscaled outline.
     *
     */
    return cf2_intToFixed(
             decoder->builder.face->root.size->metrics.y_ppem );
  }


  /* get standard stem widths for the current subfont; */
  /* FreeType stores these as integer font units       */
  /* (note: variable names seem swapped)               */
  FT_LOCAL_DEF( CF2_Fixed )
  cf2_getStdVW( CFF_Decoder*  decoder )
  {
    FT_ASSERT( decoder && decoder->current_subfont );

    return cf2_intToFixed(
             decoder->current_subfont->private_dict.standard_height );
  }


  FT_LOCAL_DEF( CF2_Fixed )
  cf2_getStdHW( CFF_Decoder*  decoder )
  {
    FT_ASSERT( decoder && decoder->current_subfont );

    return cf2_intToFixed(
             decoder->current_subfont->private_dict.standard_width );
  }


  /* note: FreeType stores 1000 times the actual value for `BlueScale' */
  FT_LOCAL_DEF( void )
  cf2_getBlueMetrics( CFF_Decoder*  decoder,
                      CF2_Fixed*    blueScale,
                      CF2_Fixed*    blueShift,
                      CF2_Fixed*    blueFuzz )
  {
    FT_ASSERT( decoder && decoder->current_subfont );

    *blueScale = FT_DivFix(
                   decoder->current_subfont->private_dict.blue_scale,
                   cf2_intToFixed( 1000 ) );
    *blueShift = cf2_intToFixed(
                   decoder->current_subfont->private_dict.blue_shift );
    *blueFuzz  = cf2_intToFixed(
                   decoder->current_subfont->private_dict.blue_fuzz );
  }


  /* get blue values counts and arrays; the FreeType parser has validated */
  /* the counts and verified that each is an even number                  */
  FT_LOCAL_DEF( void )
  cf2_getBlueValues( CFF_Decoder*  decoder,
                     size_t*       count,
                     FT_Pos*      *data )
  {
    FT_ASSERT( decoder && decoder->current_subfont );

    *count = decoder->current_subfont->private_dict.num_blue_values;
    *data  = (FT_Pos*)
               &decoder->current_subfont->private_dict.blue_values;
  }


  FT_LOCAL_DEF( void )
  cf2_getOtherBlues( CFF_Decoder*  decoder,
                     size_t*       count,
                     FT_Pos*      *data )
  {
    FT_ASSERT( decoder && decoder->current_subfont );

    *count = decoder->current_subfont->private_dict.num_other_blues;
    *data  = (FT_Pos*)
               &decoder->current_subfont->private_dict.other_blues;
  }


  FT_LOCAL_DEF( void )
  cf2_getFamilyBlues( CFF_Decoder*  decoder,
                      size_t*       count,
                      FT_Pos*      *data )
  {
    FT_ASSERT( decoder && decoder->current_subfont );

    *count = decoder->current_subfont->private_dict.num_family_blues;
    *data  = (FT_Pos*)
               &decoder->current_subfont->private_dict.family_blues;
  }


  FT_LOCAL_DEF( void )
  cf2_getFamilyOtherBlues( CFF_Decoder*  decoder,
                           size_t*       count,
                           FT_Pos*      *data )
  {
    FT_ASSERT( decoder && decoder->current_subfont );

    *count = decoder->current_subfont->private_dict.num_family_other_blues;
    *data  = (FT_Pos*)
               &decoder->current_subfont->private_dict.family_other_blues;
  }


  FT_LOCAL_DEF( CF2_Int )
  cf2_getLanguageGroup( CFF_Decoder*  decoder )
  {
    FT_ASSERT( decoder && decoder->current_subfont );

    return decoder->current_subfont->private_dict.language_group;
  }


  /* convert unbiased subroutine index to `CF2_Buffer' and */
  /* return 0 on success                                   */
  FT_LOCAL_DEF( CF2_Int )
  cf2_initGlobalRegionBuffer( CFF_Decoder*  decoder,
                              CF2_Int       subrNum,
                              CF2_Buffer    buf )
  {
    CF2_UInt  idx;


    FT_ASSERT( decoder );

    FT_ZERO( buf );

    idx = (CF2_UInt)( subrNum + decoder->globals_bias );
    if ( idx >= decoder->num_globals )
      return TRUE;     /* error */

    FT_ASSERT( decoder->globals );

    buf->start =
    buf->ptr   = decoder->globals[idx];
    buf->end   = decoder->globals[idx + 1];

    return FALSE;      /* success */
  }


  /* convert AdobeStandardEncoding code to CF2_Buffer; */
  /* used for seac component                           */
  FT_LOCAL_DEF( FT_Error )
  cf2_getSeacComponent( CFF_Decoder*  decoder,
                        CF2_Int       code,
                        CF2_Buffer    buf )
  {
    CF2_Int   gid;
    FT_Byte*  charstring;
    FT_ULong  len;
    FT_Error  error;


    FT_ASSERT( decoder );

    FT_ZERO( buf );

#ifdef FT_CONFIG_OPTION_INCREMENTAL
    /* Incremental fonts don't necessarily have valid charsets.        */
    /* They use the character code, not the glyph index, in this case. */
    if ( decoder->builder.face->root.internal->incremental_interface )
      gid = code;
    else
#endif /* FT_CONFIG_OPTION_INCREMENTAL */
    {
      gid = cff_lookup_glyph_by_stdcharcode( decoder->cff, code );
      if ( gid < 0 )
        return FT_THROW( Invalid_Glyph_Format );
    }

    error = cff_get_glyph_data( decoder->builder.face,
                                (CF2_UInt)gid,
                                &charstring,
                                &len );
    /* TODO: for now, just pass the FreeType error through */
    if ( error )
      return error;

    /* assume input has been validated */
    FT_ASSERT( charstring + len >= charstring );

    buf->start = charstring;
    buf->end   = charstring + len;
    buf->ptr   = buf->start;

    return FT_Err_Ok;
  }


  FT_LOCAL_DEF( void )
  cf2_freeSeacComponent( CFF_Decoder*  decoder,
                         CF2_Buffer    buf )
  {
    FT_ASSERT( decoder );

    cff_free_glyph_data( decoder->builder.face,
                         (FT_Byte**)&buf->start,
                         (FT_ULong)( buf->end - buf->start ) );
  }


  FT_LOCAL_DEF( CF2_Int )
  cf2_initLocalRegionBuffer( CFF_Decoder*  decoder,
                             CF2_Int       subrNum,
                             CF2_Buffer    buf )
  {
    CF2_UInt  idx;


    FT_ASSERT( decoder );

    FT_ZERO( buf );

    idx = (CF2_UInt)( subrNum + decoder->locals_bias );
    if ( idx >= decoder->num_locals )
      return TRUE;     /* error */

    FT_ASSERT( decoder->locals );

    buf->start =
    buf->ptr   = decoder->locals[idx];
    buf->end   = decoder->locals[idx + 1];

    return FALSE;      /* success */
  }


  FT_LOCAL_DEF( CF2_Fixed )
  cf2_getDefaultWidthX( CFF_Decoder*  decoder )
  {
    FT_ASSERT( decoder && decoder->current_subfont );

    return cf2_intToFixed(
             decoder->current_subfont->private_dict.default_width );
  }


  FT_LOCAL_DEF( CF2_Fixed )
  cf2_getNominalWidthX( CFF_Decoder*  decoder )
  {
    FT_ASSERT( decoder && decoder->current_subfont );

    return cf2_intToFixed(
             decoder->current_subfont->private_dict.nominal_width );
  }


  FT_LOCAL_DEF( void )
  cf2_outline_reset( CF2_Outline  outline )
  {
    CFF_Decoder*  decoder = outline->decoder;


    FT_ASSERT( decoder );

    outline->root.windingMomentum = 0;

    FT_GlyphLoader_Rewind( decoder->builder.loader );
  }


  FT_LOCAL_DEF( void )
  cf2_outline_close( CF2_Outline  outline )
  {
    CFF_Decoder*  decoder = outline->decoder;


    FT_ASSERT( decoder );

    cff_builder_close_contour( &decoder->builder );

    FT_GlyphLoader_Add( decoder->builder.loader );
  }


/* END */
