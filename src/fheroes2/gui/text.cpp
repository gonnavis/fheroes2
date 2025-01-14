/***************************************************************************
 *   Copyright (C) 2009 by Andrey Afletdinov <fheroes2@gmail.com>          *
 *                                                                         *
 *   Part of the Free Heroes2 Engine:                                      *
 *   http://sourceforge.net/projects/fheroes2                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <algorithm>
#include <cassert>
#include <cctype>

#include "agg.h"
#include "agg_image.h"
#include "settings.h"
#include "text.h"
#include "tools.h"

namespace
{
    bool isSmallFont( int font )
    {
        return font == Font::SMALL || font == Font::YELLOW_SMALL || font == Font::GRAY_SMALL;
    }

    bool isLargeFont( int font )
    {
        return font == Font::WHITE_LARGE;
    }
}

TextInterface::TextInterface( int ft )
    : font( ft )
{}

TextAscii::TextAscii( const std::string & msg, int ft )
    : TextInterface( ft )
    , message( msg )
{}

void TextAscii::SetText( const std::string & msg )
{
    message = msg;
}

void TextAscii::SetFont( int ft )
{
    font = ft;
}

void TextAscii::Clear( void )
{
    message.clear();
}

size_t TextAscii::Size( void ) const
{
    return message.size();
}

int TextAscii::CharWidth( const uint8_t character, const int ft )
{
    if ( character < 0x21 || character > fheroes2::AGG::ASCIILastSupportedCharacter( ft ) ) {
        if ( isSmallFont( ft ) )
            return 4;
        else if ( isLargeFont( ft ) )
            return 12;
        else
            return 6;
    }
    else {
        return fheroes2::AGG::GetLetter( character, ft ).width();
    }
}

int TextAscii::FontHeight( const int f )
{
    if ( isSmallFont( f ) )
        return 8 + 2 + 1;
    else if ( isLargeFont( f ) )
        return 26 + 6 + 1;
    else
        return 13 + 3 + 1;
}

int TextAscii::w( size_t s, size_t c ) const
{
    const size_t size = message.size();
    if ( size == 0 )
        return 0;

    int res = 0;

    if ( s > size - 1 )
        s = size - 1;
    if ( !c || c > size )
        c = size - s;

    for ( size_t i = s; i < s + c; ++i )
        res += CharWidth( static_cast<uint8_t>( message[i] ), font );

    return res;
}

int TextAscii::w( void ) const
{
    return w( 0, message.size() );
}

int TextAscii::h( void ) const
{
    return h( 0 );
}

int TextAscii::h( int width ) const
{
    if ( message.empty() )
        return 0;

    if ( 0 == width || w() <= width )
        return FontHeight( font );

    int res = 0;
    int www = 0;

    std::string::const_iterator pos1 = message.begin();
    std::string::const_iterator pos2 = message.end();
    std::string::const_iterator space = pos2;

    const uint32_t maxSupportedCharacter = fheroes2::AGG::ASCIILastSupportedCharacter( font );

    const int fontHeight = FontHeight( font );

    while ( pos1 < pos2 ) {
        // To use std::isspace safely with plain chars (or signed chars), the argument should first be converted to unsigned char:
        // https://en.cppreference.com/w/cpp/string/byte/isspace
        const uint8_t character = static_cast<uint8_t>( *pos1 );

        if ( std::isspace( character ) || character > maxSupportedCharacter ) {
            space = pos1;
        }

        if ( www + CharWidth( character, font ) >= width ) {
            www = 0;
            res += fontHeight;
            if ( pos2 != space )
                pos1 = space + 1;
            space = pos2;
            continue;
        }

        www += CharWidth( character, font );
        ++pos1;
    }

    return res;
}

void TextAscii::Blit( s32 ax, s32 ay, int maxw, fheroes2::Image & dst )
{
    if ( message.empty() )
        return;

    int sx = ax;

    const uint32_t maxSupportedCharacter = fheroes2::AGG::ASCIILastSupportedCharacter( font );

    for ( std::string::const_iterator it = message.begin(); it != message.end(); ++it ) {
        if ( maxw && ( ax - sx ) >= maxw )
            break;

        const uint8_t character = static_cast<uint8_t>( *it );

        // space or unknown letter
        if ( character < 0x21 || character > maxSupportedCharacter ) {
            ax += CharWidth( character, font );
            continue;
        }

        const fheroes2::Sprite & sprite = fheroes2::AGG::GetLetter( character, font );
        if ( sprite.empty() )
            continue;

        const int updatedWidth = ax + sprite.width();
        if ( maxw && ( updatedWidth - sx ) >= maxw )
            break;

        fheroes2::Blit( sprite, dst, ax + sprite.x(), ay + sprite.y() + 2 );
        ax = updatedWidth;
    }
}

Text::Text()
    : message( nullptr )
    , gw( 0 )
    , gh( 0 )
{
    message = new TextAscii();
}

Text::Text( const std::string & msg, int ft )
    : message( nullptr )
    , gw( 0 )
    , gh( 0 )
{
    message = new TextAscii( msg, ft );

    gw = message->w();
    gh = message->h();
}

Text::~Text()
{
    delete message;
}

Text::Text( const Text & t )
{
    assert( t.message != nullptr );
    message = new TextAscii( dynamic_cast<TextAscii &>( *t.message ) );

    gw = t.gw;
    gh = t.gh;
}

void Text::Set( const std::string & msg, int ft )
{
    message->SetText( msg );
    message->SetFont( ft );
    gw = message->w();
    gh = message->h();
}

void Text::Set( const std::string & msg )
{
    message->SetText( msg );
    gw = message->w();
    gh = message->h();
}

void Text::Set( int ft )
{
    message->SetFont( ft );
    gw = message->w();
    gh = message->h();
}

void Text::Clear( void )
{
    message->Clear();
    gw = 0;
    gh = 0;
}

size_t Text::Size( void ) const
{
    return message->Size();
}

void Text::Blit( const fheroes2::Point & dst_pt, fheroes2::Image & dst ) const
{
    return message->Blit( dst_pt.x, dst_pt.y, 0, dst );
}

void Text::Blit( s32 ax, s32 ay, fheroes2::Image & dst ) const
{
    return message->Blit( ax, ay, 0, dst );
}

void Text::Blit( s32 ax, s32 ay, int maxw, fheroes2::Image & dst ) const
{
    return message->Blit( ax, ay, maxw, dst );
}

u32 Text::width( const std::string & str, int ft, u32 start, u32 count )
{
    if ( !str.empty() ) {
        TextAscii text( str, ft );
        return text.w( start, count );
    }
    return 0;
}

u32 Text::height( const std::string & str, int ft, u32 width )
{
    if ( !str.empty() ) {
        TextAscii text( str, ft );
        return text.h( width );
    }

    return 0;
}

int32_t Text::getCharacterWidth( const uint8_t character, const int fontType )
{
    return TextAscii::CharWidth( character, fontType );
}

int32_t Text::getFitWidth( const std::string & text, const int fontId, const int32_t width_ )
{
    if ( text.empty() || width_ < 1 )
        return 0;

    int32_t fitWidth = 0;
    uint32_t characterCount = 0;

    TextAscii textWrapper( text, fontId );

    while ( fitWidth < width_ && characterCount < text.size() ) {
        ++characterCount;
        const int32_t foundWidth = textWrapper.w( 0, characterCount );
        if ( foundWidth > width_ )
            break;

        fitWidth = foundWidth;
    }

    return fitWidth;
}

TextBox::TextBox()
    : align( ALIGN_CENTER )
{}

TextBox::TextBox( const std::string & msg, int ft, uint32_t width_ )
    : align( ALIGN_CENTER )
{
    Set( msg, ft, width_ );
}

TextBox::TextBox( const std::string & msg, int ft, const fheroes2::Rect & rt )
    : align( ALIGN_CENTER )
{
    Set( msg, ft, rt.width );
    Blit( rt.x, rt.y );
}

void TextBox::Set( const std::string & msg, int ft, uint32_t width_ )
{
    messages.clear();
    fheroes2::Rect::height = 0;
    if ( msg.empty() )
        return;

    const char sep = '\n';
    std::string substr;
    substr.reserve( msg.size() );
    std::string::const_iterator pos1 = msg.begin();
    std::string::const_iterator pos2;
    while ( msg.end() != ( pos2 = std::find( pos1, msg.end(), sep ) ) ) {
        substr.assign( pos1, pos2 );
        Append( substr, ft, width_ );
        pos1 = pos2 + 1;
    }
    if ( pos1 < msg.end() ) {
        substr.assign( pos1, msg.end() );
        Append( substr, ft, width_ );
    }
}

void TextBox::SetAlign( int f )
{
    align = f;
}

void TextBox::Append( const std::string & msg, int ft, u32 width_ )
{
    uint32_t www = 0;
    fheroes2::Rect::width = width_;

    std::string::const_iterator pos1 = msg.begin();
    std::string::const_iterator pos2 = pos1;
    std::string::const_iterator pos3 = msg.end();
    std::string::const_iterator space = pos2;

    const uint32_t maxSupportedCharacter = fheroes2::AGG::ASCIILastSupportedCharacter( ft );

    const int fontHeight = TextAscii::FontHeight( ft );

    while ( pos2 < pos3 ) {
        // To use std::isspace safely with plain chars (or signed chars), the argument should first be converted to unsigned char:
        // https://en.cppreference.com/w/cpp/string/byte/isspace
        const uint8_t character = static_cast<uint8_t>( *pos2 );

        if ( std::isspace( character ) || character > maxSupportedCharacter ) {
            space = pos2;
        }
        const int charWidth = TextAscii::CharWidth( character, ft );

        if ( www + charWidth >= width_ ) {
            www = 0;
            fheroes2::Rect::height += fontHeight;
            if ( pos3 != space ) {
                if ( space == msg.begin() ) {
                    if ( pos2 - pos1 < 1 ) // this should never happen!
                        return;
                    messages.emplace_back( msg.substr( pos1 - msg.begin(), pos2 - pos1 ), ft );
                }
                else {
                    pos2 = space + 1;
                    messages.emplace_back( msg.substr( pos1 - msg.begin(), pos2 - pos1 - 1 ), ft );
                }
            }
            else {
                messages.emplace_back( msg.substr( pos1 - msg.begin(), pos2 - pos1 ), ft );
            }

            pos1 = pos2;
            space = pos3;
            continue;
        }

        www += charWidth;
        ++pos2;
    }

    if ( pos1 != pos2 ) {
        fheroes2::Rect::height += fontHeight;
        messages.emplace_back( msg.substr( pos1 - msg.begin(), pos2 - pos1 ), ft );
    }
}

void TextBox::Blit( s32 ax, s32 ay, fheroes2::Image & sf )
{
    fheroes2::Rect::x = ax;
    fheroes2::Rect::y = ay;

    for ( std::list<Text>::const_iterator it = messages.begin(); it != messages.end(); ++it ) {
        switch ( align ) {
        case ALIGN_LEFT:
            ( *it ).Blit( ax, ay, sf );
            break;

        case ALIGN_RIGHT:
            ( *it ).Blit( ax + fheroes2::Rect::width - ( *it ).w(), ay, sf );
            break;

        // center
        default:
            ( *it ).Blit( ax + ( fheroes2::Rect::width - ( *it ).w() ) / 2, ay, sf );
            break;
        }

        ay += ( *it ).h();
    }
}

TextSprite::TextSprite()
    : _restorer( fheroes2::Display::instance(), 0, 0, 0, 0 )
    , hide( true )
{}

TextSprite::TextSprite( const std::string & msg, int ft, s32 ax, s32 ay )
    : Text( msg, ft )
    , _restorer( fheroes2::Display::instance(), ax, ay, gw, gh + 5 )
    , hide( true )
{}

void TextSprite::Show( void )
{
    Blit( _restorer.x(), _restorer.y() );
    hide = false;
}

void TextSprite::Hide( void )
{
    if ( !hide )
        _restorer.restore();
    hide = true;
}

void TextSprite::SetText( const std::string & msg )
{
    Hide();
    Set( msg );
    _restorer.update( _restorer.x(), _restorer.y(), gw, gh + 5 );
}

void TextSprite::SetText( const std::string & msg, int ft )
{
    Hide();
    Set( msg, ft );
    _restorer.update( _restorer.x(), _restorer.y(), gw, gh + 5 );
}

void TextSprite::SetFont( int ft )
{
    Hide();
    Set( ft );
    _restorer.update( _restorer.x(), _restorer.y(), gw, gh + 5 );
}

void TextSprite::SetPos( s32 ax, s32 ay )
{
    _restorer.update( ax, ay, gw, gh + 5 );
}

int TextSprite::w( void ) const
{
    return gw;
}

int TextSprite::h( void ) const
{
    return gh + 5;
}

bool TextSprite::isHide( void ) const
{
    return hide;
}

bool TextSprite::isShow( void ) const
{
    return !hide;
}

fheroes2::Rect TextSprite::GetRect( void ) const
{
    return fheroes2::Rect( _restorer.x(), _restorer.y(), _restorer.width(), _restorer.height() );
}
