/*
 * Copyright 2007-2010 (C) - Frictional Games
 *
 * This file is part of OALWrapper
 *
 * For conditions of distribution and use, see copyright notice in LICENSE
 */
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

int	_fseek64_wrap(FILE *f,ogg_int64_t off,int whence);