/*
 * Copyright 2007-2010 (C) - Frictional Games
 *
 * This file is part of OALWrapper
 *
 * For conditions of distribution and use, see copyright notice in LICENSE
 */
#include "OALWrapper/OAL_OggHelper.h"
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

///////////////////////////////////////////////////////////
//	Workaround for linking dynamically in win32
///////////////////////////////////////////////////////////
int _fseek64_wrap(FILE *f,ogg_int64_t off,int whence)
{
    if(f==NULL)return(-1);
    return fseek(f, (long) off,whence);
}


ov_callbacks gCallbacks =
{
    (size_t (*)(void *, size_t, size_t, void *))  fread,
    (int (*)(void *, ogg_int64_t, int))           _fseek64_wrap,
    (int (*)(void *))                             fclose,
    (long (*)(void *))                            ftell
};
