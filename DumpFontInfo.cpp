// DumpFontInfo.cpp
// Copyright (C) 2020 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>
// This file is public domain software.
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_WINFONTS_H
#include FT_BITMAP_H
#include FT_TRUETYPE_TABLES_H
#include FT_TRUETYPE_IDS_H
using namespace std;

typedef struct _WIN_PANOSE
{
    unsigned char bFamilyType;
    unsigned char bSerifStyle;
    unsigned char bWeight;
    unsigned char bProportion;
    unsigned char bContrast;
    unsigned char bStrokeVariation;
    unsigned char bArmStyle;
    unsigned char bLetterform;
    unsigned char bMidline;
    unsigned char bXHeight;
} WIN_PANOSE;

std::string DoGetPanoseString(const PANOSE *panose)
{
    std::string ret;
    switch (panose->bFamilyType)
    {
    case PAN_ANY: ret += "PAN_ANY"; break;
    case PAN_NO_FIT: ret += "PAN_NO_FIT"; break;
    case PAN_FAMILY_TEXT_DISPLAY: ret += "PAN_FAMILY_TEXT_DISPLAY"; break;
    case PAN_FAMILY_SCRIPT: ret += "PAN_FAMILY_SCRIPT"; break;
    case PAN_FAMILY_DECORATIVE: ret += "PAN_FAMILY_DECORATIVE"; break;
    case PAN_FAMILY_PICTORIAL: ret += "PAN_FAMILY_PICTORIAL"; break;
    default: ret += "(unknown)";
    }

    ret += ", ";

    switch (panose->bSerifStyle)
    {
    case PAN_ANY: ret += "PAN_ANY"; break;
    case PAN_NO_FIT: ret += "PAN_NO_FIT"; break;
    case PAN_SERIF_COVE: ret += "PAN_SERIF_COVE"; break;
    case PAN_SERIF_OBTUSE_COVE: ret += "PAN_SERIF_OBTUSE_COVE"; break;
    case PAN_SERIF_SQUARE_COVE: ret += "PAN_SERIF_SQUARE_COVE"; break;
    case PAN_SERIF_OBTUSE_SQUARE_COVE: ret += "PAN_SERIF_OBTUSE_SQUARE_COVE"; break;
    case PAN_SERIF_SQUARE: ret += "PAN_SERIF_SQUARE"; break;
    case PAN_SERIF_THIN: ret += "PAN_SERIF_THIN"; break;
    case PAN_SERIF_BONE: ret += "PAN_SERIF_BONE"; break;
    case PAN_SERIF_EXAGGERATED: ret += "PAN_SERIF_EXAGGERATED"; break;
    case PAN_SERIF_TRIANGLE: ret += "PAN_SERIF_TRIANGLE"; break;
    case PAN_SERIF_NORMAL_SANS: ret += "PAN_SERIF_NORMAL_SANS"; break;
    case PAN_SERIF_OBTUSE_SANS: ret += "PAN_SERIF_OBTUSE_SANS"; break;
    case PAN_SERIF_PERP_SANS: ret += "PAN_SERIF_PERP_SANS"; break;
    case PAN_SERIF_FLARED: ret += "PAN_SERIF_FLARED"; break;
    case PAN_SERIF_ROUNDED: ret += "PAN_SERIF_ROUNDED"; break;
    default: ret += "(unknown)";
    }

    ret += ", ";

    switch (panose->bWeight)
    {
    case PAN_ANY: ret += "PAN_ANY"; break;
    case PAN_NO_FIT: ret += "No fit"; break;
    case PAN_WEIGHT_VERY_LIGHT: ret += "PAN_WEIGHT_VERY_LIGHT"; break;
    case PAN_WEIGHT_LIGHT: ret += "PAN_WEIGHT_LIGHT"; break;
    case PAN_WEIGHT_THIN: ret += "PAN_WEIGHT_THIN"; break;
    case PAN_WEIGHT_BOOK: ret += "PAN_WEIGHT_BOOK"; break;
    case PAN_WEIGHT_MEDIUM: ret += "PAN_WEIGHT_MEDIUM"; break;
    case PAN_WEIGHT_DEMI: ret += "PAN_WEIGHT_DEMI"; break;
    case PAN_WEIGHT_BOLD: ret += "PAN_WEIGHT_BOLD"; break;
    case PAN_WEIGHT_HEAVY: ret += "PAN_WEIGHT_HEAVY"; break;
    case PAN_WEIGHT_BLACK: ret += "PAN_WEIGHT_BLACK"; break;
    case PAN_WEIGHT_NORD: ret += "PAN_WEIGHT_NORD"; break;
    default: ret += "(unknown)";
    }

    ret += ", ";

    switch (panose->bProportion)
    {
    case PAN_ANY: ret += "PAN_ANY"; break;
    case PAN_NO_FIT: ret += "PAN_NO_FIT"; break;
    case PAN_PROP_OLD_STYLE: ret += "PAN_PROP_OLD_STYLE"; break;
    case PAN_PROP_MODERN: ret += "PAN_PROP_MODERN"; break;
    case PAN_PROP_EVEN_WIDTH: ret += "PAN_PROP_EVEN_WIDTH"; break;
    case PAN_PROP_EXPANDED: ret += "PAN_PROP_EXPANDED"; break;
    case PAN_PROP_CONDENSED: ret += "PAN_PROP_CONDENSED"; break;
    case PAN_PROP_VERY_EXPANDED: ret += "PAN_PROP_VERY_EXPANDED"; break;
    case PAN_PROP_VERY_CONDENSED: ret += "PAN_PROP_VERY_CONDENSED"; break;
    case PAN_PROP_MONOSPACED: ret += "PAN_PROP_MONOSPACED"; break;
    default: ret += "(unknown)";
    }

    ret += ", ";

    switch (panose->bContrast)
    {
    case PAN_ANY: ret += "PAN_ANY"; break;
    case PAN_NO_FIT: ret += "PAN_NO_FIT"; break;
    case PAN_CONTRAST_NONE: ret += "PAN_CONTRAST_NONE"; break;
    case PAN_CONTRAST_VERY_LOW: ret += "PAN_CONTRAST_VERY_LOW"; break;
    case PAN_CONTRAST_LOW: ret += "PAN_CONTRAST_LOW"; break;
    case PAN_CONTRAST_MEDIUM_LOW: ret += "PAN_CONTRAST_MEDIUM_LOW"; break;
    case PAN_CONTRAST_MEDIUM: ret += "PAN_CONTRAST_MEDIUM"; break;
    case PAN_CONTRAST_MEDIUM_HIGH: ret += "PAN_CONTRAST_MEDIUM_HIGH"; break;
    case PAN_CONTRAST_HIGH: ret += "PAN_CONTRAST_HIGH"; break;
    case PAN_CONTRAST_VERY_HIGH: ret += "PAN_CONTRAST_VERY_HIGH"; break;
    default: ret += "(unknown)";
    }

    ret += ", ";

    switch (panose->bStrokeVariation)
    {
    case PAN_ANY: ret += "PAN_ANY"; break;
    case PAN_NO_FIT: ret += "PAN_NO_FIT"; break;
    case PAN_STROKE_GRADUAL_DIAG: ret += "PAN_STROKE_GRADUAL_DIAG"; break;
    case PAN_STROKE_GRADUAL_TRAN: ret += "PAN_STROKE_GRADUAL_TRAN"; break;
    case PAN_STROKE_GRADUAL_VERT: ret += "PAN_STROKE_GRADUAL_VERT"; break;
    case PAN_STROKE_GRADUAL_HORZ: ret += "PAN_STROKE_GRADUAL_HORZ"; break;
    case PAN_STROKE_RAPID_VERT: ret += "PAN_STROKE_RAPID_VERT"; break;
    case PAN_STROKE_RAPID_HORZ: ret += "PAN_STROKE_RAPID_HORZ"; break;
    case PAN_STROKE_INSTANT_VERT: ret += "PAN_STROKE_INSTANT_VERT"; break;
    default: ret += "(unknown)";
    }

    ret += ", ";

    switch (panose->bArmStyle)
    {
    case PAN_ANY: ret += "PAN_ANY"; break;
    case PAN_NO_FIT: ret += "PAN_NO_FIT"; break;
    case PAN_STRAIGHT_ARMS_HORZ: ret += "PAN_STRAIGHT_ARMS_HORZ"; break;
    case PAN_STRAIGHT_ARMS_WEDGE: ret += "PAN_STRAIGHT_ARMS_WEDGE"; break;
    case PAN_STRAIGHT_ARMS_VERT: ret += "PAN_STRAIGHT_ARMS_VERT"; break;
    case PAN_STRAIGHT_ARMS_SINGLE_SERIF: ret += "PAN_STRAIGHT_ARMS_SINGLE_SERIF"; break;
    case PAN_STRAIGHT_ARMS_DOUBLE_SERIF: ret += "PAN_STRAIGHT_ARMS_DOUBLE_SERIF"; break;
    case PAN_BENT_ARMS_HORZ: ret += "PAN_BENT_ARMS_HORZ"; break;
    case PAN_BENT_ARMS_WEDGE: ret += "PAN_BENT_ARMS_WEDGE"; break;
    case PAN_BENT_ARMS_VERT: ret += "PAN_BENT_ARMS_VERT"; break;
    case PAN_BENT_ARMS_SINGLE_SERIF: ret += "PAN_BENT_ARMS_SINGLE_SERIF"; break;
    case PAN_BENT_ARMS_DOUBLE_SERIF: ret += "PAN_BENT_ARMS_DOUBLE_SERIF"; break;
    default: ret += "(unknown)";
    }

    ret += ", ";

    switch (panose->bLetterform)
    {
    case PAN_ANY: ret += "PAN_ANY"; break;
    case PAN_NO_FIT: ret += "PAN_NO_FIT"; break;
    case PAN_LETT_NORMAL_CONTACT: ret += "PAN_LETT_NORMAL_CONTACT"; break;
    case PAN_LETT_NORMAL_WEIGHTED: ret += "PAN_LETT_NORMAL_WEIGHTED"; break;
    case PAN_LETT_NORMAL_BOXED: ret += "PAN_LETT_NORMAL_BOXED"; break;
    case PAN_LETT_NORMAL_FLATTENED: ret += "PAN_LETT_NORMAL_FLATTENED"; break;
    case PAN_LETT_NORMAL_ROUNDED: ret += "PAN_LETT_NORMAL_ROUNDED"; break;
    case PAN_LETT_NORMAL_OFF_CENTER: ret += "PAN_LETT_NORMAL_OFF_CENTER"; break;
    case PAN_LETT_NORMAL_SQUARE: ret += "PAN_LETT_NORMAL_SQUARE"; break;
    case PAN_LETT_OBLIQUE_CONTACT: ret += "PAN_LETT_OBLIQUE_CONTACT"; break;
    case PAN_LETT_OBLIQUE_WEIGHTED: ret += "PAN_LETT_OBLIQUE_WEIGHTED"; break;
    case PAN_LETT_OBLIQUE_BOXED: ret += "PAN_LETT_OBLIQUE_BOXED"; break;
    case PAN_LETT_OBLIQUE_FLATTENED: ret += "PAN_LETT_OBLIQUE_FLATTENED"; break;
    case PAN_LETT_OBLIQUE_ROUNDED: ret += "PAN_LETT_OBLIQUE_ROUNDED"; break;
    case PAN_LETT_OBLIQUE_OFF_CENTER: ret += "PAN_LETT_OBLIQUE_OFF_CENTER"; break;
    case PAN_LETT_OBLIQUE_SQUARE: ret += "PAN_LETT_OBLIQUE_SQUARE"; break;
    default: ret += "(unknown)";
    }

    ret += ", ";

    switch (panose->bMidline)
    {
    case PAN_ANY: ret += "PAN_ANY"; break;
    case PAN_NO_FIT: ret += "PAN_NO_FIT"; break;
    case PAN_MIDLINE_STANDARD_TRIMMED: ret += "PAN_MIDLINE_STANDARD_TRIMMED"; break;
    case PAN_MIDLINE_STANDARD_POINTED: ret += "PAN_MIDLINE_STANDARD_POINTED"; break;
    case PAN_MIDLINE_STANDARD_SERIFED: ret += "PAN_MIDLINE_STANDARD_SERIFED"; break;
    case PAN_MIDLINE_HIGH_TRIMMED: ret += "PAN_MIDLINE_HIGH_TRIMMED"; break;
    case PAN_MIDLINE_HIGH_POINTED: ret += "PAN_MIDLINE_HIGH_POINTED"; break;
    case PAN_MIDLINE_HIGH_SERIFED: ret += "PAN_MIDLINE_HIGH_SERIFED"; break;
    case PAN_MIDLINE_CONSTANT_TRIMMED: ret += "PAN_MIDLINE_CONSTANT_TRIMMED"; break;
    case PAN_MIDLINE_CONSTANT_POINTED: ret += "PAN_MIDLINE_CONSTANT_POINTED"; break;
    case PAN_MIDLINE_CONSTANT_SERIFED: ret += "PAN_MIDLINE_CONSTANT_SERIFED"; break;
    case PAN_MIDLINE_LOW_TRIMMED: ret += "PAN_MIDLINE_LOW_TRIMMED"; break;
    case PAN_MIDLINE_LOW_POINTED: ret += "PAN_MIDLINE_LOW_POINTED"; break;
    case PAN_MIDLINE_LOW_SERIFED: ret += "PAN_MIDLINE_LOW_SERIFED"; break;
    default: ret += "(unknown)";
    }

    ret += ", ";

    switch (panose->bXHeight)
    {
    case PAN_ANY: ret += "PAN_ANY"; break;
    case PAN_NO_FIT: ret += "PAN_NO_FIT"; break;
    case PAN_XHEIGHT_CONSTANT_SMALL: ret += "PAN_XHEIGHT_CONSTANT_SMALL"; break;
    case PAN_XHEIGHT_CONSTANT_STD: ret += "PAN_XHEIGHT_CONSTANT_STD"; break;
    case PAN_XHEIGHT_CONSTANT_LARGE: ret += "PAN_XHEIGHT_CONSTANT_LARGE"; break;
    case PAN_XHEIGHT_DUCKING_SMALL: ret += "PAN_XHEIGHT_DUCKING_SMALL"; break;
    case PAN_XHEIGHT_DUCKING_STD: ret += "PAN_XHEIGHT_DUCKING_STD"; break;
    case PAN_XHEIGHT_DUCKING_LARGE: ret += "PAN_XHEIGHT_DUCKING_LARGE"; break;
    default: ret += "(unknown)";
    }

    return ret;
}

std::string DoGetEncodingString(FT_Encoding encoding)
{
    switch (encoding)
    {
    case FT_ENCODING_NONE: return "FT_ENCODING_NONE";
    case FT_ENCODING_MS_SYMBOL: return "FT_ENCODING_MS_SYMBOL";
    case FT_ENCODING_UNICODE: return "FT_ENCODING_UNICODE";
    case FT_ENCODING_SJIS: return "FT_ENCODING_SJIS";
    case FT_ENCODING_PRC: return "FT_ENCODING_PRC";
    case FT_ENCODING_BIG5: return "FT_ENCODING_BIG5";
    case FT_ENCODING_WANSUNG: return "FT_ENCODING_WANSUNG";
    case FT_ENCODING_JOHAB: return "FT_ENCODING_JOHAB";
    case FT_ENCODING_ADOBE_STANDARD: return "FT_ENCODING_ADOBE_STANDARD";
    case FT_ENCODING_ADOBE_EXPERT: return "FT_ENCODING_ADOBE_EXPERT";
    case FT_ENCODING_ADOBE_CUSTOM: return "FT_ENCODING_ADOBE_CUSTOM";
    case FT_ENCODING_ADOBE_LATIN_1: return "FT_ENCODING_ADOBE_LATIN_1";
    case FT_ENCODING_OLD_LATIN_2: return "FT_ENCODING_OLD_LATIN_2";
    case FT_ENCODING_APPLE_ROMAN: return "FT_ENCODING_APPLE_ROMAN";
    default: return "(unknown)";
    }
}

std::string DoGetPlatformIDString(FT_UShort platform_id)
{
    switch (platform_id)
    {
    case TT_PLATFORM_APPLE_UNICODE: return "TT_PLATFORM_APPLE_UNICODE";
    case TT_PLATFORM_MACINTOSH: return "TT_PLATFORM_MACINTOSH";
    case TT_PLATFORM_ISO: return "TT_PLATFORM_ISO";
    case TT_PLATFORM_MICROSOFT: return "TT_PLATFORM_MICROSOFT";
    case TT_PLATFORM_CUSTOM: return "TT_PLATFORM_CUSTOM";
    case TT_PLATFORM_ADOBE: return "TT_PLATFORM_ADOBE";
    default: return "(unknown)";
    }
}

std::string DoGetEncodingIDString(FT_UShort platform_id, FT_UShort encoding_id)
{
    switch (platform_id)
    {
    case TT_PLATFORM_APPLE_UNICODE:
        switch (encoding_id)
        {
        case TT_APPLE_ID_DEFAULT: return "TT_APPLE_ID_DEFAULT";
        case TT_APPLE_ID_UNICODE_1_1: return "TT_APPLE_ID_UNICODE_1_1";
        case TT_APPLE_ID_ISO_10646: return "TT_APPLE_ID_ISO_10646";
        case TT_APPLE_ID_UNICODE_2_0: return "TT_APPLE_ID_UNICODE_2_0";
        case TT_APPLE_ID_UNICODE_32: return "TT_APPLE_ID_UNICODE_32";
        case TT_APPLE_ID_VARIANT_SELECTOR: return "TT_APPLE_ID_VARIANT_SELECTOR";
        case TT_APPLE_ID_FULL_UNICODE: return "TT_APPLE_ID_FULL_UNICODE";
        default: return "(unknown)";
        }
    case TT_PLATFORM_MACINTOSH:
        switch (encoding_id)
        {
        case TT_MAC_ID_ROMAN: return "TT_MAC_ID_ROMAN";
        case TT_MAC_ID_JAPANESE: return "TT_MAC_ID_JAPANESE";
        case TT_MAC_ID_TRADITIONAL_CHINESE: return "TT_MAC_ID_TRADITIONAL_CHINESE";
        case TT_MAC_ID_KOREAN: return "TT_MAC_ID_KOREAN";
        case TT_MAC_ID_ARABIC: return "TT_MAC_ID_ARABIC";
        case TT_MAC_ID_HEBREW: return "TT_MAC_ID_HEBREW";
        case TT_MAC_ID_GREEK: return "TT_MAC_ID_GREEK";
        case TT_MAC_ID_RUSSIAN: return "TT_MAC_ID_RUSSIAN";
        case TT_MAC_ID_RSYMBOL: return "TT_MAC_ID_RSYMBOL";
        case TT_MAC_ID_DEVANAGARI: return "TT_MAC_ID_DEVANAGARI";
        case TT_MAC_ID_GURMUKHI: return "TT_MAC_ID_GURMUKHI";
        case TT_MAC_ID_GUJARATI: return "TT_MAC_ID_GUJARATI";
        case TT_MAC_ID_ORIYA: return "TT_MAC_ID_ORIYA";
        case TT_MAC_ID_BENGALI: return "TT_MAC_ID_BENGALI";
        case TT_MAC_ID_TAMIL: return "TT_MAC_ID_TAMIL";
        case TT_MAC_ID_TELUGU: return "TT_MAC_ID_TELUGU";
        case TT_MAC_ID_KANNADA: return "TT_MAC_ID_KANNADA";
        case TT_MAC_ID_MALAYALAM: return "TT_MAC_ID_MALAYALAM";
        case TT_MAC_ID_SINHALESE: return "TT_MAC_ID_SINHALESE";
        case TT_MAC_ID_BURMESE: return "TT_MAC_ID_BURMESE";
        case TT_MAC_ID_KHMER: return "TT_MAC_ID_KHMER";
        case TT_MAC_ID_THAI: return "TT_MAC_ID_THAI";
        case TT_MAC_ID_LAOTIAN: return "TT_MAC_ID_LAOTIAN";
        case TT_MAC_ID_GEORGIAN: return "TT_MAC_ID_GEORGIAN";
        case TT_MAC_ID_ARMENIAN: return "TT_MAC_ID_ARMENIAN";
        case TT_MAC_ID_SIMPLIFIED_CHINESE: return "TT_MAC_ID_SIMPLIFIED_CHINESE";
        case TT_MAC_ID_TIBETAN: return "TT_MAC_ID_TIBETAN";
        case TT_MAC_ID_MONGOLIAN: return "TT_MAC_ID_MONGOLIAN";
        case TT_MAC_ID_GEEZ: return "TT_MAC_ID_GEEZ";
        case TT_MAC_ID_SLAVIC: return "TT_MAC_ID_SLAVIC";
        case TT_MAC_ID_VIETNAMESE: return "TT_MAC_ID_VIETNAMESE";
        case TT_MAC_ID_SINDHI: return "TT_MAC_ID_SINDHI";
        case TT_MAC_ID_UNINTERP: return "TT_MAC_ID_UNINTERP";
        default: return "(unknown)";
        }
    case TT_PLATFORM_ISO:
        switch (encoding_id)
        {
        case TT_ISO_ID_7BIT_ASCII: return "TT_ISO_ID_7BIT_ASCII";
        case TT_ISO_ID_10646: return "TT_ISO_ID_10646";
        case TT_ISO_ID_8859_1: return "TT_ISO_ID_8859_1";
        default: return "(unknown)";
        }
    case TT_PLATFORM_MICROSOFT:
        switch (encoding_id)
        {
        case TT_MS_ID_SYMBOL_CS: return "TT_MS_ID_SYMBOL_CS";
        case TT_MS_ID_UNICODE_CS: return "TT_MS_ID_UNICODE_CS";
        case TT_MS_ID_SJIS: return "TT_MS_ID_SJIS";
        case TT_MS_ID_PRC: return "TT_MS_ID_PRC";
        case TT_MS_ID_BIG_5: return "TT_MS_ID_BIG_5";
        case TT_MS_ID_WANSUNG: return "TT_MS_ID_WANSUNG";
        case TT_MS_ID_JOHAB: return "TT_MS_ID_JOHAB";
        case TT_MS_ID_UCS_4: return "TT_MS_ID_UCS_4";
        default: return "(unknown)";
        }
    case TT_PLATFORM_CUSTOM:
        return "TT_PLATFORM_CUSTOM";
    case TT_PLATFORM_ADOBE:
        switch (encoding_id)
        {
        case TT_ADOBE_ID_STANDARD: return "TT_ADOBE_ID_STANDARD";
        case TT_ADOBE_ID_EXPERT: return "TT_ADOBE_ID_EXPERT";
        case TT_ADOBE_ID_CUSTOM: return "TT_ADOBE_ID_CUSTOM";
        case TT_ADOBE_ID_LATIN_1: return "TT_ADOBE_ID_LATIN_1";
        default: return "(unknown)";
        }
    default: return "(unknown)";
    }
}

void show_help(void)
{
    cout << "Usage: DumpFontInfo \"font-file.ttf\"\n";
}

int main(int argc, char **argv)
{
    FT_Library library;
    FT_Face face;
    FT_Long iFace, num_faces;
    FT_Error error;
    const char *filename;

    if (argc <= 1)
    {
        show_help();
        return 0;
    }

    std::string arg = argv[1];
    if (arg == "--help")
    {
        show_help();
        return 0;
    }

    if (arg == "--version")
    {
        cout << "DumpFontInfo ver.0.5 by katahiromz\n";
        return 0;
    }

    filename = arg.c_str();

    FT_Init_FreeType(&library);

    FT_New_Face(library, filename, -1, &face);
    if (face)
    {
        num_faces = face->num_faces;
        FT_Done_Face(face);
    }

    cout << "Font file '" << filename << "' has " << num_faces << " faces.\n";

    for (iFace = 0; iFace < num_faces; ++iFace)
    {
        FT_New_Face(library, filename, iFace, &face);
        if (!face)
        {
            cout << "Unable to load face #" << iFace << "." << endl;
            continue;
        }

        cout << "-----------------------------------\n";
        cout << "File '" << filename << "', face #" << iFace << ": '" << face->family_name << "'\n";
        cout << "-----------------------------------\n";

#define POUT(x) cout << ("  " #x) << ": " << (x) << endl

        cout << "Flags:\n";
        POUT(FT_HAS_HORIZONTAL(face));
        POUT(FT_HAS_VERTICAL(face));
        POUT(FT_HAS_KERNING(face));
        POUT(FT_IS_SCALABLE(face));
        POUT(FT_IS_SFNT(face));
        POUT(FT_IS_FIXED_WIDTH(face));
        POUT(FT_HAS_FIXED_SIZES(face));
        POUT(FT_HAS_GLYPH_NAMES(face));
        POUT(FT_HAS_MULTIPLE_MASTERS(face));
        POUT(FT_IS_NAMED_INSTANCE(face));
        POUT(FT_IS_VARIATION(face));
        POUT(FT_IS_CID_KEYED(face));
        POUT(FT_IS_TRICKY(face));
        POUT(FT_HAS_COLOR(face));

        cout << "\nFT_Face members:\n";
        POUT(face->num_faces);
        POUT(face->face_index);
        POUT(face->face_flags);
        POUT(face->style_flags);
        POUT(face->num_glyphs);
        POUT(face->family_name);
        POUT(face->style_name);
        POUT(face->num_fixed_sizes);
        POUT(face->available_sizes);
        POUT(face->num_charmaps);
        POUT(face->charmaps);
        //POUT(face->generic);
        //POUT(face->bbox);
        POUT(face->units_per_EM);
        POUT(face->ascender);
        POUT(face->descender);
        POUT(face->height);
        POUT(face->max_advance_width);
        POUT(face->max_advance_height);
        POUT(face->underline_position);
        POUT(face->underline_thickness);
        POUT(face->glyph);
        POUT(face->size);
        POUT(face->charmap);

        if (face->num_charmaps && face->charmaps)
        {
            for (FT_Int i = 0; i < face->num_charmaps; ++i)
            {
                cout << "CharMap #" << i << ": ";
                FT_CharMap charmap = face->charmaps[i];
                cout << DoGetEncodingString(charmap->encoding) << ", ";
                cout << DoGetPlatformIDString(charmap->platform_id) << ", ";
                cout << DoGetEncodingIDString(charmap->platform_id, charmap->encoding_id) << "\n";
            }
        }

        if (face->num_fixed_sizes && face->available_sizes)
        {
            for (FT_Int i = 0; i < face->num_fixed_sizes; ++i)
            {
                FT_Bitmap_Size* size = &face->available_sizes[i];
                cout << "Size #" << i << ": (";
                cout << size->height << ", " << size->width << "), " << size->size << ", (";
                cout << size->x_ppem << ", " << size->y_ppem << ")\n";
            }
        }

        FT_WinFNT_HeaderRec fnt;
        error = FT_Get_WinFNT_Header(face, &fnt);
        if (!error)
        {
            cout << "WinFNT header:\n";
            POUT(fnt.version);
            POUT(fnt.file_size);
            POUT(fnt.copyright);
            POUT(fnt.file_type);
            POUT(fnt.nominal_point_size);
            POUT(fnt.vertical_resolution);
            POUT(fnt.horizontal_resolution);
            POUT(fnt.ascent);
            POUT(fnt.internal_leading);
            POUT(fnt.external_leading);
            POUT((int)fnt.italic);
            POUT((int)fnt.underline);
            POUT((int)fnt.strike_out);
            POUT(fnt.weight);
            POUT((int)fnt.charset);
            POUT(fnt.pixel_width);
            POUT(fnt.pixel_height);
            POUT((int)fnt.pitch_and_family);
            POUT(fnt.avg_width);
            POUT(fnt.max_width);
            POUT((int)fnt.first_char);
            POUT((int)fnt.last_char);
            POUT((int)fnt.default_char);
            POUT((int)fnt.break_char);
            POUT(fnt.bytes_per_row);
            POUT(fnt.device_offset);
            POUT(fnt.face_name_offset);
            POUT(fnt.bits_pointer);
            POUT(fnt.bits_offset);
            POUT((int)fnt.reserved);
            POUT(fnt.flags);
            POUT(fnt.A_space);
            POUT(fnt.B_space);
            POUT(fnt.C_space);
            POUT(fnt.color_table_offset);
        }

        if (TT_OS2 *pOS2 = (TT_OS2 *)FT_Get_Sfnt_Table(face, FT_SFNT_OS2))
        {
            cout << "OS/2 header:\n";
            POUT(pOS2->version);
            POUT(pOS2->xAvgCharWidth);
            POUT(pOS2->usWeightClass);
            POUT(pOS2->usWidthClass);
            POUT(pOS2->fsType);
            POUT(pOS2->ySubscriptXSize);
            POUT(pOS2->ySubscriptYSize);
            POUT(pOS2->ySubscriptXOffset);
            POUT(pOS2->ySubscriptYOffset);
            POUT(pOS2->ySuperscriptXSize);
            POUT(pOS2->ySuperscriptYSize);
            POUT(pOS2->ySuperscriptXOffset);
            POUT(pOS2->ySuperscriptYOffset);
            POUT(pOS2->yStrikeoutSize);
            POUT(pOS2->yStrikeoutPosition);
            POUT(pOS2->sFamilyClass);
            cout << "  pOS2->panose: " << DoGetPanoseString((PANOSE *)pOS2->panose) << std::endl;
            POUT(pOS2->ulUnicodeRange1);
            POUT(pOS2->ulUnicodeRange2);
            POUT(pOS2->ulUnicodeRange3);
            POUT(pOS2->ulUnicodeRange4);
            POUT((unsigned int&)pOS2->achVendID);
            POUT(pOS2->fsSelection);
            POUT(pOS2->usFirstCharIndex);
            POUT(pOS2->usLastCharIndex);
            POUT(pOS2->sTypoAscender);
            POUT(pOS2->sTypoDescender);
            POUT(pOS2->sTypoLineGap);
            POUT(pOS2->usWinAscent);
            POUT(pOS2->usWinDescent);
            POUT(pOS2->ulCodePageRange1);
            POUT(pOS2->ulCodePageRange2);
            POUT(pOS2->sxHeight);
            POUT(pOS2->sCapHeight);
            POUT(pOS2->usDefaultChar);
            POUT(pOS2->usBreakChar);
            POUT(pOS2->usMaxContext);
            POUT(pOS2->usLowerOpticalPointSize);
            POUT(pOS2->usUpperOpticalPointSize);
        }

        if (TT_HoriHeader *pHori = (TT_HoriHeader *)FT_Get_Sfnt_Table(face, FT_SFNT_HHEA))
        {
            cout << "Hori header:\n";
            POUT(pHori->Version);
            POUT(pHori->Ascender);
            POUT(pHori->Descender);
            POUT(pHori->Line_Gap);
            POUT(pHori->advance_Width_Max);
            POUT(pHori->min_Left_Side_Bearing);
            POUT(pHori->min_Right_Side_Bearing);
            POUT(pHori->xMax_Extent);
            POUT(pHori->caret_Slope_Rise);
            POUT(pHori->caret_Slope_Run);
            POUT(pHori->caret_Offset);
            //POUT(pHori->Reserved);
            POUT(pHori->metric_Data_Format);
            POUT(pHori->number_Of_HMetrics);
            POUT(pHori->long_metrics);
            POUT(pHori->short_metrics);
        }

        FT_Done_Face(face);
    }

    FT_Done_FreeType(library);
    return 0;
}
